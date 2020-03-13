#include "CustomClass.h"

#include <QDebug>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    auto custom = CustomClass();
    qDebug() << "custom has right now the values:" << custom.avg << custom.exp;

//    QCoreApplication a(argc, argv);

//    return a.exec();
    return 13;
}
