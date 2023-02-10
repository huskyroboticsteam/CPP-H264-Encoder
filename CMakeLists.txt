cmake_minimum_required(VERSION 3.12)

# Include some helper packages for installation
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

project(H264Encoder
  LANGUAGES C CXX
  VERSION 1.1.1)

add_library(H264Encoder STATIC
  src/encoder.cpp)
# find_package(x264 REQUIRED)
target_link_libraries(H264Encoder x264 avutil avcodec avformat swscale)

### Installation config ###

# If the project name is defined (i.e. if this project is not being included as
# a submodule)
if (DEFINED PROJECT_NAME)
  # Install the static library to the system, and export the list of installed
  # targets to h264encoder-targets
  install(TARGETS H264Encoder
	EXPORT h264encoder-targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
  # Install the header files to the system
  install(FILES src/encoder.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/H264Encoder)

  # Install the list of targets to the system
  install(EXPORT h264encoder-targets
	FILE H264EncoderTargets.cmake
	NAMESPACE H264Encoder::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/H264Encoder)

  # Generate a CMake package configuration file for the library
  configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/H264EncoderConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/H264EncoderConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/H264Encoder)
  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/H264EncoderConfigVersion.cmake
    VERSION ${CMAKE_PROJECT_VERSION}
    COMPATIBILITY SameMinorVersion)
  # Install the CMake package configuration file
  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/H264EncoderConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/H264EncoderConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/H264Encoder)

  ### Packaging configuration ###
  # Borrowed/adapted from https://www.scivision.dev/cmake-cpack-basic/
  set(CPACK_GENERATOR "DEB")
  set(CPACK_PACKAGE_NAME "h264encoder")
  # Version format: major.minor.patch
  set(CPACK_PACKAGE_VERSION "${CMAKE_PROJECT_VERSION}")
  set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION})
  set(CPACK_PACKAGE_CONTACT "Husky Robotics Team <uwrobots@uw.edu>")
  set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
  set(CPACK_PACKAGE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  install(FILES ${CPACK_RESOURCE_FILE_README}
	DESTINATION share/docs/${PROJECT_NAME})

  include(CPack)

endif()
