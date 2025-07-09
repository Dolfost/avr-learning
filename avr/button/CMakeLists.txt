cmake_minimum_required(VERSION 3.25)

project(button LANGUAGES C CXX ASM)

avr_add_executable(button)
target_sources(${button_ELF_TARGET} 
	PRIVATE
		main.c
)
