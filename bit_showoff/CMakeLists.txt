cmake_minimum_required(VERSION 3.25)

project(bit_showoff LANGUAGES C CXX ASM)

avr_add_executable(bit_showoff)
target_sources(${bit_showoff_ELF_TARGET} 
	PRIVATE
		main.c
)
