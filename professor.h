#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "people.h"

class Professor: public People
{
private:
    QString department;

public:
    Professor();
    Professor(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString Department);

    QChar status();

    QString tableID();
    QString tableStatusPost();
    QString tableJob();
    QString tableGroup();

    QString showBox();
    QString showApp();

    void setPeople(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString firstString, QString secondString, int Int);
};

#endif // PROFESSOR_H
