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

file(COPY ${CMAKE_CURRENT_LIST_DIR}/test.ssp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
