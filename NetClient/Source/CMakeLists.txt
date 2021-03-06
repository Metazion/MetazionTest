ADD_DEFINITIONS(-D_UNICODE)

SET(METAZION_DIR $ENV{METAZION})
MESSAGE(STATUS ${METAZION_DIR})

SET(METAZION_INCLUDE_DIR ${METAZION_DIR})
SET(SELF_INCLUDE_DIR ${INCLUDE_DIR})
MESSAGE(STATUS ${METAZION_INCLUDE_DIR})
MESSAGE(STATUS ${SELF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${METAZION_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SELF_INCLUDE_DIR})

SET(METAZION_LIBRARY_DIR ${METAZION_DIR}/${LIB}/${PLATFORM})
MESSAGE(STATUS ${METAZION_LIBRARY_DIR})
LINK_DIRECTORIES(${METAZION_LIBRARY_DIR})

FILE(GLOB SELF_HEADERS "./*.hpp")
FILE(GLOB SELF_SOURCES "./*.cpp")

ADD_EXECUTABLE(${SELF}
    ${SELF_HEADERS}
    ${SELF_SOURCES}
)

SET(METAZION_NET_LINK_LIBRARY optimized MzNet debug MzNetD)
TARGET_LINK_LIBRARIES(${SELF} ${METAZION_NET_LINK_LIBRARY})
SET(METAZION_SHARE_LINK_LIBRARY optimized MzShare debug MzShareD)
TARGET_LINK_LIBRARIES(${SELF} ${METAZION_SHARE_LINK_LIBRARY})
IF(UNIX)
TARGET_LINK_LIBRARIES(${SELF} pthread)
ENDIF(UNIX)

SET(LIBRARY_OUTPUT_PATH ${BUILD_DIR}/${LIB}/${PLATFORM})
SET(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR}/${BIN}/${PLATFORM})

IF(PRODUCT_INSTALL)
    INSTALL(TARGETS ${SELF}
    LIBRARY DESTINATION ${LIB_DIR}
    ARCHIVE DESTINATION ${LIB_DIR}
	RUNTIME DESTINATION ${BIN_DIR})
ENDIF(PRODUCT_INSTALL)

# These are used to create visual studio folders.
SOURCE_GROUP(Header FILES ${SELF_HEADERS})
SOURCE_GROUP(Source FILES ${SELF_SOURCES})