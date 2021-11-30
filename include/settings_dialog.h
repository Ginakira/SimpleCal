#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QLabel>

#include "include/settings.h"


namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    ~SettingsDialog() override;

signals:

    void applied();

private slots:

    void change_background_button_clicked(Settings::BG_COLOR bg_color, QLabel *label);

    void reset_background_button_clicked(Settings::BG_COLOR bg_color, QLabel *label);

private:
    void save_settings();

    void update_settings_label();

    Ui::SettingsDialog *ui;
};

#endif // SETTINGS_DIALOG_H
