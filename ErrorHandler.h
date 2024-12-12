#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

class ErrorHandler {
public:
    static void showError(const QString& errorMessage) {
        QMessageBox::critical(nullptr, "Error", errorMessage);
    }

    static void handleException(const std::exception& e) {
        QString errorMessage = QString("Exception: %1").arg(e.what());
        showError(errorMessage);
    }

    static void handleUnknownException() {
        QString errorMessage = "An unknown error occurred.";
        showError(errorMessage);
    }
};

#endif
