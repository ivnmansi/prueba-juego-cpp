@echo off
echo === Building game ===

echo Creating directories...
if not exist obj mkdir obj

echo Compiling main.cpp...
g++ -IC:\msys64\mingw64\include\SDL2 -Iinc -std=c++17 -Wall -c main.cpp -o obj\main.o
if %errorlevel% neq 0 goto error

echo Compiling source files...
for %%f in (src\*.cpp) do (
    echo Compiling %%f...
    g++ -IC:\msys64\mingw64\include\SDL2 -Iinc -std=c++17 -Wall -c %%f -o obj\%%~nf.o
    if %errorlevel% neq 0 goto error
)

echo Linking...
g++ obj\*.o -LC:\msys64\mingw64\lib\sdl2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o game.exe
if %errorlevel% neq 0 goto error

echo === Build successful! ===
goto end

:error
echo === Build failed! ===
exit /b 1

:end