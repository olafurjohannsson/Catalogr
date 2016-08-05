#include "worker.h"

Worker::Worker()
{

}

Worker::Worker(QTextBrowser *txtBrowser, QString text) {
    this->txtBrowser = txtBrowser;
    this->text = text;
/*
    this->thread = new QThread();
    this->moveToThread(this->thread);
    connect(this, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(this->thread, SIGNAL(started()), this, SLOT(process()));
    connect(this, SIGNAL(finished()), this->thread, SLOT(quit()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    connect(this->thread, SIGNAL(finished()), this->thread, SLOT(deleteLater()));
    this->thread->start();
    */
}

Worker::~Worker() {
    //delete this->txtBrowser;
}

void Worker::process() {
    qDebug() << "process";

    QDirIterator iterator(QDir(this->text), QDirIterator::Subdirectories);
    qint64 size = 0, files = 0;
    while (iterator.hasNext()) {
        QString item = iterator.next();
        QFileInfo innerFile(item);
        if (innerFile.isFile()) {
            files++;
            size += innerFile.size();
        }
    }

    this->txtBrowser->setText(QString("%1 files, Size: %2 bytes").arg(files).arg(size));
}

//void Worker::finished() { }

//void Worker::error(QString err) { }
