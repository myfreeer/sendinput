echo Syncing msys2 packages...
C:\msys64\usr\bin\pacman -Sq --noconfirm --needed --noprogressbar --ask=20 mingw-w64-x86_64-ninja mingw-w64-i686-ninja
rem C:\msys64\usr\bin\pacman -Scq --noconfirm

echo Building and testing 64-bit version...
set MSYSTEM=MINGW64
call C:\msys64\usr\bin\bash -lc "cd \"$APPVEYOR_BUILD_FOLDER\" && exec ./build.sh"
move /Y .\build_x86_64-w64-mingw32\sendinput.exe .\sendinput_x64.exe
move /Y .\build_x86_64-w64-mingw32\sendinput_io.exe .\sendinput_io_x64.exe

echo Building and testing 32-bit version...
set MSYSTEM=MINGW32
call C:\msys64\usr\bin\bash -lc "cd \"$APPVEYOR_BUILD_FOLDER\" && exec ./build.sh"
move /Y .\build_i686-w64-mingw32\sendinput.exe .\sendinput_x86.exe
move /Y .\build_i686-w64-mingw32\sendinput_io.exe .\sendinput_io_x86.exe

echo Packaging...
7z a -mx9 sendinput.7z .\sendinput_x64.exe .\sendinput_x86.exe .\sendinput_io_x64.exe .\sendinput_io_x86.exe
echo Done.