if (NOT TARGET pico_lhe)
    add_library(pico_lhe INTERFACE)

    target_sources(pico_lhe INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/lhe.c
    )

    target_include_directories(pico_lhe INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}
    )

    target_link_libraries(pico_lhe INTERFACE
            pico_stdlib
            hardware_adc
            hardware_gpio
    )
endif()