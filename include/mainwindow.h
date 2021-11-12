#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "include/basic_cal_widget.h"
#include "include/percent_cal_widget.h"
#include "include/relative_cal_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void save_settings();

    void load_settings();

    Ui::MainWindow *ui;
    BasicCalWidget *basic_cal_widget_;
    PercentCalWidget *percent_cal_widget_;
    RelativeCalWidget *relative_cal_widget_;
};

#endif // MAINWINDOW_H
