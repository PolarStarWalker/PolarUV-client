project ("DataStructs")

add_library(DataStructs CommandsStruct.cpp RobotSettingsStruct.cpp ClientSettingsStruct.cpp MotorsStruct.cpp)

target_precompile_headers(DataStructs PUBLIC DataStructs.hpp)