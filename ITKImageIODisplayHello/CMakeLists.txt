
if(NOT DEFINED NAME_SUFFIX)
  message(FATAL_ERROR "NAME_SUFFIX is expected to be set")
endif()

set(factory_type "ImageIO")
set(factory_module "ITKIOImageBase")
set(factory_source
  itkDisplayHelloImageIO.cxx
  itkDisplayHelloImageIOFactory.cxx
  )

project(DisplayHello${factory_type}_${NAME_SUFFIX})

include(GenerateExportHeader)

message(STATUS "Configuring ${CMAKE_PROJECT_NAME}:${PROJECT_NAME}")

# --------------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------------

#
# ITK
#

set(${PROJECT_NAME}_ITK_COMPONENTS
  ${factory_module}
  )
find_package(
  ITK ${ITK_MINIMUM_REQUIRED_VERSION}
  COMPONENTS ${${PROJECT_NAME}_ITK_COMPONENTS} REQUIRED
  )
include(${ITK_USE_FILE})

# --------------------------------------------------------------------------
# IO Factory
# --------------------------------------------------------------------------

set(io_factory_name ${PROJECT_NAME})
add_library(${io_factory_name} SHARED
  ${factory_source}
  )
target_link_libraries(${io_factory_name} LINK_PUBLIC ${ITK_LIBRARIES})

set(itk-module "DisplayHello${factory_type}")
set_target_properties(${io_factory_name}
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${ITK${factory_type}DisplayHello_LIBRARY_OUTPUT_DIRECTORY}
    LIBRARY_OUTPUT_DIRECTORY ${ITK${factory_type}DisplayHello_LIBRARY_OUTPUT_DIRECTORY}
    COMPILE_DEFINITIONS "DISPLAYHELLO_${factory_type}_FACTORY_NAME=\"${PROJECT_NAME}\""
    DEFINE_SYMBOL ${itk-module}_EXPORTS
  )

generate_export_header(${io_factory_name}
  EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/${itk-module}Export.h
  EXPORT_MACRO_NAME ${itk-module}_EXPORT
  NO_EXPORT_MACRO_NAME ${itk-module}_HIDDEN
  STATIC_DEFINE ITK_STATIC )


itk_module_load(${factory_module})
set(${factory_type}_INCLUDE_DIRS ${${factory_module}_INCLUDE_DIRS} PARENT_SCOPE)
