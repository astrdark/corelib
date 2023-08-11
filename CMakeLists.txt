cmake_minimum_required(VERSION 3.25)
project(CoreLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(CORELIB_HDRS
	include/CoreLib/CTThrow.hpp
	include/CoreLib/IntegerTypes.hpp
	include/CoreLib/Tuple.hpp
	include/CoreLib/FixedString.hpp
	include/CoreLib/TemplateUtils.hpp
	include/CoreLib/TypeName.hpp)

set(CORELIB_SRCS
	src/library.cpp
	src/TemplateUtils.tests.cpp
	src/Tuple.tests.cpp
	src/TypeName.tests.cpp)

add_library(CoreLib ${CORELIB_SRCS} ${CORELIB_HDRS})
target_include_directories(CoreLib PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(CORELIB_SAMPLE_SRCS
	sample/main.cpp
)

add_executable(CoreLibSample ${CORELIB_SAMPLE_SRCS})
target_link_libraries(CoreLibSample PRIVATE CoreLib)
