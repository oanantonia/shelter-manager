#pragma once
#include <qwidget.h>
#include <QTableView>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QTabWidget>
#include <QStackedWidget>
#include "UserService.h"
#include "AdoptionListTableModel.h"

class UserGUI : public QWidget
{
private:
	UserService& user_service;
	QStackedWidget* stacked_widget; 

	std::vector<Dog> dogs;
	std::vector<Dog> dogs_to_display;
	int current_index;

	std::string filename;

	QLineEdit* breed_edit;
	QLineEdit* age_edit;
	QLabel* dog_label;
	QPushButton* see_dogs_button;
	QPushButton* next_button;
	QPushButton* adopt_button;
	QPushButton* adoption_list_button;
	QPushButton* back_button;
	QPushButton* open_button;
	QTableView* adoption_table;
	AdoptionListTableModel* adoption_model;

public:
	UserGUI(UserService& user_service, QStackedWidget* stacked_widget);
	void buildGUI();
	void adoption_list_widget();
	void choose_file_widget();
	void show_current_dog();
	void filter_dogs();
	void next();
	void adopt();
	void open();
	void csv();
	void html();
};

