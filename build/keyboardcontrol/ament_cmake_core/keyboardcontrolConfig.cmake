# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_keyboardcontrol_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED keyboardcontrol_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(keyboardcontrol_FOUND FALSE)
  elseif(NOT keyboardcontrol_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(keyboardcontrol_FOUND FALSE)
  endif()
  return()
endif()
set(_keyboardcontrol_CONFIG_INCLUDED TRUE)

# output package information
if(NOT keyboardcontrol_FIND_QUIETLY)
  message(STATUS "Found keyboardcontrol: 0.0.0 (${keyboardcontrol_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'keyboardcontrol' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${keyboardcontrol_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(keyboardcontrol_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${keyboardcontrol_DIR}/${_extra}")
endforeach()
