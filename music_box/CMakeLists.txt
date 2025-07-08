cmake_minimum_required(VERSION 3.25)

project(music_box LANGUAGES C CXX ASM)

avr_add_executable(music_box)
target_sources(${music_box_ELF_TARGET} 
	PRIVATE
		main.c
)
