IF (WIN32)  
    set(jni_include $ENV{JAVA_HOME}/include/win32)
ELSEIF (APPLE)  
    set(jni_include $ENV{JAVA_HOME}/include/linux)
ELSEIF (UNIX)  
    set(jni_include $ENV{JAVA_HOME}/include/linux)
ENDIF () 

include_directories (
    ./
    ${SOURCE_DIR}/
    $ENV{JAVA_HOME}/include
    ${jni_include}
)

set (ltp4j_VERSION "0.0.2")

set(ltp4j_SRC ltp4j.cpp)

# -----------------------------------------------
# SHARED LIBRARY
# -----------------------------------------------
add_library (ltp4j_shared_lib SHARED
    ${ltp4j_SRC})
target_link_libraries (ltp4j_shared_lib segmentor_static_lib postagger_static_lib
   parser_static_lib)
set_target_properties (ltp4j_shared_lib PROPERTIES
    VERSION     ${ltp4j_VERSION}
    OUTPUT_NAME ltp4j)

link_directories ( ${LIBRARY_OUTPUT_PATH} )