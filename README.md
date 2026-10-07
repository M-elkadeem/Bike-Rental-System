# Bike-Rental-System

A C++ console application for managing a bike rental shop. It supports user registration and login, separate admin and customer menus, and a rental timer that keeps counting correctly even if the program is closed and restarted.

## Features

**Customers**
- Register and log in
- Rent an available bike
- Return a bike (rental duration and cost are calculated per second)
- View the bikes they currently have rented

**Admins**
- Display all bikes
- Search bikes by ID or brand
- Add and delete bikes
- View all active rentals

**General**
- Persistent storage in plain text files (`bikes_data.txt`, `users_data.txt`)
- Rental time survives shutdowns: the shutdown and restart times are recorded and the offline period is added to the rental duration
- Per-bike rental rate, type, frame size and mileage tracking

## Project structure

| File | Purpose |
|------|---------|
| `mybike.cpp` | Entry point (`main`) |
| `bike.h` / `bike.cpp` | `bike` class: bike details, availability, rental timing |
| `bikesystem.h` / `bikesystem.cpp` | `bikesystem` class: bike inventory, renting/returning, search, save/load |
| `user.h` / `user.cpp` | `user` base class with `admin` and `customer` subclasses and their menus |
| `usermanagement.h` / `usermanagement.cpp` | Registration, login, user save/load, main menu |
| `bikes_data.txt` | Saved bikes (CSV-style, one bike per line) |
| `users_data.txt` | Saved users (CSV-style, one user per line) |
| `Documentation.pdf` | Project documentation |

## Build and run

The program uses `system("cls")` and `system("pause")`, so it targets **Windows**.

With g++ (MinGW):

```bash
g++ -std=c++17 -o bikerental mybike.cpp bike.cpp bikesystem.cpp user.cpp usermanagement.cpp
./bikerental
```

Or create a Console App project in Visual Studio, add all `.cpp` and `.h` files, and build. Run the program from the folder that contains the `.txt` data files so it can load them.

## Usage

1. Start the program and choose **Login** or **Register**.
2. Log in with your username, password and numeric user ID.
3. Use the customer or admin menu to rent, return, or manage bikes.
4. Exit from the main menu so the data is saved.

## Notes

- Passwords are currently stored in plain text in `users_data.txt`. This is fine for a learning project but should be replaced with hashing before any real use.
- Rental rates are charged per second.
