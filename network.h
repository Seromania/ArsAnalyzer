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
    Q_PROPERTY(QString token READ getToken())
public:
    explicit Network(DBConnector* con = 0, QObject *parent = 0);

    Q_INVOKABLE void test();
    Q_INVOKABLE void getNameFor(const int& id);
    Q_INVOKABLE void getCountryFor(const int& id, const QString& alliance);

    Q_INVOKABLE void writeToken(const QString &token) const;
    QString getToken() const;

signals:
    void gotName(const QString& name);
    void gotCountry(Country *country);

private slots:
    void onPostAnswer(QNetworkReply* reply);
    void onNameAnswer(QNetworkReply* reply);
    void onCountryAnswer(QNetworkReply* reply);

private:
    bool replyHasError(const QNetworkReply* reply) const;
    QString getReplyAnswer(QNetworkReply* reply) const;

private:
    QSharedPointer<DBConnector> dbcon;
    QString m_tmpAlliance;
};

#endif // NETWORK_H
