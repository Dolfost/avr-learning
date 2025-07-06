cmake_minimum_required(VERSION 3.25)

project(serial_organ LANGUAGES C CXX ASM)

avr_add_executable(serial_organ)
target_sources(${serial_organ_ELF_TARGET} 
	PRIVATE
		main.c organ.c
)
