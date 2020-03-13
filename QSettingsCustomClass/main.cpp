#include "CustomClass.h"

// Qt
#include <QtCore/QDebug>
#include <QtCore/QMetaType>
#include <QtCore/QSettings>
#include <QtCore/QVariant>
//#include <QCoreApplication> //not needed right now

int main(int argc, char *argv[])
{
    qRegisterMetaTypeStreamOperators<CustomClass>("CustomClass");

    // scope for writing QSettings
    {
        auto custom = CustomClass();
        qDebug() << "custom has right now the values:" << custom.avg << custom.exp;

        custom.avg = 123;
        custom.exp = 3.14; // pi day tomorrow!
        qDebug() << "custom has right now the values:" << custom.avg << custom.exp;

        QSettings settings(QSettings::UserScope, "marcelpetrick.it", "CustomClass");
        settings.beginGroup("firstExample");
        settings.setValue("custom", QVariant::fromValue(custom));
        settings.endGroup();
        settings.sync();
    }

    // retrieve the values again
    {
        QSettings settings(QSettings::UserScope, "marcelpetrick.it", "CustomClass");
        auto variant = settings.value("custom");
//        int const customClassTypetype = qRegisterMetaType<"CustomClass">;
//        if(variant.canConvert(customClassTypetype))
        {
            auto custom = variant.value<CustomClass>();
            qDebug() << "retrieved data from registry with values" << custom.avg << custom.exp; // :)
        }
    }

    //left over, no need for an event loop right now
//    QCoreApplication a(argc, argv);

//    return a.exec();

    return 13;
}
