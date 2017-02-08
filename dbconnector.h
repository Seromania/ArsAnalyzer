#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStandardPaths>
#include <QList>

#include "country.h"

class DBConnector : public QObject
{
    Q_OBJECT


public:
    DBConnector(QObject *parent = 0);
    ~DBConnector();

public:
    bool openDB();
    bool deleteDB();
    QSqlError lastError() const;

    QString getToken() const;
    void writeToken(const QString &token) const;

    QList<Country *> getCountries() const;
    void addCountry(Country* country) const;
    void updateCountry(Country* country) const;
    void writeCountries(QList<Country*> countries) const;
    void deleteCountry(Country* country) const;

private:
    QSqlDatabase db;

    QString getDBPath() const;
    bool checkIfDBExists() const;
    void createDB() const;
};

#endif // DBCONNECTOR_H
