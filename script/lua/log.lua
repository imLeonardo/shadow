local clog = require("luabridge.clog")

local privte,public = {}, {}

function privte:format(fmt, p, ...)
    if p then
        return "lua: " .. string.format(fmt, p, ...)
    else
        return "lua: " .. fmt
    end
end

function public:trace(fmt, p, ...)
    clog.trace(privte:format(fmt, p, ...))
end

function public:debug(fmt, p, ...)
    clog.debug(privte:format(fmt, p, ...))
end

function public:info(fmt, p, ...)
    clog.info(privte:format(fmt, p, ...))
end

function public:warn(fmt, p, ...)
    clog.warn(privte:format(fmt, p, ...))
end

function public:error(fmt, p, ...)
    clog.error(privte:format(fmt, p, ...))
end

function public:critical(fmt, p, ...)
    clog.critical(privte:format(fmt, p, ...))
end

return public