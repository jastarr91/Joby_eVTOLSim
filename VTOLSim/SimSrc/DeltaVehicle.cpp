#include "DeltaVehicle.h"
#include "SimConst.h"
#include <iostream>

// Init class variables
double DeltaVehicle::_totalTimeInFlight_hr = 0.0;
double DeltaVehicle::_totalTimeInCharge_hr = 0.0;
double DeltaVehicle::_totalTimeInWait_hr = 0.0;
double DeltaVehicle::_totalPassengerTravel_mi = 0.0;
int DeltaVehicle::_totalVehicles = 0;
int DeltaVehicle::_maxFaults = 0;

DeltaVehicle::DeltaVehicle() : Vehicle(90, 120, 0.62, 0.8, 2, 0.22)
{
    ++_totalVehicles;
}

void DeltaVehicle::updateTimeInCharge(DWORD time_ms)
{
    _totalTimeInCharge_hr += MS_TO_HR(time_ms);
}

void DeltaVehicle::updateTimeInWait(DWORD time_ms)
{
    _totalTimeInWait_hr += MS_TO_HR(time_ms);
}

void DeltaVehicle::updateTimeInFlight(DWORD time_ms)
{
    _totalTimeInFlight_hr += MS_TO_HR(time_ms);
}

void DeltaVehicle::updatePassengerTravel(DWORD time_ms)
{
    _totalPassengerTravel_mi += ((double)_cruiseSpeed_mph * MS_TO_HR(time_ms) * (double)_passengerCount);
}

void DeltaVehicle::updateMaxFaults(int faults)
{
    if (faults > _maxFaults)
        _maxFaults = faults;
}

void DeltaVehicle::printData()
{
    // Calculate averages
    double avgTimeInFlight_hrpv = (_totalTimeInFlight_hr / (double)_totalVehicles);
    double avgTimeInCharge_hrpv = (_totalTimeInCharge_hr / (double)_totalVehicles);
    double avgTimeInWait_hrpv = (_totalTimeInWait_hr / (double)_totalVehicles);
    
    // NOTE: total miles and max faults are updated during vehicle update
    std::cout << "--Delta Vehicle (" << _totalVehicles << ") --\
                    \n\tAvg Flight Time (hr/veh): " << avgTimeInFlight_hrpv << "\
                    \n\tAvg Charge Time (hr/veh): " << avgTimeInCharge_hrpv << "\
                    \n\tAvg Wait Time (hr/veh): " << avgTimeInWait_hrpv << "\
                    \n\tTotal Passenger Distance (mi): " << _totalPassengerTravel_mi << "\
                    \n\tMax Faults: " << _maxFaults << "\n\n";
}