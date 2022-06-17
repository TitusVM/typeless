#include "keyboardwidget.h"

#include <QDebug>

KeyboardWidget::KeyboardWidget(std::vector<std::vector<int>> matrix, uint64_t *usage, int size, QWidget *parent) : QWidget(parent)
{
    this->matrix = matrix;
    this->usage = usage;
    this->size = size;

    this->updateData(this->usage);

    this->btnList = new QList<QPushButton*>();
    this->hBoxes = new QList<QHBoxLayout*>();
    this->mainLayout = new QVBoxLayout();
}

void KeyboardWidget::updateData(uint64_t* usage)
{
    this->min = UINT64_MAX;
    this->max = 0;
    this->usage = usage;

    for (size_t j = 0; j < this->size; ++j)
    {
        if (this->usage[j] > max)
        {
            this->max = this->usage[j];
        }
        if (this->usage[j] < this->min)
        {
            this->min = this->usage[j];
        }
    }
}

void KeyboardWidget::createUI()
{
    for (int i = 0; i < matrix.size(); i++)
    {
        QHBoxLayout *hbox = new QHBoxLayout();
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if(matrix[i][j] != 0)
            {
                QString letter = QString((char)(matrix[i][j]));QPushButton *button = new QPushButton(letter);
                uint64_t current = this->usage[matrix[i][j] - 65];
                double normalisation = 0;

                if(this->max != 0)
                {
                    normalisation = ((double)current - (double)this->min) / ((double)this->max - (double)this->min);
                }

                QString color = QString::number((int)(normalisation*(double)255));
                QString textColor = QString::number((int)((double)255 - normalisation*(double)255));
                QString text("color: rgb(255," + textColor + "," + textColor + "); ");
                QString s(text + "background: rgb(" + color +  "," + color + ",255);");
                button->setStyleSheet(s);
                hbox->addWidget(button);
            }
            else
            {
                hbox->addSpacerItem(new QSpacerItem(50,20));
            }
        }
        this->hBoxes->append(hbox);
    }

    for (int i = 0; i < this->hBoxes->size(); i++)
    {
        this->mainLayout->addLayout(this->hBoxes->at(i));
    }
    setLayout(this->mainLayout);
    emit signalLoaded();
}
