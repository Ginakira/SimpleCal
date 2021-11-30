#include "include/mainwindow.h"
#include "./ui/ui_mainwindow.h"
#include "include/settings.h"

#include <QCloseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    basic_cal_widget_ = new BasicCalWidget(this);
    percent_cal_widget_ = new PercentCalWidget(this);
    relative_cal_widget_ = new RelativeCalWidget(this);

    ui->basic_group_box->layout()->addWidget(basic_cal_widget_);
    ui->percent_group_box->layout()->addWidget(percent_cal_widget_);
    ui->relative_group_box->layout()->addWidget(relative_cal_widget_);

#ifdef Q_OS_WIN
    QFont font = QApplication::font();
    font.setFamily("Microsoft YaHei"); // Windows下设置字体为微软雅黑
    QApplication::setFont(font);
#endif

    // 恢复设置
    Settings::init();
    restore_window_geometry();
    apply_settings();

    // 菜单绑定
    connect(ui->settings_action, &QAction::triggered, this, &MainWindow::handle_settings_action_triggered);
}

MainWindow::~MainWindow() {
    delete ui;
    delete basic_cal_widget_;
    delete percent_cal_widget_;
    delete relative_cal_widget_;
    delete settings_dialog_;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    save_window_geometry();
    event->accept();
}

void MainWindow::save_window_geometry() {
    Settings::save_window_geometry(saveGeometry());
}

void MainWindow::apply_settings() {
    apply_font_size();
    apply_background_color(Settings::BG_COLOR::BASIC, ui->basic_group_box);
    apply_background_color(Settings::BG_COLOR::PERCENT, ui->percent_group_box);
    apply_background_color(Settings::BG_COLOR::RELATIVE, ui->relative_group_box);
}

void MainWindow::handle_settings_action_triggered() {
    if (!settings_dialog_) {
        settings_dialog_ = new SettingsDialog(this);
        connect(settings_dialog_, &SettingsDialog::accepted, this, [this]() {
            apply_settings();
        });
        connect(settings_dialog_, &SettingsDialog::applied, this, &MainWindow::apply_settings);
    }
    settings_dialog_->exec();
}

void MainWindow::restore_window_geometry() {
    QByteArray window_geometry = Settings::load_window_geometry();
    this->restoreGeometry(window_geometry);
}

void MainWindow::apply_font_size() {
    int size = Settings::load_font_size();
    this->setStyleSheet(QString("QLineEdit { font-size: %1px; }").arg(size));
    qDebug() << "SET FONT SIZE" << size;
}

void MainWindow::apply_background_color(Settings::BG_COLOR bg_color, QGroupBox *group_box) {
    QString hex_color = Settings::load_bg_color(bg_color);
    qDebug() << "SET BG_COLOR" << bg_color << hex_color;
    QString style_sheet;
    if (!hex_color.isEmpty()) {
        style_sheet += QString("background-color: %1;").arg(hex_color);
    }
    group_box->setStyleSheet(style_sheet);
}

