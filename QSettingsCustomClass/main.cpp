#include "CustomClass.h"

// Qt
#include <QtCore/QDebug>
#include <QtCore/QMetaType>
#include <QtCore/QSettings>
#include <QtCore/QVariant>

namespace  {
QString const cCompanyName{"marcelpetrick.it"};
QString const cAppName{"CustomClass"};
QString const cGroupName{"firstExample"};
};

int main(int argc, char *argv[])
{
    std::ignore = argc;
    std::ignore = argv;

    qRegisterMetaTypeStreamOperators<CustomClass>("CustomClass");

    // scope for writing QSettings
    {
        auto custom = CustomClass();
        qDebug() << "custom has right now the values:" << custom._avg << custom._exp;

        custom._avg = 123;
        custom._exp = 3.14; // pi day tomorrow!
        qDebug() << "custom has right now the values:" << custom._avg << custom._exp;

        QSettings settings(QSettings::UserScope, cCompanyName, cAppName);
        settings.beginGroup(cGroupName);
        settings.setValue("custom", QVariant::fromValue(custom));
        settings.endGroup();
        settings.sync();
    }

    // retrieve the values again
    {
        QSettings settings(QSettings::UserScope, cCompanyName, cAppName);
        settings.beginGroup(cGroupName);
        auto variant = settings.value("custom");
//        int const customClassTypetype = qRegisterMetaType<"CustomClass">;
//        if(variant.canConvert(customClassTypetype))
        {
            auto custom = variant.value<CustomClass>();
            qDebug() << "retrieved data from registry with values" << custom._avg << custom._exp; // :)
        }
        settings.endGroup(); // not that this matters in that case
    }

    // output:
    // custom has right now the values: 1337 0.001
    // custom has right now the values: 123 3.14
    // retrieved data from registry with values 123 3.14

    return 1337;
}
