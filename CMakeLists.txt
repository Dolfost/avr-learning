cmake_minimum_required(VERSION 3.25)

project(avr-learning)

set(AVR_PROGRAMMER usbasp)
set(AVR_MCU        atmega168a)
set(AVR_APPEND_PLATFORM_TO_ARTIFACTS YES)

set(F_CPU 1000000)
set(BAUD  9600)

add_subdirectory(blinker)
add_subdirectory(pov_toy)
