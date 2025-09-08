#include "gamepanel.h"
#include "loading.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "LandLords_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    //注册资源文件
    QResource::registerResource("./resource.rcc");
    Loading w;
    w.show();
    return a.exec();
}
