#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// Ein sehr simpler "Webserver" Simulation-Output
void start_web_server() {
    int pressure = 20; // Startdruck in mbar
    while (true) {
        // Wir simulieren einen Atemzyklus
        for(int i=0; i<10; ++i) {
            pressure = 20 + (i * 2); 
            // In einer echten App würde hier ein Socket-Listen stehen
            // Für die Demo simulieren wir die Log-Ausgabe, die K8s sieht
            std::cout << "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
            std::cout << "<html><body><h1>Hamilton Simulator Live</h1>";
            std::cout << "<p>Aktueller Beatmungsdruck: " << pressure << " mbar</p>";
            std::cout << "</body></html>" << std::endl;
            
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

int main() {
    std::cout << "Hamilton Ventilator Simulator gestartet..." << std::endl;
    start_web_server();
    return 0;
}
