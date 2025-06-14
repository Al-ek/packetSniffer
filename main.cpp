#include "wi-fi/wi-fi_interface.hpp"
#include "bluetooth/bluetooth_interface.hpp"

#include <thread>
#include <iostream>

int main() {
    wifi_interface wifi;
    bluetooth_interface bluetooth;

    // Launch wifi.run() in a new thread
    std::thread wifiThread([&]() {
        if (!wifi.run()) {
            std::cerr << "Wi-Fi capture stopped or failed.\n";
        }
    });

    // Launch bluetooth.run() in another thread
    std::thread bluetoothThread([&]() {
        if (!bluetooth.run()) {
            std::cerr << "Bluetooth capture stopped or failed.\n";
        }
    });

    // Wait for both threads to finish (blocking)
    wifiThread.join();
    bluetoothThread.join();

    return 0;
}
