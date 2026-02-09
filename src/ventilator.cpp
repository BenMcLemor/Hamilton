#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

int main() {
    std::cout << "--- HAMILTON MEDICAL: C++ SIMULATOR STARTING ---" << std::endl;
    
    std::vector<std::string> states = {
        "NORMAL BREATHING", 
        "O2 ENRICHMENT ACTIVE", 
        "PRESSURE STABILIZING", 
        "ALARM CHECK OK"
    };

    int i = 0;
    while (true) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "[" << std::ctime(&now) << "] "
                  << "SIM-VAL: " << (rand() % 20 + 90) << "% O2 | "
                  << "STATE: " << states[i % 4] << std::endl;
        
        i++;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}
