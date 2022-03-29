#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QTableWidget>
#include <QtWidgets>
#include <QLabel>
#include <QDebug>
#include <QTextStream>

#include "people.h"
#include "student.h"
#include "professor.h"
#include "worker.h"
#include "list.h"
#include "manual.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Table; }
QT_END_NAMESPACE

class Table : public QMainWindow
{
    Q_OBJECT

public:
    Table(QWidget *parent = nullptr);
    ~Table();

private slots:

    void on_add_clicked();

    void on_addWidgetStudent_clicked();
    void on_addWidgetProfessor_clicked();
    void on_addWidgetWorker_clicked();
    void on_backAdd_clicked();

    void on_cancelStudent_clicked();
    void on_cancelProfessor_clicked();
    void on_cancelWorker_clicked();

    void on_edit_clicked();

    void on_cancelEditStudent_clicked();
    void on_cancelEditProfessor_clicked();
    void on_cancelEditWorker_clicked();

    void on_find_clicked();
    void on_remove_clicked();

    void on_addNewStudent_clicked();
    void on_addNewProfessor_clicked();
    void on_addNewWorker_clicked();

    void on_editStudent_clicked();
    void on_editProfessor_clicked();
    void on_editWorker_clicked();

    void on_backFind_clicked();
    void on_findNameWidget_clicked();
    void on_findIDWidget_clicked();
    void on_findStatusWidget_clicked();

    void on_cancelFindName_clicked();
    void on_findName_clicked();
    void on_cancelFindID_clicked();
    void on_findID_clicked();
    void on_cancelFindStatus_clicked();
    void on_findStatus_clicked();

    void on_action_new_triggered();
    void on_action_open_triggered();
    void on_action_save_triggered();
    void on_action_save_as_triggered();
    void on_action_quit_triggered();

    void on_action_manual_triggered();
    void on_action_about_triggered();

private:
    Ui::Table *ui;

    List<People*> list;

    void newTable(List<People*> &list1);
    void writeToFile(QFile &file);
    void clearWidget();

    int indexEdit;
    QString openFile;
    bool checkModificationFile;

    void edit_Student();
    void edit_Professor();
    void edit_Worker();
};
#endif // TABLE_H
