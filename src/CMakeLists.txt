PROJECT(VectorFieldRenderer-core)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0 FATAL_ERROR)
cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0016 NEW)

MESSAGE(STATUS "Configuring RFID_MobiVis Source")



# glob sources from core directories
FILE(GLOB VectorFieldRendererSources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	rendering/*.c
    rendering/*.cpp
	application/*.cpp
	glsl/*.frag
	glsl/*.vert
	main.cpp
)

FILE(GLOB VectorFieldRendererHeaders RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    rendering/*.h
	application/*.h
)

include_directories(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH} ${GLM_INCLUDE_DIR})


ADD_DEFINITIONS(${VectorFieldRendererGlobalDefinitions})

INCLUDE_DIRECTORIES(${VectorFieldRendererIncludeDirs})
LINK_DIRECTORIES(${GLFW_LIBRARY} ${GLEW_LIBRARY})

MESSAGE("GLEW Library = ${GLEW_LIBRARY}")
MESSAGE("GLFW Library = ${GLFW3_LIBRARY}")

add_executable (VectorFieldRenderer
	${VectorFieldRendererSources}
	${VectorFieldRendererHeaders}
  )

IF(WIN32)
	TARGET_LINK_LIBRARIES(VectorFieldRenderer ${OPENGL_LIBRARY} ${GLFW3_LIBRARY}/glfw3.lib ${GLEW_LIBRARY}/glew32.lib)
ELSE(WIN32)
	TARGET_LINK_LIBRARIES(VectorFieldRenderer ${OPENGL_LIBRARY} ${GLFW3_LIBRARY} ${GLEW_LIBRARY})
ENDIF(WIN32)

DEFINE_SOURCE_GROUPS_FROM_SUBDIR(VectorFieldRendererSources ${VectorFieldRendererHome} "")
DEFINE_SOURCE_GROUPS_FROM_SUBDIR(VectorFieldRendererHeaders ${VectorFieldRendererHome} "")