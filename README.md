# Dog Shelter Management System 🐾

A desktop application for managing a dog shelter, with a graphical interface built in **C++** using the **Qt** framework. The project focuses on **Object-Oriented Programming (OOP)** and a clean **layered architecture**.

## Architecture & Design
The code is split into clearly separated layers:
* **Domain:** the `Dog` entity, plus a `DogValidator` that rejects invalid input with custom exceptions.
* **Repository:** an `IRepository` interface with in-memory and text-file implementations.
* **Service:** admin and user logic, kept independent of the interface.
* **GUI:** Qt widgets for each mode, built on top of the services.

Design patterns used:
* **Command Pattern:** every add, remove and update is stored as an `Action` object, which makes **undo/redo** possible.
* **Polymorphism:** the adoption list can be saved as **CSV** or **HTML** through a common `AdoptionList` base class.
* **Model/View:** the adoption list is shown in a table backed by a custom Qt table model.

## Features
* **Admin Mode:** add, remove and update dogs, with **Undo/Redo** buttons and **Ctrl+Z / Ctrl+Y** shortcuts.
* **Breed Statistics:** a custom-drawn chart showing how many dogs there are of each breed.
* **User Mode:** browse dogs one at a time, see their photo and adopt them.
* **Filters:** show only dogs of a given breed and/or up to a maximum age.
* **Adoption List:** view your adopted dogs in a table, then save the list as CSV or HTML and open it in one click.

## Tech Stack
* **Language:** C++17
* **GUI:** Qt 6 (Widgets)
* **Build System:** CMake
* **Storage:** Text files, CSV and HTML

## How to run

### Option 1: Download (Windows)
* **Download:** get `DogShelterManager-windows-x64.zip` from the [Releases](../../releases) page
* **Unzip** it anywhere
* **Run** `shelter_app.exe`
* **Enjoy :)**

### Option 2: Build from source
* **Install:** a C++ compiler, [CMake](https://cmake.org/download/) and [Qt 6](https://www.qt.io/download-qt-installer-oss)
  (on Ubuntu: **sudo apt install qt6-base-dev cmake g++**)
* **Clone repository:** clone the project on your computer
* **Build:** open a terminal in the project folder and run
  ```sh
  cmake -S . -B build -DCMAKE_PREFIX_PATH=<path-to-Qt>
  cmake --build build --config Release
  ```
  where `<path-to-Qt>` is your Qt kit folder, e.g. `C:/Qt/6.11.0/msvc2022_64`. Linux users who installed Qt with apt can leave out `-DCMAKE_PREFIX_PATH`.
* **Run:** **build\Release\shelter_app.exe** on Windows, or **./build/shelter_app** on Linux
* **Enjoy :)**

## Versions
* **v2.0:** Qt graphical interface (current)
* **v1.0:** console version ([browse code](../../tree/v1.0))
