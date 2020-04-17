#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	//w.setStyleSheet(line);
    w.show();

    return a.exec();
}
