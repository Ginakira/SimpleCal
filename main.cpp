#include "include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString("SimpleCal v%1").arg(QCoreApplication::applicationVersion()));
    w.show();
    return a.exec();
}
