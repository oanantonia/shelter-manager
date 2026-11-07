#include <QApplication>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "AdminGUI.h"
#include "UserGUI.h"
#include "TextFileRepository.h"
#include "CSVAdoptionList.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    TextFileRepository repo{ "dogs.txt" };
    AdminService admin_srv{ repo };
    UserService user_srv{ repo };
    user_srv.set_adoption_list(new CSVAdoptionList("my_adoptions.csv"));

    //a.setStyle("Fusion");
    //QPalette palette;
    //palette.setColor(QPalette::Window, Qt::white/*QColor(255, 245, 248)*/);
    //palette.setColor(QPalette::WindowText, QColor(110, 99, 110));
    //palette.setColor(QPalette::Base, Qt::white);
    //palette.setColor(QPalette::Text, QColor(110, 99, 110));
    //palette.setColor(QPalette::Button, QColor(255, 240, 248)/*QColor(245, 200, 215)*/);
    //palette.setColor(QPalette::ButtonText, QColor(110, 99, 110));
    //palette.setColor(QPalette::Highlight, QColor(220, 180, 220));
    //palette.setColor(QPalette::HighlightedText, Qt::white);
    //a.setPalette(palette);
    a.setStyleSheet("QPushButton, QLabel { font-weight: bold; }");

    QStackedWidget* widget_stack = new QStackedWidget{};
    QWidget* start_screen = new QWidget{};
    QVBoxLayout* start_layout = new QVBoxLayout{ start_screen };

    start_layout->setContentsMargins(20, 20, 20, 20);
    start_layout->setSpacing(15);

    QLabel* welcome_label = new QLabel{ "Welcome to the Dog Shelter!" };
    welcome_label->setStyleSheet("font-family: 'Verdana'; font-size: 25px; font-weight: bold;");
    welcome_label->setAlignment(Qt::AlignCenter);

    QPushButton* admin_mode_button = new QPushButton{ "Admin Mode" };
    QPushButton* user_mode_button = new QPushButton{ "User Mode" };

    start_layout->addStretch();
    start_layout->addStretch();
    start_layout->addWidget(welcome_label);
    start_layout->addStretch();

    QHBoxLayout* button_layout = new QHBoxLayout{};
    button_layout->addWidget(admin_mode_button);
    button_layout->addWidget(user_mode_button);

    start_layout->addStretch();
    start_layout->addLayout(button_layout);
    start_layout->addStretch();

    AdminGUI* admin_gui = new AdminGUI{ admin_srv, widget_stack };
    UserGUI* user_gui = new UserGUI{ user_srv, widget_stack };

    widget_stack->addWidget(start_screen);
    widget_stack->addWidget(admin_gui);
    widget_stack->addWidget(user_gui);

    QObject::connect(admin_mode_button, &QPushButton::clicked, [widget_stack]() {
        widget_stack->setCurrentIndex(1);
    });

    QObject::connect(user_mode_button, &QPushButton::clicked, [widget_stack, user_gui]() {
        widget_stack->setCurrentIndex(2), user_gui->choose_file_widget();
        });

    widget_stack->resize(600, 400);
    widget_stack->show();
    return a.exec();
}
