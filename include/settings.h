//
// Created by Sakata on 2021/11/4.
//

#ifndef SIMPLECAL_SETTINGS_H
#define SIMPLECAL_SETTINGS_H

#include <QByteArray>
#include <QSettings>

class Settings {
public:
    enum BG_COLOR {
        BASIC,
        PERCENT,
        RELATIVE
    };

    static void init();

    static void save_window_geometry(const QByteArray &state);

    static QByteArray load_window_geometry();

    static void save_font_size(int size);

    static int load_font_size();

    static void save_bg_color(Settings::BG_COLOR color, const QString &hex_color);

    static QString load_bg_color(Settings::BG_COLOR color);

    static void reset_bg_color(Settings::BG_COLOR color);

private:
    static const char *bg_keys_[];
};


#endif //SIMPLECAL_SETTINGS_H
