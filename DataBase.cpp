#include "DataBase.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <iostream>

DataBase::DataBase(const QString& file) : filename(file) {
    if (QSqlDatabase::contains("my_unique_connection")) {
        db = QSqlDatabase::database("my_unique_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", "my_unique_connection");
        db.setDatabaseName(filename);
        if (!db.open()) {
            std::cerr << "Failed to open database: " << db.lastError().text().toStdString() << std::endl;
        }
    }
   open();
   initialize();
}

DataBase::~DataBase() {
    close();
}

void DataBase::open() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if (!db.open()) {
        std::cerr << "Failed to open database: " << db.lastError().text().toStdString() << std::endl;
    }
}

void DataBase::close() {
    if (db.isOpen()) {
        db.close();
    }
}

void DataBase::initialize() {
    QSqlQuery query;
    QString createTable = R"(
        CREATE TABLE IF NOT EXISTS Flights (
            flightNumber INTEGER PRIMARY KEY,
            destination TEXT NOT NULL,
            day INTEGER NOT NULL,
            month INTEGER NOT NULL,
            time INTEGER NOT NULL,
            seats INTEGER NOT NULL
        );
    )";
    if (!query.exec(createTable)) {
        std::cerr << "Error creating Flights table: "
                  << query.lastError().text().toStdString() << std::endl;
    }
}



std::vector<Flight> DataBase::readFromFile() const {
    std::vector<Flight> flights;
    QSqlQuery query("SELECT flightNumber, destination, day, month, time, seats FROM Flights");
    while (query.next()) {
        int flightNumber = query.value(0).toInt();
        QString destination = query.value(1).toString();
        int day = query.value(2).toInt();
        int month = query.value(3).toInt();
        int time = query.value(4).toInt();
        int seats = query.value(5).toInt();
        flights.emplace_back(flightNumber, destination.toStdString(), day, month, time, seats);
    }
    return flights;
}

void DataBase::writeToFile(const std::vector<Flight>& flights) const {
    QSqlQuery query;
    QString insertOrReplace = R"(
        INSERT OR REPLACE INTO Flights (flightNumber, destination, day, month, time, seats)
        VALUES (:flightNumber, :destination, :day, :month, :time, :seats);
    )";

    for (const auto& flight : flights) {
        query.prepare(insertOrReplace);
        query.bindValue(":flightNumber", flight.getFlightNumber());
        query.bindValue(":destination", QString::fromStdString(flight.getDestination()));
        query.bindValue(":day", flight.getDay());
        query.bindValue(":month", flight.getMonth());
        query.bindValue(":time", flight.getTime());
        query.bindValue(":seats", flight.getSeats());
        if (!query.exec()) {
            std::cerr << "Failed to write flight: "
                      << query.lastError().text().toStdString() << std::endl;
        }
    }
}

void DataBase::addFlight(const Flight& flight) const {
    QSqlQuery query;
    QString insert = R"(
        INSERT INTO Flights (flightNumber, destination, day, month, time, seats)
        VALUES (:flightNumber, :destination, :day, :month, :time, :seats);
    )";
    query.prepare(insert);
    query.bindValue(":flightNumber", flight.getFlightNumber());
    query.bindValue(":destination", QString::fromStdString(flight.getDestination()));
    query.bindValue(":day", flight.getDay());
    query.bindValue(":month", flight.getMonth());
    query.bindValue(":time", flight.getTime());
    query.bindValue(":seats", flight.getSeats());

    if (!query.exec()) {
        std::cerr << "Failed to add flight: "
                  << query.lastError().text().toStdString() << std::endl;
    }
}


void DataBase::editFlight(const Flight& flight) const {
    QSqlQuery query;
    QString update = R"(
        UPDATE Flights
        SET destination = :destination, day = :day, month = :month, time = :time, seats = :seats
        WHERE flightNumber = :flightNumber;
    )";
    query.prepare(update);
    query.bindValue(":flightNumber", flight.getFlightNumber());
    query.bindValue(":destination", QString::fromStdString(flight.getDestination()));
    query.bindValue(":day", flight.getDay());
    query.bindValue(":month", flight.getMonth());
    query.bindValue(":time", flight.getTime());
    query.bindValue(":seats", flight.getSeats());

    if (!query.exec()) {
        std::cerr << "Failed to edit flight: "
                  << query.lastError().text().toStdString() << std::endl;
    } else {
        std::cout << "Flight updated successfully." << std::endl;
    }
}


void DataBase::deleteFlight(int flightNumber) const {
    if (!db.isOpen()) {
        std::cerr << "Database is not open!" << std::endl;
        return;
    }

    QSqlQuery query;
    QString remove = "DELETE FROM Flights WHERE flightNumber = :flightNumber;";
    query.prepare(remove);
    query.bindValue(":flightNumber", flightNumber);

    if (!query.exec()) {
        std::cerr << "Failed to delete flight: "
                  << query.lastError().text().toStdString() << std::endl;
    } else {
        if (query.numRowsAffected() == 0) {
            std::cerr << "No flight found with flightNumber " << flightNumber << std::endl;
        } else {
            std::cout << "Flight with flightNumber " << flightNumber << " deleted successfully!" << std::endl;
        }
    }
}

QSqlDatabase& DataBase::getDatabase() {
    return db;
}

std::optional<Flight> DataBase::getFlight(int flightNumber) const {
    QSqlQuery query;
    query.prepare("SELECT flightNumber, destination, day, month, time, seats FROM Flights WHERE flightNumber = :flightNumber");
    query.bindValue(":flightNumber", flightNumber);

    if (query.exec() && query.next()) {
        int flightNum = query.value(0).toInt();
        QString destination = query.value(1).toString();
        int day = query.value(2).toInt();
        int month = query.value(3).toInt();
        int time = query.value(4).toInt();
        int seats = query.value(5).toInt();

        return Flight(flightNum, destination.toStdString(), day, month, time, seats);
    }

    std::cerr << "Failed to retrieve flight " << flightNumber << ": "
              << query.lastError().text().toStdString() << std::endl;
    return std::nullopt;
}

void DataBase::updateSeats(int flightNumber, int seats) const {
    QSqlQuery query;
    query.prepare("UPDATE Flights SET seats = :seats WHERE flightNumber = :flightNumber");
    query.bindValue(":seats", seats);
    query.bindValue(":flightNumber", flightNumber);

    if (!query.exec()) {
        std::cerr << "Failed to update seats for flight " << flightNumber << ": "
                  << query.lastError().text().toStdString() << std::endl;
    }
}

