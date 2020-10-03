cmake -B build -S . "-DCMAKE_TOOLCHAIN_FILE=$Env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -D"VCPKG_OVERLAY_PORTS=$Env:CommonLibF4Path/ports" "-DVCPKG_TARGET_TRIPLET=x64-windows-static"
Read-Host -Prompt "Press Enter to exit"
