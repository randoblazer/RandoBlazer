cmake_minimum_required(VERSION 3.12)
project(RandoBlazer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
  set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
endif()

add_library(randoblazerlib STATIC
  IpsPatch.cpp
  IpsPatch.h
  ItemPool.cpp
  ItemPool.h
  Locations.cpp
  Locations.h
  Lairs.cpp
  Lairs.h
  LogicGraph.cpp
  LogicGraph.h
  Filler.cpp
  Filler.h
  World.cpp
  World.h
  Random.cpp
  Random.h
  Randomizer.cpp
  Randomizer.h
  ROMCheck.cpp
  ROMCheck.h
  ROMUpdate.cpp
  ROMUpdate.h
  SpoilerLog.cpp
  SpoilerLog.h
  TextUpdate.cpp
  TextUpdate.h
)
target_link_libraries(randoblazerlib PRIVATE)

if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
  add_executable(randoblazer_emscripten
    Emscripten.cpp
  )
  target_compile_options(randoblazer_emscripten PRIVATE --bind)
  target_link_libraries(randoblazer_emscripten PRIVATE randoblazerlib idbfs.js --bind)
  set_target_properties(randoblazer_emscripten PROPERTIES
    OUTPUT_NAME randoblazer
  )
else()
  add_executable(randoblazer_cli
    cli.cpp
  )
  target_link_libraries(randoblazer_cli PRIVATE randoblazerlib)
  set_target_properties(randoblazer_cli PROPERTIES
    OUTPUT_NAME randoblazer
  )
endif()

if (ROM)
  message(STATUS "ROM found at: ${ROM}")
  enable_testing()

  add_test(
    NAME portability_check
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/run-test.cmake "-DEXE=$<TARGET_FILE:randoblazer_cli>" "-DROM=${ROM}"
  )
  set_tests_properties(portability_check PROPERTIES
    ENVIRONMENT "EXE=$<TARGET_FILE:randoblazer_cli>;ROM=${ROM}"
  )
endif()
