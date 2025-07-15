cmake_minimum_required(VERSION 3.25)

project(usart_audio_recorder LANGUAGES C CXX ASM)

avr_add_executable(usart_audio_recorder)
target_sources(${usart_audio_recorder_ELF_TARGET} 
	PRIVATE
		main.c
)
target_link_libraries(${usart_audio_recorder_ELF_TARGET} avrtools::avrtools)
