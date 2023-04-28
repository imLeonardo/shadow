package.path = "./?.lua;./script/lua/?.lua;" .. package.path

local test1 = require("test1")

local p = test1.getPrivate()

print(p.name .. ":" .. p.score)
