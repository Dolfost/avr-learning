cmake_minimum_required(VERSION 3.25)

project(avrtools LANGUAGES C CXX ASM)

avr_add_library(avrtools)
target_sources(${avrtools_ELF_TARGET} 
	PRIVATE
		src/usart.c
		src/button.c
		src/speaker.c
	PUBLIC FILE_SET HEADERS BASE_DIRS include FILES
		include/avrtools/usart.h
		include/avrtools/button.h
		include/avrtools/speaker.h
)
add_library(avrtools::avrtools ALIAS ${avrtools_ELF_TARGET})
