#include "include/mainwindow.h"
#include "./ui/ui_mainwindow.h"
#include "include/settings.h"

#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    load_settings();

    basic_cal_widget_ = new BasicCalWidget(this);
    percent_cal_widget_ = new PercentCalWidget(this);
    relative_cal_widget_ = new RelativeCalWidget(this);

    ui->basic_group_box->layout()->addWidget(basic_cal_widget_);
    ui->percent_group_box->layout()->addWidget(percent_cal_widget_);
    ui->relative_group_box->layout()->addWidget(relative_cal_widget_);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    save_settings();
    event->accept();
}

void MainWindow::save_settings() {
    Settings::save_window_geometry(saveGeometry());
}

void MainWindow::load_settings() {
    Settings::init();
    QByteArray window_geometry = Settings::load_window_geometry();
    restoreGeometry(window_geometry);
}
