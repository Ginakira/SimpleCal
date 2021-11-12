#ifndef PERCENT_CAL_WIDGET_H
#define PERCENT_CAL_WIDGET_H

#include <QWidget>
#include <QValidator>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class PercentCalWidget;
}

class PercentCalWidget : public QWidget {
Q_OBJECT

public:
    explicit PercentCalWidget(QWidget *parent = nullptr);

    ~PercentCalWidget() override;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:

    void recalculate();

private:
    Ui::PercentCalWidget *ui;
    QValidator *number_validator_;
    std::array<std::tuple<QPushButton *, std::function<double(double, double)>>, 4> cal_buttons_;
};

#endif // PERCENT_CAL_WIDGET_H
