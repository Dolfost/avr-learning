set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

find_program(AVRCPP   avr-g++     REQUIRED)
find_program(AVRC     avr-gcc	    REQUIRED)
find_program(AVRSTRIP avr-strip		REQUIRED)
find_program(OBJCOPY  avr-objcopy REQUIRED)
find_program(OBJDUMP  avr-objdump REQUIRED)
find_program(AVRSIZE  avr-size    REQUIRED)
find_program(AVRDUDE  avrdude     REQUIRED)

set(CMAKE_CXX_COMPILER ${AVRCPP})
set(CMAKE_C_COMPILER   ${AVRC})
set(CMAKE_ASM_COMPILER ${AVRC})

execute_process(
	COMMAND ${AVRCPP} -print-search-dirs
	OUTPUT_VARIABLE AVR_SEARCH_DIRS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REGEX MATCH "install: (.+)" AVR_INSTALL_DIR "${AVR_SEARCH_DIRS}")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_FIND_ROOT_PATH ${AVR_INSTALL_DIR})
