cmake_minimum_required(VERSION 3.25)

project(serial_loopback LANGUAGES C CXX ASM)

avr_add_executable(serial_loopback)
target_sources(${serial_loopback_ELF_TARGET} 
	PRIVATE
		main.c
)
