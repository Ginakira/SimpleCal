#include "include/mainwindow.h"
#include "include/config.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VER);
    w.setWindowTitle(
            QString("%1 v%2").arg(QCoreApplication::applicationName(),
                                  QCoreApplication::applicationVersion()));
    w.show();
    return a.exec();
}
