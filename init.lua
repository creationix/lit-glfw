local ffi = require('ffi')
local bundle = require('luvi').bundle

-- Workaround to polyfill bundle.action till luvi is updated.
require('./bundle-action')
local pathJoin = require('luvi').path.join

-- Get path
local base = module.dir:gsub("^bundle:", "")
local dir = pathJoin(base, ffi.os .. "-" .. ffi.arch)
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

ffi.cdef(bundle.readfile(pathJoin(base, "glfw.h")))
ffi.cdef((bundle.readfile(pathJoin(base, "wrapper.h")):gsub("^%#[^\n]*", ""):gsub("GLFWAPI", "")))

local types = {
  [tonumber(wrapper.GLFWerrorevt)] = {"error", "description"},
  [tonumber(wrapper.GLFWwindowposevt)] = {"window", "xpos", "ypos"},
  [tonumber(wrapper.GLFWwindowsizeevt)] = {"window", "width", "height"},
  [tonumber(wrapper.GLFWwindowcloseevt)] = {"window"},
  [tonumber(wrapper.GLFWwindowrefreshevt)] = {"window"},
  [tonumber(wrapper.GLFWwindowfocusevt)] = {"window", "focused"},
  [tonumber(wrapper.GLFWwindowiconifyevt)] = {"window", "iconified"},
  [tonumber(wrapper.GLFWframebuffersizeevt)] = {"window", "width", "height"},
  [tonumber(wrapper.GLFWmousebuttonevt)] = {"window", "button", "action", "mods"},
  [tonumber(wrapper.GLFWcursorposevt)] = {"window", "xpos", "ypos"},
  [tonumber(wrapper.GLFWcursorenterevt)] = {"window", "entered"},
  [tonumber(wrapper.GLFWscrollevt)] = {"window", "xoffset", "yoffset"},
  [tonumber(wrapper.GLFWkeyevt)] = {"window", "key", "scancode", "action", "mods"},
  [tonumber(wrapper.GLFWcharevt)] = {"window", "codepoint"},
  [tonumber(wrapper.GLFWcharmodsevt)] = {"window", "codepoint", "mods"},
  [tonumber(wrapper.GLFWdropevt)] = {"window", "count", "paths"},
  [tonumber(wrapper.GLFWmonitorevt)] = {"monitor", "action"},
}

local names = {
  [tonumber(wrapper.GLFWerrorevt)] = "error",
  [tonumber(wrapper.GLFWwindowposevt)] = "windowpos",
  [tonumber(wrapper.GLFWwindowsizeevt)] = "windowsize",
  [tonumber(wrapper.GLFWwindowcloseevt)] = "windowclose",
  [tonumber(wrapper.GLFWwindowrefreshevt)] = "windowrefresh",
  [tonumber(wrapper.GLFWwindowfocusevt)] = "windowfocus",
  [tonumber(wrapper.GLFWwindowiconifyevt)] = "windowiconify",
  [tonumber(wrapper.GLFWframebuffersizeevt)] = "framebuffersize",
  [tonumber(wrapper.GLFWmousebuttonevt)] = "mousebutton",
  [tonumber(wrapper.GLFWcursorposevt)] = "cursorpos",
  [tonumber(wrapper.GLFWcursorenterevt)] = "cursorenter",
  [tonumber(wrapper.GLFWscrollevt)] = "scroll",
  [tonumber(wrapper.GLFWkeyevt)] = "key",
  [tonumber(wrapper.GLFWcharevt)] = "char",
  [tonumber(wrapper.GLFWcharmodsevt)] = "charmods",
  [tonumber(wrapper.GLFWdropevt)] = "drop",
  [tonumber(wrapper.GLFWmonitorevt)] = "monitor",
}

local function toLua(event)
  if event == nil then return nil end
  local num = tonumber(event.type)
  local table = {
    type = names[num]
  }
  local fields = types[num]
  for i = 1, #fields do
    local field = fields[i]
    table[field] = event[field]
  end
  return table
end

return {glfw, wrapper, toLua}

