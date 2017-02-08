#include "network.h"

Network::Network(DBConnector *con, QObject *parent) : QObject(parent)
  , dbcon(con)
  , m_tmpAlliance("")
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

void Network::writeToken(const QString &token) const {
    dbcon.data()->writeToken(token);
}

QString Network::getToken() const {
    return dbcon.data()->getToken();
}

void Network::onPostAnswer(QNetworkReply *reply) {
    if (replyHasError(reply)) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    QString answer = getReplyAnswer(reply);

    qDebug() << "Answer-Length: " << answer.length();
    qDebug() << "Answer: " << answer;

}

void Network::onNameAnswer(QNetworkReply *reply) {
    if (replyHasError(reply)) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    QString answer = getReplyAnswer(reply);

    qDebug() << "Answer-Length: " << answer.length();
    qDebug() << "Answer: " << answer;

    QJsonDocument doc = QJsonDocument::fromJson(answer.toUtf8());
    if (!doc.isNull()) {
        QJsonObject obj = doc.object();

        foreach (const QJsonValue& stateval, obj) {
            QJsonObject state = stateval.toObject();
            if (!state["sNAM"].isUndefined()) {
                qDebug() << "Name: " << state["sNAM"].toString();
                emit gotName(state["sNAM"].toString());
                return;
            }
        }
    }

    emit gotName("");
}

void Network::onCountryAnswer(QNetworkReply *reply) {
    if (replyHasError(reply)) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    QString answer = getReplyAnswer(reply);

    qDebug() << "Answer-Length: " << answer.length();
    qDebug() << "Answer: " << answer;

    QJsonDocument doc = QJsonDocument::fromJson(answer.toUtf8());
    if (!doc.isNull()) {
        QJsonObject obj = doc.object();
        QString idstr = obj.keys().first();

        foreach (const QJsonValue& stateval, obj) {
            QJsonObject state = stateval.toObject();

            int id = idstr.toInt();
            int muster = 0;
            QString name = "";
            QString alliance = m_tmpAlliance;
            float mil = 0.0f;
            bool hasAtomic = false;
            bool hasRocket = false;
            bool hasSatellite = false;

            if (!state["sNAM"].isUndefined())
                name = state["sNAM"].toString();
            if (!state["sMUS"].isUndefined())
                muster = state["sMUS"].toString().toInt();
            if (!state["MIL"].isUndefined())
                mil = state["MIL"].toString().toDouble();
            if (!state["ATM"].isUndefined()) {
                int atm = state["ATM"].toString().toDouble();
                if (atm == 502) {
                    hasAtomic = true;
                    hasRocket = true;
                    hasSatellite = true;
                } else if (atm == 501) {
                    hasAtomic = true;
                    hasRocket = true;
                } else if (atm == 500) {
                    hasAtomic = true;
                }
            }

            Country *country = new Country();
            country->setID(id);
            country->setMuster(muster);
            country->setName(name);
            country->setAlliance(alliance);
            country->setMilitary(mil);
            country->setHasAtomic(hasAtomic);
            country->setHasRocket(hasRocket);
            country->setHasSatellite(hasSatellite);

            m_tmpAlliance = "";

            emit gotCountry(country);
            return;
        }
    }

    emit gotName("");
}

bool Network::replyHasError(const QNetworkReply *reply) const {
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode != 200) {
        return true;
    }

    return false;
}

QString Network::getReplyAnswer(QNetworkReply *reply) const {
    QByteArray bytes = reply->readAll();
    return QString::fromUtf8(bytes.data(), bytes.size());
}

void Network::getNameFor(const int &id) {
    QUrl serviceUrl = QUrl("https://api.ars-regendi.com/" + dbcon.data()->getToken());

    QString jss = "json={\"ids\":[" + QString::number(id) + "], \"dat\":[\"sNAM\"]}";
    QByteArray jsonstr = jss.toStdString().c_str();

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onNameAnswer(QNetworkReply*)));

    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    networkManager->post(networkRequest,jsonstr);

}

void Network::getCountryFor(const int &id, const QString &alliance) {
    m_tmpAlliance = alliance;

    QUrl serviceUrl = QUrl("https://api.ars-regendi.com/" + dbcon.data()->getToken());

    QString jss = "json={\"ids\":[" + QString::number(id) + "], \"dat\":[\"sMUS\",\"sNAM\",\"MIL\",\"ATM\"]}";
    QByteArray jsonstr = jss.toStdString().c_str();

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(onCountryAnswer(QNetworkReply*)));

    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    networkManager->post(networkRequest,jsonstr);
}
