# https://decovar.dev/blog/2021/03/08/cmake-cpp-library
# https://medium.com/@kkunalsharma825/install-and-export-in-cmake-5c26d20ff715
# For CMAKE_INSTALL_INCLUDEDIR definition
include(GNUInstallDirs)

# random_events
find_package(random_events CONFIG REQUIRED)

# Build libraries
add_executable(random_events_client client.cpp
        include/client.h
)
include_directories(${random_events_SOURCE_DIR}/src/random_events/include)
target_include_directories(random_events_client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(random_events_client PUBLIC random_events)

set(HEADER_FILES 
    include/client.h 
)
set_target_properties(random_events_client PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

# Install the main random_events library
install(
        TARGETS random_events_client
        EXPORT ${PROJECT_NAME}Targets
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT runtime
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT dev
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/client_program" COMPONENT dev
)
