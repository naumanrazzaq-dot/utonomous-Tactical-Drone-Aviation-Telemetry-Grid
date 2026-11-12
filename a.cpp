#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class AviationAsset {
protected:
    string assetID;
    bool isAirborne;

public:
    static int activeFleetSize;

    AviationAsset(string id) : assetID(id), isAirborne(true) {
        activeFleetSize++;
    }

    virtual ~AviationAsset() {
        activeFleetSize--;
    }

    virtual void generateFlightLog() = 0;
};

int AviationAsset::activeFleetSize = 0;

class FlightTelemetryModule : virtual public AviationAsset {
protected:
    double batteryVoltage;

public:
    FlightTelemetryModule(string id, double voltage) : AviationAsset(id), batteryVoltage(voltage) {}

    void checkTelemetry() {
        cout << "Telemetry [" << assetID << "] battery voltage: " << batteryVoltage << "V." << endl;
    }
};

class NavigationSystemModule : virtual public AviationAsset {
protected:
    double gpsAltitudeMeters;

public:
    NavigationSystemModule(string id, double altitude) : AviationAsset(id), gpsAltitudeMeters(altitude) {}

    void checkNavigation() {
        cout << "Navigation [" << assetID << "] altitude locked at " << gpsAltitudeMeters << "m." << endl;
    }
};

class TacticalReconDrone : public FlightTelemetryModule, public NavigationSystemModule {
private:
    int targetsTracked;

public:
    TacticalReconDrone(string id, double voltage, double altitude, int targets)
        : AviationAsset(id),
          FlightTelemetryModule(id, voltage),
          NavigationSystemModule(id, altitude),
          targetsTracked(targets) {}

    ~TacticalReconDrone() {
        cout << "Tactical drone " << assetID << " returned to base and secured." << endl;
    }

    void generateFlightLog() override {
        cout << "\n--- Tactical Recon Flight Log: " << assetID << " ---" << endl;
        checkTelemetry();
        checkNavigation();
        cout << "Hostile Targets Tracked: " << targetsTracked << endl;
        cout << "Mission Status: Successful" << endl;
    }
};

int main() {
    AviationAsset* drone = new TacticalReconDrone("DRONE-X9", 52.4, 450.0, 14);

    drone->generateFlightLog();

    cout << "\nActive Fleet Assets: " << AviationAsset::activeFleetSize << endl;

    delete drone;

    cout << "Active Fleet Assets After Recall: " << AviationAsset::activeFleetSize << endl;

    return 0;
}
