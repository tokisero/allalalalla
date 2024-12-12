#include "BookedFlightsWindow.h"
#include "ui_BookedFlightsWindow.h"
#include "Flight.h"
#include <QMessageBox>
#include <QDebug>
#include "ErrorHandler.h"


BookedFlightsWindow::BookedFlightsWindow(Queue<Flight>* queue, DataBase* db, QWidget* parent)
    : QDialog(parent),
    ui(new Ui::BookedFlightsWindow),
    listModel(new QStandardItemModel(this)),
    database(db),
    bookedFlightsQueue(queue),
    selectedIndex() {
    ui->setupUi(this);
    ui->listView->setModel(listModel);
    selectedIndex = QModelIndex();
}

BookedFlightsWindow::~BookedFlightsWindow() {
    delete ui;
}

void BookedFlightsWindow::loadBookedFlights() {
    try {
        listModel->clear();

        if (!bookedFlightsQueue) {
            throw std::invalid_argument("Queue is null!");
        }

        for (const Flight& flight : bookedFlightsQueue->toVector()) {
            QString flightInfo = QString("Flight #%1\n Destination: %2\n Date: %3.%4\n Time: %5:00\n")
            .arg(flight.getFlightNumber())
                .arg(QString::fromStdString(flight.getDestination()))
                .arg(flight.getDay())
                .arg(flight.getMonth())
                .arg(flight.getTime());

            listModel->appendRow(new QStandardItem(flightInfo));
        }
    } catch (const std::exception& e) {
        ErrorHandler::handleException(e);
    } catch (...) {
        ErrorHandler::handleUnknownException();
    }
}

void BookedFlightsWindow::on_listView_clicked(const QModelIndex& index) {
    selectedIndex = index;
}

void BookedFlightsWindow::on_cancelButton_clicked() {
    try {
        if (!selectedIndex.isValid()) {
            throw std::invalid_argument("No flight selected!");
        }
        QString selectedText = listModel->itemFromIndex(selectedIndex)->text();
        QRegularExpression regex(
            R"(Flight #(\d+)\n Destination: ([^\n]+)\n Date: (\d+)\.(\d+)\n Time: (\d+):00\n)");
        QRegularExpressionMatch match = regex.match(selectedText);

        if (!match.hasMatch()) {
            throw std::invalid_argument("Failed to parse selected flight data!");
        }

        Flight foundFlight;
        int flightNumber = match.captured(1).toInt();
        std::vector<Flight> flights = bookedFlightsQueue->toVector();
        for (auto it = flights.begin(); it != flights.end(); ++it) {
            if (it->getFlightNumber() == flightNumber) {
                foundFlight = *it;
                break;
            }
        }
        int seats = 1 + foundFlight.getSeats();
        database->updateSeats(flightNumber, seats);
        listModel->removeRow(selectedIndex.row());
        selectedIndex = QModelIndex();
        if (bookedFlightsQueue) {
            bookedFlightsQueue->removeElement(foundFlight);
        }
    } catch (const std::exception& e) {
        ErrorHandler::handleException(e);
    } catch (...) {
        ErrorHandler::handleUnknownException();
    }
}
