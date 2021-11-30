//
// Created by Sakata on 2021/11/4.
//

#include <QCoreApplication>
#include <QSettings>
#include "include/settings.h"
#include "include/config.h"

#define ORGANIZATION_NAME "GINAKIRA"
#define ORGANIZATION_DOMAIN "pmrfansub.tk"

#define WINDOW_GEOMETRY "window/geometry"
#define FONT_SIZE "display/font_size"
#define BASIC_BG_COLOR "display/basic_bg_color"
#define PERCENT_BG_COLOR "display/percent_bg_color"
#define RELATIVE_BG_COLOR "display/relative_bg_color"

#define DEFAULT_FONT_SIZE 30
#define DEFAULT_LABEL_TEXT "默认"

const char *Settings::bg_keys_[]{
        BASIC_BG_COLOR, PERCENT_BG_COLOR, RELATIVE_BG_COLOR
};


void Settings::init() {
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VER);
}

void Settings::save_window_geometry(const QByteArray &state) {
    QSettings settings;
    settings.setValue(WINDOW_GEOMETRY, state);
}

QByteArray Settings::load_window_geometry() {
    QSettings settings;
    return settings.value(WINDOW_GEOMETRY).toByteArray();
}

void Settings::save_font_size(int size) {
    QSettings settings;
    settings.setValue(FONT_SIZE, size);
}

int Settings::load_font_size() {
    QSettings settings;
    return settings.value(FONT_SIZE, DEFAULT_FONT_SIZE).toInt();
}

void Settings::save_bg_color(Settings::BG_COLOR color, const QString &hex_color) {
    if (hex_color == DEFAULT_LABEL_TEXT) {
        return;
    }
    QSettings settings;
    settings.setValue(bg_keys_[color], hex_color);
}

QString Settings::load_bg_color(Settings::BG_COLOR color) {
    QSettings settings;
    return settings.value(bg_keys_[color]).toString();
}

void Settings::reset_bg_color(Settings::BG_COLOR color) {
    QSettings settings;
    settings.remove(bg_keys_[color]);
}
