#include "CustomClass.h"

// Qt
#include <QtCore/QDebug>
#include <QtCore/QMetaType>
//#include <QCoreApplication>

int main(int argc, char *argv[])
{
    auto custom = CustomClass();
    qDebug() << "custom has right now the values:" << custom.avg << custom.exp;

    custom.avg = 123;
    custom.exp = 3.14; // pi day tomorrow!

    qRegisterMetaTypeStreamOperators<CustomClass>("CustomClass");


    //left over, no need for an event loop right now
//    QCoreApplication a(argc, argv);

//    return a.exec();

    return 13;
}
