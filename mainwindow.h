#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QStringRef>
#include <QObject>
#include <QListWidgetItem>
#include <QDebug>
#include <QLabel>
#include <QStringBuilder>
#include <QDate>
#include <QDateTime>
#include <QFileInfo>
#include <QFileInfoList>
#include <QTextBrowser>
#include <QThread>

#include "browser.h"
#include "worker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void textChanged(QString);
    void itemDoubleClicked(QListWidgetItem*);
    void itemClicked(QListWidgetItem*);

private:
    Ui::MainWindow *ui;
    void updateList(QString);
    Browser browser;
};

#endif // MAINWINDOW_H
