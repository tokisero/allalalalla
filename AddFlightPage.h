// AddFlightPage.h
#pragma once

#include <QDialog>
#include <QMessageBox>
#include "FlightManager.h"

namespace Ui {
class AddFlightPage;
}

class AddFlightPage : public QDialog, public FlightManager  {
    Q_OBJECT

public:
    explicit AddFlightPage(QWidget *parent = nullptr);
    ~AddFlightPage();

private slots:
    void onButtonClicked();

private:
    Ui::AddFlightPage *ui;
    QPushButton* addFlightButton;
};
