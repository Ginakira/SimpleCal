#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>

#include "include/basic_cal_widget.h"
#include "include/percent_cal_widget.h"
#include "include/relative_cal_widget.h"
#include "include/settings_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:

    void handle_settings_action_triggered();

private:
    void save_window_geometry();

    void restore_window_geometry();

    void apply_font_size();

    void apply_background_color(Settings::BG_COLOR bg_color, QGroupBox *group_box);

    void apply_settings();

    Ui::MainWindow *ui;
    BasicCalWidget *basic_cal_widget_;
    PercentCalWidget *percent_cal_widget_;
    RelativeCalWidget *relative_cal_widget_;

    SettingsDialog *settings_dialog_{nullptr};
};

#endif // MAINWINDOW_H
