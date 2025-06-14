#include "wi-fi_interface.hpp"

void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet) {
    std::cout << "[Wi-Fi] Receievd " << header->len << " bytes: ";
    for (int i = 0; i < header->len; ++i) {
        printf("%02x ", packet[i]);
    }
    std::cout << std::endl;
}
bool wifi_interface::run() {
    std::system("sudo ip link set wlp0s20f3 down");
    std::system("sudo iw dev wlp0s20f3 set type monitor");
    std::system("sudo ip link set wlp0s20f3 up");

    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *handle = pcap_open_live("wlp0s20f3", BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Failed to open device: " << errbuf << std::endl;
        return false;
    }

    std::cout << "Capturing packets on interface: wlp0s20f3" << std::endl;
    pcap_loop(handle, -1, packet_handler, nullptr);

    pcap_close(handle);
    return true;
}
