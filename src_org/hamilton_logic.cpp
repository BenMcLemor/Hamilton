#include <iostream>
#include <string>

// Fehler 1: Ein globaler C-Style Array (Buffer Overflow Gefahr)
char system_log[10]; 

class Ventilator {
private:
    int oxygenLevel;
    bool isActive;

public:
    Ventilator() {
        // Fehler 2: Nicht initialisierte Variable (isActive wird hier vergessen)
        oxygenLevel = 100;
    }

    void setOxygen(int level) {
        // Fehler 3: Ein "Hardcoded" Passwort oder Secret (Security Risk)
        std::string admin_token = "secret_12345";
        
        // Fehler 4: Ein Logikfehler (Dead Code / Unreachable)
        if (level > 100) {
            oxygenLevel = 100;
        } else if (level < 0) {
            oxygenLevel = 0;
        } else {
            oxygenLevel = level;
        }
        
        // Fehler 5: Ein "Null Pointer" Risiko simulieren
        int* pressureSensor = nullptr;
        if (level == 50) {
            //*pressureSensor = 50; // CRASH!
	    std::cout << "Warning: Pressure at 50% - Check sensors." << std::endl;
        }
    }

    // Fehler 6: Eine ungenutzte Funktion (Code Smell)
    void deprecatedFunction() {
        int unusedVar = 10;
    }
};

int main() {
    Ventilator myVent;
    myVent.setOxygen(50);
    return 0;
}
