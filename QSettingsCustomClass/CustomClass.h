#pragma once

// Qt
#include <QtCore/QMetaType>
#include <QtCore/QDataStream>

//! @note workflow follows mostly https://stackoverflow.com/questions/18144377/writing-and-reading-custom-class-to-qsettings (first answer)
//! with the two QDataStream methods as friends

class CustomClass
{
public:
//    CustomClass();

    // handling for the QDataStream says that we need ctor, copy ctor and dtor - all public
    // (setting them default, just creates a problem, at least with c++17, because deleted by default)

    // TODO handlers for the QDataStream
    friend QDataStream& operator<<(QDataStream& out, const CustomClass& value)
    {
        out << value.avg;
        out << value.exp;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, CustomClass& value)
    {
        in >> value.avg;
        in >> value.exp;

        return in;
    }

    // fields
    int avg{1337};
    double exp{0.001};
};
Q_DECLARE_METATYPE(CustomClass); //! @attention beware of namespace, if one is used
