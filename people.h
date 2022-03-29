#ifndef PEOPLE_H
#define PEOPLE_H

#include <QString>
#include <QDate>

class People
{
protected:
    QString name;
    QDate birthday;
    QString telephone;
    QString address;
    int id;

public:
    People()
    {
        name = "";
        birthday.setDate(2000, 1, 1);
        telephone = "";
        address = "";
        id = 0;
    }

    People(QString Name, QDate Birthday, QString Telephone, QString Address, int ID)
    {
        name = Name;
        birthday =  Birthday;
        telephone = Telephone;
        address = Address;
        id = ID;
    }

    ///Возвращает условное обозначение класса
    virtual QChar status() = 0;

    QString tableName() { return name; }
    QString tableBirthday() { return birthday.toString(); }
    QString tableTelephone() { return telephone; }
    QString tableAddress() { return address; }

    virtual QString tableID() = 0;
    virtual QString tableStatusPost() = 0;
    virtual QString tableJob() = 0;
    virtual QString tableGroup() = 0;

    QString showID() { return QString().setNum(id); }
    QString showName() { return name; }
    QString showBirtday() { return birthday.toString(); }
    QString showTelephone() { return telephone; }
    QString showAddress() { return address; }

    virtual QString showBox() = 0;
    virtual QString showApp() = 0;

    ///Ввод информации
    virtual void setPeople(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString firstString, QString secondString, int Int) = 0;
};

#endif // PEOPLE_H
