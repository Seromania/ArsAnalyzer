#include "country.h"

Country::Country(QObject *parent)
    : QObject(parent)
    , m_id(-1)
    , m_hasAtomic(false)
    , m_hasRocket(false)
    , m_hasSatellite(false)
    , m_military(0.0f)
    , m_name("")
    , m_alliance("")
{

}

void Country::setID(const int &id) {
    if(id == m_id)
        return;

    m_id = id;
    emit idChanged(m_id);
}
int Country::getID() const {
    return m_id;
}

void Country::setMilitary(const float &military) {
    if (military == m_military)
        return;

    m_military = military;
    emit militaryChanged(m_military);
}
float Country::getMilitary() const {
    return m_military;
}

void Country::setHasAtomic(const bool &hasAtomic) {
    if (hasAtomic == m_hasAtomic)
        return;

    m_hasAtomic = hasAtomic;
    emit hasAtomicChanged(m_hasAtomic);
}
bool Country::getHasAtomic() const {
    return m_hasAtomic;
}

void Country::setHasRocket(const bool &hasRocket) {
    if (hasRocket == m_hasRocket)
        return;

    m_hasRocket = hasRocket;
    emit hasRocketChanged(m_hasRocket);
}
bool Country::getHasRocket() const {
    return m_hasRocket;
}

void Country::setHasSatellite(const bool &hasSatellite) {
    if (hasSatellite == m_hasSatellite)
        return;

    m_hasSatellite = hasSatellite;
    emit hasSatelliteChanged(m_hasSatellite);
}
bool Country::getHasSatellite() const {
    return m_hasSatellite;
}

void Country::setName(const QString &name) {
    if (name == m_name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}
QString Country::getName() const {
    return m_name;
}

void Country::setAlliance(const QString &alliance) {
    if (alliance == m_alliance)
        return;

    m_alliance = alliance;
    emit allianceChanged(m_alliance);
}
QString Country::getAlliance() const {
    return m_alliance;
}

void Country::print() const {
    qDebug() << "----------";
    qDebug() << "ID...........: " << m_id;
    qDebug() << "Name.........: " << m_name;
    qDebug() << "Alliance.....: " << m_alliance;
    qDebug() << "Military.....: " << m_military;
    qDebug() << "Has Atombomb.: " << m_hasAtomic;
    qDebug() << "Has Rocket...: " << m_hasRocket;
    qDebug() << "Has Satellite: " << m_hasSatellite;
}
