#pragma once

#include "Flight.h"
#include <vector>
#include <QString>
#include <QSqlDatabase>
#include "ValidatedSqlTableModel.h"

class DataBase {
private:
    QString filename;
    QSqlDatabase db;
    void open();
    void close();
    void initialize();

public:
    explicit DataBase(const QString& file);
    ~DataBase();
    std::vector<Flight> readFromFile() const;
    void writeToFile(const std::vector<Flight>& flights) const;
    void addFlight(const Flight& flight) const;
    void editFlight(const Flight& flight) const;
    void deleteFlight(int flightNumber) const;
    QSqlDatabase& getDatabase();
    void updateSeats(int flightNumber, int seats) const;
    std::optional<Flight> getFlight(int flightNumber) const;


};
