#ifndef BOOKEDFLIGHTSWINDOW_H
#define BOOKEDFLIGHTSWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include <QModelIndex>
#include "Queue.h"
#include <QSqlDatabase>
#include "DataBase.h"

namespace Ui {
class BookedFlightsWindow;
}

class BookedFlightsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BookedFlightsWindow(Queue<Flight>* queue, DataBase* db, QWidget* parent = nullptr);
    ~BookedFlightsWindow();
    void loadBookedFlights();


private slots:
    void on_listView_clicked(const QModelIndex &index);
    void on_cancelButton_clicked();

private:
    Ui::BookedFlightsWindow* ui;
    QStandardItemModel* listModel;
    DataBase* database;
    QModelIndex selectedIndex;
    Queue<Flight>* bookedFlightsQueue;
};

#endif // BOOKEDFLIGHTSWINDOW_H
