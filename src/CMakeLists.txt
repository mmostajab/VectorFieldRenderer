PROJECT(VectorFieldRenderer-core)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0 FATAL_ERROR)
cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0016 NEW)

MESSAGE(STATUS "Configuring RFID_MobiVis Source")



# glob sources from core directories
FILE(GLOB VectorFieldRendererSources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.cpp
)

FILE(GLOB VectorFieldRendererHeaders RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.h
)

include_directories(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIR})


ADD_DEFINITIONS(${VectorFieldRendererGlobalDefinitions})

INCLUDE_DIRECTORIES(${VectorFieldRendererIncludeDirs})
LINK_DIRECTORIES(${GLFW_LIBRARIES} ${GLEW_LIBRARY})

add_executable (VectorFieldRenderer
	${VectorFieldRendererSources}
	${VectorFieldRendererHeaders}
  )


TARGET_LINK_LIBRARIES(VectorFieldRenderer ${GLFW_LIBRARY} ${GLEW_LIBRARY})

DEFINE_SOURCE_GROUPS_FROM_SUBDIR(VectorFieldRendererSources ${VectorFieldRendererHome} "")
DEFINE_SOURCE_GROUPS_FROM_SUBDIR(VectorFieldRendererHeaders ${VectorFieldRendererHome} "")