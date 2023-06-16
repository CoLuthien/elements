
include(ExternalProject)

set(PUGL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/build/pugl)
set(PUGL_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib/pugl)
set(PUGL_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib/pugl/include/puglpp-0)
set(PUGL_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib/pugl/lib)

ExternalProject_Add(pugl
    GIT_REPOSITORY https://github.com/lv2/pugl.git
    GIT_TAG main
    PREFIX ${PUGL_PREFIX}
    CONFIGURE_COMMAND meson ${PUGL_PREFIX}/build ${PUGL_PREFIX}/src/pugl -Ddocs=disabled -Dexamples=disabled -Dincludedir=include -Dlibdir=lib -Dprefix=/
    BUILD_COMMAND meson build ${PUGL_PREFIX}/src/pugl
    INSTALL_COMMAND meson install -C ${PUGL_PREFIX}/build --destdir ${PUGL_INSTALL_DIR}
)

add_library(libpugl 
    SHARED IMPORTED
)


set_target_properties(libpugl PROPERTIES 
    IMPORTED_LOCATION ${PUGL_LIB_DIR}/libpugl_x11_vulkan-0.so
)

add_dependencies(libpugl pugl)
