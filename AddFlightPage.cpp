#include "AddFlightPage.h"
#include "ui_AddFlightPage.h"
#include <string>

AddFlightPage::AddFlightPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddFlightPage){
    ui->setupUi(this);
    addFlightButton = new QPushButton("Add Flight", this);
    connect(addFlightButton, &QPushButton::clicked, this, &AddFlightPage::onButtonClicked);
}

AddFlightPage::~AddFlightPage() {
    delete ui;
}

void AddFlightPage::onButtonClicked() {
    QString flightNumber = ui->flightNumberField->text();
    QString destination = ui->destinationField->text();
    QString day = ui->dayField->text();
    QString month = ui->monthField->text();
    QString time = ui->TimeField->text();
    QString seats = ui->seatsField->text();

    int flightNumberInt = flightNumber.toInt();
    int dayInt = day.toInt();
    int monthInt = month.toInt();
    int timeInt = time.toInt();
    int seatsInt = seats.toInt();
    std::string dest = destination.toStdString();


    // Проверка на валидность (можно добавить проверку ошибок для каждого поля)
    if (flightNumberInt == 0 || dayInt == 0 || monthInt == 0 || timeInt == 0 || seatsInt == 0) {
        QMessageBox::warning(this, "Input Error", "Please enter valid numeric values for all fields.");
        return;
    }

    if (flightNumber.isEmpty() || destination.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }
    addFlight(flightNumberInt, dest, dayInt, monthInt, timeInt, seatsInt);
    QMessageBox::information(this, "Success", "Flight added successfully!");
    this->close();
}
