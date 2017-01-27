#include "dbconnector.h"

DBConnector::DBConnector(QObject *parent)
    : QObject(parent)
{

}

DBConnector::~DBConnector() {

}

bool DBConnector::openDB() {
    QString path = "";

    qDebug() << "Path: " << getDBPath();
    qDebug() << "Check: " << checkIfDBExists();

    if(!checkIfDBExists())
        createDB();

    path = getDBPath();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    bool ret = db.open();
    qDebug() << "DB Open: " << ret;
    qDebug() << "DB Path: " << getDBPath();

    return ret;
}

bool DBConnector::deleteDB() {
    return false;
}

QSqlError DBConnector::lastError() const {
    return db.lastError();
}

QString DBConnector::getToken() const {
    QSqlQuery query("SELECT token FROM tblToken;", db);

    if (query.first()) {
        return query.value(0).toString();
    }

    return "";
}

void DBConnector::writeToken(const QString &token) const {
    QSqlQuery query("DELETE FROM tblToken;");
    if (!query.exec())
        qDebug() << "(WriteToken:DELETE) LastError: " << query.lastError();


    query.prepare("INSERT INTO tblToken (token) VALUES (:token);");
    query.bindValue(":token", token);

    if (!query.exec())
        qDebug() << "(WriteToken:INSERT) LastError: " << query.lastError();
}

QString DBConnector::getDBPath() const {
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/sxsystems.db";
    return dbPath;
}

bool DBConnector::checkIfDBExists() const {
    QDir dir(getDBPath());
    return dir.exists();
}

void DBConnector::createDB() const {
    if (!checkIfDBExists()) {
        qDebug() << "Created: " << QFile::copy(":/sxsystems.db", getDBPath());
        QFile file(getDBPath());
        file.setPermissions(QFile::WriteUser);
    }
}

QList<Country*> DBConnector::getCountries() const {
    QList<Country*> retList;

    QSqlQuery query("SELECT * FROM tblCountry;");
    while(query.next()) {
        int cid = query.value("ID").toInt();
        float cmilitary = query.value("Military").toFloat();
        bool chasatomic = (query.value("HasAtomic").toInt() > 0) ? true : false;
        bool chasrocket = (query.value("HasRocket").toInt() > 0) ? true : false;
        bool chassatellite = (query.value("HasSatellite").toInt() > 0) ? true : false;
        QString cname = query.value("Name").toString();
        QString calliance = query.value("Alliance").toString();


        Country *country = new Country();
        country->setID(cid);
        country->setMilitary(cmilitary);
        country->setHasAtomic(chasatomic);
        country->setHasRocket(chasrocket);
        country->setHasSatellite(chassatellite);
        country->setName(cname);
        country->setAlliance(calliance);

        retList.append(country);
    }

    return retList;
}
