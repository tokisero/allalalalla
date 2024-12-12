    #include "AdminPanell.h"
    #include "ui_AdminPanell.h"
    #include <QFile>
    #include <QJsonArray>
    #include <QJsonObject>
    #include <QJsonDocument>

    AdminPanell::AdminPanell(DataBase* db, QWidget* parent)
        : BasePanel(db, parent), ui(new Ui::AdminPanell), currentRow(-1) {
        ui->setupUi(this);
        loadData("Flights");
        setupTableView(ui->tableView);


    }

    AdminPanell::~AdminPanell() {
        delete ui;
    }

    void AdminPanell::on_AddButton_clicked() {
        tableModel->insertRow(tableModel->rowCount());
    }

    void AdminPanell::on_DeleteButton_clicked() {
        try {
            if (currentRow < 0) {
                throw std::runtime_error("No row selected for deletion!");
            }

            tableModel->removeRow(currentRow);
            if (!tableModel->submitAll()) {
                throw std::runtime_error("Failed to delete row from the database.");
            }
            currentRow = -1;
        } catch (const std::exception& e) {
            ErrorHandler::handleException(e);
        } catch (...) {
            ErrorHandler::handleUnknownException();
        }
    }


    void AdminPanell::on_UpdateButton_clicked() {
        tableModel->select();
    }

    void AdminPanell::on_tableView_clicked(const QModelIndex& index) {
        currentRow = index.row();
    }

    template <typename T>
    void saveToFile(const T& data, const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "Could not open file for writing!";
            return;
        }

        QJsonDocument doc(T::fromVariantList(data.toVariantList()));
        file.write(doc.toJson());
        file.close();

        qDebug() << "Data saved to" << filename;
    }


    void AdminPanell::on_SaveToButton_clicked() {
        try {
            QSortFilterProxyModel* proxyModel = qobject_cast<QSortFilterProxyModel*>(ui->tableView->model());
            if (!proxyModel) {
                throw std::runtime_error("Proxy model not found!");
            }
            QJsonArray jsonArray;
            for (int row = 0; row < proxyModel->rowCount(); ++row) {
                QJsonObject jsonObject;
                for (int col = 0; col < proxyModel->columnCount(); ++col) {
                    QString header = proxyModel->headerData(col, Qt::Horizontal).toString();
                    QModelIndex index = proxyModel->index(row, col);
                    QVariant data = proxyModel->data(index);
                    jsonObject[header] = data.toString();
                }
                jsonArray.append(jsonObject);
            }
            if (jsonArray.isEmpty()) {
                throw std::runtime_error("No data to save!");
            }
            saveToFile(jsonArray, "filteredResults.json");
            QMessageBox::information(this, "Success", "Data has been successfully saved to filteredResults.json.");
        } catch (const std::exception& e) {
            ErrorHandler::handleException(e);
        } catch (...) {
            ErrorHandler::handleUnknownException();
        }
    }




    void AdminPanell::on_logoutButton_clicked()
    {
        logoutRequested();
    }


