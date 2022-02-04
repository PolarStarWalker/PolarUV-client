project (DataStructs)

add_library(DataStructs CommandsStruct.cpp VideoPipelineStruct.cpp)

target_link_libraries(DataStructs ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(DataStructs ${CONAN_LIBS})

target_precompile_headers(DataStructs PUBLIC DataStructs.hpp)