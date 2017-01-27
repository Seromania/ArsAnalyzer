#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "dbconnector.h"

class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(DBConnector* con = 0, QObject *parent = 0);

    Q_INVOKABLE void test();
    Q_INVOKABLE void getNameFor(const int& id);

signals:
    void gotName(const QString& name);

private slots:
    void onPostAnswer(QNetworkReply* reply);


private:
    QSharedPointer<DBConnector> dbcon;
    bool wantNameForState;
};

#endif // NETWORK_H
