#include "countrymanager.h"

const int CountryManager::ID            = Qt::UserRole + 1;
const int CountryManager::Alliance      = Qt::UserRole + 2;
const int CountryManager::HasAtomic     = Qt::UserRole + 3;
const int CountryManager::HasRocket     = Qt::UserRole + 4;
const int CountryManager::HasSatellite  = Qt::UserRole + 5;
const int CountryManager::Name          = Qt::UserRole + 6;
const int CountryManager::Military      = Qt::UserRole + 7;

CountryManager::CountryManager(DBConnector *dbcon, QObject *parent)
    : QAbstractListModel(parent)
    , m_dbcon(dbcon)
{

}

void CountryManager::getCountriesFromDB() {
    if(m_dbcon.isNull())
        return;

    m_lstCountries = m_dbcon.data()->getCountries();

    foreach (Country* country, m_lstCountries) {
        country->print();
    }
}

void CountryManager::addCountry(int id, QString alliance) {
    Country *testcountry = new Country();
    testcountry->setID(id);
    testcountry->setName("Teststaat #" + QString::number(id));
    testcountry->setHasAtomic(false);
    testcountry->setHasRocket(true);
    testcountry->setHasSatellite(false);
    testcountry->setAlliance(alliance);

    beginInsertRows(QModelIndex(), m_lstCountries.size(), m_lstCountries.size());
    m_lstCountries.append(testcountry);
    endInsertRows();
}


QHash<int, QByteArray> CountryManager::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(ID, QByteArray("id"));
    roles.insert(Alliance, QByteArray("alliance"));
    roles.insert(HasAtomic, QByteArray("hasAtomic"));
    roles.insert(HasRocket, QByteArray("hasRocket"));
    roles.insert(HasSatellite, QByteArray("hasSatellite"));
    roles.insert(Name, QByteArray("name"));
    roles.insert(Military, QByteArray("military"));

    return roles;
}

int CountryManager::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_lstCountries.size();
}

QVariant CountryManager::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (index.row() > (m_lstCountries.size() -1))
        return QVariant();

    Country *country = m_lstCountries.at(index.row());

    switch(role) {
    case Qt::DisplayRole:
    case ID:
        return QVariant::fromValue(country->getID());
    case Alliance:
        return QVariant::fromValue(country->getAlliance());
    case HasAtomic:
        return QVariant::fromValue(country->getHasAtomic());
    case HasRocket:
        return QVariant::fromValue(country->getHasRocket());
    case HasSatellite:
        return QVariant::fromValue(country->getHasSatellite());
    case Name:
        return QVariant::fromValue(country->getName());
    case Military:
        return QVariant::fromValue(country->getMilitary());

    default:
        return QVariant();
    }
}
