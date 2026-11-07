#pragma once
#include <qwidget.h>
#include "AdminService.h"
#include "UserService.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QStackedWidget>

class AdminGUI : public QWidget
{
private:
	AdminService& admin_service;
	QStackedWidget* stacked_widget;

	QListWidget* dogs_list;
	QLineEdit* name_edit;
	QLineEdit* breed_edit;
	QLineEdit* age_edit;
	QLineEdit* photo_edit;
	QPushButton* add_button;
	QPushButton* remove_button;
	QPushButton* update_button;
	QPushButton* back_button;
	QPushButton* chart_button;
	QPushButton* undo_button;
	QPushButton* redo_button;

public:
	AdminGUI(AdminService& admin_service, QStackedWidget* stacked_widget);
	void buildGUI();
	void populate_list();
	void add();
	void remove();
	void update();
	void back();
	void selection();
	void undo();
	void redo();
};

