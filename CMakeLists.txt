cmake_minimum_required(VERSION 2.8)

SET ( EXECUTABLE task_sim )

# UNCOMMENT FOR GRAPHICS
#add_definitions(-D_GRAPHICS_)
add_definitions(-D preprocessing)
FIND_PACKAGE( OpenCV REQUIRED )
FIND_PACKAGE( Qt COMPONENTS QtOpenGL REQUIRED )
FIND_PACKAGE( Qt4 REQUIRED )
SET( QT_USE_QTOPENGL TRUE )
SET(  QT_USE_QTXML TRUE )
INCLUDE( ${QT_USE_FILE} )


FILE ( GLOB SOURCES ./*.cpp ./MISC/*.cpp ./EVOL_ALGORITHM/*.cpp ./MOEA/*.cpp ./ROB_SENSORS_OBJS/*.cpp ./EXP/*.cpp ./CONTROLLERS/*.cpp ./EXP/RENDERING/*.cpp)
FILE ( GLOB HEADERS ./*.h ./MISC/*.h ./EVOL_ALGORITHM/*.h ./MOEA/*.h ./ROB_SENSORS_OBJS/*.cpp ./EXP/*.h ./CONTROLLERS/*.h ./EXP/RENDERING/*.h)
FILE ( GLOB UIS ./*.ui ./EXP/RENDERING/*.ui)

QT4_WRAP_CPP( SOURCES ${HEADERS} )
QT4_WRAP_UI( SOURCES  ${UIS} )
FIND_PACKAGE ( GLUT )
FIND_PACKAGE ( OpenGL )
FIND_PACKAGE ( MPI )

INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${MPI_INCLUDE_PATH} /usr/include/ /usr/include/openmpi/ /usr/include/mpi/ /usr/local/include/ ${CMAKE_CURRENT_BINARY_DIR} ./EXP/RENDERING /usr/local/include/opencv2/)

#/usr/local/qwt-6.1.1-svn/include/
# UNCOMMENT FOR GRAPHICS

# To add c++11 support
if (MSVC) # MSVC compiler (Win32 only)
        # Display more warnings
        SET (CMAKE_CXX_FLAGS "/W3")
elseif (UNIX OR CMAKE_COMPILER_IS_GNUCXX) # Clang OR Gcc (Linux, Mac OS or Win32 with MingW)
        # Enable C++11 and displays all warnings
        SET (CMAKE_CXX_COMPILER mpicxx)
        SET (CMAKE_CXX_FLAGS "-pthread -lstdc++ -std=c++11")
        if (APPLE) # Clang / Mac OS only
                # Required on OSX to compile c++11
                SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -mmacosx-version-min=10.7")
        endif(APPLE)
endif()

ADD_EXECUTABLE( ${EXECUTABLE} ${SOURCES})

#TARGET_LINK_LIBRARIES( ${EXECUTABLE}  ${OPENGL_glu_LIBRARY}  ${GLUT_LIBRARIES} -lmpi -lGL -lGLU  -lGLEW -lOSMesa ${QT_LIBRARIES} )#revel xvidcore QGLViewer
TARGET_LINK_LIBRARIES( ${EXECUTABLE} ${OpenCV_LIBS} ${OPENGL_glu_LIBRARY}  ${GLUT_LIBRARIES} -lmpi -lGLU  -lGLEW -lOSMesa ${QT_LIBRARIES} )#revel xvidcore QGLViewer
TARGET_LINK_LIBRARIES( ${EXECUTABLE} "-L/sw/lib -lgsl -lgslcblas -lm -lfreeimage" )#-L/usr/local/qwt-6.1.1-svn/lib  -lqwt


#TARGET_LINK_LIBRARIES( ${EXECUTABLE} ${OPENGL_glu_LIBRARY}  ${GLUT_LIBRARIES} -lGLEW -lGL -lGLU -L/usr/lib/x86_64-linux-gnu/ -lOSMesa  ${QT_LIBRARIES} )
#TARGET_LINK_LIBRARIES( ${EXECUTABLE} "-L/sw/lib -lgsl -lgslcblas -lm -L/usr/local/qwt-6.1.1-svn/lib  -lqwt -L/usr/lib/x86_64-linux-gnu/ -lavcodec -lavutil -lavformat -lswscale" )

