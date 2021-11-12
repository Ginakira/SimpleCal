//
// Created by Sakata on 2021/11/4.
//

#include "include/utils.h"

/**
 * 生成一个数字校验器
 * @param reg_str 正则表达式（默认为正负整数和任意位数浮点数）
 * @return 用于输入框验证的校验器
 */
QRegExpValidator *Utils::generate_number_validator(const QString &reg_str) {
    return new QRegExpValidator(QRegExp(reg_str));
}

/**
 * 验证字符串是否是合法的数字字符串
 * @param str 待校验的字符串
 * @return {是否合法，转换结果}
 */
std::tuple<bool, double> Utils::validate_str_is_number(const QString &str) {
    bool valid = false;
    double num = str.toDouble(&valid);
    return {valid, num};
}
