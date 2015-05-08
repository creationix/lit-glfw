return {
  name = "creationix/glfw",
  version = "3.2.0",
  homepage = "https://github.com/creationix/lit-glfw",
  description = "FFI bindings to the GLFW library",
  tags = {"ffi", "gui", "glfw"},
  author = { name = "Tim Caswell" },
  license = "MIT",
  files = {
    "*.lua",
    "*.h",
    "!glfw",
    "!glfw-test",
    "$OS-$ARCH/*",
  }
}
