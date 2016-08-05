#ifndef WORKER_H
#define WORKER_H


#include <QObject>
#include <QString>
#include <QDir>
#include <QDirIterator>
#include <QTextBrowser>
#include <QDebug>

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker();
    Worker(QTextBrowser*, QString);
    ~Worker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);

private:
    QTextBrowser *txtBrowser;
    QString text;
    QThread *thread;
};

#endif // WORKER_H
