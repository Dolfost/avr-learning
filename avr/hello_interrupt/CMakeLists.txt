cmake_minimum_required(VERSION 3.25)

project(hello_interrupt LANGUAGES C CXX ASM)

avr_add_executable(hello_interrupt)
target_sources(${hello_interrupt_ELF_TARGET} 
	PRIVATE
		main.c
)
target_link_libraries(${hello_interrupt_ELF_TARGET} avrtools::avrtools)
