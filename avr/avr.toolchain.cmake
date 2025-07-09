# variables that could be set:
#  variable                          default value
#  AVR_PROGRAMMER                    usbasp
#  AVR_MCU                           atmega8
#  AVR_UPLOAD_BAUDRATE               <not set>
#  AVR_AVRDUDE_OPTIONS               <not set>
#  AVR_AVRDUDE_PORT                  usb
#  AVR_APPEND_PLATFORM_TO_ARTIFACTS  NO

# let CMake know that we are crosscompiling
set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# executables
find_program(AVRCPP      avr-g++     REQUIRED)
find_program(AVRC        avr-gcc	   REQUIRED)
find_program(AVRSTRIP    avr-strip   REQUIRED)
find_program(AVROBJCOPY  avr-objcopy REQUIRED)
find_program(AVROBJDUMP  avr-objdump REQUIRED)
find_program(AVRSIZE     avr-size    REQUIRED)
find_program(AVRDUDE     avrdude     REQUIRED)

# let the CMake know about the target platform compilers
set(CMAKE_CXX_COMPILER ${AVRCPP})
set(CMAKE_C_COMPILER   ${AVRC})
set(CMAKE_ASM_COMPILER ${AVRC})
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# toolchain identification
set(AVR YES)

# provide default values for variables
if(NOT AVR_PROGRAMMER) # set default programmer
	set(AVR_PROGRAMMER usbasp)
endif()
if(NOT AVR_MCU) # set default MCU
	set(AVR_MCU atmega8)
endif()
if(NOT AVR_AVRDUDE_PORT) # set default avrdude port
	set(AVR_AVRDUDE_PORT usb)
endif()

# process AVR_APPEND_PLATFORM_TO_ARTIFACTS
if(AVR_APPEND_PLATFORM_TO_ARTIFACTS) 
	set(TARGET_POSTFIX "-${AVR_MCU}")
else()
	set(TARGET_POSTFIX "")
endif()

# define base options for avrdude
set(AVR_AVRDUDE_BASE_OPTIONS -p ${AVR_MCU} -c ${AVR_PROGRAMMER} -P ${AVR_AVRDUDE_PORT})

# use AVR_AVRDUDE_BAUDRATE as baudrate for upload tool (if defined)
if(AVR_AVRDUDE_BAUDRATE)
	set(AVR_AVRDUDE_BASE_OPTIONS ${AVR_UAVRDUDEBASE_OPTIONS} -b ${AVR_AVRDUDE_BAUDRATE})
endif()


#    avr_add_executable(EXECUTABLE_NAME sources...)
# Creates cmake targets for EXECUTABLE_NAME. Also next variables get populated:
#	   - ${EXECUTABLE_NAME}
#	   - ${EXECUTABLE_NAME}_ELF_TARGET
#	   - ${EXECUTABLE_NAME}_HEX_TARGET
#	   - ${EXECUTABLE_NAME}_LST_TARGET
#	   - ${EXECUTABLE_NAME}_MAP_TARGET
#	   - ${EXECUTABLE_NAME}_EEPROM_TARGET
# for example you can provide target compile options with
#     avr_add_executable(blinker blinker.c)
#     target_compile_options(${blinker_ELF_TARGET} PRIVATE -Os)
function(avr_add_executable EXECUTABLE_NAME)
	set(elf_file ${EXECUTABLE_NAME}${TARGET_POSTFIX}.elf)
	set(hex_file ${EXECUTABLE_NAME}${TARGET_POSTFIX}.hex)
	set(lst_file ${EXECUTABLE_NAME}${TARGET_POSTFIX}.lst)
	set(map_file ${EXECUTABLE_NAME}${TARGET_POSTFIX}.map)
	set(eeprom_image ${EXECUTABLE_NAME}${TARGET_POSTFIX}-eeprom.hex)

	set(${EXECUTABLE_NAME}_ELF_TARGET ${elf_file} PARENT_SCOPE)
	set(${EXECUTABLE_NAME}_HEX_TARGET ${hex_file} PARENT_SCOPE)
	set(${EXECUTABLE_NAME}_LST_TARGET ${lst_file} PARENT_SCOPE)
	set(${EXECUTABLE_NAME}_MAP_TARGET ${map_file} PARENT_SCOPE)
	set(${EXECUTABLE_NAME}_EEPROM_TARGET ${eeprom_file} PARENT_SCOPE)

	add_executable(${elf_file} EXCLUDE_FROM_ALL ${ARGN})

	set_target_properties(${elf_file}
		PROPERTIES
			 COMPILE_FLAGS "-mmcu=${AVR_MCU}"
			 LINK_FLAGS "-mmcu=${AVR_MCU} -Wl,--gc-sections -mrelax -Wl,-Map,${map_file}"
	)

	add_custom_command(
		COMMAND ${AVROBJCOPY} -j .text -j .data -O ihex ${elf_file} ${hex_file}
		COMMAND ${AVRSIZE} ${elf_file}
		OUTPUT ${hex_file}
		DEPENDS ${elf_file}
	)

	add_custom_command(
		COMMAND ${AVROBJDUMP} -d ${elf_file} > ${lst_file}
		OUTPUT ${lst_file}
		DEPENDS ${elf_file}
	)

	add_custom_command(
			COMMAND ${AVROBJCOPY} -j .eeprom --set-section-flags=.eeprom=alloc,load
				--change-section-lma .eeprom=0 --no-change-warnings
				-O ihex ${elf_file} ${eeprom_image}
			OUTPUT ${eeprom_image}
			DEPENDS ${elf_file}
	)

	add_custom_target(${EXECUTABLE_NAME} ALL
		DEPENDS ${hex_file} ${lst_file} ${eeprom_image}
	)
	set_target_properties(${EXECUTABLE_NAME}
		PROPERTIES OUTPUT_NAME "${elf_file}"
	)

	# clean
	get_directory_property(clean_files ADDITIONAL_MAKE_CLEAN_FILES)
	set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${map_file}")

	# upload - with avrdude
	add_custom_target(upload_${EXECUTABLE_NAME}
		${AVRDUDE} ${AVR_AVRDUDE_BASE_OPTIONS} ${AVR_AVRDUDE_OPTIONS} -U flash:w:${hex_file}
		DEPENDS ${hex_file}
		COMMENT "Uploading ${hex_file} to ${AVR_MCU} using ${AVR_PROGRAMMER}"
	)

	# upload eeprom only - with avrdude
	add_custom_target(upload_${EXECUTABLE_NAME}_eeprom
		${AVRDUDE} ${AVR_AVRDUDE_BASE_OPTIONS} ${AVR_AVRDUDE_OPTIONS} -U eeprom:w:${eeprom_image}
		DEPENDS ${eeprom_image}
		COMMENT "Uploading ${eeprom_image} to ${AVR_MCU} using ${AVR_PROGRAMMER}"
	)

	# disassemble
	add_custom_target(disassemble_${EXECUTABLE_NAME}
			${AVROBJDUMP} -h -S ${elf_file} > ${EXECUTABLE_NAME}.lst
			DEPENDS ${elf_file}
	)
endfunction()

#    avr_add_library(LIBRARY_NAME sources...)
# Creates cmake library target for LIBRARY_NAME with ooptional platform
# postfix. Also next variables get populated:
#	   - ${LIBRARY_NAME}_ELF_TARGET
# for example you can provide target compile options with
#     avr_add_library(blinker blinker.c)
#     target_compile_options(${blinker_ELF_TARGET} PRIVATE -Os)
function(avr_add_library LIBRARY_NAME)
		set(lib_file ${LIBRARY_NAME}${TARGET_POSTFIX}.elf)
		set (${LIBRARY_NAME}_ELF_TARGET ${lib_file} PARENT_SCOPE)

    add_library(${lib_file} STATIC ${ARGN})

    set_target_properties(${lib_file}
			PROPERTIES
				COMPILE_FLAGS "-mmcu=${AVR_MCU}"
				OUTPUT_NAME "${lib_file}"
    )

	if(NOT TARGET ${LIBRARY_NAME})
		add_custom_target(${LIBRARY_NAME} ALL
			DEPENDS ${lib_file}
		)
		set_target_properties(${LIBRARY_NAME}
			PROPERTIES OUTPUT_NAME "${lib_file}"
		)
	endif()
endfunction(avr_add_library)
