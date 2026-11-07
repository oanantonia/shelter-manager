#pragma once
#include <QAbstractTableModel>
#include "UserService.h"

class AdoptionListTableModel : public QAbstractTableModel {
private:
    UserService& service;

public:
    AdoptionListTableModel(UserService& service, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void add_dog(const Dog& dog);
};  