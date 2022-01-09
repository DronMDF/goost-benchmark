CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

PROJECT(goost-benchmark)

FIND_PACKAGE(OpenSSL REQUIRED)

INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g0 -fomit-frame-pointer -std=c++17 -Wall -Wextra -pedantic -Werror")

ADD_EXECUTABLE(
	goost-benchmark
	main.cpp
	Benchmark.cpp
	MagmaCfbSinkFactory.cpp
	MagmaEcbSinkFactory.cpp
	MagmaEcbSSE3SinkFactory.cpp
	MemorySink.cpp
	NullSink.cpp
	OpensslSink.cpp
	OpensslSinkFactory.cpp
	SinkImpl.cpp
	SSE3Alg.cpp
	SSE3EcbIOFactory.cpp
	StringKeyContainer.cpp
	TransparentSinkFactory.cpp
)

TARGET_LINK_LIBRARIES(
	goost-benchmark
	goost
	${CMAKE_THREAD_LIBS_INIT}
	${OPENSSL_LIBRARIES}
)

ADD_EXECUTABLE(
	reference
	reference.cpp
)

TARGET_LINK_LIBRARIES(
	reference
	${CMAKE_THREAD_LIBS_INIT}
	${OPENSSL_LIBRARIES}
)

ADD_CUSTOM_TARGET(
	style
	COMMAND ${CMAKE_SOURCE_DIR}/style.sh
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
