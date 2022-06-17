#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>
#include <QList>
#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>

class KeyboardWidget : public QWidget
{
Q_OBJECT

public:
    KeyboardWidget(std::vector<std::vector<int>>, uint64_t*, int, QWidget *parent = nullptr);
    void createUI();
    void updateData(uint64_t*);

// PRIVATE METHODS
private:

// INPUTS
private:
    std::vector<std::vector<int>> matrix;
    uint64_t *usage;

// TOOLS
    int size;
    uint64_t max;
    uint64_t min;

// UI
private:
    QList<QPushButton*> *btnList;
    QList<QHBoxLayout*> *hBoxes;
    QVBoxLayout *mainLayout;

// SIGNALS
signals:
    void signalLoaded();
};

#endif // KEYBOARDWIDGET_H
