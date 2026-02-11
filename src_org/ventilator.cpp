// meta-hamilton/recipes-simulator/ventilator/files/ventilator.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <fstream>
#include <random>

class VentilatorSimulator {
private:
    std::vector<std::string> states;
    std::default_random_engine generator;
    std::normal_distribution<double> o2_distribution{95.0, 2.0};  // O2-Ziel: 95% ±2%
    std::normal_distribution<double> pressure_distribution{20.0, 1.5}; // Druck: 20 cmH2O ±1.5
    int cycle_count;

public:
    VentilatorSimulator() : cycle_count(0) {
        states = {
            "NORMAL BREATHING", 
            "O2 ENRICHMENT ACTIVE", 
            "PRESSURE STABILIZING", 
            "ALARM CHECK OK"
        };
    }

    void simulateCycle() {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        double o2 = o2_distribution(generator);
        double pressure = pressure_distribution(generator);
        
        // Medizinisches Log-Format (Hamilton-kompatibel)
        std::cout << "[" << std::ctime(&now) << "] "
                  << "DEVICE: ventilator-sim | "
                  << "O2: " << std::round(o2 * 10) / 10 << "% | "
                  << "PEEP: " << std::round(pressure * 10) / 10 << " cmH2O | "
                  << "STATE: " << states[cycle_count % 4] << " | "
                  << "CYCLE: " << cycle_count++ << std::endl;

        // Metriken für Monitoring (wird von systemd gejourd)
        std::ofstream metrics("/var/log/ventilator_metrics.log", std::ios::app);
        if(metrics.is_open()) {
            metrics << now << "," 
                    << std::round(o2 * 10) / 10 << ","
                    << std::round(pressure * 10) / 10 << ","
                    << states[cycle_count % 4] << std::endl;
            metrics.close();
        }
    }

    void run() {
        std::cout << "=== HAMILTON MEDICAL VENTILATOR SIMULATOR ===" << std::endl;
        std::cout << "Version: 1.0.0 (Yocto Native Build)" << std::endl;
        std::cout << "Safety Level: IEC 62304 Class C" << std::endl;
        std::cout << "=============================================" << std::endl;
        
        while (true) {
            simulateCycle();
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
};

int main() {
    VentilatorSimulator simulator;
    simulator.run();
    return 0;
}
