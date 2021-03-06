## Command line synfig binary
add_executable(synfig_bin main.cpp)
set_target_properties(synfig_bin PROPERTIES OUTPUT_NAME synfig)

target_sources(synfig_bin
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/definitions.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/joblistprocessor.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/optionsprocessor.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/printing_functions.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/renderprogress.cpp"
)

target_link_libraries(synfig_bin synfig)
target_link_libraries(synfig_bin
    ${Boost_SYSTEM_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARIES}
    ${Boost_PROGRAM_OPTIONS_LIBRARIES}
    ${Boost_CHRONO_LIBRARIES}
)

install (
    TARGETS synfig_bin
    DESTINATION bin
)
