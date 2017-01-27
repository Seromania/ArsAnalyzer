#include "network.h"

Network::Network(DBConnector *con, QObject *parent) : QObject(parent)
  , dbcon(con)
  , wantNameForState(false)
{

}

void Network::test() {
    QUrl serviceUrl = QUrl("https://api.ars-regendi.com/" + dbcon.data()->getToken());
            //QUrl("https://api.ars-regendi.com/" + dbcon.data()->getToken() + "/s/199380");

    QByteArray jsonstr = "json={\"ids\":[199380,199381], \"dat\":[\"sNAM\",\"MIL\",\"ATM\"]}";

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onPostAnswer(QNetworkReply*)));

    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    networkManager->post(networkRequest,jsonstr);
}

void Network::onPostAnswer(QNetworkReply *reply) {
    QByteArray bytes = reply->readAll();
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode != 200) {
        qDebug() << "Status: " << QVariant(statusCode).toString();
        qDebug() << "Error: " << reply->errorString();
    }

    qDebug() << "Answer-Length: " << bytes.length();
    qDebug() << "Answer: " << str;

    if (wantNameForState) {
        wantNameForState = false;
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        if (!doc.isNull()) {
            QJsonObject obj = doc.object();

            foreach (const QJsonValue& stateval, obj) {
                QJsonObject state = stateval.toObject();
                if (!state["sNAM"].isUndefined()) {
                    qDebug() << "Name: " << state["sNAM"].toString();
                    emit gotName(state["sNAM"].toString());
                }
            }
        }
    }
}

void Network::getNameFor(const int &id) {
    wantNameForState = true;


    QUrl serviceUrl = QUrl("https://api.ars-regendi.com/" + dbcon.data()->getToken());
            //QUrl("https://api.ars-regendi.com/" + dbcon.data()->getToken() + "/s/199380");

    QString jss = "json={\"ids\":[" + QString::number(id) + "], \"dat\":[\"sNAM\"]}";
    QByteArray jsonstr = jss.toStdString().c_str();

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onPostAnswer(QNetworkReply*)));

    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    networkManager->post(networkRequest,jsonstr);

}
