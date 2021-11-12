#include "include/percent_cal_widget.h"
#include "./ui/ui_percent_cal_widget.h"

#include <QDebug>
#include <QTimer>
#include <QEvent>

#include "include/utils.h"

PercentCalWidget::PercentCalWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::PercentCalWidget) {
    ui->setupUi(this);

    // 设置输入框校验器
    number_validator_ = Utils::generate_number_validator();
    ui->input_a_edit->setValidator(number_validator_);
    ui->input_percent_edit->setValidator(number_validator_);

    // 构建计算按钮及其计算方法数组
    cal_buttons_[0] = std::make_tuple(ui->add_button, [](double a, double percent) {
        return a * (1 + percent);
    });
    cal_buttons_[1] = std::make_tuple(ui->sub_button, [](double a, double percent) {
        return a * (1 - percent);
    });
    cal_buttons_[2] = std::make_tuple(ui->mul_button, [](double a, double percent) {
        return a * percent;
    });
    cal_buttons_[3] = std::make_tuple(ui->div_button, [](double a, double percent) {
        return a / percent;
    });

    // 绑定输入框文字改变事件
    connect(ui->input_a_edit, &QLineEdit::textChanged, this, &PercentCalWidget::recalculate);
    connect(ui->input_percent_edit, &QLineEdit::textChanged, this, &PercentCalWidget::recalculate);

    // 绑定计算方法按钮点击事件
    for (auto &[cal_button, _] : cal_buttons_) {
        connect(cal_button, &QPushButton::clicked, this, &PercentCalWidget::recalculate);
    }

    // 获得焦点时全选
    ui->input_a_edit->installEventFilter(this);
    ui->input_percent_edit->installEventFilter(this);
}

PercentCalWidget::~PercentCalWidget() {
    delete ui;
    delete number_validator_;
}

void PercentCalWidget::recalculate() {
// 检验输入框是否合法
    auto[input_a_valid, input_a_num] = Utils::validate_str_is_number(ui->input_a_edit->text());
    auto[input_percent_valid, input_percent_num] = Utils::validate_str_is_number(ui->input_percent_edit->text());
    if (!input_a_valid || !input_percent_valid) {
        ui->result_edit->clear();
        return;
    }

    // 查找当前激活的计算按钮并计算结果
    for (auto &[button, cal_func] : cal_buttons_) {
        if (button->isChecked()) {
            double result = cal_func(input_a_num, input_percent_num * 0.01);
            ui->result_edit->setText(QString::number(result));
            break;
        }
    }
}

bool PercentCalWidget::eventFilter(QObject *obj, QEvent *event) {
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
