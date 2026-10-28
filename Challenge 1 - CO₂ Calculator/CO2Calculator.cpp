#include <iostream>
#include <iomanip>
using namespace std;

double getDistance() { // Get the distance entered by the user
    double distance;

    cout << "Enter distance in miles: ";
    cin >> distance;

    return distance;
}

int getFuelType() { // Ask the user to choose a fuel type
    int fuel;

    cout << "\nSelect fuel type:" << endl;
    cout << "1. Diesel" << endl;
    cout << "2. Petrol" << endl;
    cout << "Enter your choice: ";
    cin >> fuel;

    return fuel;
}

double calculateCO2(double distance, int fuel) { // Calculate CO2 emissions based on distance and fuel

    double litres = (distance * 9.66) / 100; // Calculate the amount of fuel used in litres
    double emissions;

    if (fuel == 1) { // Calculate emissions for diesel
        emissions = litres * 2.68;
    }
    else { // Calculate emissions for petrol
        emissions = litres * 2.31;
    }

    return emissions;
}

int main() { // Main function starts here

    cout << "CO2 Emissions Calculator" << endl; // Display the program title
    cout << "------------------------" << endl;

    double distance = getDistance(); // Get the distance

    if (!cin || distance < 0) { // Check if the distance is valid
        cout << "Invalid distance!" << endl;
        return 1;
    }

    int fuel = getFuelType(); // Get the fuel type

    if (!cin || (fuel != 1 && fuel != 2)) { // Check if the fuel choice is valid
        cout << "Invalid fuel type!" << endl;
        return 1;
    }

    double result = calculateCO2(distance, fuel); // Calculate the total CO2 emissions

    cout << fixed << setprecision(2); // Show the result with two decimal places
    cout << "\nEstimated CO2 emissions: "
         << result << " kg" << endl;

    return 0;
}