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

    // valid
    if (!txt.isEmpty()) {
        // check if folder
        QDir dir(txt);
        if (dir.exists()) {

            // set UI
            ui->lineEdit->setText(txt);
            ui->listWidget->clear();

            // iterate directory
            QDirIterator iterator(txt, QDir::Dirs | QDir::Files);

            QStringList items;
            while (iterator.hasNext()) {
                QString item = iterator.next();
                if (item.endsWith("/.")) {
                    continue;
                }

                QFileInfo fileInfo(item);
                if (fileInfo.isFile()) {
                    item = QString("%1 (%2) bytes").arg(item).arg(fileInfo.size());
                }

                items.append(item);
            }

            // add to UI
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
