#include "network.h"

Network::Network(DBConnector *con, QObject *parent) : QObject(parent)
  , dbcon(con)
{

}

void Network::test() {
    QUrl serviceUrl = QUrl("https://api.ars-regendi.com/" + dbcon.data()->getToken());
            //QUrl("https://api.ars-regendi.com/" + dbcon.data()->getToken() + "/s/199380");

    QByteArray jsonstr = "json={\"ids\":[199380], \"dat\":[\"sNAM\"]}";

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onPostAnswer(QNetworkReply*)));

    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    networkManager->post(networkRequest,jsonstr);

    qDebug() << "Post: " << jsonstr;
}

void Network::onPostAnswer(QNetworkReply *reply) {
    QByteArray bytes = reply->readAll();
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "Error: " << reply->errorString();
    qDebug() << "Status: " << QVariant(statusCode).toString();
    qDebug() << "Answer-Length: " << bytes.length();
    qDebug() << "Answer: " << str;
}


