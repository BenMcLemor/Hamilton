cmake_minimum_required(VERSION 3.10)

# Projektname
project(HamiltonVentilator VERSION 1.0 LANGUAGES CXX)

# C++ Standard festlegen (wichtig für moderne Medizintechnik)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Das ausführbare Programm definieren
add_executable(ventilator_app hamilton_logic.cpp)

# Hier könnten später Bibliotheken hinzugefügt werden
