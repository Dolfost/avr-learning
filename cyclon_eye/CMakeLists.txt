cmake_minimum_required(VERSION 3.25)

project(cyclon_eye LANGUAGES C CXX ASM)

avr_add_executable(cyclon_eye)
target_sources(${cyclon_eye_ELF_TARGET} 
	PRIVATE
		main.cpp
)
