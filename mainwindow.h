#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QLineEdit>
#include <QStyle>

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;

    QLineEdit *input;
    QLabel *output;
    QPushButton *button;

    void addStyles();

private slots:
    void find();
    void updateText(const QString& text);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
