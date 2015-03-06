LUAJIT_OS=$(shell luajit -e "print(require('ffi').os)")
LUAJIT_ARCH=$(shell luajit -e "print(require('ffi').arch)")
TARGET_DIR=$(LUAJIT_OS)-$(LUAJIT_ARCH)

ifeq ($(LUAJIT_OS), OSX)
BASE_LIB=libglfw.3.1.dylib
WRAPPER_LIB=libwglfw.dylib
endif
ifeq ($(LUAJIT_OS), Linux)
BASE_LIB=libglfw.so.3.1
WRAPPER_LIB=libwglfw.so
endif

all: build
	cmake --build build
	cp build/glfw/src/$(BASE_LIB) $(TARGET_DIR)
	cp build/$(WRAPPER_LIB) $(TARGET_DIR)

build:
	cmake -Bbuild -H. -GNinja  -Wno-dev -DBUILD_SHARED_LIBS=ON \
	  -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF \
	  -DGLFW_BUILD_DOCS=OFF -DGLFW_INSTALL=OFF

clean:
	rm -rf build
