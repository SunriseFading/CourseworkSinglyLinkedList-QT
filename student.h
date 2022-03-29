#ifndef STUDENT_H
#define STUDENT_H

#include "people.h"

class Student: public People
{
private:
    QString group;
    QString educational_form;

public:
    Student();
    Student(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString Group, QString EdForm);

    QChar status();

    QString tableID();
    QString tableStatusPost();
    QString tableJob();
    QString tableGroup();

    QString showApp();
    QString showBox();

    void setPeople(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString firstString, QString secondString, int Int);
};

#endif // STUDENT_H
