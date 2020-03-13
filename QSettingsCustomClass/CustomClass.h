#pragma once

#include <QMetaType>

class CustomClass
{
public:
//    CustomClass();

    // handling for the QDataStream says that we need ctor, copy ctor and dtor - all public
    // (setting them default, just creates a problem, at least with c++17, because deleted by default)

    // TODO handlers for the QDataStream

    // fields
    int avg{1337};
    double exp{0.001};
};
Q_DECLARE_METATYPE(CustomClass); //! @attention beware of namespace, if one is used
