set(SOURCES
	test_main.cpp
	test_jit.cpp
)

add_executable(jit_test
	${SOURCES}
)

target_link_libraries(jit_test
	PRIVATE
	Catch2
	jit
)

add_test(NAME jit_test COMMAND jit_test)
