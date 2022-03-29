#include "worker.h"

Worker::Worker() : People(), post(""), case_number(0) {}

Worker::Worker(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString Post, int CaseNum)
    : People(Name, Birthday, Telephone, Address, ID),
      post(Post), case_number(CaseNum) {}

QChar Worker::status()
{
    return 'W';
}

QString Worker::tableID()
{
    return QString().setNum(id);
}

QString Worker::tableStatusPost()
{
    return post;
}

QString Worker::tableJob()
{
    return QString().setNum(case_number);
}

QString Worker::tableGroup()
{
    return "----------";
}

QString Worker::showBox()
{
    return post;
}

QString Worker::showApp()
{
    return QString().setNum(case_number);
}

void Worker::setPeople(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString firstString, QString secondString, int Int)
{
    name = Name;
    birthday = Birthday;
    telephone = Telephone;
    address = Address;
    id = ID;
    post = firstString;
    case_number = Int;
}
