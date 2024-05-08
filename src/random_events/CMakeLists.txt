# https://decovar.dev/blog/2021/03/08/cmake-cpp-library
# https://medium.com/@kkunalsharma825/install-and-export-in-cmake-5c26d20ff715
# For CMAKE_INSTALL_INCLUDEDIR definition
include(GNUInstallDirs)

# Export [random_events] as a cmake-built package
# Needed to set the namespace for both the export targets and the alias libraries.
set(cmake_package_name random_events CACHE INTERNAL "")

# Create the CMake package file descriptors
include(CMakePackageConfigHelpers)
set(targets_export_name ${cmake_package_name}Targets CACHE INTERNAL "")
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated" CACHE INTERNAL "")
set(cmake_files_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${cmake_package_name}")
set(version_file "${generated_dir}/${cmake_package_name}ConfigVersion.cmake")
write_basic_package_version_file(${version_file} VERSION ${RANDOM_EVENTS_VERSION} COMPATIBILITY AnyNewerVersion)
install(EXPORT ${targets_export_name}
        COMPONENT "${PROJECT_NAME}"
        NAMESPACE ${cmake_package_name}::
        DESTINATION ${cmake_files_install_dir})

# Generate config_file (<pkg_name>Config.cmake)
set(include_install_dir ${CMAKE_INSTALL_INCLUDEDIR}/random_events
    CACHE PATH "Location of header files")
set(sysconfig_install_dir ${CMAKE_INSTALL_SYSCONFDIR}/random_events
    CACHE PATH "Location of configuration files")
set(config_file "${generated_dir}/${cmake_package_name}Config.cmake")
configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in" "${config_file}"
                              INSTALL_DESTINATION ${cmake_files_install_dir}
                              PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_SYSCONFDIR
)

install(FILES ${version_file} ${config_file}
        COMPONENT "${PROJECT_NAME}"
        DESTINATION ${cmake_files_install_dir}
)

# Build libraries
add_library(random_events interval.cpp
        include/variable.h
        include/set.h
        include/product_algebra.h
        include/interval.h
        set.cpp
        product_algebra.cpp
        sigma_algebra.cpp
)
target_include_directories(random_events PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(HEADER_FILES 
    include/interval.h 
    include/product_algebra.h
    include/set.h
    include/sigma_algebra.h
    include/variable.h
)
set_target_properties(random_events PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

# Install the main random_events library
install(
        TARGETS random_events
        EXPORT ${PROJECT_NAME}Targets
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT runtime
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT dev
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/random_events" COMPONENT dev
)
#OR
# Install all header files for the main random_events library
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ #Note the trailing / to signify copying files in the folder only (not the folder itself)
#        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/random_events
#        FILES_MATCHING REGEX ".*\\.(h|inl)$")
