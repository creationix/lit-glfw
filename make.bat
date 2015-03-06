
@SET LUAJIT_OS=Windows
@SET LUAJIT_ARCH=x64
@SET TARGET_DIR=%LUAJIT_OS%-%LUAJIT_ARCH%

@SET BASE_LIB=glfw3.dll
@SET WRAPPER_LIB=wglfw.dll

@if not "x%1" == "x" GOTO :%1

:all
@IF NOT EXIST build CALL make.bat build
cmake --build build --config Release
COPY build\glfw\src\Release\%BASE_LIB% %TARGET_DIR%\
COPY build\Release\%WRAPPER_LIB% %TARGET_DIR%\
@GOTO :end

:build
cmake -Bbuild -H. -G"Visual Studio 12 Win64" -DBUILD_SHARED_LIBS=ON -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_INSTALL=OFF
@GOTO :end

:clean
rmdir /S /Q build
@GOTO :end

:end
