PROJECT( DFTU )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


# required if linking to static library
#add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE ${CMAKE_SOURCE_DIR}/thirdparty/antlr/antlr-4.8-complete.jar)
# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(Expr Expr.g4 PARSER LISTENER
             PACKAGE dftu)

include_directories(${ANTLR_Expr_OUTPUT_DIR})

ADD_LIBRARY( dftu SHARED src/dftu.cpp ${ANTLR_Expr_CXX_OUTPUTS} )
TARGET_COMPILE_DEFINITIONS( dftu PUBLIC DFTU_LIBRARY )
TARGET_INCLUDE_DIRECTORIES( dftu PUBLIC include )

ADD_EXECUTABLE( demo src/demo.cpp )

target_link_libraries(demo dftu)

target_link_libraries(dftu antlr4_shared)

INSTALL( TARGETS dftu DESTINATION lib )
INSTALL( TARGETS demo DESTINATION bin )
get_target_property( ANTLR4_SHARED_LOCATION antlr4_shared IMPORTED_LOCATION )
get_filename_component( ANTLR4_VERSIONED ${ANTLR4_SHARED_LOCATION} REALPATH )
INSTALL( FILES ${ANTLR4_SHARED_LOCATION} ${ANTLR4_VERSIONED} DESTINATION lib )
