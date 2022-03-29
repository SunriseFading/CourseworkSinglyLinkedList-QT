#ifndef WORKER_H
#define WORKER_H

#include "people.h"

class Worker: public People
{
private:
    QString post;
    int case_number;

public:
    Worker();
    Worker(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString Post, int CaseNum);

    QChar status();

    QString tableID();
    QString tableStatusPost();
    QString tableJob();
    QString tableGroup();

    QString showBox();
    QString showApp();

    void setPeople(QString Name, QDate Birthday, QString Telephone, QString Address, int ID, QString firstString, QString secondString, int Int);
};

#endif // WORKER_H
