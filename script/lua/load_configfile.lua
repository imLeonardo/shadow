package.path = "./?.lua;./script/lua/?.lua;" .. package.path

local log = require("log")

local config

local function swap(t, left, right)
    local tmp = t[left]
    t[left] = t[right]
    t[right] = tmp
end

local function partition(t, left, right)
    local tmp = t[left]
    while (left < right) do
        while (left < right and t[right] >= tmp) do
            right = right - 1
        end
        t[left] = t[right]
        while (left < right and t[left] <= tmp) do
            left = left + 1
        end
        t[right] = t[left]
    end
    t[left] = tmp
    return left
end

local function quickSort(t, left, right)
    if #t < 2 then
        return
    end
    if left < right then
        local partitionIndex = partition(t, left, right)
        quickSort(t, left, partitionIndex - 1)
        quickSort(t, partitionIndex + 1, right)
    end
end

function loadFile(configfile)
    log:info("load config file: %s.", configfile)
    configfile = string.gsub(configfile, ".lua", "")
    config = require(configfile)
    local t = { 1, 3, 3, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10 }
    quickSort(t, 1, #t)
    log:debug("t: %s", table.concat(t, ","))

    return config
end

function getConfig()
    return config
end

function printConfig()

end
