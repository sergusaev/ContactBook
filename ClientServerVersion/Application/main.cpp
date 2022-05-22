#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "contacts_model.h"
#include "clientmanager.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

//    qRegisterMetaTypeStreamOperators<Contact>();
    QGuiApplication app(argc, argv);


    net::ConnectionArgumentsParser parser (*QCoreApplication::instance());
    ClientManager::instance().setConnectionSettings(parser);


    QQmlApplicationEngine engine;
    ContactsModel model;
    engine.addImportPath(":/qml");
//    ContactsModel::registerModel("Contacts");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("contactsModel", &model);

    engine.load(url);

    return app.exec();
}
