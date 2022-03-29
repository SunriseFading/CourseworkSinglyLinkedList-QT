#include "table.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Table w;
    w.setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowContextHelpButtonHint);
    w.show();
    return a.exec();
}
