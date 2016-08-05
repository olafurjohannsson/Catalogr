#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "system.h"

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
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClicked(QListWidgetItem*)));
    qDebug() << "pid in item ctor: " << getpid();

    char hostname[256];
    char username[256];
    gethostname(hostname, 256);
    getlogin_r(username, 256);

    qDebug() << QString("Hostname: %1 - Username: %2").arg(hostname).arg(username);

    ui->lblHostname->setText(hostname);
    ui->lblUsername->setText(username);

    int threadCount = QThread::idealThreadCount();
    ui->lblCores->setText(QString("%1 Cores").arg(threadCount));
    int memSize = (getMemorySize() / 1024 / 1024 / 1024);
    ui->lblMemory->setText(QString("%1 GB").arg(memSize));


}

/*
 * Scan your computer and post the info on a secret link for you to view
 * */

void MainWindow::itemClicked(QListWidgetItem *item)
{
    QString text = item->text();

    QFileInfo fileInfo(text);

    QDateTime dt = fileInfo.created();
    QDateTime mod = fileInfo.lastModified();
    QDateTime read = fileInfo.lastRead();

    if (fileInfo.isFile())
    {
        ui->txtMeta->setText(
                    QString("Size: %1 bytes\nCreated: %2\nPath: %3\nFilename: %4\nModified: %5\nRead: %6\nExec: %7\nSymlink: %8\nHidden: %9")
                    .arg(fileInfo.size())
                    .arg(dt.toString())
                    .arg(fileInfo.path())
                    .arg(fileInfo.fileName())
                    .arg(mod.toString())
                    .arg(read.toString())
                    .arg(fileInfo.isExecutable() ? "Executable" : "Not executable")
                    .arg(fileInfo.isSymLink() ? "Symlink" : "No symlink")
                    .arg(fileInfo.isHidden() ? "Hidden" : "Not hidden"));
    }
    else {
        qDebug() << "pid in itemCliced: " << getpid();
        //Worker* worker = new Worker(ui->txtMeta, text);
        //worker->process();
    }
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
        this->updateList(data);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
