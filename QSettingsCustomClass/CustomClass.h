#pragma once

// Qt
#include <QtCore/QMetaType>
#include <QtCore/QDataStream>
#include <QtCore/QList>

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

    // handlers for the QDataStream
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
//! @brief Container, which uses some container with type CustomClass.
//! //! ------------------------------------------------------------------------------------
class CustomClassContainer
{
public:
    // handlers for the QDataStream
    friend QDataStream& operator<<(QDataStream& out, const CustomClassContainer& value)
    {
        // for the flag
        out << value._hasSpecialFlag;

        // for the list

        //! idea: was to use QList, because this is serializable, but does not work
//        auto stdList = std::list(value._params.begin(), value._params.end());
//        auto qlist = QList<CustomClassContainer>::fromStdList(stdList);
//        out << qlist;

        //! Iterate over the items and put them to the stream.
        for( auto const& elem : value._params)
        {
            out << elem;
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, CustomClassContainer& value)
    {
        // for the flag
        in >> value._hasSpecialFlag;

        // for the list
        // see: https://stackoverflow.com/questions/21186434/save-and-load-qlistclass-to-file
        while (!in.atEnd())
        {
            // create new item
            CustomClass cc;
            // read
            in >> cc;
            // put into container
            value._params.push_back(cc);
        }

        return in;
    }

    // fields
    bool _hasSpecialFlag{false};
    std::vector<CustomClass> _params{};
};
Q_DECLARE_METATYPE(CustomClassContainer);
