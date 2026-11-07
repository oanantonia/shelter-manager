#include "ChartWidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <algorithm>

ChartWidget::ChartWidget(const std::vector<Dog>& dogs, QWidget* parent): QWidget{ parent }
{
    this->update_data(dogs);
}

void ChartWidget::update_data(const std::vector<Dog>& dogs)
{
    this->breed_counts.clear();
    for (const auto& dog : dogs) {
        this->breed_counts[dog.get_breed()]++;
    }
    this->repaint();
}

void ChartWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter{ this };
    painter.setRenderHint(QPainter::Antialiasing); 

    if (this->breed_counts.empty()) {
        painter.drawText(this->rect(), Qt::AlignCenter, "No dog data available to chart!");
        return;
    }

    int total_dogs = 0;
    for (const auto& pair : this->breed_counts) {
        total_dogs += pair.second;
    }

    int margin = 50;
    int pie_size = std::min(this->width(), this->height()) - 2 * margin;
    QRect pie_rect(margin, margin, pie_size, pie_size);

    std::vector<Qt::GlobalColor> colors = { Qt::cyan, Qt::magenta, Qt::yellow, Qt::green, Qt::red, Qt::darkBlue };
    int color_index = 0;

    int current_start_angle = 0;

    int legend_x = margin + pie_size + 40;
    int legend_y = margin + 20;

    for (const auto& pair : this->breed_counts) {
        std::string breed = pair.first;
        int count = pair.second;

        double percentage = (double)count / total_dogs;
        int span_angle = std::round(percentage * 360.0 * 16.0);

        painter.setBrush(QBrush(colors[color_index % colors.size()]));
        painter.drawPie(pie_rect, current_start_angle, span_angle);

        painter.drawRect(legend_x, legend_y, 15, 15);
        painter.setPen(Qt::black); 
        QString legend_text = QString::fromStdString(breed) + " (" + QString::number(count) + ")";
        painter.drawText(legend_x + 25, legend_y + 12, legend_text);

        current_start_angle += span_angle;
        legend_y += 30;
        color_index++;
    }
}