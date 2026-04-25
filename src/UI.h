#pragma once
#include "AdminService.h"
#include "UserService.h"

class UI {
private:
    AdminService& admin_service;
    UserService& user_service;

    void print_main_menu();
    void print_admin_menu();
    void print_user_menu();

    void ui_add_dog();
    void ui_delete_dog();
    void ui_update_dog();
    void ui_display_all_dogs();

    void ui_adopt_dogs();
    void ui_display_adoption_list();
    void ui_adopt_dogs_filtered();

    void run_admin_mode();
    void run_user_mode();

public:
    UI(AdminService& admin_service, UserService& user_service);
    void start();
    ~UI();
};
