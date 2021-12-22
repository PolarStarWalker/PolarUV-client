cmake_minimum_required(VERSION 3.16)

if (CMAKE_BUILD_TYPE MATCHES "Release")
    add_executable(Client WIN32 Startup.cpp Startup.hpp)
else()
    add_executable(Client Startup.cpp Startup.hpp)
endif()

file(COPY Icons DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Pipelines DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Media)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Media/Video)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Media/Image)



if (WIN32)

    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
#        set(DEBUG_SUFFIX "d")
    endif ()

    message(STATUS ${QT_CMAKE_PREFIX_PATH})

    set(QT_INSTALL_PATH "${QT_CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()

    foreach (QT_LIB ${REQUIRED_LIBS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

#conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(MainWindow)
add_subdirectory(Lib)

target_link_libraries(Client MainWindow)
target_link_libraries(Client ${CONAN_LIBS})
