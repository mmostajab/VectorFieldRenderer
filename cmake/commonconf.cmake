IF(NOT CommonconfProcessed)

SET(VectorFieldRendererHome ${CMAKE_CURRENT_SOURCE_DIR})
SET(VectorFieldRendererBinaryDir ${CMAKE_BINARY_DIR})

MESSAGE(STATUS "VectorFieldRenderer Source Directory: ${VectorFieldRendererHome}")
MESSAGE(STATUS "VectorFieldRenderer Binary Directory: ${VectorFieldRendererBinaryDir}")

# include macros
INCLUDE(${VectorFieldRendererHome}/cmake/macros.cmake)

# detect compiler and architecture
IF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 10")
    SET(VectorFieldRenderer_MSVC2010 TRUE)
    SET(VectorFieldRenderer_WIN32 TRUE)
    MESSAGE(STATUS "Visual Studio 2010 Build (32 Bit)")
ELSE()
    MESSAGE(WARNING "Unsupported or unknown generator: ${CMAKE_GENERATOR}")
ENDIF()


# set binary output path
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# common include directories
LIST(APPEND VectorFieldRendererIncludeDirs ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}) 

LIST(APPEND VectorFieldRendererGlobalDefinitions "-DMOBIRFIDVIS_SOURCE_DIR=\"${VectorFieldRendererHome}\"")

# platform-dependent configuration
IF(WIN32)
    LIST(APPEND VectorFieldRendererGlobalDefinitions "-DNOMINMAX" "-D_CRT_SECURE_NO_DEPRECATE")

    # Disable warnings for Microsoft compiler:
    # C4290: C++ exception specification ignored except to indicate a function is
    #        not __declspec(nothrow)
    # C4390: ';' : empty controlled statement found; is this the intent?
    #        occurs when OpenGL error logging macros are disabled
    # C4503: The decorated name was longer than the compiler limit (4096), and was truncated.
    #        Occurs in AutoEvaluatePipeline due to some nested nested map-iterator-map. Could
    #        not be deactivated locally...
    LIST(APPEND VectorFieldRendererGlobalDefinitions /wd4290 /wd4390 /wd4503)

    # prevent error: number of sections exceeded object file format limit
    LIST(APPEND VectorFieldRendererGlobalDefinitions /bigobj)
    
    # allows 32 Bit builds to use more than 2GB RAM (VC++ only)
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /LARGEADDRESSAWARE")
    SET(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
    
    LIST(APPEND VectorFieldRenderer_GlobalExternalLibs netapi32 version)
ENDIF(WIN32)

IF(CMAKE_COMPILER_IS_GNUCXX)
    # enable C++11 support in GCC
    LIST(APPEND CMAKE_CXX_FLAGS "-std=c++11")
ENDIF()
 
# SET(CMAKE_MODULE_PATH {$QT5_INPUT_DIRECTORY}/lib/cmake/Qt5Core)

IF(VECTOR_FIELD_RENDERER_SRC)
#	FIND_PATH(QtPath REQUIRED)

	message("Qt Directory = ${QtPath}")
	LIST(APPEND CMAKE_PREFIX_PATH "${QtPath}/lib/cmake/Qt5Core")
	LIST(APPEND CMAKE_PREFIX_PATH "${QtPath}/lib/cmake/Qt5Gui")
	LIST(APPEND CMAKE_PREFIX_PATH "${QtPath}/lib/cmake/Qt5Widgets")

	find_package(OpenGL REQUIRED)
	find_package(GLFW3 REQUIRED)
	find_package(GLEW REQUIRED)
	find_package(GLM REQUIRED)
	
#	FIND_PACKAGE(Qt5Core REQUIRED )
#	FIND_PACKAGE(Qt5Gui REQUIRED )
#	FIND_PACKAGE(Qt5Widgets REQUIRED )
#	FIND_PACKAGE(Irrlicht REQUIRED )

#    LIST(APPEND RFID_MobiVisGlobalExternalLibs ${IRRLICHT_LIBRARY})

#	Include_directories(${Qt5Core_INCLUDE_DIRS})
#	Include_directories(${Qt5Gui_INCLUDE_DIRS})
#    Include_directories(${Qt5Widgets_INCLUDE_DIRS})
#	Include_directories(${IRRLICHT_INCLUDE_DIR})

ENDIF(VECTOR_FIELD_RENDERER_SRC)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${VectorFieldRendererHome}/cmake")

SET(CommonconfProcessed TRUE)

ENDIF(NOT CommonconfProcessed)
