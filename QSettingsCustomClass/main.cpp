#include "CustomClass.h"

// Qt
#include <QtCore/QDebug>
#include <QtCore/QMetaType>
#include <QtCore/QSettings>
#include <QtCore/QVariant>

// std
#include <vector>

namespace  {
QString const cCompanyName{"marcelpetrick.it"};
QString const cAppName{"CustomClass"};
QString const cGroupName{"firstExample"};
int const cLEET{1337};
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

    //! -------------------- yeah, maybe make it a real QTest ------------------

    qRegisterMetaTypeStreamOperators<CustomClassContainer>("CustomClassContainer");

    // scope for writing:
    {
        // initialize
        auto ccc = CustomClassContainer();
        ccc._hasSpecialFlag = true;
        for(int i = 0; i < 3; i++)
        {
            auto custom = CustomClass();
            custom._avg = 1 * i;
            custom._exp = 0.111 * i;
            ccc._params.push_back(custom);
        }
        QSettings settings(QSettings::UserScope, cCompanyName, cAppName);
        settings.beginGroup(cGroupName);
        settings.setValue("CustomContainerClass", QVariant::fromValue(ccc));
        settings.endGroup();
        settings.sync();
    }

    // scope for reading
    {
        QSettings settings(QSettings::UserScope, cCompanyName, cAppName);
        settings.beginGroup(cGroupName);
        auto variant = settings.value("CustomContainerClass");
        auto ccc = variant.value<CustomClassContainer>();
        qDebug() << "retrieved data from registry with values" << (ccc._hasSpecialFlag ? "TRUE" : "FALSE" );
        qDebug() << " print now the param-package:";
        for(auto const& elem : ccc._params)
        {
            qDebug() << "\t" << elem._avg << elem._exp; // :)
        }
        settings.endGroup(); // not that this matters in that case
    }

    //! problem: assert fail; what now?
    // QVariant::save: unable to save type 'CustomClassContainer' (type id: 1025).
    //ASSERT failure in QVariant::save: "Invalid type to save", file kernel\qvariant.cpp, line 2594

    // TODO to serialize the std::map<std::String, CustomContainerClass> maybe use the way to serialize a QMap.
    // and convert eh std::map to QMap
    // or Abust groups: see https://gist.github.com/nowrep/1810670

    return cLEET;
}
