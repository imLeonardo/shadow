--local log = require("log")
--
--function test_add(...)
--    log:info("test_add")
--
--    return 0
--end

local private = {
    name,
    gender,
    score = 100
}

local public = {}

function public.getPrivate()
    return private
end

function public.getName()
    return private.score
end

return public
