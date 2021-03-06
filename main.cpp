// Wiencis, Rojek, Ochorok - 19.06 - System finansów
// Kod stworzony podczas tworzenia aplikacji desktopowej w środowisku QT

#include "login.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "login_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    login w;
    w.show();
    return a.exec();
}
