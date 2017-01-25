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

class DBConnector : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString token READ getToken())

public:
    DBConnector(QObject *parent = 0);
    ~DBConnector();

public:
    bool openDB();
    bool deleteDB();
    QSqlError lastError() const;

    QString getToken() const;
    Q_INVOKABLE void writeToken(const QString &token) const;

private:
    QSqlDatabase db;

    QString getDBPath() const;
    bool checkIfDBExists() const;
    void createDB() const;
};

#endif // DBCONNECTOR_H
