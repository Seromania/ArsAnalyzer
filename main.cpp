#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "dbconnector.h"
#include "network.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    app.setApplicationName("ArsAnalyzer");

    DBConnector* dbcon = new DBConnector();
    Network* network = new Network(dbcon);

    if(!dbcon->openDB())
        qDebug() << "Fehler: " << dbcon->lastError();
    else
        qDebug() << "Token: " << dbcon->getToken();

    QQmlApplicationEngine engine;

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("dbCon", dbcon);
    context->setContextProperty("network", network);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));



    return app.exec();
}
