cmake_minimum_required(VERSION 3.25)

project(debouncer LANGUAGES C CXX ASM)

avr_add_executable(debouncer)
target_sources(${debouncer_ELF_TARGET} 
	PRIVATE
		main.c
)
