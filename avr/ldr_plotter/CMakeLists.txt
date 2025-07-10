cmake_minimum_required(VERSION 3.25)

project(ldr_plotter LANGUAGES C CXX ASM)

avr_add_executable(ldr_plotter)
target_sources(${ldr_plotter_ELF_TARGET} 
	PRIVATE
		main.c
)
target_link_libraries(${ldr_plotter_ELF_TARGET} avrtools::avrtools)
