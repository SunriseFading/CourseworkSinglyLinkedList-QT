#include "manual.h"
#include "ui_manual.h"

Manual::Manual(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manual)
{
    ui->setupUi(this);

    QFile file(QDir::currentPath()+"/Manual.htm");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString strManual;
    strManual = stream.readAll();

    ui->htm->setOpenExternalLinks(true);
    ui->htm->setHtml(strManual);

    setWindowTitle(tr("%1[*]").arg("Manual"));
}

Manual::~Manual()
{
    delete ui;
}
