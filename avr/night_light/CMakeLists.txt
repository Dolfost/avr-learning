cmake_minimum_required(VERSION 3.25)

project(night_light LANGUAGES C CXX ASM)

avr_add_executable(night_light)
target_sources(${night_light_ELF_TARGET} 
	PRIVATE
		main.c
)
target_link_libraries(${night_light_ELF_TARGET} avrtools::avrtools)
