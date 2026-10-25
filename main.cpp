#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

class Vehicle {
private:
    int id;
    string model;
    double ratePerDay;
    int rentalDays;

public:
    Vehicle(int vehicleId, string vehicleModel, double rate)
    {
        id = vehicleId;
        model = vehicleModel;
        ratePerDay = rate;
        rentalDays = 0;
    }

    int getId() { return id; }
    string getModel() { return model; }
    double getRatePerDay() { return ratePerDay; }
    int getRentalDays() { return rentalDays; }

    bool setRentalDays(int days)
    {
        if (days < 1 || days > 30)
            return false;
        rentalDays = days;
        return true;
    }

    double calculateCharge()
    {
        return ratePerDay * rentalDays;
    }

    void display()
    {
        cout << "Vehicle ID    : " << id << endl;
        cout << "Model         : " << model << endl;
        cout << "Rate per day  : Rs. " << ratePerDay << endl;
        cout << "Rental days   : " << rentalDays << endl;
    }
};

class Car : public Vehicle {
private:
    int seats;

public:
    Car(int id, string model, double rate, int seatCount) : Vehicle(id, model, rate)
    {
        seats = seatCount;
    }

    double calculateCharge()
    {
        double insurance = 500;
        return getRatePerDay() * getRentalDays() + insurance;
    }

    void display()
    {
        cout << "\nCar Rental Details" << endl;
        Vehicle::display();
        cout << "Seats         : " << seats << endl;
        cout << "Insurance fee : Rs. 500" << endl;
        cout << "Total charge  : Rs. " << calculateCharge() << endl;
    }
};

class Bike : public Vehicle {
private:
    int engineCC;

public:
    Bike(int id, string model, double rate, int cc) : Vehicle(id, model, rate)
    {
        engineCC = cc;
    }

    double calculateCharge()
    {
        double total = getRatePerDay() * getRentalDays();
        if (getRentalDays() >= 5)
            total = total - total * 0.10;
        return total;
    }

    void display()
    {
        cout << "\n Bike Rental Details" << endl;
        Vehicle::display();
        cout << "Engine        : " << engineCC << " cc" << endl;
        if (getRentalDays() >= 5)
            cout << "Discount      : 10% (rented for 5 days or more)" << endl;
        cout << "Total charge  : Rs. " << calculateCharge() << endl;
    }
};

int readInt(string prompt)
{
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        if (cin.eof()) {
            cout << "\nInput ended. Exiting." << endl;
            exit(0);
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter a whole number: ";
    }
    cin.ignore(1000, '\n');
    return value;
}

double readDouble(string prompt)
{
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        if (cin.eof()) {
            cout << "\nInput ended. Exiting." << endl;
            exit(0);
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter a number: ";
    }
    cin.ignore(1000, '\n');
    return value;
}

int readPositiveInt(string prompt)
{
    int value = readInt(prompt);
    while (value <= 0) {
        cout << "Value must be greater than 0." << endl;
        value = readInt(prompt);
    }
    return value;
}

double readPositiveDouble(string prompt)
{
    double value = readDouble(prompt);
    while (value <= 0) {
        cout << "Rate must be greater than 0." << endl;
        value = readDouble(prompt);
    }
    return value;
}

int readInRange(string prompt, int low, int high)
{
    int value = readInt(prompt);
    while (value < low || value > high) {
        cout << "Please enter a value between " << low << " and " << high << "." << endl;
        value = readInt(prompt);
    }
    return value;
}

string readModel()
{
    string model;
    cout << "Enter model name: ";
    getline(cin, model);
    while (model.empty()) {
        if (cin.eof()) {
            cout << "\nInput ended. Exiting." << endl;
            exit(0);
        }
        cout << "Model name cannot be empty." << endl;
        cout << "Enter model name: ";
        getline(cin, model);
    }
    return model;
}

void rentCar()
{
    cout << "\nCar Rental" << endl;
    int id = readPositiveInt("Enter vehicle ID: ");
    string model = readModel();
    double rate = readPositiveDouble("Enter rental rate per day (Rs.): ");
    int seats = readInRange("Enter number of seats (2-8): ", 2, 8);

    Car myCar(id, model, rate, seats);

    int days = readInt("Enter rental duration in days (1-30): ");
    while (!myCar.setRentalDays(days)) {
        cout << "Invalid duration! Days must be between 1 and 30." << endl;
        days = readInt("Enter rental duration in days (1-30): ");
    }

    myCar.display();
}

void rentBike()
{
    cout << "\nBike Rental" << endl;
    int id = readPositiveInt("Enter vehicle ID: ");
    string model = readModel();
    double rate = readPositiveDouble("Enter rental rate per day (Rs.): ");
    int cc = readInRange("Enter engine capacity in cc (50-1500): ", 50, 1500);

    Bike myBike(id, model, rate, cc);

    int days = readInt("Enter rental duration in days (1-30): ");
    while (!myBike.setRentalDays(days)) {
        cout << "Invalid duration! Days must be between 1 and 30." << endl;
        days = readInt("Enter rental duration in days (1-30): ");
    }

    myBike.display();
}

int main()
{
    cout << fixed << setprecision(2);

    int choice;
    do {
        cout << "\nVehicle Rental System" << endl;
        cout << "1. Rent a Car" << endl;
        cout << "2. Rent a Bike" << endl;
        cout << "3. Exit" << endl;
        choice = readInt("Enter your choice: ");

        if (choice == 1)
            rentCar();
        else if (choice == 2)
            rentBike();
        else if (choice != 3)
            cout << "Invalid choice! Please select 1, 2 or 3." << endl;
    } while (choice != 3);

    cout << "Thank you for using the Vehicle Rental System." << endl;
    return 0;
}
