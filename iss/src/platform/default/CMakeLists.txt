file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(mt-iss
		common.cpp
		executor.cpp
		main.cpp
		memory.cpp
		mutations.cpp
		random.cpp
		tests.cpp
	    ${HEADERS})

target_link_libraries(mt-iss dl rv32 gcov ${Boost_LIBRARIES})
INSTALL(TARGETS mt-iss RUNTIME DESTINATION bin)
