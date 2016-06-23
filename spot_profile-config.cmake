if( CMAKE_VERSION VERSION_LESS 2.8.3 )
    message( FATAL_ERROR "spot_profile requires at least CMake version 2.8.3" )
endif()

if( NOT TARGET spot_profile )

    add_library( spot_profile STATIC
        ${CMAKE_CURRENT_LIST_DIR}/spot_profile.cpp
        ${CMAKE_CURRENT_LIST_DIR}/spot_profile.hpp
        )

    target_include_directories( spot_profile
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
        )

endif()

