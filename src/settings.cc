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

void Settings::init() {
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
