#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "quick/widget/svg.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<Svg>("com.vision.quick", 1, 0, "Svg");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
