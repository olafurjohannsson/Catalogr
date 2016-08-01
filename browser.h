#include <QObject>
#include <QDir>
#include <QDirIterator>
#include <QDebug>

#ifndef BROWSER_H
#define BROWSER_H


class Browser
{
public:
    Browser();
    Browser(std::string dir);
    ~Browser();

public slots:

private:
    std::string _currentDirectory;
    void iterate();
};

#endif // BROWSER_H
