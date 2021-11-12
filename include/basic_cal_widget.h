#ifndef BASIC_CAL_WIDGET_H
#define BASIC_CAL_WIDGET_H

#include <QWidget>
#include <QValidator>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class BasicCalWidget;
}

class BasicCalWidget : public QWidget {
Q_OBJECT

public:
    explicit BasicCalWidget(QWidget *parent = nullptr);

    ~BasicCalWidget() override;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:

    void recalculate();

private:
    Ui::BasicCalWidget *ui;
    QValidator *number_validator_;
    std::array<std::tuple<QPushButton *, std::function<double(double, double)>>, 4> cal_buttons_;
};

#endif // BASIC_CAL_WIDGET_H
