exports.name = "creationix/glfw"
exports.version = "3.1.2"
exports.homepage = "https://github.com/creationix/lit-glfw"
exports.files = {
  "*.lua",
  "*.h",
  "**/$OS-$ARCH**",
}  

local ffi = require('ffi')
local bundle = require('luvi').bundle

-- Workaround to polyfill bundle.action till luvi is updated.
require('./bundle-action')

-- Get path
local base = module.dir:gsub("^bundle:", "") .. '/'
local dir = base .. ffi.os .. "-" .. ffi.arch
local entries = bundle.readdir(dir)
local path = dir .. '/' .. entries[1]

local glfw = bundle.action(path, function (path)
  return ffi.load(path)
end)

ffi.cdef(bundle.readfile(base .. "glfw.h"))

return glfw

