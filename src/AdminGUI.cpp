#include "AdminGUI.h"
#include "Exceptions.h"
#include "ChartWidget.h"
#include <QShortcut>
#include <QMessageBox>
#include <QHBoxLayout>
#include <qgridlayout.h>
#include <qlabel.h>
#include <QGroupBox>

AdminGUI::AdminGUI(AdminService& admin_service, QStackedWidget* stacked_widget) : 
	admin_service{ admin_service }, stacked_widget{stacked_widget}
{
	this->buildGUI();
	this->populate_list();

	QObject::connect(this->add_button, &QPushButton::clicked,
		this, &AdminGUI::add);

	QObject::connect(this->remove_button, &QPushButton::clicked,
		this, &AdminGUI::remove);

	QObject::connect(this->update_button, &QPushButton::clicked,
		this, &AdminGUI::update);
	
	QObject::connect(this->dogs_list, &QListWidget::itemSelectionChanged,
		this, &AdminGUI::selection);

	QObject::connect(this->back_button, &QPushButton::clicked, [this]() {
		this->name_edit->clear();
		this->breed_edit->clear();
		this->age_edit->clear();
		this->photo_edit->clear();
		this->stacked_widget->setCurrentIndex(0);
		});

	QObject::connect(chart_button, &QPushButton::clicked, [this]() {
		ChartWidget* chart = new ChartWidget{ this->admin_service.get_dogs() };
		chart->setWindowTitle("Dog Breed Statistics");
		chart->resize(600, 400);
		chart->show();
		});

	QObject::connect(this->undo_button, &QPushButton::clicked, this, &AdminGUI::undo);
	QObject::connect(this->redo_button, &QPushButton::clicked, this, &AdminGUI::redo);

	QShortcut* undo_shortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QObject::connect(undo_shortcut, &QShortcut::activated, this, &AdminGUI::undo);

	QShortcut* redo_shortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
	QObject::connect(redo_shortcut, &QShortcut::activated, this, &AdminGUI::redo);
}

void AdminGUI::buildGUI()
{
	QHBoxLayout* main_layout = new QHBoxLayout{ this };

	this->dogs_list = new QListWidget{};
	QFont listFont = this->dogs_list->font();
	listFont.setBold(true);
	this->dogs_list->setFont(listFont);
	main_layout->addWidget(this->dogs_list);

	main_layout->setContentsMargins(20, 20, 20, 20);
	main_layout->setSpacing(15);

	QGroupBox* form_group = new QGroupBox("Options");
	QGridLayout* right_layout = new QGridLayout{ form_group };
	right_layout->setSpacing(10);

	QLabel* name_label = new QLabel{ "Name" };
	QLabel* breed_label = new QLabel{ "Breed" };
	QLabel* age_label = new QLabel{ "Age" };
	QLabel* photo_label = new QLabel{ "Photo" };
	this->name_edit = new QLineEdit{};
	this->breed_edit = new QLineEdit{};
	this->age_edit = new QLineEdit{};
	this->photo_edit = new QLineEdit{};

	right_layout->addWidget(name_label, 0, 0);
	right_layout->addWidget(name_edit, 0, 1);
	right_layout->addWidget(breed_label, 1, 0);
	right_layout->addWidget(breed_edit, 1, 1);
	right_layout->addWidget(age_label, 2, 0);
	right_layout->addWidget(age_edit, 2, 1);
	right_layout->addWidget(photo_label, 3, 0);
	right_layout->addWidget(photo_edit, 3, 1);

	QGridLayout* button_layout = new QGridLayout{};
	this->add_button = new QPushButton{ "Add" };
	this->remove_button = new QPushButton{ "Remove" };
	this->update_button = new QPushButton{ "Update" };
	this->chart_button = new QPushButton{ "Chart" };
	this->back_button = new QPushButton{ "Back" };
	this->undo_button = new QPushButton{ "Undo" };
	this->redo_button = new QPushButton{ "Redo" };
	button_layout->addWidget(this->add_button);
	button_layout->addWidget(this->remove_button);
	button_layout->addWidget(this->update_button);
	button_layout->addWidget(this->chart_button);
	button_layout->addWidget(this->back_button);
	button_layout->addWidget(this->undo_button);
	button_layout->addWidget(this->redo_button);
	right_layout->addLayout(button_layout, 4, 0, 1, 2);

	main_layout->addWidget(form_group);

}

void AdminGUI::populate_list()
{
	this->dogs_list->clear();
	std::vector<Dog> dogs = this->admin_service.get_dogs();
	for (auto& d : dogs) {
		std::string str = d.get_name() + ", " + d.get_breed() + ", " + std::to_string(d.get_age());
		this->dogs_list->addItem(QString::fromStdString(str));
	}
}

void AdminGUI::add()
{
	QString name = this->name_edit->text();
	QString breed = this->breed_edit->text();
	QString age_string = this->age_edit->text();
	QString photo = this->photo_edit->text();
	try {
		bool is_num;
		int age = age_string.toInt(&is_num);

		if (!is_num) {
			throw UIException("Age must be a valid number!");
		}

		this->admin_service.add_dog(breed.toStdString(), name.toStdString(), age, photo.toStdString());
		this->populate_list();
	}
	catch (std::exception& e) {
		QMessageBox::warning(this, "Error", e.what());
	}
	this->name_edit->clear();
	this->breed_edit->clear();
	this->age_edit->clear();
	this->photo_edit->clear();
}

void AdminGUI::remove()
{
	QString name = this->name_edit->text();
	QString breed = this->breed_edit->text();
	QString age_string = this->age_edit->text();
	QString photo = this->photo_edit->text();
	try {
		if (!(age_string.isEmpty() && photo.isEmpty())) {
			throw UIException("To remove a dog from the list you only need the name and the breed");
		}

		this->admin_service.delete_dog(breed.toStdString(), name.toStdString());
		this->populate_list();
	}
	catch (std::exception& e) {
		QMessageBox::warning(this, "Error", e.what());
	}
	this->name_edit->clear();
	this->breed_edit->clear();
	this->age_edit->clear();
	this->photo_edit->clear();
}

void AdminGUI::update()
{
	QString name = this->name_edit->text();
	QString breed = this->breed_edit->text();
	QString age_string = this->age_edit->text();
	QString photo = this->photo_edit->text();
	try {
		if (!age_string.isEmpty() && !photo.isEmpty()) {
			throw UIException("You can only update one of the fields 'Age' or 'Photo' at once");
		}
		else if (age_string.isEmpty() && photo.isEmpty()) {
			throw UIException("You need to fill either the 'Age' or the 'Photo' field in order to update something");
		}
		else if (photo.isEmpty()) {
			bool is_num;
			int age = age_string.toInt(&is_num);

			if (!is_num) {
				throw UIException("Age must be a valid number!");
			}

			this->admin_service.update_dog_age(breed.toStdString(), name.toStdString(), age);
			this->populate_list();
		}
		else if (age_string.isEmpty()) {
			this->admin_service.update_dog_photograph(breed.toStdString(), name.toStdString(), photo.toStdString());
			this->populate_list();
		}

	}
	catch (std::exception& e) {
		QMessageBox::warning(this, "Error", e.what());
	}
	this->name_edit->clear();
	this->breed_edit->clear();
	this->age_edit->clear();
	this->photo_edit->clear();
}

void AdminGUI::back()
{}

void AdminGUI::selection()
{
	auto indexes = this->dogs_list->selectionModel()->selectedIndexes();
	int i = -1;
	if (indexes.size() > 0) {
		i = indexes[0].row();
	}
	if (i == -1) {
		return;
	}
	Dog dog = this->admin_service.get_dogs()[i];
	this->name_edit->setText(QString::fromStdString(dog.get_name()));
	this->breed_edit->setText(QString::fromStdString(dog.get_breed()));
	this->age_edit->setText(QString::number(dog.get_age()));
	this->photo_edit->setText(QString::fromStdString(dog.get_photograph()));
}

void AdminGUI::undo()
{
	try {
		this->admin_service.undo();
		this->populate_list();
	}
	catch (std::exception& e) {
		QMessageBox::warning(this, "Error", e.what());
	}
}

void AdminGUI::redo()
{
	try {
		this->admin_service.redo();
		this->populate_list();
	}
	catch (std::exception& e) {
		QMessageBox::warning(this, "Error", e.what());
	}
}

