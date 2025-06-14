#ifndef BLUETOOTH_INTERFACE_HPP
#define BLUETOOTH_INTERFACE_HPP

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>


class bluetooth_interface {
public:
    bool run(); 
};

#endif
