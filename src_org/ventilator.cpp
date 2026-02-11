#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

// Funktion, um das Szenario zu simulieren
void run_simulation(std::string scenario) {
    int pressure = 0;
    while (true) {
        if (scenario == "STRESS_TEST") {
            pressure = 40 + (rand() % 20); // Hoher Druck für Alarm-Tests
            std::cout << "[ALARM] Stress-Test aktiv! Druck: " << pressure << " mbar" << std::endl;
        } else {
            pressure = 15 + (rand() % 5);  // Normaler Atemdruck
            std::cout << "[INFO] Normalbetrieb. Druck: " << pressure << " mbar" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

// Minimaler Webserver-Thread
void start_web_server(int port, std::string scenario) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Web-Interface auf Port " << port << " gestartet..." << std::endl;

    while (true) {
        int new_socket = accept(server_fd, NULL, NULL);
        std::string response = 
            "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
            "<html><body><h1>Hamilton Simulator</h1>"
            "<p>Szenario: <b>" + scenario + "</b></p>"
            "<p>Status: <span style='color:green'>Online</span></p>"
            "</body></html>";
        send(new_socket, response.c_str(), response.length(), 0);
        close(new_socket);
    }
}

int main() {
    // 1. Szenario aus Umgebungsvariable lesen
    const char* env_val = std::getenv("TEST_SCENARIO");
    std::string scenario = (env_val != nullptr) ? env_val : "NORMAL";

    std::cout << "=== Hamilton Simulator gestartet ===" << std::endl;
    std::cout << "Gewaeltes Szenario: " << scenario << std::endl;

    // 2. Webserver in eigenem Thread starten (für den Ingress)
    std::thread web_thread(start_web_server, 8080, scenario);
    
    // 3. Simulation im Haupt-Thread starten
    run_simulation(scenario);

    web_thread.join();
    return 0;
}
