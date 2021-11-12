#ifndef RELATIVE_CAL_WIDGET_H
#define RELATIVE_CAL_WIDGET_H

#include <QWidget>
#include <QValidator>

namespace Ui {
class RelativeCalWidget;
}

class RelativeCalWidget : public QWidget {
Q_OBJECT

public:
    explicit RelativeCalWidget(QWidget *parent = nullptr);

    ~RelativeCalWidget() override;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:

    void recalculate();

private:
    Ui::RelativeCalWidget *ui;
    QValidator *number_validator_;
};

#endif // RELATIVE_CAL_WIDGET_H
