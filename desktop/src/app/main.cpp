#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "displayconfig.h"
#include "outputlistmodel.h"
#include "remotesensor.h"
#include "sensorlistmodel.h"

#include <KScreen/Config>
#include <KScreen/Output>

int main(int argc, char* argv[])
{
    // Create App
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Register custom type to be accessible from QML
    qmlRegisterType<RemoteSensor>("me.fuhrmannb.rotatomatic", 0, 1, "RemoteSensor");
    qmlRegisterType<SensorListModel>("me.fuhrmannb.rotatomatic", 0, 1, "SensorListModel");
    qmlRegisterType<OutputListModel>("me.fuhrmannb.rotatomatic", 0, 1, "OutputListModel");
    qmlRegisterType<KScreen::Output>("org.kde.kscreen", 1, 0, "KScreenOutput");
    qmlRegisterType<KScreen::Config>("org.kde.kscreen", 1, 0, "KScreenConfig");

    // Setup models
    SensorListModel sensorListModel;
    OutputListModel outputListModel;

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("sensorListModel", &sensorListModel);
    context->setContextProperty("outputListModel", &outputListModel);
    qmlRegisterSingletonType<DisplayConfig>("me.fuhrmannb.rotatomatic", 0, 1, "DisplayConfig",
        [](QQmlEngine* engine, QJSEngine* scriptEngine) -> QObject* {
            Q_UNUSED(engine)
            Q_UNUSED(scriptEngine)

            return DisplayConfig::instance();
        });

    // Setup QML engine and load main.qml
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    // Start app
    return app.exec();
}
