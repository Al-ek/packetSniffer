#include "bluetooth_interface.hpp"

bool bluetooth_interface::run() {
    int dev_id = hci_get_route(nullptr);
    if (dev_id < 0) {
        std::cerr << "No Bluetooth adapter found" << std::endl;
        return false;
    }

    int sock = hci_open_dev(dev_id);
    if (sock < 0) {
        std::cerr << "Failed to open Bluetooth device." << std::endl;
        return false;
    }

    // Set filter to capture all packets
    struct hci_filter filter;
    hci_filter_clear(&filter);
    hci_filter_all_ptypes(&filter);
    hci_filter_all_events(&filter);
    if (setsockopt(sock, SOL_HCI, HCI_FILTER, &filter, sizeof(filter)) < 0) {
        std::cerr << "Failed to set socket options." << std::endl;
        close(sock);
        return false;
    }

    // Buffer for incoming packets
    const int buf_size = 1024;
    unsigned char buf[buf_size];

    std::cout << "Listening for Bluetooth packets. Press Ctrl+C to stop.\n";

    while (true) {
        ssize_t len = read(sock, buf, buf_size);
        if (len < 0) {
            std::cerr << "Error reading from socket." << std::endl;
            close(sock);
            return false;
        }

        std::cout << "[Bluetooth] Received " << len << " bytes: ";

        // For demonstration, print first 16 bytes in hex
        size_t to_print = (len < 16) ? len : 16;
        std::cout << "Data (hex): ";
        for (size_t i = 0; i < to_print; i++) {
            printf("%02X ", buf[i]);
        }
        std::cout << std::endl;
    }

    // Never reached but good practice
    close(sock);
    return true;
}
