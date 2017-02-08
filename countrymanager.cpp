#include "countrymanager.h"

const int CountryManager::ID            = Qt::UserRole + 1;
const int CountryManager::Alliance      = Qt::UserRole + 2;
const int CountryManager::HasAtomic     = Qt::UserRole + 3;
const int CountryManager::HasRocket     = Qt::UserRole + 4;
const int CountryManager::HasSatellite  = Qt::UserRole + 5;
const int CountryManager::Name          = Qt::UserRole + 6;
const int CountryManager::Military      = Qt::UserRole + 7;
const int CountryManager::Muster        = Qt::UserRole + 8;

CountryManager::CountryManager(DBConnector *dbcon, Network *network, QObject *parent)
    : QAbstractListModel(parent)
    , m_dbcon(dbcon)
    , m_network(network)
{
    connect(network, SIGNAL(gotCountry(Country*)), this, SLOT(onGotCountry(Country*)));
}

void CountryManager::getCountriesFromDB() {
    if(m_dbcon.isNull())
        return;

    m_lstCountries = m_dbcon.data()->getCountries();

    foreach (Country* country, m_lstCountries) {
        country->print();
    }
}

void CountryManager::updateCountriesAlliance(const int &id, const QString &alliance)
{
    int indx = 0;
    for(Country* country : m_lstCountries) {
        if (country->getID() == id) {
            country->setAlliance(alliance);
            m_dbcon.data()->updateCountry(country);

            QVector<int> roles;
            roles.append(Alliance);

            dataChanged(this->index(indx, indx), this->index(indx, indx), roles);
            return;
        }
        indx++;
    }
}

void CountryManager::deleteCountry(const int &id)
{
    int indx = 0;
    for(Country* country : m_lstCountries) {
        if (country->getID() == id) {
            m_dbcon.data()->deleteCountry(country);

            beginRemoveRows(QModelIndex(), indx, indx);
            m_lstCountries.removeAt(indx);
            endRemoveRows();
            return;
        }
        indx++;
    }
}

void CountryManager::onGotCountry(Country *country) {
    country->print();

    if (!m_dbcon.isNull())
        m_dbcon.data()->addCountry(country);

    if (isCountryAlreadyInList(country))
        return updateCountryWith(country);

    beginInsertRows(QModelIndex(), m_lstCountries.size(), m_lstCountries.size());
    m_lstCountries.append(country);
    endInsertRows();
}

bool CountryManager::isCountryAlreadyInList(Country *country) const {
    foreach (Country* ctr, m_lstCountries) {
        if (ctr->getID() == country->getID())
            return true;
    }
    return false;
}

void CountryManager::updateCountryWith(Country *country) {
    int indx = 0;
    foreach (Country* ctr, m_lstCountries) {
        if (ctr->getID() == country->getID()) {
            ctr->setName(country->getName());
            ctr->setAlliance(country->getAlliance());
            ctr->setMilitary(country->getMilitary());
            ctr->setHasAtomic(country->getHasAtomic());
            ctr->setHasRocket(country->getHasRocket());
            ctr->setHasSatellite(country->getHasSatellite());

            QVector<int> roles;
            roles.append(Name);
            roles.append(Alliance);
            roles.append(Military);
            roles.append(HasAtomic);
            roles.append(HasRocket);
            roles.append(HasSatellite);
            roles.append(Muster);

            m_dbcon.data()->updateCountry(ctr);

            dataChanged(this->index(indx, indx), this->index(indx, indx), roles);
            return;
        }
        indx++;
    }
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
    roles.insert(Muster, QByteArray("muster"));

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
    case Muster:
        return QVariant::fromValue(country->getMuster());

    default:
        return QVariant();
    }
}
