//
// Created by Sakata on 2021/11/4.
//

#ifndef SIMPLECAL_UTILS_H
#define SIMPLECAL_UTILS_H

#include <QRegExpValidator>

class Utils {
public:
    static QRegExpValidator *generate_number_validator(const QString &reg_str = R"(^(\-|\+)?\d+(\.\d+)?$)");

    static std::tuple<bool, double> validate_str_is_number(const QString &str);
};


#endif //SIMPLECAL_UTILS_H
