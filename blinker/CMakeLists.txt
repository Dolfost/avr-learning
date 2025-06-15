cmake_minimum_required(VERSION 3.25)

project(blinker LANGUAGES C CXX ASM)

avr_add_library(do_nothing)
target_sources(${do_nothing_ELF_TARGET}
	PUBLIC 
		lib.c 
	PUBLIC FILE_SET HEADERS 
		BASE_DIRS .
		FILES lib.h 
)

target_include_directories(${do_nothing_ELF_TARGET} PUBLIC src)

avr_add_executable(blinker)
target_compile_definitions(${blinker_ELF_TARGET} 
	PRIVATE 
		F_CPU=1000000
		BAUD=9600
)
target_sources(${blinker_ELF_TARGET} 
	PRIVATE
		main.c
)
target_compile_options(${blinker_ELF_TARGET} PRIVATE -Os)
target_link_libraries(${blinker_ELF_TARGET} PRIVATE ${do_nothing_ELF_TARGET})
