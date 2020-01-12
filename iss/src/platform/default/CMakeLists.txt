file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(mt-iss
	    main.cpp
	    ${HEADERS})

target_link_libraries(mt-iss rv32 ${Boost_LIBRARIES})

INSTALL(TARGETS mt-iss RUNTIME DESTINATION bin)
