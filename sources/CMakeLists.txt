cmake_minimum_required (VERSION 3.1)
project(fr)

set (CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

if(OpenCV_FOUND)
	message("-- Opencv Found")
endif()

set(fr_include 	${OpenCV_INCLUDE_DIRS}
                  /usr/local/Cellar/mongo-cxx-driver/3.4.0/include/mongocxx/v_noabi
                  /usr/local/Cellar/mongo-cxx-driver/3.4.0/include/bsoncxx/v_noabi
	)
include_directories(${fr_include})

set(fr_libraries 	/usr/local/Cellar/mongo-cxx-driver/3.4.0/lib) 
link_directories(${fr_libraries})

add_executable(fr main.cpp ${SOURCE} ${HEADERS})

target_link_libraries(fr ${OpenCV_LIBS} mongocxx bsoncxx)
