find_package(Threads REQUIRED)

set(libmath "")
if (NOT MSVC)
  set(libmath m)
endif()

set(ssp4ctest_src ssp4c_test.c)


add_executable(ssp4ctest ${ssp4ctest_src})
target_include_directories(ssp4ctest PRIVATE .)
target_link_libraries(ssp4ctest ssp4c Threads::Threads ${libmath})
install(TARGETS ssp4ctest RUNTIME DESTINATION bin)

add_test(NAME ssp4c COMMAND $<TARGET_FILE_NAME:ssp4ctest> test.ssp)

add_custom_command(TARGET ssp4ctest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/ssp/test)

add_custom_command(TARGET ssp4ctest POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/ssp/test/SystemStructure.ssd ${CMAKE_CURRENT_BINARY_DIR}/ssp/test
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/ssp/test"
  COMMAND ${CMAKE_COMMAND} -E tar "cvf" "${CMAKE_CURRENT_BINARY_DIR}/test.ssp" --format=zip .)
