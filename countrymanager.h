#ifndef COUNTRYMANAGER_H
#define COUNTRYMANAGER_H

#include <QObject>
#include <QAbstractListModel>
#include <QVariant>
#include <QList>
#include <QHash>

#include "country.h"
#include "dbconnector.h"

class CountryManager : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CountryManager(DBConnector* dbcon, QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    QHash<int, QByteArray> roleNames() const;

    void getCountriesFromDB();
    Q_INVOKABLE void addCountry(int id, QString alliance = "");

signals:

private:


private:
    QList<Country*> m_lstCountries;
    QSharedPointer<DBConnector> m_dbcon;

    static const int ID;
    static const int Alliance;
    static const int HasAtomic;
    static const int HasRocket;
    static const int HasSatellite;
    static const int Name;
    static const int Military;
};

#endif // COUNTRYMANAGER_H
