#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // start with root
    this->updateList("/");
    this->ui->lineEdit->setText("/");

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClicked(QListWidgetItem*)));
}

void MainWindow::updateList(QString txt) {
    qDebug() << txt;
    if (!txt.isEmpty()) {
        // check if folder
        QDir dir(txt);
        if (dir.exists()) {
            ui->listWidget->clear();

            QDirIterator iterator(txt);

            QStringList items;
            while (iterator.hasNext()) {
                items.append(iterator.next());
            }
            ui->listWidget->addItems(items);
        }
    }
}

// text changed in list box
void MainWindow::textChanged(QString txt)
{
    this->updateList(txt);
}

void MainWindow::itemDoubleClicked(QListWidgetItem *item)
{
    QString data = item->text();

    // going up a dir
    if (data.endsWith("/..")) {
        // remove last ..
        QString filter = data.mid(0, data.lastIndexOf("/.."));

        // remove current dir
        this->updateList(filter.mid(0, filter.lastIndexOf("/") + 1));
    }
    else {
        this->updateList(item->text());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
