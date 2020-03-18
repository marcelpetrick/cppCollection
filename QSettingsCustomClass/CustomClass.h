#pragma once

// Qt
#include <QtCore/QMetaType>
#include <QtCore/QDataStream>

//! @note workflow follows mostly https://stackoverflow.com/questions/18144377/writing-and-reading-custom-class-to-qsettings (first answer)
//! with the two QDataStream methods as friends

//! ------------------------------------------------------------------------------------
//! @brief Container for some custom-class to test if the serialisation/deserialisation works.
//! //! ------------------------------------------------------------------------------------
class CustomClass
{
public:
//    CustomClass();

    // handling for the QDataStream says that we need ctor, copy ctor and dtor - all public
    // (setting them default, just creates a problem, at least with c++17, because deleted by default)

    // TODO handlers for the QDataStream
    friend QDataStream& operator<<(QDataStream& out, const CustomClass& value)
    {
        out << value._avg;
        out << value._exp;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, CustomClass& value)
    {
        in >> value._avg;
        in >> value._exp;

        return in;
    }

    // fields
    int _avg{1337};
    double _exp{0.001};
};
Q_DECLARE_METATYPE(CustomClass); //! @attention beware of namespace, if one is used

//! ------------------------------------------------------------------------------------
//! @brief Container, which uses some container with typoe CustomClass.
//! //! ------------------------------------------------------------------------------------
class CustomClassContainer
{
public:


    // fields
    bool _hasSpecialFlag{false};
    std::vector<CustomClass> _params{};
};
Q_DECLARE_METATYPE(CustomClassContainer);
