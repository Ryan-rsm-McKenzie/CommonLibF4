cmake -B"build" -S"." -A"x64" -D"CMAKE_TOOLCHAIN_FILE=$Env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -D"VCPKG_TARGET_TRIPLET=x64-windows-static"
Read-Host -Prompt "Press Enter to exit"
