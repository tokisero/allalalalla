#ifndef USERPANEL_H
#define USERPANEL_H

#include "BasePanel.h"
#include "Queue.h"
#include <QTableView>
#include <QModelIndex>
#include "BookedFlightsWindow.h"

namespace Ui {
class UserPanell;
}

class UserPanell : public BasePanel {
    Q_OBJECT

public:
    explicit UserPanell(DataBase* db, QWidget* parent = nullptr);
    ~UserPanell();

private slots:
    void on_BookFlight_clicked();
    void on_ListABooked_clicked();
    void on_tableView_clicked(const QModelIndex& index);
    void on_UpdateButton_clicked() override;


    void on_logoutButton_clicked();

private:
    Ui::UserPanell* ui;
    int currentRow;
    Queue<Flight>* bookedFlightsQueue;
    BookedFlightsWindow* bookedFlightsWindow;

signals:
    void logoutRequested();
};

#endif // USERPANEL_H
