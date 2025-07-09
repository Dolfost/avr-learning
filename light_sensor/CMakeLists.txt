cmake_minimum_required(VERSION 3.25)

project(light_sensor LANGUAGES C CXX ASM)

avr_add_executable(light_sensor)
target_sources(${light_sensor_ELF_TARGET} 
	PRIVATE
		main.c
)
target_link_libraries(${light_sensor_ELF_TARGET} avrtools::avrtools)
