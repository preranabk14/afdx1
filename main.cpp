#include <iostream>
#include <vector>
// Hypothetical AFDX library
#include <libafdx.h>

int main() {
    // Initialize AFDX stack
    if (!afdx_init()) {
        std::cerr << "Failed to initialize AFDX stack." << std::endl;
        return 1;
    }

    // Define and configure a Virtual Link (VL)
    VirtualLink vl;
    vl.id = 1;
    vl.bandwidth = 100000; // in bits per second
    vl.latency = 10;       // in milliseconds

    if (!afdx_configure_vl(&vl)) {
        std::cerr << "Failed to configure Virtual Link." << std::endl;
        afdx_cleanup();
        return 1;
    }

    // Data array to convert and send
    std::vector<uint8_t> data = {1, 2, 3, 4, 5}; // Example data array

    // Encapsulate data into AFDX frame
    AFDXFrame frame;
    if (!afdx_encapsulate(&vl, data.data(), data.size(), &frame)) {
        std::cerr << "Failed to encapsulate data into AFDX frame." << std::endl;
        afdx_cleanup();
        return 1;
    }

    // Send AFDX frame
    if (!afdx_send(&frame)) {
        std::cerr << "Failed to send AFDX frame." << std::endl;
        afdx_cleanup();
        return 1;
    }

    std::cout << "Data sent successfully in AFDX format." << std::endl;

    // Cleanup
    afdx_cleanup();
    return 0;
}
