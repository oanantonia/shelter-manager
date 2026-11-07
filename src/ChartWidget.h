#pragma once
#include <QWidget>
#include <vector>
#include <map>
#include <string>
#include "Dog.h"

class ChartWidget : public QWidget
{
private:
    std::map<std::string, int> breed_counts;

public:
    ChartWidget(const std::vector<Dog>& dogs, QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    void update_data(const std::vector<Dog>& dogs);
};