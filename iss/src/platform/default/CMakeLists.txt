file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(mt-iss
		main.cpp
		test_rules.cpp
		memory_interface.cpp
		instr_builder.cpp
		code_builder.cpp
		executor.cpp
		mutations.cpp
		random.cpp
	    ${HEADERS})

target_link_libraries(mt-iss rv32 ${Boost_LIBRARIES})

INSTALL(TARGETS mt-iss RUNTIME DESTINATION bin)
