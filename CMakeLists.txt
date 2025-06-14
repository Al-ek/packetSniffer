cmake_minimum_required(VERSION 3.10)
project(packetSniffer)
set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PCAP REQUIRED libpcap)
pkg_check_modules(Bluez REQUIRED bluez)

include_directories(
    ${CMAKE_SOURCE_DIR}/wi-fi
    ${CMAKE_SOURCE_DIR}/bluetooth
)

add_executable(packetSniffer 
    main.cpp 
    wi-fi/wifi_interface.cpp
    bluetooth/bluetooth_interface.cpp
)

target_link_libraries(packetSniffer ${PCAP_LIBRARIES} bluetooth)
