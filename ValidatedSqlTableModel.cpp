#include "ValidatedSqlTableModel.h"
#include <QRegularExpression>

ValidatedSqlTableModel::ValidatedSqlTableModel(QObject* parent, QSqlDatabase db)
    : QSqlTableModel(parent, db) {}

bool ValidatedSqlTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role == Qt::EditRole) {
        try {
            if (!validateData(index, value)) {
                return false;
            }
        } catch (const std::exception& e) {
            ErrorHandler::handleException(e);
            return false;
        } catch (...) {
            ErrorHandler::handleUnknownException();
            return false;
        }
    }
    return QSqlTableModel::setData(index, value, role);
}

bool ValidatedSqlTableModel::submitAll() {
    try {
        for (int row = 0; row < rowCount(); ++row) {
            for (int col = 0; col < columnCount(); ++col) {
                QModelIndex index = this->index(row, col);
                QVariant value = this->data(index);
                validateData(index, value);
            }
        }
        return QSqlTableModel::submitAll();
    } catch (const std::exception& e) {
        ErrorHandler::handleException(e);
        return false;
    } catch (...) {
        ErrorHandler::handleUnknownException();
        return false;
    }
}

bool ValidatedSqlTableModel::validateData(const QModelIndex& index, const QVariant& value) const {
    try {
        switch (index.column()) {
        case 0:
            if (!value.toInt()) {
                throw std::invalid_argument("FlightNumber must contain an integer value.");
            }
            break;
        case 1: {
            QString textValue = value.toString().trimmed();
            QRegularExpression regex("^[a-zA-Z\\s\\-]+$");
            if (!regex.match(textValue).hasMatch()) {
                throw std::invalid_argument("Destination must contain only letters, spaces, and hyphens.");
            }
            break;
        }
        case 2:
            if (!value.toInt() || value.toInt() < 1 || value.toInt() > 31) {
                throw std::invalid_argument("The departure day must be entered correctly.");
            }
            break;
        case 3: {
            if (!value.toInt() || value.toInt() < 1 || value.toInt() > 12) {
                throw std::invalid_argument("The month of departure must be entered correctly.");
            }
            break;
        case 4: {
            if (!value.toInt() || value.toInt() < 0 || value.toInt() > 23) {
                throw std::invalid_argument("The time of departure must be entered correctly.");
            }
            break;
        }
        case 5: {
            if (!value.toInt() || value.toInt() < 0 || value.toInt() > 500) {
                throw std::invalid_argument("The seats of the flight must be entered correctly.");
            }
            break;
        }
        }
        default:
            break;
        }
        return true;
    } catch (const std::exception& e) {
        ErrorHandler::handleException(e);
        return false;
    } catch (...) {
        ErrorHandler::handleUnknownException();
        return false;
    }
}
