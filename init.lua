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
assert(entries and #entries == 2, "Expected 2 entries in arch folder")
local mainPath, wrapperPath = unpack(entries)
if mainPath:match("wrapper") then
  mainPath, wrapperPath = wrapperPath, mainPath
end
mainPath = dir .. '/' .. mainPath
wrapperPath = dir .. '/' .. wrapperPath

local glfw = bundle.action(mainPath, function (path)
  return ffi.load(path)
end)
local wrapper = bundle.action(wrapperPath, function (path)
  return ffi.load(path)
end)

ffi.cdef(bundle.readfile(base .. "glfw.h"))
ffi.cdef((bundle.readfile(base .. "wrapper.h"):gsub("^%#[^\n]*", "")))

return {glfw, wrapper}

