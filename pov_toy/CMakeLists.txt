cmake_minimum_required(VERSION 3.25)

project(pov_toy LANGUAGES C CXX ASM)

avr_add_executable(pov_toy)
target_compile_definitions(${pov_toy_ELF_TARGET} 
	PRIVATE 
		F_CPU=${F_CPU}
		BAUD=${BAUD}
)
target_sources(${pov_toy_ELF_TARGET} 
	PRIVATE
		main.c
)
target_compile_options(${pov_toy_ELF_TARGET} PRIVATE -Os)
