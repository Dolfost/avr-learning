cmake_minimum_required(VERSION 3.25)

project(avr-learning)

set(AVR_PROGRAMMER usbasp)
set(AVR_MCU        atmega168a)

add_subdirectory(blinker)
