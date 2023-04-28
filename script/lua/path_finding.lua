-- 常量
local posRate = 100       -- 坐标放大倍数
local posHalfRate = 50        -- 坐标放大倍数一半
local flagOpen = 1         -- 待处理的节点
local flagClose = 2         -- 已处理的节点
-- 方向
local dirL = 1          -- 左
local dirT = 2          -- 上
local dirR = 3          -- 右
local dirB = 4          -- 下
local dirLT = 5          -- 左上
local dirRT = 6          -- 右上
local dirRB = 7          -- 右下
local dirLB = 8          -- 左下
local dirMin = 1         -- 范围：最小
local dirMax = 8         -- 范围：最大
local dirInvalid = -1        -- 无效方向

-- 逻辑
local logic = {}
local aid = {}

-- 地图节点数据结构
--local node = {
--	x = 1,
--	y = 1,
--	h = 0,
--	g = 0,
--  flag = 0,
--	parent = {},
--}

-- A星寻路算法
-- 返回值：path, path_num (path 为 node 数组，包含终点不含起点), key_step, key_step_num; 失败返回 nil
function logic.findPath(block, srcX, srcY, dstX, dstY)
    if phyblock.isBlock(block, srcX, srcY) or phyblock.isBlock(block, dstX, dstY) then
        return nil
    end
    -- 先将首节点加入待处理点
    local width = phyblock.width(block)
    local dst = { minX = dstX - posHalfRate, maxX = dstX + posHalfRate, minY = dstY - posHalfRate, maxY = dstY + posHalfRate }
    local srcNode = { x = srcX, y = srcY, h = 0, g = 0, flag = flagOpen }
    local openlist, opennum, allNode = { srcNode }, 1, { [width * srcY + srcX] = srcNode }
    -- 一步一步查找路径
    repeat
        -- 找出消耗最小的待处理点
        local node = aid.findMinErase(openlist)
        node.flag = flagClose
        opennum = opennum - 1
        -- 达到终点
        if aid.sameGrid(node, dst) then
            local path = { { x = dstX, y = dstY } }
            node = node.parent
            while node.parent do
                table.insert(path, node)
                node = node.parent
            end
            -- 整理顺序
            local num = #path
            local loop = num // 2
            for i = 1, loop do
                local temp = path[i]
                path[i] = path[num - i + 1]
                path[num - i + 1] = temp
            end
            local keyStep, keyStepNum = logic.getKeyStep(path, num)
            return path, num, keyStep, keyStepNum
        end
        -- 添加附近的点
        local pos = aid.neighbors(block, node)
        for _, v in pairs(pos) do
            local _node = allNode[width * v[2] + v[1]]
            if not _node then
                -- 新节点
                _node = { x = v[1], y = v[2],
                          g = node.g + aid.computeG(v[1], v[2], node.x, node.y),
                          h = aid.computeH(v[1], v[2], dstX, dstY),
                          parent = node,
                          flag = flagOpen,
                }
                table.insert(openlist, _node)
                allNode[width * v[2] + v[1]] = _node
                opennum = opennum + 1
            elseif _node.flag == flagOpen then
                local g = node.g + aid.computeG(node.x, node.y, v[1], v[2])
                if g < _node.g then
                    _node.g = g
                    _node.h = aid.computeH(v[1], v[2], dstX, dstY)
                    _node.parent = node
                end
            end
        end
    until (opennum < 1)
    return nil
end

-- 根据路径提取关键点（转折点） (path 下标数组 )
-- 返回：path 中的关键index, 数量
function logic.getKeyStep(path, num)
    local keyStep = {}
    for i = 2, num - 1 do
        if aid.isNotLine(path[i - 1], path[i], path[i + 1]) then
            table.insert(keyStep, i)
        end
    end
    -- 目的地是关键点
    table.insert(keyStep, num)
    return keyStep, #keyStep
end

-- 在 start 点随机向一个方向移动 step 步，并且只能在 center 点方圆 radius 距离内
-- 返回值：path, path_num (path 为 node 数组，包含终点不含起点), key_step, key_step_num; 失败返回 nil
function logic.randomPath(block, startX, startY, step, centerX, centerY, radius)
    local node = { x = startX, y = startY }
    radius = radius * radius -- 两点之间的距离(不开平方，直接用平方和，提高效率)
    -- 随机确定方向，走一步
    local dir = aid.randomForward(block, node, centerX, centerY, radius)
    if dir == dirInvalid then
        return nil
    end
    local path, keyStep = { { x = node.x, y = node.y } }, {}
    -- 继续走下一步
    for i = 2, step do
        local x, y = aid.convertPos(dir, node)
        if phyblock.walkable(block, x, y) and aid.distance(centerX, centerY, x, y) <= radius then
            node.x = x
            node.y = y
            table.insert(path, { x = x, y = y })
        else
            -- 从新找方向
            dir = aid.randomForward(block, node, centerX, centerY, radius)
            if dir == dirInvalid then
                return nil
            end
            table.insert(path, { x = node.x, y = node.y })
            -- 记录转折点
            table.insert(keyStep, #path)
        end
    end
    -- 目的地是关键点
    table.insert(keyStep, #path)
    return path, #path, keyStep, #keyStep
end

-- 从 src 点走到 dst 点附近 distance 距离的地方，但是不能走出以 center 点为圆心，radius为半径的范围
-- 返回值：path, path_num (path 为 node 数组，包含终点不含起点), key_step, key_step_num; 失败返回 nil
function logic.rangePath(block, srcX, srcY, dstX, dstY, distance, centerX, centerY, radius)
    if phyblock.isBlock(block, srcX, srcY) or phyblock.isBlock(block, dstX, dstY) then
        return nil
    end
    -- 先将首节点加入待处理点
    local width = phyblock.width(block)
    local dst = { x_min = dstX - posHalfRate, x_max = dstX + posHalfRate, y_min = dstY - posHalfRate, y_max = dstY + posHalfRate }
    local srcNode = { x = srcX, y = srcY, h = 0, g = 0, flag = flagOpen }
    local openlist, opennum, allnode = { srcNode }, 1, { [width * srcY + srcX] = srcNode }
    radius = radius * radius
    distance = distance * distance
    -- 一步一步查找路径
    repeat
        -- 找出消耗最小的待处理点
        local node = aid.findMinErase(openlist)
        node.flag = flagClose
        opennum = opennum - 1
        -- 达到终点或到范围边上dst最近的点
        local centerDis = aid.distance(centerX, centerY, node.x, node.y)
        local dstDis = aid.distance(dstX, dstY, node.x, node.y)
        if centerDis > radius or dstDis <= distance or aid.sameGrid(node, dst) then
            -- 出范围了则退一步
            if centerDis > radius then
                node = node.parent
            end
            -- 起始点就超过了范围
            if not node then
                return nil
            end
            local path = {}
            repeat
                table.insert(path, node)
                node = node.parent
            until node == nil
            -- 整理顺序
            local num = #path
            local loop = num // 2
            for i = 1, loop do
                local temp = path[i]
                path[i] = path[num - i + 1]
                path[num - i + 1] = temp
            end
            local keyStep, keyStepNum = logic.getKeyStep(path, num)
            return path, num, keyStep, keyStepNum
        end
        -- 添加附近的点
        local pos = aid.neighbors(block, node)
        for _, v in pairs(pos) do
            local _node = allnode[width * v[2] + v[1]]
            if not _node then
                -- 新节点
                _node = { x = v[1], y = v[2],
                          g = node.g + aid.computeG(v[1], v[2], node.x, node.y),
                          h = aid.computeH(v[1], v[2], dstX, dstY),
                          parent = node,
                          flag = flagOpen,
                }
                table.insert(openlist, _node)
                allnode[width * v[2] + v[1]] = _node
                opennum = opennum + 1
            elseif _node.flag == flagOpen then
                local g = node.g + aid.computeG(node.x, node.y, v[1], v[2])
                if g < _node.g then
                    _node.g = g
                    _node.h = aid.computeH(v[1], v[2], dstX, dstY)
                    _node.parent = node
                end
            end
        end
    until (opennum < 1)
    return nil
end

-- 打印路径
function logic.printPath(path, key_step)
    local strPath = "path:"
    for i = 1, #path do
        local key = false
        for _, ks in pairs(key_step) do
            if ks == i then
                key = true
                break
            end
        end
        if key then
            strPath = strPath .. "{key>>x:" .. path[i].x .. ",y:" .. path[i].y .. "}"
        else
            strPath = strPath .. "{x:" .. path[i].x .. ",y:" .. path[i].y .. "}"
        end
    end
    print(strPath)
end

----------------------------------------------------------------
-- 内部助手

-- 走路消耗
function aid.nodeF(node)
    return node.g + node.h
end

-- 找出消耗最小的待处理点
function aid.findMinErase(open_list)
    local node, min
    for k, temp in pairs(open_list) do
        if node then
            if aid.nodeF(temp) <= aid.nodeF(node) and temp.h < node.h then
                node = temp
                min = k
            end
        else
            node = temp
            min = k
        end
    end
    open_list[min] = nil
    return node
end

-- 计算 g(n) 距离
function aid.computeG(a_x, a_y, b_x, b_y)
    local dX = math.abs(a_x - b_x)
    local dY = math.abs(a_y - b_y)
    if dX > dY then
        return 14 * dY + 10 * (dX - dY)
    else
        return 14 * dX + 10 * (dY - dX)
    end
end

-- 计算 h(n) 距离
function aid.computeH(a_x, a_y, b_x, b_y)
    local dX = math.abs(a_x - b_x)
    local dY = math.abs(a_y - b_y)
    if dX > dY then
        return dX * 14
    else
        return dY * 14
    end
end

-- 两点是否在同一个格子中
function aid.sameGrid(node, target)
    -- 大概范围就行，不用太精确
    if node.x < target.minX or node.x > target.maxX then
        return false
    end
    if node.y < target.minY or node.y > target.maxY then
        return false
    end
    return true
end

-- 添加附近的点
function aid.neighbors(block, node)
    local pos = {}
    -- L
    local x, y = node.x - posRate, node.y
    if phyblock.walkable(block, x, y) then
        table.insert(pos, { x, y })
    end
    -- T
    x, y = node.x, node.y + posRate
    if phyblock.walkable(block, x, y) then
        table.insert(pos, { x, y })
    end
    -- R
    x, y = node.x + posRate, node.y
    if phyblock.walkable(block, x, y) then
        table.insert(pos, { x, y })
    end
    -- B
    x, y = node.x, node.y - posRate
    if phyblock.walkable(block, x, y) then
        table.insert(pos, { x, y })
    end
    -- LT
    x, y = node.x - posRate, node.y + posRate
    if phyblock.walkable(block, x, y) then
        table.insert(pos, { x, y })
    end
    -- RT
    x, y = node.x + posRate, node.y + posRate
    if phyblock.walkable(block, x, y) then
        table.insert(pos, { x, y })
    end
    -- RB
    x, y = node.x + posRate, node.y - posRate
    if phyblock.walkable(block, x, y) then
        table.insert(pos, { x, y })
    end
    -- LB
    x, y = node.x - posRate, node.y - posRate
    if phyblock.walkable(block, x, y) then
        table.insert(pos, { x, y })
    end
    return pos
end

-- 判断三个点不在同一个方向, b 是中间点 node
function aid.isNotLine(a, b, c)
    local ax, bx, cx = a.x // posRate, b.x // posRate, c.x // posRate
    local ay, by, cy = a.y // posRate, b.y // posRate, c.y // posRate
    -- R
    if ax == bx - 1 then
        if ay == by - 1 then
            -- RT
            return cy ~= by + 1 or cx ~= bx + 1
        elseif ay == by then
            -- RR
            return cy ~= by or cx ~= bx + 1
        else
            -- RB
            return cy ~= by - 1 or cx ~= bx + 1
        end
    elseif ax == bx then
        -- M
        if ay == by - 1 then
            -- MT
            return cx ~= ax or cy ~= by + 1
        else
            -- MB
            return cx ~= ax or cy ~= by - 1
        end
    else
        -- L
        if ay == by - 1 then
            -- LT
            return cy ~= by + 1 or cx ~= bx - 1
        elseif ay == by then
            -- LL
            return cy ~= by or cx ~= bx - 1
        else
            -- LB
            return cy ~= by - 1 or cx ~= bx - 1
        end
    end
    return false
end

-- 两点之间的距离
function aid.distance(ax, ay, bx, by)
    local x = ax - bx
    local y = ay - by
    return x * x + y * y
end

-- 随机向一个方向前行一步
-- 成功返回 方向和修改step坐标至新位置，失败返回 dir_invalid
function aid.randomForward(block, step, center_x, center_y, radius)
    local dir = math.random(dirMin, dirMax)
    -- 朝该方向走一步
    local x, y = aid.convertPos(dir, step)
    if phyblock.walkable(block, x, y) and aid.distance(center_x, center_y, x, y) <= radius then
        step.x = x
        step.y = y
        return dir
    end
    -- 尝试所有方向
    for _dir = dirMin, dirMax do
        if _dir ~= dir then
            x, y = aid.convertPos(_dir, step)
            if phyblock.walkable(block, x, y) and aid.distance(center_x, center_y, x, y) <= radius then
                step.x = x
                step.y = y
                return dir
            end
        end
    end
    return dirInvalid
end

-- 方向坐标转换，返回 x,y
function aid.convertPos(dir, pos)
    if dir == dirL then
        return pos.x - posRate, pos.y
    elseif dir == dirLT then
        return pos.x - posRate, pos.y + posRate
    elseif dir == dirLB then
        return pos.x - posRate, pos.y - posRate
    elseif dir == dirR then
        return pos.x + posRate, pos.y
    elseif dir == dirRT then
        return pos.x + posRate, pos.y + posRate
    elseif dir == dirRB then
        return pos.x + posRate, pos.y - posRate
    elseif dir == dirT then
        return pos.x, pos.y + posRate
    elseif dir == dirB then
        return pos.x, pos.y - posRate
    end
end

return logic