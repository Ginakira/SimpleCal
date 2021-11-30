#include "include/settings_dialog.h"
#include "./ui/ui_settings_dialog.h"

#include <QDebug>
#include <QColorDialog>

#define DEFAULT_TEXT "默认"

SettingsDialog::SettingsDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::SettingsDialog) {
    ui->setupUi(this);

    update_settings_label();

    connect(ui->ok_button, &QPushButton::clicked, this, [this]() {
        save_settings();
        SettingsDialog::accept();
    });
    connect(ui->apply_button, &QPushButton::clicked, this, [this]() {
        save_settings();
        emit applied();
    });
    connect(ui->cacel_button, &QPushButton::clicked, this, &SettingsDialog::reject);

    // 绑定颜色选择按钮
    connect(ui->change_basic_bg_color_button, &QPushButton::clicked, this, [this]() {
        change_background_button_clicked(Settings::BG_COLOR::BASIC, ui->basic_bg_color_label);
    });

    connect(ui->change_percent_bg_color_button, &QPushButton::clicked, this, [this]() {
        change_background_button_clicked(Settings::BG_COLOR::PERCENT, ui->percent_bg_color_label);
    });
    connect(ui->change_relative_bg_color_button, &QPushButton::clicked, this, [this]() {
        change_background_button_clicked(Settings::BG_COLOR::PERCENT, ui->relative_bg_color_label);
    });
    // 绑定颜色重置按钮
    connect(ui->reset_basic_bg_color_button, &QPushButton::clicked, this, [this]() {
        reset_background_button_clicked(Settings::BG_COLOR::BASIC, ui->basic_bg_color_label);
    });
    connect(ui->reset_percent_bg_color_button, &QPushButton::clicked, this, [this]() {
        reset_background_button_clicked(Settings::BG_COLOR::PERCENT, ui->percent_bg_color_label);
    });
    connect(ui->reset_relative_bg_color_button, &QPushButton::clicked, this, [this]() {
        reset_background_button_clicked(Settings::BG_COLOR::RELATIVE, ui->relative_bg_color_label);
    });
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::save_settings() {
    // 保存字号
    Settings::save_font_size(ui->font_size_spin_box->value());
    // 保存背景色
    Settings::save_bg_color(Settings::BG_COLOR::BASIC, ui->basic_bg_color_label->text());
    Settings::save_bg_color(Settings::BG_COLOR::PERCENT, ui->percent_bg_color_label->text());
    Settings::save_bg_color(Settings::BG_COLOR::RELATIVE, ui->relative_bg_color_label->text());

}

void SettingsDialog::update_settings_label() {
    int font_size = Settings::load_font_size();
    ui->font_size_spin_box->setValue(font_size);

    QString basic_bg = Settings::load_bg_color(Settings::BASIC);
    QString percent_bg = Settings::load_bg_color(Settings::PERCENT);
    QString relative_bg = Settings::load_bg_color(Settings::RELATIVE);

    ui->basic_bg_color_label->setText(basic_bg.isEmpty() ? DEFAULT_TEXT : basic_bg);
    ui->percent_bg_color_label->setText(percent_bg.isEmpty() ? DEFAULT_TEXT : percent_bg);
    ui->relative_bg_color_label->setText(relative_bg.isEmpty() ? DEFAULT_TEXT : relative_bg);
}

void SettingsDialog::change_background_button_clicked(Settings::BG_COLOR bg_color, QLabel *label) {
    QColorDialog dialog;
    dialog.setCurrentColor(QColor(Settings::load_bg_color(bg_color)));
    connect(&dialog, &QColorDialog::colorSelected, this, [&, this](const QColor &color) {
        Settings::save_bg_color(bg_color, color.name());
        label->setText(color.name());
    });
    dialog.exec();
}

void SettingsDialog::reset_background_button_clicked(Settings::BG_COLOR bg_color, QLabel *label) {
    Settings::reset_bg_color(bg_color);
    label->setText(DEFAULT_TEXT);
}
