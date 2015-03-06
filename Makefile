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

libs: build
	cmake --build build --config Release
	cp build/glfw/src/$(BASE_LIB) $(TARGET_DIR)
	cp build/$(WRAPPER_LIB) $(TARGET_DIR)

glfw:
	git submodule update --init glfw

build: glfw
	cmake -Bbuild -H. -GNinja  -Wno-dev -DBUILD_SHARED_LIBS=ON \
	  -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF \
	  -DGLFW_BUILD_DOCS=OFF -DGLFW_INSTALL=OFF

glfw-test:
	git submodule update --init glfw-test

glfw-test/deps: glfw-test
	cd glfw-test && lit install
	rm -rf glfw-test/deps/glfw
	ln -s ../.. glfw-test/deps/glfw

test: libs glfw-test/deps
	LUVI_APP=glfw-test lit

clean:
	rm -rf build glfw-test/deps
