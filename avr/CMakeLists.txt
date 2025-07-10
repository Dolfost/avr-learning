cmake_minimum_required(VERSION 3.25)

project(avr-learning-avr)

set(AVR_APPEND_PLATFORM_TO_ARTIFACTS YES)

set(F_CPU 1000000)
set(BAUD  9600)
add_compile_definitions(
		F_CPU=${F_CPU}
		BAUD=${BAUD}
)
add_compile_options(-Os)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions("-DDEBUG")
endif()


add_subdirectory(blinker)
add_subdirectory(pov_toy)
add_subdirectory(cyclon_eye)
add_subdirectory(bit_showoff)
add_subdirectory(buzzer)
add_subdirectory(serial_loopback)
add_subdirectory(serial_organ)
add_subdirectory(button)
add_subdirectory(debouncer)
add_subdirectory(music_box)
add_subdirectory(avrtools) # tools
add_subdirectory(light_sensor)
add_subdirectory(usart_audio_recorder)
add_subdirectory(night_light)
add_subdirectory(ldr_plotter)
