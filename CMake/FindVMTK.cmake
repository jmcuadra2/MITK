find_path(VMTK_INCLUDE_DIR
  NAMES vtkvmtkConfigure.h
  PATHS ${MITK_EXTERNAL_PROJECT_PREFIX}
  PATH_SUFFIXES include/vmtk
)

set(VMTK_LIBRARY_DIR "${MITK_EXTERNAL_PROJECT_PREFIX}/lib/vmtk")

find_library(VMTK_COMMON_LIB vtkvmtkCommon ${VMTK_LIBRARY_DIR})
find_library(VMTK_COMPUTATIONAL_GEOMETRY_LIB vtkvmtkComputationalGeometry ${VMTK_LIBRARY_DIR})
find_library(VMTK_DIFFERENTIAL_GEOMETRY_LIB vtkvmtkDifferentialGeometry ${VMTK_LIBRARY_DIR})
find_library(VMTK_IO_LIB vtkvmtkIO ${VMTK_LIBRARY_DIR})
find_library(VMTK_ITK_LIB vtkvmtkITK ${VMTK_LIBRARY_DIR})
find_library(VMTK_MISC_LIB vtkvmtkMisc ${VMTK_LIBRARY_DIR})
find_library(VMTK_SEGMENTATION_LIB vtkvmtkSegmentation ${VMTK_LIBRARY_DIR})

find_package_handle_standard_args(VMTK DEFAULT_MSG
  VMTK_INCLUDE_DIR
  VMTK_COMMON_LIB
  VMTK_COMPUTATIONAL_GEOMETRY_LIB
  VMTK_DIFFERENTIAL_GEOMETRY_LIB
  VMTK_IO_LIB
  VMTK_ITK_LIB
  VMTK_MISC_LIB
  VMTK_SEGMENTATION_LIB
)

if(VMTK_FOUND)
  set(VMTK_INCLUDE_DIRS ${VMTK_INCLUDE_DIR})
  set(VMTK_LIBRARIES
    ${VMTK_COMMON_LIB}
    ${VMTK_COMPUTATIONAL_GEOMETRY_LIB}
    ${VMTK_DIFFERENTIAL_GEOMETRY_LIB}
    ${VMTK_IO_LIB}
    ${VMTK_ITK_LIB}
    ${VMTK_MISC_LIB}
    ${VMTK_SEGMENTATION_LIB}
  )
endif()

mark_as_advanced(
  VMTK_INCLUDE_DIR
  VMTK_COMMON_LIB
  VMTK_COMPUTATIONAL_GEOMETRY_LIB
  VMTK_DIFFERENTIAL_GEOMETRY_LIB
  VMTK_IO_LIB
  VMTK_ITK_LIB
  VMTK_MISC_LIB
  VMTK_SEGMENTATION_LIB
)
