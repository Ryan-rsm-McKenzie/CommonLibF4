vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/stl_interfaces
    REF boost-1.74.0
    SHA512 8d6b0f0fe0b16cc79d52dd899cf8973c8abeb9d1087110c3bade797021ff10420c2d0d959b9442bce7499f0f028d690ef5e5a70300607950d025df8e9ab637a4
    HEAD_REF master
)

file(REMOVE ${SOURCE_PATH}/CMakeLists.txt)
file(COPY ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt DESTINATION ${SOURCE_PATH})
file(COPY ${CMAKE_CURRENT_LIST_DIR}/stl_interfaces-config.cmake.in DESTINATION ${SOURCE_PATH}/cmake)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
)

vcpkg_install_cmake()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug)

file(INSTALL ${SOURCE_PATH}/LICENSE_1_0.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
