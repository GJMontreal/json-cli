# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.10)

include(pico_sdk_import.cmake)

project(json_reader C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(json_reader)

target_sources(json_reader PUBLIC
  ./main.cpp
  ./src/InputHandler.cpp
)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)


target_include_directories(json_reader PRIVATE 
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/src/include
)

target_compile_options( json_reader PUBLIC
        ### Gnu/Clang C Options
        $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-fdiagnostics-color=always>
        $<$<COMPILE_LANG_AND_ID:CXX,Clang>:-fcolor-diagnostics>

        # $<$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>:-Wall>
        $<$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>:-Wextra>
        $<$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>:-Werror>
        $<$<COMPILE_LANG_AND_ID:CXX,Clang>:-Weverything>
        )

target_link_libraries(json_reader PUBLIC
        pico_stdlib
        cmsis_core # CMSIS core headers via the SDK
)

target_link_libraries(json_reader PRIVATE 
  nlohmann_json::nlohmann_json
)


pico_enable_stdio_uart(json_reader 1)
pico_add_extra_outputs(json_reader)
