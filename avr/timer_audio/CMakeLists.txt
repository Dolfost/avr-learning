cmake_minimum_required(VERSION 3.25)

set(PROJ timer_audio)
project(${PROJ} LANGUAGES C CXX ASM)

avr_add_executable(${PROJ})
target_sources(${${PROJ}_ELF_TARGET} 
	PRIVATE
		main.c
)
target_link_libraries(${${PROJ}_ELF_TARGET} avrtools::avrtools)
