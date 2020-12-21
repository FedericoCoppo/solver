#include "mainwindow.h"

#include <QApplication>

Q_DECLARE_METATYPE(uint16_t)
Q_DECLARE_METATYPE(uint8_t)
Q_DECLARE_METATYPE(uint32_t)

int main(int argc, char *argv[])
{
    qRegisterMetaType<uint16_t>("uint16_t");
    qRegisterMetaType<uint32_t>("uint32_t");
    qRegisterMetaType<uint8_t>("uint8_t");

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Solver Offerte Commerciali  [Versione 1.0]");
    w.show();
    return a.exec();
}
