#include "student.h"

Student::Student() : People(), group(""), educational_form("") {}

Student::Student(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString Group, QString EdForm)
    : People(Name, Birthday, Telephone, Address, ID),
      group(Group), educational_form(EdForm) {}

QChar Student::status()
{
    return 'S';
}

QString Student::tableID()
{
    return QString().setNum(id);
}

QString Student::tableStatusPost()
{
    return "Student";
}

QString Student::tableJob()
{
    return "----------";
}

QString Student::tableGroup()
{
    return group + "(" + educational_form + ")";
}

QString Student::showApp()
{
    return group;
}

QString Student::showBox()
{
    return educational_form;
}

void Student::setPeople(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString firstString, QString secondString, int Int)
{
    name = Name;
    birthday = Birthday;
    telephone = Telephone;
    address = Address;
    id = ID;
    group = firstString;
    educational_form = secondString;
}
