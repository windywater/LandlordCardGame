#include "MainFrame.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(":/zh.qm", QApplication::applicationDirPath());
    a.installTranslator(&translator);

    QFile qssFile(":/stylesheet.qss");
    qssFile.open(QIODevice::ReadOnly);
    QString stylesheet = QString::fromUtf8(qssFile.readAll());
    a.setStyleSheet(stylesheet);
    qssFile.close();

    MainFrame w;
    w.setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    w.show();

    return a.exec();
}
