#include "CustomClass.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    auto custom = CustomClass();

    QCoreApplication a(argc, argv);

    return a.exec();
}
