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

private:
    Ui::MainWindow *ui;
    void updateList(QString);
};

#endif // MAINWINDOW_H
