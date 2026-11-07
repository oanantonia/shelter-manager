#pragma once
#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDesktopServices>
#include <QFileInfo>
#include <QHeaderView>
#include <QUrl>
#include <QGroupBox>
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include "UserGUI.h"
#include "Exceptions.h"

UserGUI::UserGUI(UserService& user_service, QStackedWidget* stacked_widget):
    user_service{ user_service }, stacked_widget{ stacked_widget }, current_index{ 0 }, adoption_table{ nullptr }, adoption_model{ nullptr }
{
    this->buildGUI();
    this->dogs = this->user_service.get_dogs();
    this->dogs_to_display = this->dogs;
    
    QObject::connect(this->back_button, &QPushButton::clicked, [this]() {
        this->dog_label->setText("\nDog information will appear here\n:) \n");

        this->user_service.clear_adoption_list();

        if (this->adoption_table != nullptr) {
            this->adoption_table->window()->close();
        }

        this->breed_edit->clear();
        this->age_edit->clear();

        this->dogs = this->user_service.get_dogs();
        this->dogs_to_display = this->dogs;
        this->current_index = 0;
        this->stacked_widget->setCurrentIndex(0);
        });

    QObject::connect(this->adoption_list_button, &QPushButton::clicked, [this]() {
        this->adoption_list_widget();
        });

    QObject::connect(this->next_button, &QPushButton::clicked, [this]() {
        this->next();
        }); 

    QObject::connect(this->see_dogs_button, &QPushButton::clicked, [this]() {
        this->filter_dogs();
        });

    QObject::connect(this->adopt_button, &QPushButton::clicked, [this]() {
        this->adopt();
        });
}

void UserGUI::buildGUI()
{
    QVBoxLayout* main_layout = new QVBoxLayout{ this };

    main_layout->setContentsMargins(20, 20, 20, 20);
    main_layout->setSpacing(15);

    QGroupBox* filters_group = new QGroupBox("Filters");
    QGridLayout* top_layout = new QGridLayout{ filters_group };
    top_layout->setSpacing(15);

    QLabel* breed_label = new QLabel{ "Enter breed to filter by (empty for all):" };
    QLabel* age_label = new QLabel{ "Enter maximum age (empty for all):" };
    this->breed_edit = new QLineEdit{};
    this->age_edit = new QLineEdit{};

    top_layout->addWidget(breed_label, 0, 0);
    top_layout->addWidget(breed_edit, 0, 1);
    top_layout->addWidget(age_label, 1, 0);
    top_layout->addWidget(age_edit, 1, 1);

    this->see_dogs_button = new QPushButton{"Display dogs"};
    top_layout->addWidget(this->see_dogs_button, 2, 1);

    main_layout->addWidget(filters_group);
    
    QGroupBox* display_group = new QGroupBox();
    QVBoxLayout* middle_layout = new QVBoxLayout{ display_group };
    this->dog_label = new QLabel{ "\nDog information will appear here\n:) \n"};
    this->dog_label->setAlignment(Qt::AlignCenter);
    middle_layout->addWidget(dog_label);

    QHBoxLayout* middle_buttons_layout = new QHBoxLayout{};
    this->adopt_button = new QPushButton{ "Adopt" };
    middle_buttons_layout->addWidget(this->adopt_button);
    this->next_button = new QPushButton{ "Next" };
    middle_buttons_layout->addWidget(this->next_button);
    middle_layout->addLayout(middle_buttons_layout);

    main_layout->addStretch();
    main_layout->addWidget(display_group);

    QHBoxLayout* button_layout = new QHBoxLayout{};
    this->adoption_list_button = new QPushButton{ "My adoption list" };
    this->back_button = new QPushButton{ "Back" };
    button_layout->addWidget(this->back_button);
    button_layout->addWidget(this->adoption_list_button);

    main_layout->addStretch();
    main_layout->addLayout(button_layout);

}

void UserGUI::adoption_list_widget()
{
    QWidget* adoption_list_window = new QWidget{};
    QVBoxLayout* adoption_list_layout = new QVBoxLayout{ adoption_list_window };

    this->adoption_table = new QTableView{};
    this->adoption_model = new AdoptionListTableModel{ this->user_service };
    this->adoption_table->setModel(this->adoption_model);

    this->adoption_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QGroupBox* list_group = new QGroupBox{ "My adoption list" };
    QVBoxLayout* table_layout = new QVBoxLayout{ list_group };
    table_layout->addWidget(this->adoption_table);

    adoption_list_layout->addWidget(list_group);

    this->open_button = new QPushButton{ "Open" };
    QObject::connect(this->open_button, &QPushButton::clicked, [this]() {
        this->open();
        });

    adoption_list_layout->addWidget(open_button);

    adoption_list_window->resize(500, 300);
    adoption_list_window->show();
}

void UserGUI::choose_file_widget()
{
    QMessageBox msg_box;
    msg_box.setWindowTitle("Choose File Type");
    msg_box.setText("What type of file would you like to save the adoption list in?");

    QPushButton* csv_button = msg_box.addButton("CSV", QMessageBox::ActionRole);
    QPushButton* html_button = msg_box.addButton("HTML", QMessageBox::ActionRole);

    msg_box.exec();

    if (msg_box.clickedButton() == csv_button) {
        this->csv();
    }
    else if (msg_box.clickedButton() == html_button) {
        this->html();
    }
    else {
        this->csv();
    }
}

void UserGUI::show_current_dog()
{
    if (this->dogs_to_display.empty()) {
        this->dog_label->setText("No dogs left to adopt!");
        return;
    }

    Dog current = this->dogs_to_display[this->current_index];
    this->dog_label->setText(QString::fromStdString("Name: " + current.get_name() + "\nBreed: " + current.get_breed() +
        "\nAge: " + std::to_string(current.get_age())));

    QDesktopServices::openUrl(QUrl(QString::fromStdString(current.get_photograph())));
}

void UserGUI::filter_dogs()
{
    QString breed = this->breed_edit->text();
    QString age_string = this->age_edit->text();
    int age = 100;

    if (!age_string.isEmpty()) {
        bool is_num;
        age = age_string.toInt(&is_num);

        if (!is_num) {
            QMessageBox::warning(this, "Error", "Age must be a valid number!");
            return;
        }
    }

    this->dogs_to_display = this->user_service.get_filtered_dogs(breed.toStdString(), age);
    this->current_index = 0;
    this->show_current_dog();

}

void UserGUI::next()
{
    if (this->dogs_to_display.empty()) {
        return;
    }
    this->current_index++;
    if (this->current_index >= this->dogs_to_display.size()) {
        this->current_index = 0;
    }
    this->show_current_dog();
}

void UserGUI::adopt()
{
    if (this->dogs_to_display.empty()) {
        return;
    }
    try {
        Dog dog_to_adopt = this->dogs_to_display[this->current_index];

        if (this->adoption_model != nullptr) {
            this->adoption_model->add_dog(dog_to_adopt);
        }
        else {
            this->user_service.adopt_dog(dog_to_adopt);
        }

        this->dogs_to_display.erase(this->dogs_to_display.begin() + this->current_index);

        if (this->current_index >= this->dogs_to_display.size()) {
            this->current_index = 0;
        }
        this->show_current_dog();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void UserGUI::open()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(QString::fromStdString(this->filename)).absoluteFilePath()));
}

void UserGUI::csv()
{
    user_service.set_adoption_list(new CSVAdoptionList("my_adoption_list.csv"));
    this->filename = "my_adoption_list.csv";
}

void UserGUI::html()
{
    user_service.set_adoption_list(new HTMLAdoptionList("my_adoption_list.html"));
    this->filename = "my_adoption_list.html";
}
