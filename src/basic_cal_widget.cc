#include "include/basic_cal_widget.h"
#include "./ui/ui_basic_cal_widget.h"

#include <QDebug>
#include <QTimer>
#include <QEvent>

#include "include/utils.h"

BasicCalWidget::BasicCalWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::BasicCalWidget) {
    ui->setupUi(this);

    // 设置输入框校验器
    number_validator_ = Utils::generate_number_validator();
    ui->input_a_edit->setValidator(number_validator_);
    ui->input_b_edit->setValidator(number_validator_);

    // 构建计算按钮及其计算方法数组
    cal_buttons_[0] = std::make_tuple(ui->add_button, [](double a, double b) {
        return a + b;
    });
    cal_buttons_[1] = std::make_tuple(ui->sub_button, [](double a, double b) {
        return a - b;
    });
    cal_buttons_[2] = std::make_tuple(ui->mul_button, [](double a, double b) {
        return a * b;
    });
    cal_buttons_[3] = std::make_tuple(ui->div_button, [](double a, double b) {
        return a / b;
    });

    // 绑定输入框文字改变事件
    connect(ui->input_a_edit, &QLineEdit::textChanged, this, &BasicCalWidget::recalculate);
    connect(ui->input_b_edit, &QLineEdit::textChanged, this, &BasicCalWidget::recalculate);

    // 绑定计算方法按钮点击事件
    for (auto &[cal_button, _] : cal_buttons_) {
        connect(cal_button, &QPushButton::clicked, this, &BasicCalWidget::recalculate);
    }

    // 获得焦点时全选
    ui->input_a_edit->installEventFilter(this);
    ui->input_b_edit->installEventFilter(this);
}

BasicCalWidget::~BasicCalWidget() {
    delete ui;
    delete number_validator_;
}

void BasicCalWidget::recalculate() {
    // 检验输入框是否合法
    auto[input_a_valid, input_a_num] = Utils::validate_str_is_number(ui->input_a_edit->text());
    auto[input_b_valid, input_b_num] = Utils::validate_str_is_number(ui->input_b_edit->text());
    if (!input_a_valid || !input_b_valid) {
        ui->result_edit->clear();
        return;
    }

    // 查找当前激活的计算按钮并计算结果
    for (auto &[button, cal_func] : cal_buttons_) {
        if (button->isChecked()) {
            double result = cal_func(input_a_num, input_b_num);
            ui->result_edit->setText(QString::number(result));
            break;
        }
    }
}

bool BasicCalWidget::eventFilter(QObject *obj, QEvent *event) {
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
