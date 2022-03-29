#ifndef MANUAL_H
#define MANUAL_H

#include <QDialog>
#include <QTextBrowser>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>

namespace Ui {
class Manual;
}

class Manual : public QDialog
{
    Q_OBJECT

public:
    explicit Manual(QWidget *parent = nullptr);
    ~Manual();

private:
    Ui::Manual *ui;
};

#endif // MANUAL_H
