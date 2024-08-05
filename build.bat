echo Setup required Environment 
echo -------------------------------------

SET RAYLIB_PATH=C:\raylib\raylib 
SET COMPILER_PATH=C:\raylib\w64devkit\bin
SET PATH=%COMPILER_PATH%;%PATH%
SET CC=gcc
SET CFLAGS=-s -static -Os -std=c99 -Wall -IC:\raylib\raylib\src -Iexternal -DPLATFORM_DESKTOP
SET LDFLAGS=-LC:\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm

cd %CD%

echo
echo Clean latest build
echo ------------------------

cmd /c IF EXIST ludoultimate.exe del /F ludoultimate.exe

echo
echo Compile program
echo -----------------------

%CC% --version
%CC% -o ludoultimate.exe ludoultimate.c %CFLAGS% C:\raylib\raylib\src\raylib.rc.data %LDFLAGS%

echo
echo Execute program
echo -----------------------

cmd /c IF EXIST ludoultimate.exe ludoultimate.exe
