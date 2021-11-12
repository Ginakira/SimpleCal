#include "include/relative_cal_widget.h"
#include "./ui/ui_relative_cal_widget.h"

#include <QTimer>

#include "include/utils.h"

RelativeCalWidget::RelativeCalWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::RelativeCalWidget) {
    ui->setupUi(this);

    // 设置输入框校验器
    number_validator_ = Utils::generate_number_validator();
    ui->input_a_edit->setValidator(number_validator_);
    ui->input_b_edit->setValidator(number_validator_);

    // 绑定输入框文字改变事件
    connect(ui->input_a_edit, &QLineEdit::textChanged, this, &RelativeCalWidget::recalculate);
    connect(ui->input_b_edit, &QLineEdit::textChanged, this, &RelativeCalWidget::recalculate);

    // 获得焦点时全选
    ui->input_a_edit->installEventFilter(this);
    ui->input_b_edit->installEventFilter(this);
}

RelativeCalWidget::~RelativeCalWidget() {
    delete ui;
    delete number_validator_;
}

void RelativeCalWidget::recalculate() {
    // 检验输入框是否合法
    auto[input_a_valid, input_a_num] = Utils::validate_str_is_number(ui->input_a_edit->text());
    auto[input_b_valid, input_b_num] = Utils::validate_str_is_number(ui->input_b_edit->text());
    if (!input_a_valid || !input_b_valid) {
        ui->result_edit->clear();
        return;
    }

    double result = (input_b_num - input_a_num) / input_a_num * 100;
    ui->result_edit->setText(QString("%1%2")
                                     .arg(result > 0 ? "+" : "")
                                     .arg(result));
}

bool RelativeCalWidget::eventFilter(QObject *obj, QEvent *event) {
    switch (event->type()) {
        case QEvent::FocusIn: {
            QTimer::singleShot(0, qobject_cast<QLineEdit *>(obj), &QLineEdit::selectAll);
            return true;
        }
        default:
            break;
    }
    return QObject::eventFilter(obj, event);
}
