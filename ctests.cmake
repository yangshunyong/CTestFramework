function(create_test_app testname)
    set(SOURCES ${testname}.cpp)

    add_executable(${testname} ${SOURCES})
    add_test(NAME ${testname} COMMAND $<TARGET_FILE:${testname}> ${ARGN})
endfunction()