#include "BasePanel.h"
#include "FilterTable.h"


BasePanel::BasePanel(DataBase* db, QWidget* parent)
    : PanelInterface(parent), database(db), tableModel(nullptr), proxyModel(nullptr) {

}

BasePanel::~BasePanel() {
    delete tableModel;
    delete proxyModel;
}

void BasePanel::setupTableView(QTableView* tableView) {
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(tableModel);

    FilterTable* header = new FilterTable(Qt::Horizontal, tableView);
    header->setFilterModel(proxyModel);

    tableView->setModel(proxyModel);
    tableView->setHorizontalHeader(header);
    if (!header->filtersCreated) {
        header->updateFilters();
    }

    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void BasePanel::loadData(const QString& tableName) {
    try {
        tableModel = new ValidatedSqlTableModel(this, database->getDatabase());
        tableModel->setTable(tableName);
        if (!tableModel->select()) {
            throw std::runtime_error("Failed to load data from the database.");
        }
    } catch (const std::exception& e) {
        ErrorHandler::handleException(e);
    } catch (...) {
        ErrorHandler::handleUnknownException();
    }
}
