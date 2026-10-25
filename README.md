<div align="center">

# Vehicle Rental System

**A beginner-friendly C++ project that demonstrates single inheritance**

![Language](https://img.shields.io/badge/language-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Concept](https://img.shields.io/badge/concept-Single%20Inheritance-2EA44F?style=for-the-badge)
![Course](https://img.shields.io/badge/OOPS-PPF%20Mini%20Project-F59E0B?style=for-the-badge)

</div>

---

## Table of Contents

1. [About the Project](#about-the-project)
2. [Project Structure](#project-structure)
3. [How to Compile and Run](#how-to-compile-and-run)
4. [Class Design and Inheritance](#class-design-and-inheritance)
5. [Code Walkthrough](#code-walkthrough)
6. [OOPS Concepts Used](#oops-concepts-used)
7. [Rental Charge Rules](#rental-charge-rules)
8. [Input Validation](#input-validation)
9. [Program Flow](#program-flow)
10. [Sample Outputs](#sample-outputs)
11. [Viva Questions and Answers](#viva-questions-and-answers)
12. [Author](#author)

---

## About the Project

This program represents **cars** and **bikes** that can be rented, and calculates the rental charges for each one. A car and a bike share some common details (ID, model, rate per day, rental days), so those live in one **base class** called `Vehicle`. `Car` and `Bike` are **derived classes** that inherit from `Vehicle` and add their own details and their own charge calculation.

### Assignment requirements covered

| Requirement | Where it is done |
| --- | --- |
| Base `Vehicle` class with common details | `class Vehicle` stores ID, model, rate per day and rental days |
| `Car` and `Bike` derived using single inheritance | `class Car : public Vehicle` and `class Bike : public Vehicle` |
| Different charge logic for cars and bikes | `calculateCharge()` is written separately in `Car` and in `Bike` |
| Display details, duration, rate and total charges | `display()` in `Car` and `Bike` |
| Validate rental duration, handle invalid input | `setRentalDays()` and the input helper functions |

---

## Project Structure

```text
vehicle-rental-system/
├── main.cpp       all the code (three classes and the menu)
└── README.md      this file
```

---

## How to Compile and Run

You need a C++ compiler such as `g++`.

```bash
g++ main.cpp -o rental
```

Run it:

```bash
./rental          # Linux and macOS
rental.exe        # Windows
```

Then follow the menu: choose **1** to rent a car, **2** to rent a bike or **3** to exit.

---

## Class Design and Inheritance

```text
              +-----------------------+
              |        Vehicle        |   <- base class
              |-----------------------|
              | - id                  |
              | - model               |
              | - ratePerDay          |
              | - rentalDays          |
              |-----------------------|
              | + getters             |
              | + setRentalDays()     |
              | + calculateCharge()   |
              | + display()           |
              +-----------+-----------+
                          ^
            +-------------+-------------+
            |                           |
  +---------+-----------+   +-----------+---------+
  |         Car         |   |         Bike        |   <- derived classes
  |---------------------|   |---------------------|
  | - seats             |   | - engineCC          |
  |---------------------|   |---------------------|
  | + calculateCharge() |   | + calculateCharge() |
  | + display()         |   | + display()         |
  +---------------------+   +---------------------+
```

### What is inheritance here?

`Car` and `Bike` are **kinds of** `Vehicle`. Instead of writing the ID, model, rate and days again in both classes, we write them once in `Vehicle` and let the other two classes **inherit** them.

This is **single inheritance**: each derived class has exactly one parent class.

```cpp
class Car : public Vehicle {
    ...
};

class Bike : public Vehicle {
    ...
};
```

The part `: public Vehicle` means "Car inherits from Vehicle". A `Car` object automatically has everything a `Vehicle` has, plus its own `seats`.

### Calling the parent constructor

When a `Car` is created, the `Vehicle` part must be created first. The `Car` constructor passes the common values up to the `Vehicle` constructor:

```cpp
Car(int id, string model, double rate, int seatCount) : Vehicle(id, model, rate)
{
    seats = seatCount;
}
```

`: Vehicle(id, model, rate)` runs the parent constructor, and then the body sets `seats`, which belongs only to `Car`.

### Function overriding

Both `Car` and `Bike` have functions named `calculateCharge()` and `display()`, the same names that exist in `Vehicle`. Each derived class **redefines** them with its own logic. This is called **function overriding**.

| Function | In `Vehicle` | In `Car` | In `Bike` |
| --- | --- | --- | --- |
| `calculateCharge()` | rate × days | rate × days + Rs. 500 insurance | rate × days, minus 10% if 5 days or more |
| `display()` | prints ID, model, rate, days | prints a car heading, calls `Vehicle::display()`, then adds seats, insurance and total | prints a bike heading, calls `Vehicle::display()`, then adds engine size, discount and total |

Inside `Car::display()` and `Bike::display()`, the line `Vehicle::display();` calls the parent version so the common details are not written twice.

---

## Code Walkthrough

### 1. The `Vehicle` base class

```cpp
class Vehicle {
private:
    int id;
    string model;
    double ratePerDay;
    int rentalDays;
public:
    ...
};
```

- All four data members are **private**, so no other code can change them directly. This is **encapsulation**.
- The constructor stores the ID, model and rate, and starts `rentalDays` at 0.
- Public **getter** functions (`getId()`, `getRatePerDay()` and so on) let other classes read the values.
- `setRentalDays(int days)` is the only way to set the duration. It returns `false` for anything outside 1 to 30, so a wrong value is never stored.

### 2. The `Car` class

- Adds one new member, `seats`.
- Because `ratePerDay` and `rentalDays` are private in `Vehicle`, `Car` reads them with `getRatePerDay()` and `getRentalDays()`.
- `calculateCharge()` returns `rate × days + 500`.

### 3. The `Bike` class

- Adds one new member, `engineCC`.
- `calculateCharge()` returns `rate × days`, and takes 10% off when the bike is rented for 5 days or more.

### 4. Input helper functions

Small functions such as `readInt()`, `readDouble()`, `readPositiveInt()` and `readInRange()` keep asking until the user types something valid. They use `cin.fail()` handling, so typing letters where a number is expected does not crash the program.

### 5. `rentCar()` and `rentBike()`

Each function:

1. Reads the ID, model, rate and the extra detail (seats or engine size).
2. Creates an **object** (`Car myCar(...)` or `Bike myBike(...)`).
3. Asks for the duration and keeps asking until `setRentalDays()` accepts it.
4. Calls `display()` to print the details and total charge.

### 6. `main()`

Shows the menu in a loop until the user picks **Exit**.

---

## OOPS Concepts Used

| Concept | How it is used in this project |
| --- | --- |
| **Classes and objects** | `Vehicle`, `Car` and `Bike` are classes. `myCar` and `myBike` are objects created at run time |
| **Constructors** | `Vehicle`, `Car` and `Bike` each have a constructor that sets the starting values. Derived constructors call the parent constructor |
| **Encapsulation** | Data members are `private`. They are read through getters and the rental days are changed only through `setRentalDays()`, which validates the value |
| **Single inheritance** | `Car` and `Bike` each inherit from one parent, `Vehicle` |
| **Function overriding** | `calculateCharge()` and `display()` are redefined in `Car` and `Bike` |

---

## Rental Charge Rules

| | Car | Bike |
| --- | --- | --- |
| Base amount | rate × days | rate × days |
| Extra fee | Rs. 500 insurance (fixed) | none |
| Discount | none | 10% off for 5 days or more |

**Car example:** rate Rs. 2000 for 3 days gives 2000 × 3 + 500 = **Rs. 6500**

**Bike example:** rate Rs. 500 for 5 days gives 500 × 5 = 2500, minus 10% (250) = **Rs. 2250**

---

## Input Validation

| Input | Allowed | What happens otherwise |
| --- | --- | --- |
| Menu choice | 1, 2 or 3 | "Invalid choice" and the menu is shown again |
| Vehicle ID | Whole number above 0 | Asked again |
| Model name | Not empty | Asked again |
| Rate per day | Number above 0 | Asked again |
| Seats (car) | 2 to 8 | Asked again |
| Engine size (bike) | 50 to 1500 cc | Asked again |
| Rental days | Whole number from 1 to 30 | "Invalid duration" and asked again |
| Letters instead of a number | Not allowed | "Invalid input" and asked again, no crash |

---

## Program Flow

```text
Start
  |
  v
Show menu  <-----------------------------+
  |                                      |
  +-- 1 --> read car details             |
  |         create Car object            |
  |         read days (repeat if invalid)|
  |         show details and total ------+
  |
  +-- 2 --> read bike details
  |         create Bike object
  |         read days (repeat if invalid)
  |         show details and total ------+
  |
  +-- 3 --> print thank-you message --> End
```

---

## Sample Outputs

These are real outputs from the compiled program. The text after each prompt is what the user typed.

### 1. Normal inputs

A car for 3 days and a bike for 2 days.

```text
===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 1

--- Car Rental ---
Enter vehicle ID: 101
Enter model name: Maruti Swift
Enter rental rate per day (Rs.): 2000
Enter number of seats (2-8): 5
Enter rental duration in days (1-30): 3

----- Car Rental Details -----
Vehicle ID    : 101
Model         : Maruti Swift
Rate per day  : Rs. 2000.00
Rental days   : 3
Seats         : 5
Insurance fee : Rs. 500
Total charge  : Rs. 6500.00
------------------------------

===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 2

--- Bike Rental ---
Enter vehicle ID: 201
Enter model name: Bajaj Pulsar 150
Enter rental rate per day (Rs.): 500
Enter engine capacity in cc (50-1500): 150
Enter rental duration in days (1-30): 2

----- Bike Rental Details -----
Vehicle ID    : 201
Model         : Bajaj Pulsar 150
Rate per day  : Rs. 500.00
Rental days   : 2
Engine        : 150 cc
Total charge  : Rs. 1000.00
-------------------------------

===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 3
Thank you for using the Vehicle Rental System.
```

Both totals match the rules: car 2000 × 3 + 500 = 6500, bike 500 × 2 = 1000.

### 2. Boundary inputs

| Case tested | Input | Expected total |
| --- | --- | --- |
| Minimum days | Bike, 1 day, Rs. 400 | Rs. 400.00 |
| Just below bike discount | Bike, 4 days, Rs. 500 | Rs. 2000.00 (no discount) |
| Exactly at bike discount | Bike, 5 days, Rs. 500 | Rs. 2250.00 (10% off) |
| Maximum days | Car, 30 days, Rs. 1500 | Rs. 45500.00 |

```text
===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 2

--- Bike Rental ---
Enter vehicle ID: 202
Enter model name: Honda Activa 125
Enter rental rate per day (Rs.): 400
Enter engine capacity in cc (50-1500): 125
Enter rental duration in days (1-30): 1

----- Bike Rental Details -----
Vehicle ID    : 202
Model         : Honda Activa 125
Rate per day  : Rs. 400.00
Rental days   : 1
Engine        : 125 cc
Total charge  : Rs. 400.00
-------------------------------

===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 2

--- Bike Rental ---
Enter vehicle ID: 203
Enter model name: Bajaj Pulsar 150
Enter rental rate per day (Rs.): 500
Enter engine capacity in cc (50-1500): 150
Enter rental duration in days (1-30): 4

----- Bike Rental Details -----
Vehicle ID    : 203
Model         : Bajaj Pulsar 150
Rate per day  : Rs. 500.00
Rental days   : 4
Engine        : 150 cc
Total charge  : Rs. 2000.00
-------------------------------

===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 2

--- Bike Rental ---
Enter vehicle ID: 203
Enter model name: Bajaj Pulsar 150
Enter rental rate per day (Rs.): 500
Enter engine capacity in cc (50-1500): 150
Enter rental duration in days (1-30): 5

----- Bike Rental Details -----
Vehicle ID    : 203
Model         : Bajaj Pulsar 150
Rate per day  : Rs. 500.00
Rental days   : 5
Engine        : 150 cc
Discount      : 10% (rented for 5 days or more)
Total charge  : Rs. 2250.00
-------------------------------

===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 1

--- Car Rental ---
Enter vehicle ID: 103
Enter model name: Tata Tiago
Enter rental rate per day (Rs.): 1500
Enter number of seats (2-8): 5
Enter rental duration in days (1-30): 30

----- Car Rental Details -----
Vehicle ID    : 103
Model         : Tata Tiago
Rate per day  : Rs. 1500.00
Rental days   : 30
Seats         : 5
Insurance fee : Rs. 500
Total charge  : Rs. 45500.00
------------------------------

===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 3
Thank you for using the Vehicle Rental System.
```

### 3. Invalid inputs

This run tries a wrong menu choice, letters in number fields, zero and negative values, an empty model, out-of-range seats and engine size, and invalid rental days (0, -3, 31 and letters). The program rejects each one, asks again, and finishes normally.

```text
===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 9
Invalid choice! Please select 1, 2 or 3.

===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: abc
Invalid input! Please enter a whole number: 1

--- Car Rental ---
Enter vehicle ID: -5
Value must be greater than 0.
Enter vehicle ID: 0
Value must be greater than 0.
Enter vehicle ID: abc
Invalid input! Please enter a whole number: 101
Enter model name: 
Model name cannot be empty.
Enter model name: Maruti Swift
Enter rental rate per day (Rs.): -500
Rate must be greater than 0.
Enter rental rate per day (Rs.): 0
Rate must be greater than 0.
Enter rental rate per day (Rs.): xyz
Invalid input! Please enter a number: 1800
Enter number of seats (2-8): 1
Please enter a value between 2 and 8.
Enter number of seats (2-8): 9
Please enter a value between 2 and 8.
Enter number of seats (2-8): 4
Enter rental duration in days (1-30): 0
Invalid duration! Days must be between 1 and 30.
Enter rental duration in days (1-30): -3
Invalid duration! Days must be between 1 and 30.
Enter rental duration in days (1-30): 31
Invalid duration! Days must be between 1 and 30.
Enter rental duration in days (1-30): abc
Invalid input! Please enter a whole number: 7

----- Car Rental Details -----
Vehicle ID    : 101
Model         : Maruti Swift
Rate per day  : Rs. 1800.00
Rental days   : 7
Seats         : 4
Insurance fee : Rs. 500
Total charge  : Rs. 13100.00
------------------------------

===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 2

--- Bike Rental ---
Enter vehicle ID: 301
Enter model name: Activa
Enter rental rate per day (Rs.): 400
Enter engine capacity in cc (50-1500): 20
Please enter a value between 50 and 1500.
Enter engine capacity in cc (50-1500): 2000
Please enter a value between 50 and 1500.
Enter engine capacity in cc (50-1500): 125
Enter rental duration in days (1-30): 1

----- Bike Rental Details -----
Vehicle ID    : 301
Model         : Activa
Rate per day  : Rs. 400.00
Rental days   : 1
Engine        : 125 cc
Total charge  : Rs. 400.00
-------------------------------

===== Vehicle Rental System =====
1. Rent a Car
2. Rent a Bike
3. Exit
Enter your choice: 3
Thank you for using the Vehicle Rental System.
```

---

## Viva Questions and Answers

**Q1. What is inheritance?**
It lets one class (the derived class) reuse the data and functions of another class (the base class). Here `Car` and `Bike` reuse the common details of `Vehicle`.

**Q2. Which type of inheritance is used?**
Single inheritance, because each derived class has only one base class.

**Q3. What does `: public Vehicle` mean?**
It makes the class inherit from `Vehicle`. `public` keeps the base class's public members public in the derived class.

**Q4. Why are the data members private?**
For encapsulation. Outside code cannot change them directly, so wrong values cannot get in. Access is only through getters and `setRentalDays()`.

**Q5. How does the derived class initialise the base class part?**
By calling the base constructor in its initialiser list: `Car(...) : Vehicle(id, model, rate)`.

**Q6. What is function overriding?**
Redefining a base class function in the derived class with the same name and parameters, so each class can behave in its own way. Here `calculateCharge()` and `display()` are overridden.

**Q7. How is the parent's `display()` used inside the child's `display()`?**
With the scope operator: `Vehicle::display();`.

**Q8. How is the rental duration validated?**
`setRentalDays()` only accepts 1 to 30 and returns `false` otherwise. The program keeps asking until it returns `true`.

**Q9. What happens if the user types letters instead of a number?**
`cin` goes into a fail state. The helper functions detect this with `cin.fail()` (inside the `while (!(cin >> value))` check), clear the error, discard the bad input and ask again.

---

## Author

**Shaurya**
BCA, CGC Jhanjeri
GitHub: [@Shaurya](https://github.com/Shaurya)
