#
# This is a CMake makefile.  You can find the cmake utility and
# information about it at http://www.cmake.org
#

cmake_minimum_required (VERSION 3.1)
project(fr)

set (CMAKE_CXX_STANDARD 11)

 set(SOURCE 	./../headers/IndexSearch.cpp
    )

 set(HEADERS	./../headers/FaceDB.h               
               ./../include/rapidjson/document.h
    )

# automatic OpenCV finding
find_package(OpenCV REQUIRED)

# if not, use manual specification of the OpenCVConfig.cmake path
# and comment previous line of automatic finding
# find_package(OpenCV REQUIRED PATHS /usr/local/Cellar/opencv/4.1.1_2/lib/cmake/opencv4 NO_DEFAULT_PATH)


# si encontró bien la opencv, debe mostrarte estos mensajes sin problema
# puedes chequear luego lo que está dentro de cada carpeta que se imprime
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

# Esto no necesitan hacerlo, dado que esto se configura dentro de la funcion find_packages
set(fr_libraries 	/usr/local/Cellar/mongo-cxx-driver/3.4.0/lib) 
link_directories(${fr_libraries})
#


add_executable(fr test.cpp ${SOURCE} ${HEADERS})

# Si ya adicionaste la opencv usando findpackages, lo que se recomienda
# es usar las variables que se crean.
# son las que se imprimen en las lineas 29 - 33
# target_link_libraries(fr opencv_highgui411.lib opencv_imgproc411.lib opencv_objdetect411.lib opencv_video411.lib)
target_link_libraries(fr ${OpenCV_LIBS} mongocxx bsoncxx)
