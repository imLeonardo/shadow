local clog = require("luabridge.clog")

local _M = {}

local function format(fmt, p, ...)
    if p then
        return "[lua]" .. string.format(fmt, p, ...)
    else
        return "[lua]" .. fmt
    end
end

function _M:trace(fmt, p, ...)
    clog.trace(format(fmt, p, ...))
end

function _M:debug(fmt, p, ...)
    clog.debug(format(fmt, p, ...))
end

function _M:info(fmt, p, ...)
    clog.info(format(fmt, p, ...))
end

function _M:warn(fmt, p, ...)
    clog.warn(format(fmt, p, ...))
end

function _M:error(fmt, p, ...)
    clog.error(format(fmt, p, ...))
end

function _M:critical(fmt, p, ...)
    clog.critical(format(fmt, p, ...))
end

return _M