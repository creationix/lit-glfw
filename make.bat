
@SET LUAJIT_OS=Windows
@SET LUAJIT_ARCH=x64
@SET TARGET_DIR=%LUAJIT_OS%-%LUAJIT_ARCH%
@SET LIT_PATH=lit.exe
@SET LUVI_PATH=luvi.exe
@SET GLFW_DIR=%~d0%~p0

@SET BASE_LIB=glfw3.dll
@SET WRAPPER_LIB=wglfw.dll

@if not "x%1" == "x" GOTO :%1

:compile
@IF NOT EXIST build CALL make.bat configure
cmake --build build --config Release
COPY build\glfw\src\Release\%BASE_LIB% %TARGET_DIR%\
COPY build\Release\%WRAPPER_LIB% %TARGET_DIR%\
@GOTO :end

:configure
@IF NOT EXIST glfw git submodule update --init glfw
cmake -Bbuild -H. -G"Visual Studio 12 Win64" -DBUILD_SHARED_LIBS=ON -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_INSTALL=OFF
@GOTO :end

:setup
cd glfw-test
%LIT_PATH% install
RMDIR /S /Q deps\glfw
mklink /j deps\glfw %GLFW_DIR%
cd ..
@GOTO :end

:test
@CALL make.bat compile
@IF NOT EXIST glfw-test git submodule update --init glfw-test
@IF NOT EXIST glfw-test\deps CALL make.bat setup
%LUVI_PATH% glfw-test
@GOTO :end

:clean
rmdir /S /Q build glfw-test\deps
@GOTO :end

:end
