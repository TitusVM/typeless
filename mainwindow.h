#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QLineEdit>
#include <QStyle>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;

    QLineEdit *input;
    QLabel *output;
    QPushButton *button;

    void setupUI();

private slots:
    void find();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
