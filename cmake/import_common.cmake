# Distributed under the OpenDDS License. See accompanying LICENSE
# file or http://www.opendds.org/license.html for details.
#
# Common system for to declare imported libraries and executables.

if(_OPENDDS_IMPORT_COMMON_CMAKE)
  return()
endif()
set(_OPENDDS_IMPORT_COMMON_CMAKE TRUE)

cmake_minimum_required(VERSION 3.3.2)

include(SelectLibraryConfigurations)

include("${CMAKE_CURRENT_LIST_DIR}/init.cmake")
if(NOT DEFINED ACE_ROOT OR NOT DEFINED TAO_ROOT)
  return()
endif()

macro(_opendds_append name value)
  string(TOUPPER "_OPENDDS_${name}" _var)
  list(APPEND "${_var}" "${value}")
  set("${_var}" "${${_var}}" PARENT_SCOPE)
endmacro()

set(_OPENDDS_ALL_GROUPS)
set(_OPENDDS_ALL_TARGETS)
set(_OPENDDS_ALL_LIBRARIES)
set(_OPENDDS_ALL_EXECUTABLES)
function(_opendds_group name)
  set(no_value_options)
  set(single_value_options)
  set(multi_value_options DEFAULT_REQUIRED)
  cmake_parse_arguments(arg
    "${no_value_options}" "${single_value_options}" "${multi_value_options}" ${ARGN})

  _opendds_append(ALL_GROUPS "${name}")
  set(_opendds_group_name "${name}" PARENT_SCOPE)
  string(TOUPPER "_OPENDDS_${name}" prefix)
  set(_opendds_group_prefix "${prefix}" PARENT_SCOPE)
  set("${prefix}_DEFAULT_REQUIRED" ${arg_DEFAULT_REQUIRED} PARENT_SCOPE)
  set("${prefix}_ALL_TARGETS" PARENT_SCOPE)
  set("${prefix}_ALL_LIBRARIES" PARENT_SCOPE)
  set("${prefix}_ALL_EXECUTABLES" PARENT_SCOPE)
endfunction()

function(_opendds_group_lib name)
  set(no_value_options)
  set(single_value_options MPC_NAME)
  set(multi_value_options DEPENDS)
  cmake_parse_arguments(arg
    "${no_value_options}" "${single_value_options}" "${multi_value_options}" ${ARGN})
  set(target "${_opendds_group_name}::${name}")

  _opendds_append("ALL_TARGETS" "${target}")
  _opendds_append("${_opendds_group_name}_ALL_TARGETS" "${target}")
  _opendds_append("ALL_LIBRARIES" "${target}")
  _opendds_append("${_opendds_group_name}_ALL_LIBRARIES" "${name}")

  string(TOUPPER "${name}" upper)
  set(prefix "${_opendds_group_prefix}_${upper}")
  set("${prefix}_DEPENDS" "${arg_DEPENDS}" PARENT_SCOPE)
  if(NOT DEFINED arg_MPC_NAME)
    set(arg_MPC_NAME "${name}")
  endif()
  set("${prefix}_MPC_NAME" "${arg_MPC_NAME}" PARENT_SCOPE)
endfunction()

function(_opendds_group_exe name)
  set(no_value_options)
  set(single_value_options MPC_NAME)
  set(multi_value_options DEPENDS EXTRA_BIN_DIRS)
  cmake_parse_arguments(arg
    "${no_value_options}" "${single_value_options}" "${multi_value_options}" ${ARGN})
  set(target "${_opendds_group_name}::${name}")

  _opendds_append("ALL_TARGETS" "${target}")
  _opendds_append("${_opendds_group_name}_ALL_TARGETS" "${target}")
  _opendds_append("ALL_EXECUTABLES" "${target}")
  _opendds_append("${_opendds_group_name}_ALL_EXECUTABLES" "${name}")

  string(TOUPPER "${name}" upper)
  set(prefix "${_opendds_group_prefix}_${upper}")
  set("${prefix}_DEPENDS" "${arg_DEPENDS}" PARENT_SCOPE)
  if(NOT DEFINED arg_MPC_NAME)
    set(arg_MPC_NAME "${name}")
  endif()
  set("${prefix}_MPC_NAME" "${arg_MPC_NAME}" PARENT_SCOPE)

  string(TOUPPER "${_opendds_group_name}" group_upper)
  set(bin_dirs "${${group_upper}_BIN_DIR}")
  if(arg_EXTRA_BIN_DIRS)
    list(APPEND bin_dirs ${arg_EXTRA_BIN_DIRS})
  endif()
  list(REMOVE_DUPLICATES bin_dirs)
  set("${prefix}_BIN_DIRS" "${bin_dirs}" PARENT_SCOPE)
endfunction()

function(_opendds_get_lib_filename filename_var group_name short_name)
  if(short_name STREQUAL "${group_name}")
    set(filename "${short_name}")
  else()
    set(filename "${group_name}_${short_name}")
  endif()
  set("${filename_var}" "${filename}" PARENT_SCOPE)
endfunction()

function(_opendds_find_our_libraries_for_config group libs config suffix)
  set(debug FALSE)
  if(imports IN_LIST OPENDDS_CMAKE_VERBOSE)
    set(debug TRUE)
  endif()

  string(TOUPPER "_OPENDDS_${group}" group_prefix)

  if(MSVC AND OPENDDS_STATIC)
    set(suffix "s${suffix}")
  endif()

  string(TOUPPER "${group}_LIB_DIR" lib_dir_var)
  set(lib_dir "${${lib_dir_var}}")

  foreach(lib ${libs})
    set(short_name "${lib}")
    set(target "${group}::${lib}")
    _opendds_get_lib_filename(lib "${group}" "${lib}")
    set(lib_file_base "${lib}${suffix}")
    string(TOUPPER "${group_prefix}_${short_name}" lib_prefix)
    string(TOUPPER "${lib}" upper)
    set(lib_var "${upper}_LIBRARY_${config}")
    set(found_var "${upper}_LIBRARY_FOUND")
    string(TOUPPER "${group}_IS_BEING_BUILT" group_is_being_built_var)
    set(group_is_being_built "${${group_is_being_built_var}}")

    if(TARGET "${target}")
      if(group_is_being_built)
        set(${lib_var} TARGET-TRUE CACHE INTERNAL "" FORCE)
        set(${found_var} TRUE CACHE INTERNAL "" FORCE)
      endif()
      if(debug)
        message(STATUS "${config} lib ${target} is already a target")
      endif()
      continue()
    endif()

    # If there are configuration types (like VS) and it doesn't find release,
    # then that prevents debug from being found.
    if(DEFINED "${found_var}" AND NOT "${${found_var}}" AND NOT CMAKE_CONFIGURATION_TYPES)
      if(debug)
        message(STATUS "lib ${target} already not found")
      endif()
      continue()
    endif()

    find_library(${lib_var} "${lib_file_base}" HINTS "${lib_dir}")
    if(${lib_var})
      set(${found_var} TRUE CACHE INTERNAL "" FORCE)

      # Workaround https://gitlab.kitware.com/cmake/cmake/-/issues/23249
      # These paths might be symlinks and IMPORTED_RUNTIME_ARTIFACTS seems to
      # copy symlinks verbatim, so resolve them now.
      set(lib_var_real "${lib_var}_REAL")
      get_filename_component(${lib_var_real} "${${lib_var}}" REALPATH)
      # find_library makes cache variables, so we have to override it.
      set(${lib_var} "${${lib_var_real}}" CACHE FILEPATH "" FORCE)

      if(debug)
        message(STATUS "${config} lib ${target} found: ${${lib_var_real}}")
      elseif(OPENDDS_CMAKE_VERBOSE)
        message(STATUS "${config} lib ${target} found")
      endif()

      if(MSVC AND NOT OPENDDS_STATIC)
        # find_library finds the ".lib" file on Windows, but if OpenDDS is not
        # static we also need the ".dll" file for IMPORTED_LOCATION and
        # IMPORTED_RUNTIME_ARTIFACTS to work correctly.
        find_file("${lib_var}_DLL" "${lib_file_base}.dll" HINTS "${lib_dir}")
      endif()
    elseif(NOT DEFINED ${found_var})
      if(debug)
        message(STATUS "${config} lib ${target} NOT FOUND")
      endif()
      set(${found_var} FALSE CACHE INTERNAL "" FORCE)
    endif()
  endforeach()
endfunction()

function(_opendds_find_executables group exes)
  set(debug FALSE)
  if(imports IN_LIST OPENDDS_CMAKE_VERBOSE)
    set(debug TRUE)
  endif()

  string(TOUPPER "${group}" group_upper)
  set(group_prefix "_OPENDDS_${group_upper}")
  set(group_is_being_built "${${group_upper}_IS_BEING_BUILT}")

  foreach(exe ${exes})
    set(target "${group}::${exe}")
    string(TOUPPER "${group_prefix}_${exe}" var)

    if(TARGET "${target}")
      if(group_is_being_built)
        set(${var} TRUE CACHE INTERNAL "" FORCE)
        set(${found_var} TRUE CACHE INTERNAL "" FORCE)
      endif()
      if(debug)
        message(STATUS "${config} exe ${target} is already a target")
      endif()
      continue()
    endif()

    find_program("${var}" NAMES "${exe}" HINTS ${${var}_BIN_DIRS})
  endforeach()
endfunction()

# Needs to be a macro because of select_library_configurations
macro(_opendds_find_group_targets group libs exes)
  if(MSVC)
    _opendds_find_our_libraries_for_config(${group} "${libs}" "RELEASE" "")
    _opendds_find_our_libraries_for_config(${group} "${libs}" "DEBUG" "d")
  elseif(OPENDDS_DEBUG)
    _opendds_find_our_libraries_for_config(${group} "${libs}" "DEBUG" "")
  else()
    _opendds_find_our_libraries_for_config(${group} "${libs}" "RELEASE" "")
  endif()

  foreach(_lib ${libs})
    string(TOUPPER "_OPENDDS_${group}_${_lib}_DEPENDS" _dep_var)
    if(NOT DEFINED "${_dep_var}")
      message(FATAL_ERROR "Library ${group}::${_lib} is missing a dependency list called ${_dep_var}!")
    endif()
    _opendds_get_lib_filename(_lib "${group}" "${_lib}")
    string(TOUPPER ${_lib} _lib_var)
    select_library_configurations(${_lib_var})
  endforeach()

  _opendds_find_executables("${group}" "${exes}")
endmacro()

function(_opendds_found_required_deps found_var required_deps)
  set(missing_deps)
  foreach(dep ${required_deps})
    if(NOT ${dep})
      list(APPEND missing_deps ${dep})
    endif()
  endforeach()

  if(missing_deps)
    message(SEND_ERROR "Missing required dependencies ${missing_deps}")
    set("${found_var}" FALSE PARENT_SCOPE)
  else()
    set("${found_var}" TRUE PARENT_SCOPE)
  endif()
endfunction()

function(_opendds_import_group_targets group libs exes)
  string(TOUPPER "${group}" group_upper)
  set(group_prefix "_OPENDDS_${group_upper}")

  macro(add_target_library_config target var_prefix config)
    set(lib_var "${var_prefix}_LIBRARY_${config}")
    set(lib_file "${${lib_var}}")
    if(EXISTS "${lib_file}")
      set_property(TARGET ${target}
        APPEND PROPERTY
        IMPORTED_CONFIGURATIONS ${config}
      )

      # Set any extra compiler and linker options that are needed to use the
      # libraries.
      foreach(from_libs ALL "JUST_${group_upper}")
        foreach(kind COMPILE LINK)
          set(options_var "OPENDDS_${from_libs}_LIBS_INTERFACE_${kind}_OPTIONS")
          if(DEFINED ${options_var})
            set_property(TARGET ${target}
              APPEND PROPERTY "INTERFACE_${kind}_OPTIONS" "${${options_var}}")
          endif()
        endforeach()
      endforeach()

      set(imploc "${lib_file}")
      if(MSVC)
        set_target_properties(${target}
          PROPERTIES
            "IMPORTED_IMPLIB_${config}" "${lib_file}"
        )
        set(dll "${lib_var}_DLL")
        if(DEFINED "${dll}")
          set(imploc "${${dll}}")
        endif()
      endif()
      set_target_properties(${target}
        PROPERTIES
          "IMPORTED_LINK_INTERFACE_LANGUAGES_${config}" "CXX"
          "IMPORTED_LOCATION_${config}" "${imploc}"
      )
    endif()
  endmacro()

  macro(add_target_library var_prefix include_dirs)
    set(target "${group}::${short_name}")
    string(TOUPPER "${group_prefix}_${short_name}" lib_prefix)

    if(NOT TARGET ${target} AND ${var_prefix}_LIBRARY_FOUND)
      add_library(${target} ${OPENDDS_LIBRARY_TYPE} IMPORTED GLOBAL)
      set_target_properties(${target}
        PROPERTIES
          INTERFACE_INCLUDE_DIRECTORIES "${include_dirs}"
          INTERFACE_LINK_LIBRARIES "${${prefix}_DEPENDS}"
          INTERFACE_COMPILE_DEFINITIONS "${${var_prefix}_COMPILE_DEFINITIONS}"
          INTERFACE_COMPILE_OPTIONS "${${var_prefix}_COMPILE_OPTIONS}"
      )

      add_target_library_config(${target} ${var_prefix} "RELEASE")
      add_target_library_config(${target} ${var_prefix} "DEBUG")
    endif()
  endmacro()

  foreach(lib ${libs})
    set(short_name "${lib}")
    string(TOUPPER "${group_prefix}_${lib}" prefix)
    _opendds_get_lib_filename(lib "${group}" "${lib}")
    string(TOUPPER ${lib} var_prefix)

    if(DEFINED "${var_prefix}_INCLUDE_DIRS")
      set(include_dirs "${${var_prefix}_INCLUDE_DIRS}")
    else()
      set(include_dirs "${${group_upper}_INCLUDE_DIRS}")
    endif()

    add_target_library(${var_prefix} "${include_dirs}")
  endforeach()

  foreach(exe ${exes})
    set(target "${group}::${exe}")
    string(TOUPPER "${group_prefix}_${exe}" path_var)
    set(path "${${path_var}}")
    if(TARGET "${target}")
      if(imports IN_LIST OPENDDS_CMAKE_VERBOSE)
        message(STATUS "exe ${target} is already a target")
      endif()
    else()
      add_executable(${target} IMPORTED GLOBAL)
      set_target_properties(${target}
        PROPERTIES
          IMPORTED_LOCATION "${path}"
      )
      if(imports IN_LIST OPENDDS_CMAKE_VERBOSE)
        message(STATUS "exe ${target}: ${path}")
      elseif(OPENDDS_CMAKE_VERBOSE)
        message(STATUS "exe ${target}")
      endif()
    endif()
  endforeach()
endfunction()

function(_opendds_scoped_list scoped_list_var list group)
  set(scoped_list)
  foreach(item ${list})
    list(APPEND scoped_list "${group}::${item}")
  endforeach()
  set("${scoped_list_var}" "${scoped_list}" PARENT_SCOPE)
endfunction()

function(opendds_get_library_dependencies deps_var)
  set(libs ${ARGN})
  set(passthrough FALSE)
  if(PASSTHROUGH IN_LIST libs)
    set(passthrough TRUE)
    list(REMOVE_ITEM libs PASSTHROUGH)
  endif()
  set(deps "${${deps_var}}")
  foreach(lib ${libs})
    if(NOT ${lib} IN_LIST deps)
      if(lib IN_LIST _OPENDDS_ALL_TARGETS)
        string(REPLACE "::" "_" dep_list_name "${lib}")
        string(TOUPPER "_OPENDDS_${dep_list_name}_DEPENDS" dep_list_name)
        if(DEFINED ${dep_list_name})
          opendds_get_library_dependencies(deps ${${dep_list_name}})
        endif()
        list(APPEND deps ${lib})
      elseif(passthrough)
        list(APPEND deps ${lib})
      endif()
    endif()
  endforeach()

  list(REMOVE_DUPLICATES deps)
  set(${deps_var} "${deps}" PARENT_SCOPE)
endfunction()
