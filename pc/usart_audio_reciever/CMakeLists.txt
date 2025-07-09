project(usart_audio_reciever LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS 
	SerialPort
)

qt_standard_project_setup()

qt_add_executable(reciever reciever.cpp)

target_link_libraries(reciever PRIVATE
	Qt6::SerialPort
)
