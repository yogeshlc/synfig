add_library(synfigapp SHARED "")

target_include_directories(synfigapp PUBLIC ${LIBXML_INCLUDE_DIRS})

target_sources(synfigapp
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/action.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/action_param.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/action_system.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/blineconvert.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/wplistconverter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/canvasinterface.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/cvs.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/inputdevice.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/instance.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/pluginmanager.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/settings.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/timegather.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/uimanager.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/value_desc.cpp"
)

include(actions/CMakeLists.txt)

install(
    TARGETS synfigapp
    DESTINATION lib
)
