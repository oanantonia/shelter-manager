#include "AdoptionListTableModel.h"

AdoptionListTableModel::AdoptionListTableModel(UserService& service, QObject* parent) : QAbstractTableModel(parent), service(service)
{}

int AdoptionListTableModel::rowCount(const QModelIndex& parent) const
{
    return this->service.get_adoption_list().size();
}

int AdoptionListTableModel::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant AdoptionListTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (role == Qt::DisplayRole) {
        Dog d = this->service.get_adoption_list()[index.row()];

        if (index.column() == 0) {
            return QString::fromStdString(d.get_name());
        }
        else if (index.column() == 1) {
            return QString::fromStdString(d.get_breed());
        }
        else if (index.column() == 2) {
            return QString::number(d.get_age());
        }
        else if (index.column() == 3) {
            return QString::fromStdString(d.get_photograph());
        }
    }
    return QVariant();
}

QVariant AdoptionListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return "Name";
        }
        else if (section == 1) {
            return "Breed";
        }
        else if (section == 2) {
            return "Age";
        }
        else if (section == 3) {
            return "Photograph";
        }    
    }
    return QVariant();
}

void AdoptionListTableModel::add_dog(const Dog& dog)
{
    int newRow = this->service.get_adoption_list().size();
    this->beginInsertRows(QModelIndex(), newRow, newRow);
    this->service.adopt_dog(dog);
    this->endInsertRows();
}
