#ifndef TYPELESSUI_H
#define TYPELESSUI_H


#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QLineEdit>
#include <QStyle>
#include <QElapsedTimer>
#include <QListWidget>
#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QFuture>
#include <QtConcurrent>


#include "graph.h"
#include "keyboardwidget.h"

class TypelessUI : public QWidget
{

public:
    TypelessUI(QWidget *parent = nullptr);
    double getTotalDistance(QString string);
    double getTotalDistance(char* tab, int size);
    double getDistance(char s1, char s2);
    void parseFile(QString filePath);

private:
    Graph *graph;
    std::vector<std::vector<int>> matrix;
    uint64_t *usage;
    QElapsedTimer *timer;
    QThread parseThread;
    QList<KeyboardWidget*> *keyboards;


    void createKeyboard();
    double calculateDistance(char s1, char s2);


// UI
private:
    QTableView *tableView;
    QGridLayout *layout;

    QLineEdit *input;
    QLabel *outputTime;
    QListWidget *list;
    QListWidget *usageList;
    QPushButton *buttonFind;
    QPushButton *buttonBrowse;
    QPushButton *buttonACPC;

    void createUI();

// TABLE TOOLS
private:
    QStringList horizontalHeader;
    QStringList verticalHeader;

    QStandardItemModel *model;

    void createTable();
    void updateTable();
    void updateUsageList();

// SLOTS
private slots:
    void slotSearchPressed();
    void slotBrowsePressed();
    void slotACPCPressed();
    void slotShowKeyboard();

};

#endif // TYPELESSUI_H
