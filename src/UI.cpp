#include "UI.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

UI::UI(AdminService& admin_service, UserService& user_service):
    admin_service{admin_service}, user_service{user_service}
{}

void UI::print_main_menu() {
    cout << "\n*Keep Calm and Adopt a Pet*\n";
    cout << "1. Administrator Mode\n";
    cout << "2. User Mode\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

void UI::print_admin_menu() {
    cout << "\n-Administrator Menu-\n";
    cout << "1. Add a new dog\n";
    cout << "2. Delete a dog (that was adopted)\n";
    cout << "3. Update a dog\n";
    cout << "4. See all dogs\n";
    cout << "0. Back to Main Menu\n";
    cout << "Choose an option: ";
}

void UI::print_user_menu() {
    cout << "\n-User Menu-\n";
    cout << "1. See dogs for adoption\n";
    cout << "2. Display adoption list\n";
    cout << "3. See dogs for adoption based on breed and maximum age\n";
    cout << "0. Back to Main Menu\n";
    cout << "Choose an option: ";
}

void UI::ui_add_dog() {
    string breed, name, photograph;
    int age;

    cout << "Enter breed: "; getline(cin, breed);
    cout << "Enter name: "; getline(cin, name);
    cout << "Enter age: "; cin >> age;
    if (cin.fail()) {
        cin.clear(); cin.ignore(10000, '\n');
        throw exception("Age must be a number!");
    }
    cin.ignore(); 
    cout << "Enter photograph link: "; getline(cin, photograph);

    this->admin_service.add_dog(breed, name, age, photograph);
}

void UI::ui_delete_dog() {
    string breed, name;
    cout << "Enter breed of the dog to delete: "; getline(cin, breed);
    cout << "Enter name of the dog to delete: "; getline(cin, name);

    this->admin_service.delete_dog(breed, name);
}

void UI::ui_update_dog() {
    string breed, name;
    cout << "Enter breed of the dog to update: "; getline(cin, breed);
    cout << "Enter name of the dog to update: "; getline(cin, name);

    cout << "What would you like to update?\n1. Age\n2. Photograph\nChoice: ";
    int choice;
    cin >> choice;
    if (cin.fail()) {
        cin.clear(); cin.ignore(10000, '\n');
        throw exception("CHoice must be a number!");
    }
    cin.ignore();

    if (choice == 1) {
        int new_age;
        cout << "Enter new age: "; cin >> new_age;
        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            throw exception("Age must be a number!");
        }
        cin.ignore();

        this->admin_service.update_dog_age(breed, name, new_age);
    }
    else if (choice == 2) {
        string new_photo;
        cout << "Enter new photograph link: ";  getline(cin, new_photo);

        this->admin_service.update_dog_photograph(breed, name, new_photo);
    }
    else {
        cout << "Invalid choice.\n";
    }
}

void UI::ui_display_all_dogs() {
    const vector<Dog>& dogs = this->admin_service.get_dogs();
    int size = dogs.size();

    if (size == 0) {
        cout << "The shelter is empty!\n";
        return;
    }

    cout << "\nDogs currently in the shelter:\n";
    for (auto& d: dogs) {
        cout << "Name: " << d.get_name() 
            << "|Breed: " << d.get_breed()
            << "|Age: " << d.get_age() 
            << "|Link: " << d.get_photograph() << "\n";
    }
}

void UI::ui_adopt_dogs() 
{
    vector<Dog> dogs = this->user_service.get_dogs();

    if (dogs.empty()) { 
        cout << "No dogs left to adopt!\n";
        return;
    }

    auto it = dogs.begin();

    while (!dogs.empty()) {
        Dog dog = *it;
        cout << "\n-Current Dog-\n";
        cout << "Name: " << dog.get_name()
            << "|Breed: " << dog.get_breed()
            << "|Age: " << dog.get_age() << "\n";

        ShellExecuteA(NULL, "open", dog.get_photograph().c_str(), NULL, NULL, SW_SHOWNORMAL);

        cout << "Options: \n";
        cout << "   1. Adopt\n";
        cout << "   2. Next dog\n";
        cout << "   0. Stop browsing\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            throw exception("Choice must be a number!");
        }
        cin.ignore();

        if (choice == 1) {
            this->user_service.adopt_dog(dog);
            cout << dog.get_name() << " was added to your adoption list!\n";
            it = dogs.erase(it);
            if (it == dogs.end() && !dogs.empty()) {
                it = dogs.begin(); 
            }
        }
        else if (choice == 2) {
            it++;
            if (it == dogs.end()) {
                it = dogs.begin(); 
            }
        }
        else if (choice == 0) {
            return;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
}

void UI::ui_display_adoption_list()
{
    vector<Dog> adoption_list = this->user_service.get_adoption_list();

    if (adoption_list.size() == 0) {
        cout << "Your adoption list is empty!\n";
        return;
    }

    cout << "\nYour adoption list: \n";
    for (auto& dog : adoption_list) {
        cout << "Name: " << dog.get_name() 
            << "|Breed: " << dog.get_breed()
            << "|Age: " << dog.get_age() << "\n";
    }
}

void UI::ui_adopt_dogs_filtered()
{
    string breed;
    int max_age;

    cout << "Enter breed to filter by (empty for all breeds): "; getline(cin, breed);
    cout << "Enter maximum age: "; cin >> max_age;
    if (cin.fail()) {
        cin.clear(); cin.ignore(10000, '\n');
        throw exception("Age must be a number!");
    }
    cin.ignore();

    std::vector<Dog> dogs = this->user_service.get_filtered_dogs(breed, max_age);

    if (dogs.size() == 0) {
        cout << "No dogs match!\n";
        return;
    }

    auto it = dogs.begin();

    while (!dogs.empty()) {
        Dog dog = *it;
        cout << "\n-Current Dog-\n";
        cout << "Name: " << dog.get_name()
            << "|Breed: " << dog.get_breed()
            << "|Age: " << dog.get_age() << "\n";

        ShellExecuteA(NULL, "open", dog.get_photograph().c_str(), NULL, NULL, SW_SHOWNORMAL);

        cout << "Options: \n";
        cout << "   1. Adopt\n";
        cout << "   2. Next dog\n";
        cout << "   0. Stop browsing\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            throw exception("Choice must be a number!");
        }
        cin.ignore();

        if (choice == 1) {
            this->user_service.adopt_dog(dog);
            cout << dog.get_name() << " was added to your adoption list!\n";
            it = dogs.erase(it);
            if (it == dogs.end() && !dogs.empty()) {
                it = dogs.begin();
            }
        }
        else if (choice == 2) {
            it++;
            if (it == dogs.end()) {
                it = dogs.begin();
            }
        }
        else if (choice == 0) {
            return;
        }
        else {
            cout << "Invalid choice!\n";
        }

    }
}

void UI::run_user_mode()
{
    while (true) {
        print_user_menu();
        int choice;
        try {
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); cin.ignore(10000, '\n');
                throw exception("Choice must be a number!");
            }
            cin.ignore();

            if (choice == 0) break;
            else if (choice == 1) {
                ui_adopt_dogs();
            }
            else if (choice == 2) {
                ui_display_adoption_list();
            }
            else if (choice == 3) {
                ui_adopt_dogs_filtered();
            }
            else cout << "Invalid choice!\n";
        }
        catch (exception& e) {
            cout << "\n" << e.what() << "\n";
        }
    }
}

void UI::run_admin_mode() {
    while (true) {
        print_admin_menu();
        int choice;
        try {
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); cin.ignore(10000, '\n');
                throw exception("Choice must be a number!");
            }
            cin.ignore();

            if (choice == 0) break;

            if (choice == 1) {
                ui_add_dog();
            }
            else if (choice == 2) {
                ui_delete_dog();
            }
            else if (choice == 3) {
                ui_update_dog();
            }
            else if (choice == 4) {
                ui_display_all_dogs();
            }
            else {
                cout << "Invalid choice!\n";
            }
        }
        catch (const std::exception& e) {
            cout << "\n" << e.what() << "\n";
        }
    }
}

void UI::start() {
    while (true) {
        print_main_menu();
        int choice;
        try {
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); cin.ignore(10000, '\n');
                throw exception("Choice must be a number!");
            }
            cin.ignore();

            if (choice == 0) {
                break;
            }
            else if (choice == 1) {
                run_admin_mode();
            }
            else if (choice == 2) {
                run_user_mode();
            }
            else {
                cout << "Invalid choice!\n";
            }
        }
        catch (exception& e) {
            cout << "\n" << e.what() << "\n";
        }
    }
}

UI::~UI() {}