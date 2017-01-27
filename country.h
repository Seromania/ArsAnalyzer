#ifndef COUNTRY_H
#define COUNTRY_H

#include <QObject>
#include <QDebug>

class Country : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ID READ getID WRITE setID NOTIFY idChanged)
    Q_PROPERTY(int HasAtomic READ getHasAtomic WRITE setHasAtomic NOTIFY hasAtomicChanged)
    Q_PROPERTY(int HasRocket READ getHasRocket WRITE setHasRocket NOTIFY hasRocketChanged)
    Q_PROPERTY(int HasSatellite READ getHasSatellite WRITE setHasSatellite NOTIFY hasRocketChanged)
    Q_PROPERTY(float Military READ getMilitary WRITE setMilitary NOTIFY militaryChanged)
    Q_PROPERTY(QString Name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString Alliance READ getAlliance WRITE setAlliance NOTIFY allianceChanged)

public:
    explicit Country(QObject *parent = 0);

    void setID(const int& id);
    int getID() const;

    void setHasAtomic(const bool& hasAtomic);
    bool getHasAtomic() const;

    void setHasRocket(const bool& hasRocket);
    bool getHasRocket() const;

    void setHasSatellite(const bool& hasSatellite);
    bool getHasSatellite() const;

    void setMilitary(const float& military);
    float getMilitary() const;

    void setName(const QString& name);
    QString getName() const;

    void setAlliance(const QString& alliance);
    QString getAlliance() const;

    void print() const;
signals:
    void idChanged(int);
    void hasAtomicChanged(bool);
    void hasRocketChanged(bool);
    void hasSatelliteChanged(bool);
    void militaryChanged(float);
    void nameChanged(QString);
    void allianceChanged(QString);

private:
    int m_id;
    bool m_hasAtomic;
    bool m_hasRocket;
    bool m_hasSatellite;
    float m_military;
    QString m_name;
    QString m_alliance;
};

#endif // COUNTRY_H
