cmake_minimum_required(4.0)

set(GLEW3_DIR lib/Release/x64/)
set(GLEW3_INCLUDE_DIR include)
set(GLEW3_LIBRARY_DEBUG lib/Debug/x64/glew32sd.lib)   # Статическая Debug
set(GLEW3_LIBRARY_RELEASE lib/Release/x64/glew32s.lib) # Статическая Release

add_library(GLEW STATIC IMPORTED)

set_target_properties(GLEW PROPERTIES
    IMPORTED_LOCATION_DEBUG "${GLEW3_LIBRARY_DEBUG}"
    IMPORTED_LOCATION_RELEASE "${GLEW3_LIBRARY_RELEASE}"
    INTERFACE_INCLUDE_DIRECTORIES "${GLEW3_INCLUDE_DIR}"
)