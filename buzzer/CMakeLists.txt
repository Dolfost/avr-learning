cmake_minimum_required(VERSION 3.25)

project(buzzer LANGUAGES C CXX ASM)

avr_add_executable(buzzer)
target_sources(${buzzer_ELF_TARGET} 
	PRIVATE
		main.c
)
