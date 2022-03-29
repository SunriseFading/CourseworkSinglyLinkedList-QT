#include "professor.h"

Professor::Professor() : People(), department("") {}

Professor::Professor(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString Department)
    : People(Name, Birthday, Telephone, Address, ID),
      department(Department) {}

QChar Professor::status()
{
    return 'P';
}

QString Professor::tableID()
{
    return QString().setNum(id);
}

QString Professor::tableStatusPost()
{
    return "Professor";
}

QString Professor::tableJob()
{
    return department;
}

QString Professor::tableGroup()
{
    return "----------";
}

QString Professor::showBox()
{
    return department;
}

QString Professor::showApp()
{
    return "";
}

void Professor::setPeople(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString firstString, QString secondString, int Int)
{
    name = Name;
    birthday = Birthday;
    telephone = Telephone;
    address = Address;
    id = ID;
    department = firstString;
}
