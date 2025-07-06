cmake_minimum_required(VERSION 3.25)

project(avr-learning)

set(AVR_APPEND_PLATFORM_TO_ARTIFACTS YES)

set(F_CPU 1000000)
set(BAUD  9600)
add_compile_definitions(
		F_CPU=${F_CPU}
		BAUD=${BAUD}
)
add_compile_options(-Os)

add_subdirectory(blinker)
add_subdirectory(pov_toy)
add_subdirectory(cyclon_eye)
add_subdirectory(bit_showoff)
add_subdirectory(buzzer)
add_subdirectory(serial_loopback)
add_subdirectory(serial_organ)
