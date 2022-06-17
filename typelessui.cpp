#include "typelessui.h"
#define CHAR_COUNT 26
#define NB_ROWS 3
#define NB_COLUMNS 10



/*****************************************************************\
 *                        Constructors                           *
\*****************************************************************/

TypelessUI::TypelessUI(QWidget *parent) : QWidget(parent)
{
    this->graph = new Graph(CHAR_COUNT);
    this->layout = new QGridLayout();
    this->input = new QLineEdit();

    this->list = new QListWidget();

    this->outputTime = new QLabel("Time taken : ");
    this->buttonFind = new QPushButton("Chercher");
    this->buttonBrowse = new QPushButton("Choisir fichier");
    this->buttonACPC = new QPushButton("ACPC");

    createKeyboard();
    createTable();
    createUI();
}

/*****************************************************************\
 *                       Public Methods                          *
\*****************************************************************/

double TypelessUI::getTotalDistance(QString string)
{
    QString input = string;
    input = input.toUpper();
    int size = input.length();
    char *tab = new char[input.length()];
    memcpy(tab, input.toStdString().c_str(), input.size());
    double distance = this->getTotalDistance(tab, size);
    delete[] tab;
    this->list->addItem(string + " : " + QString::number(distance, 'f', 3));
    return distance;
}

/**
 * @brief TypelessUI::getTotalDistance
 * Calls TypelessUI::getDistance for each pair of letters in given char array
 * @param tab
 * @param size
 * @return total distance travelled on the keyboard while typing the word
 */
double TypelessUI::getTotalDistance(char* tab, int size)
{
    double distance = 0;
    for(int i = 0; i < size - 1; i++)
    {
        distance += this->getDistance(tab[i], tab[i+1]);
    }
    return distance;
}


/**
 * @brief TypelessUI::getDistance
 * Calculates the physical distance between two keys on the keyboard
 * @param s1 Starting character
 * @param s2 Ending character
 * @return total distance on the keyboard (between the two characters)
 */
double TypelessUI::getDistance(char s1, char s2)
{
    double distance = 0;
    distance = this->graph->getPonderation(s1, s2);
    if(distance == 0)
    {
        distance = calculateDistance(s1, s2);
    }
    this->updateTable();
    return distance;
}

void TypelessUI::parseFile(QString filePath)
{
    QFile *file = new QFile(filePath);
    if(file->open(QIODevice::ReadOnly))
    {
        QTextStream in(file);
        this->timer = new QElapsedTimer();
        this->timer->start();
        while(!in.atEnd())
        {
            QString word = in.readLine();
            getTotalDistance(word);
        }
        this->outputTime->setText("Time : " + QString::number(this->timer->elapsed()) + " ms");
    }
    else QMessageBox::information(0, "error", file->errorString());
}

/*****************************************************************\
 *                      Private Methods                          *
\*****************************************************************/

/**
 * @brief TypelessUI::updateTable
 * Function to update table contents
 */
void TypelessUI::updateTable()
{
    this->model = new QStandardItemModel();
    for(int i = 65; i < 65 + CHAR_COUNT; i++)
    {
        QList<QStandardItem*> *row = new QList<QStandardItem*>();
        for(int j = 65; j < 65 + CHAR_COUNT; j++)
        {
            double asdf = this->graph->getPonderation((char)i, (char)j);
            QStandardItem *col = new QStandardItem(QString::number(asdf));
            row->append(col);
        }
        this->model->insertRow(i - 65, *row);
    }
    this->model->setHorizontalHeaderLabels(horizontalHeader);
    this->model->setVerticalHeaderLabels(verticalHeader);
    this->tableView->setModel(this->model);
}

/**
 * @brief TypelessUI::calculateDistance
 * Calculates the physical distance between two keys on the keyboard
 * @param s1 Starting character
 * @param s2 Ending character
 * @return distance
 */
double TypelessUI::calculateDistance(char s1, char s2)
{
    double distance = 0;
    int firstIndex[2] = {-1, -1};
    int secondIndex[2] = {-1, -1};
    for(size_t i = 0; i < NB_ROWS; i++)
    {
        for(size_t j = 0; j < NB_COLUMNS; j++)
        {
            if (this->matrix[i][j] == s1)
            {
                firstIndex[0] = i + 1;
                firstIndex[1] = j + 1;
                break;
            }
        }
        if(firstIndex[0] != -1) break;
    }

    for(size_t i = 0; i < NB_ROWS; i++)
    {
        for(size_t j = 0; j < NB_COLUMNS; j++)
        {
            if (this->matrix[i][j] == s2)
            {
                secondIndex[0] = i + 1;
                secondIndex[1] = j + 1;
                break;
            }
        }
        if(secondIndex[0] != -1) break;
    }

    distance = sqrt(pow(firstIndex[0] - secondIndex[0],2) + pow(firstIndex[1] - secondIndex[1],2));
    this->graph->ajouterArc(s1, s2, distance);
    return distance;
}

/*****************************************************************\
 *                 Private Initialising Methods                  *
\*****************************************************************/
/**
 * @brief TypelessUI::createKeyboard
 * Initializes keyboard layout using a 2D int array
 */
void TypelessUI::createKeyboard()
{
    this->matrix =
    {
        {*"Q", *"W", *"E", *"R", *"T", *"Z", *"U", *"I", *"O", *"P"},
        {*"A", *"S", *"D", *"F", *"G", *"H", *"J", *"K", *"L", 0},
        {0, *"Y", *"X", *"C", *"V", *"B", *"N", *"M", 0, 0 }
    };
}

/**
 * @brief TypelessUI::createTable
 * Initializes model for the table view by filling it with characters and initial graph weights
 */
void TypelessUI::createTable()
{
    this->tableView = new QTableView();

    for(int i = 65; i < 65 + CHAR_COUNT; i++)
    {
        horizontalHeader.append(QChar(i));
        verticalHeader.append(QChar(i));
    }
    updateTable();
}

/**
 * @brief TypelessUI::createUI
 * Initializes UI elements and layout
 */
void TypelessUI::createUI()
{
    connect(this->buttonFind, &QPushButton::clicked, this, &TypelessUI::slotSearchPressed);
    connect(this->buttonBrowse, &QPushButton::clicked, this, &TypelessUI::slotBrowsePressed);
    connect(this->buttonACPC, &QPushButton::clicked, this, &TypelessUI::slotACPCPressed);

    this->layout->addWidget(this->input, 0,0,1,1);
    this->layout->addWidget(this->buttonFind, 0,1,1,1);
    this->layout->addWidget(this->buttonBrowse, 0,2,1,1);
    this->layout->addWidget(this->list, 1,0,1,1);
    this->layout->addWidget(this->buttonACPC, 1,2,1,1);
    this->layout->addWidget(this->outputTime, 1,1,1,1);

    this->tableView->show();

    setLayout(this->layout);
}


/*****************************************************************\
 *                       Private Slots                           *
\*****************************************************************/

void TypelessUI::slotSearchPressed()
{
    this->timer = new QElapsedTimer();
    this->timer->start();

    uint64_t lastRecordedTime = 0;
    uint64_t totalTime = 0;
    QList<QString> list = this->input->text().split(" ");
    double distance = 0;
    foreach(QString string, list)
    {
        lastRecordedTime = this->timer->elapsed();
        distance += this->getTotalDistance(string);
        lastRecordedTime = this->timer->elapsed() - lastRecordedTime;
        totalTime += lastRecordedTime;
    }
    this->outputTime->setText("Time : " + QString::number(totalTime) + " ms");
}

void TypelessUI::slotBrowsePressed()
{
    QString filePath =
            QFileDialog::getOpenFileName(this, "Open a text file", "./",
                                         "Text files (*.txt)");
    //this->parseFile(filePath);
    QFuture<void> future = QtConcurrent::run([=]{
        this->parseFile(filePath);
    });
}

void TypelessUI::slotACPCPressed()
{
    this->graph->parcoursACPC(*"B");
}
