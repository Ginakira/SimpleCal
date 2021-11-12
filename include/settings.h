//
// Created by Sakata on 2021/11/4.
//

#ifndef SIMPLECAL_SETTINGS_H
#define SIMPLECAL_SETTINGS_H

#include <QByteArray>

class Settings {
public:
    static void init();

    static void save_window_geometry(const QByteArray &state);

    static QByteArray load_window_geometry();
};


#endif //SIMPLECAL_SETTINGS_H
