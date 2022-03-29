#include "table.h"
#include "ui_table.h"

Table::Table(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Table)
{
    ui->setupUi(this);

    indexEdit = -1;
    openFile = "";
    checkModificationFile = false;
    setWindowTitle(tr("%1[*]").arg("Information retrieval system \"University\""));

    //Работа с таблицей
    ui->table->setRowCount(0);
    ui->table->setColumnCount(8);

    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной строки

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Выравнивание ячеек в таблице

    ui->table->setHorizontalHeaderLabels(QStringList()
                                     <<tr("ID")
                                     <<tr("Full name")
                                     <<tr("Date of Birth")
                                     <<tr("Number")
                                     <<tr("Address")
                                     <<tr("Status/Position")
                                     <<tr("Place of work")
                                     <<tr("Group"));

    //Установление ограничений ввода
    ui->le_addGroupStudent->setMaxLength(10);
    ui->le_addAddressStudent->setMaxLength(30);
    ui->le_addAddressProfessor->setMaxLength(30);
    ui->le_addAddressWorker->setMaxLength(30);

    ui->le_editGroupStudent->setMaxLength(10);
    ui->le_editAddressStudent->setMaxLength(30);
    ui->le_editAddressProfessor->setMaxLength(30);
    ui->le_editAddressWorker->setMaxLength(30);

    QRegExp num("[0-9]{1,8}"); //Ввод только цифр
    QValidator *numValidator = new QRegExpValidator(num, this);

    ui->le_addIDStudent->setValidator(numValidator);
    ui->le_addIDProfessor->setValidator(numValidator);
    ui->le_addIDWorker->setValidator(numValidator);
    ui->le_addCaseNumWorker->setValidator(numValidator);

    ui->le_editIDStudent->setValidator(numValidator);
    ui->le_editIDProfessor->setValidator(numValidator);
    ui->le_editIDWorker->setValidator(numValidator);
    ui->le_editCaseNumWorker->setValidator(numValidator);

    ui->le_findID->setValidator(numValidator);

    QRegExp num11("[0-9]{1,11}"); //Ввод только цифр
    QValidator *num11Validator = new QRegExpValidator(num11, this);

    ui->le_addTelephoneStudent->setValidator(num11Validator);
    ui->le_addTelephoneProfessor->setValidator(num11Validator);
    ui->le_addTelephoneWorker->setValidator(num11Validator);

    ui->le_editTelephoneStudent->setValidator(num11Validator);
    ui->le_editTelephoneProfessor->setValidator(num11Validator);
    ui->le_editTelephoneWorker->setValidator(num11Validator);


    QRegExp name("[A-Za-zА-Яа-яЁё]{1}[A-Za-zА-Яа-яЁё\\s\\.]{1,30}"); //Ввод только букв латиницы или кириллицы, пробелов и точек
    QValidator *nameValidator = new QRegExpValidator(name, this);

    ui->le_addNameStudent->setValidator(nameValidator);
    ui->le_addNameProfessor->setValidator(nameValidator);
    ui->le_addNameWorker->setValidator(nameValidator);

    ui->le_editNameStudent->setValidator(nameValidator);
    ui->le_editNameProfessor->setValidator(nameValidator);
    ui->le_editNameWorker->setValidator(nameValidator);

    ui->le_findName->setValidator(nameValidator);

    //Заполнение боксов
    ui->box_addDepartmentProfessor->addItems(QStringList()
                                             <<tr("Department of Information Systems and Digital Technologies")
                                             <<tr("Department of Technical Physics and Mathematics")
                                             <<tr("Department of Information Security")
                                             <<tr("Department of Electronics, Radio Engineering and Communication Systems")
                                             <<tr("Department of Automated Control Systems and Cybernetics"));

    ui->box_editDepartmentProfessor->addItems(QStringList()
                                              <<tr("Department of Information Systems and Digital Technologies")
                                              <<tr("Department of Technical Physics and Mathematics")
                                              <<tr("Department of Information Security")
                                              <<tr("Department of Electronics, Radio Engineering and Communication Systems")
                                              <<tr("Department of Automated Control Systems and Cybernetics"));

    ui->box_addEdFormStudent->addItems(QStringList()
                                       <<tr("Full-time")
                                       <<tr("Part-time")
                                       <<tr("Correspondence"));

    ui->box_editEdFormStudent->addItems(QStringList()
                                        <<tr("Full-time")
                                        <<tr("Part-time")
                                        <<tr("Correspondence"));

    ui->box_addPostWorker->addItems(QStringList()
                                    <<tr("Guard")
                                    <<tr("Wardrobe maker")
                                    <<tr("Cleaner"));

    ui->box_editPostWorker->addItems(QStringList()
                                     <<tr("Guard")
                                     <<tr("Wardrobe maker")
                                     <<tr("Cleaner"));

    ui->box_findStatus->addItems(QStringList()
                                 <<tr("Students")
                                 <<tr("Professors")
                                 <<tr("Workers"));

    ui->stackedWidget->setCurrentIndex(0);
}

Table::~Table()
{
    delete ui;
}

void Table::newTable(List<People*> &list1)
{
    ui->table->setRowCount(list1.length());

    for (int i = 0; i < list1.length(); i++)
    {
        //Текущий элемент списка для вывода в таблицу
        People *temp = list1[i];

        QTableWidgetItem *item;
        item = new QTableWidgetItem(tr("%1").arg(temp->tableID()));
        ui->table->setItem(i, 0, item);

        item = new QTableWidgetItem(tr("%1").arg(temp->tableName()));
        ui->table->setItem(i, 1, item);

        item = new QTableWidgetItem(tr("%1").arg(temp->tableBirthday()));
        ui->table->setItem(i, 2, item);

        item = new QTableWidgetItem(tr("%1").arg(temp->tableTelephone()));
        ui->table->setItem(i, 3, item);

        item = new QTableWidgetItem(tr("%1").arg(temp->tableAddress()));
        ui->table->setItem(i, 4, item);

        item = new QTableWidgetItem(tr("%1").arg(temp->tableStatusPost()));
        ui->table->setItem(i, 5, item);

        item = new QTableWidgetItem(tr("%1").arg(temp->tableJob()));
        ui->table->setItem(i, 6, item);

        item = new QTableWidgetItem(tr("%1").arg(temp->tableGroup()));
        ui->table->setItem(i, 7, item);
    }
}

void Table::edit_Student()
{
    People *stud = list[indexEdit];

    //Вывод информации о студенте для посленующего редактирования
    ui->le_editIDStudent->setText(stud->showID());
    ui->de_editBirthdayStudent->setDate(QDate::fromString(stud->showBirtday()));
    ui->le_editNameStudent->setText(stud->showName());
    ui->le_editTelephoneStudent->setText(stud->showTelephone());
    ui->le_editAddressStudent->setText(stud->showAddress());
    ui->le_editGroupStudent->setText(stud->showApp());
    ui->box_editEdFormStudent->setCurrentText(stud->showBox());
}

void Table::edit_Professor()
{
    People *prof = list[indexEdit];

    ui->le_editIDProfessor->setText(prof->showID());
    ui->de_editBirthdayProfessor->setDate(QDate::fromString(prof->showBirtday()));
    ui->le_editNameProfessor->setText(prof->showName());
    ui->le_editTelephoneProfessor->setText(prof->showTelephone());
    ui->le_editAddressProfessor->setText(prof->showAddress());
    ui->box_editDepartmentProfessor->setCurrentText(prof->showBox());
}

void Table::edit_Worker()
{
    People *work = list[indexEdit];

    ui->le_editIDWorker->setText(work->showID());
    ui->de_editBirthdayWorker->setDate(QDate::fromString(work->showBirtday()));
    ui->le_editNameWorker->setText(work->showName());
    ui->le_editTelephoneWorker->setText(work->showTelephone());
    ui->le_editAddressWorker->setText(work->showAddress());
    ui->le_editCaseNumWorker->setText(work->showApp());
    ui->box_editPostWorker->setCurrentText(work->showBox());
}

void Table::on_add_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Table::on_addWidgetStudent_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Table::on_addWidgetProfessor_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Table::on_addWidgetWorker_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Table::on_backAdd_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Table::on_cancelStudent_clicked()
{
    ui->le_addIDStudent->clear();
    ui->le_addNameStudent->clear();
    QDate dat(2000, 1, 1);
    ui->de_addBirthdayStudent->setDate(dat);
    ui->le_addGroupStudent->clear();

    ui->le_addTelephoneStudent->clear();
    ui->le_addAddressStudent->clear();
    ui->box_addEdFormStudent->setCurrentIndex(0);


    ui->stackedWidget->setCurrentIndex(0);
}

void Table::on_cancelProfessor_clicked()
{
    ui->le_addIDProfessor->clear();
    ui->le_addNameProfessor->clear();
    QDate dat(2000, 1, 1);
    ui->de_addBirthdayProfessor->setDate(dat);

    ui->le_addTelephoneProfessor->clear();
    ui->le_addAddressProfessor->clear();
    ui->box_addDepartmentProfessor->setCurrentIndex(0);

    ui->stackedWidget->setCurrentIndex(0);
}

void Table::on_cancelWorker_clicked()
{
    ui->le_addIDWorker->clear();
    ui->le_addNameWorker->clear();
    QDate dat(2000, 1, 1);
    ui->de_addBirthdayWorker->setDate(dat);
    ui->box_addPostWorker->setCurrentIndex(0);

    ui->le_addTelephoneWorker->clear();
    ui->le_addAddressWorker->clear();
    ui->le_addCaseNumWorker->clear();

    ui->stackedWidget->setCurrentIndex(0);
}

void Table::on_edit_clicked()
{
    if(ui->table->rowCount() == 0)
    {
        QMessageBox::critical(this, "Error", "Table is empty");
    }
    else if (ui->table->currentRow() == -1)
    {
        QMessageBox::critical(this, "Error", "Select line");
    }
    else
    {
        int i = ui->table->currentRow();
        People * editPeople = list[i];

        if(editPeople->status() == 'S')
        {
            ui->stackedWidget->setCurrentIndex(5);
            indexEdit = i;
            edit_Student();
        }
        else if(editPeople->status() == 'P')
        {
            ui->stackedWidget->setCurrentIndex(6);
            indexEdit = i;
            edit_Professor();
        }
        else if(editPeople->status() == 'W')
        {
            ui->stackedWidget->setCurrentIndex(7);
            indexEdit = i;
            edit_Worker();
        }
    }
}

void Table::on_cancelEditStudent_clicked()
{
    //Очищение полей ввода данных
    ui->le_editIDStudent->clear();
    ui->le_editNameStudent->clear();
    QDate dat(2000, 1, 1);
    ui->de_editBirthdayStudent->setDate(dat);
    ui->le_editGroupStudent->clear();

    ui->le_editTelephoneStudent->clear();
    ui->le_editAddressStudent->clear();
    ui->box_editEdFormStudent->setCurrentIndex(0);


    ui->stackedWidget->setCurrentIndex(0);
}

void Table::on_cancelEditProfessor_clicked()
{
    ui->le_editIDProfessor->clear();
    ui->le_editNameProfessor->clear();
    QDate dat(2000, 1, 1);
    ui->de_editBirthdayProfessor->setDate(dat);

    ui->le_editTelephoneProfessor->clear();
    ui->le_editAddressProfessor->clear();
    ui->box_editDepartmentProfessor->setCurrentIndex(0);

    ui->stackedWidget->setCurrentIndex(0);
}

void Table::on_cancelEditWorker_clicked()
{
    ui->le_editIDWorker->clear();
    ui->le_editNameWorker->clear();
    QDate dat(2000, 1, 1);
    ui->de_editBirthdayWorker->setDate(dat);
    ui->box_editPostWorker->setCurrentIndex(0);

    ui->le_editTelephoneWorker->clear();
    ui->le_editAddressWorker->clear();
    ui->le_editCaseNumWorker->clear();

    ui->stackedWidget->setCurrentIndex(0);
}

void Table::on_find_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void Table::on_remove_clicked()
{
    if(ui->table->rowCount() == 0)
    {
        QMessageBox::critical(this, "Error", "Table is empty");
    }
    else if(ui->table->currentRow() == -1)
    {
        QMessageBox::critical(this, "Error", "Select line");
    }
    else
    {
        int i = ui->table->currentRow();
        list.removeAt(i);
        checkModificationFile = true;
    }
    newTable(list);
}

void Table::on_addNewStudent_clicked()
{
    bool notCorrect = false;

    //Проверка id
    if(ui->le_addIDStudent->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addIDStudent->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addIDStudent->setStyleSheet("QLabel { color : black; }");

    QString tempID = ui->le_addIDStudent->text();
    bool correctID = true;
    for(int i = 0; i < list.length(); i++)
    {
        if(list[i]->showID() == tempID)
        {
            correctID = false;
        }
    }
    if(!correctID)
    {
        notCorrect = true;
        ui->lbl_addIDStudent->setStyleSheet("QLabel { color : red; }");
    }

    //Проверка имени
    if(ui->le_addNameStudent->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addNameStudent->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addNameStudent->setStyleSheet("QLabel { color : black; }");

    //Проверка группы
    if(ui->le_addGroupStudent->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addGroupStudent->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addGroupStudent->setStyleSheet("QLabel { color : black; }");

    //Проверка телефона
    if(ui->le_addTelephoneStudent->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addTelephoneStudent->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addTelephoneStudent->setStyleSheet("QLabel { color : black; }");

    //Проверка адреса
    if(ui->le_addAddressStudent->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addAddressStudent->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addAddressStudent->setStyleSheet("QLabel { color : black; }");

    if(!notCorrect)
    {
        QString newName = ui->le_addNameStudent->text();
        QDate newBirthday = ui->de_addBirthdayStudent->date();
        QString newTelephone = ui->le_addTelephoneStudent->text();
        QString newAddress = ui->le_addAddressStudent->text();
        int newID = (ui->le_addIDStudent->text()).toInt();
        QString newGroup = ui->le_addGroupStudent->text();
        QString newEdForm = ui->box_addEdFormStudent->currentText();

        People *newStudent = new Student(newName, newBirthday, newTelephone, newAddress, newID, newGroup, newEdForm);

        list.append(newStudent);

        on_cancelStudent_clicked();

        checkModificationFile = true;
        newTable(list);
    }
    else
    {
        QMessageBox::warning(this, "Attention", "Incorrect data entered");
    }

}

void Table::on_addNewProfessor_clicked()
{
    bool notCorrect = false;

    //Проверка id
    if(ui->le_addIDProfessor->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addIDProfessor->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addIDProfessor->setStyleSheet("QLabel { color : black; }");

    QString tempID = ui->le_addIDProfessor->text();
    bool correctID = true;
    for(int i = 0; i < list.length(); i++)
    {
        if(list[i]->showID() == tempID)
        {
            correctID = false;
        }
    }
    if(!correctID)
    {
        notCorrect = true;
        ui->lbl_addIDProfessor->setStyleSheet("QLabel { color : red; }");
    }

    //Проверка имени
    if(ui->le_addNameProfessor->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addNameProfessor->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addNameProfessor->setStyleSheet("QLabel { color : black; }");

    //Проверка телефона
    if(ui->le_addTelephoneProfessor->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addTelephoneProfessor->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addTelephoneProfessor->setStyleSheet("QLabel { color : black; }");

    //Проверка адреса
    if(ui->le_addAddressProfessor->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addAddressProfessor->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addAddressProfessor->setStyleSheet("QLabel { color : black; }");

    if(!notCorrect)
    {
        QString newName = ui->le_addNameProfessor->text();
        QDate newBirthday = ui->de_addBirthdayProfessor->date();
        QString newTelephone = ui->le_addTelephoneProfessor->text();
        QString newAddress = ui->le_addAddressProfessor->text();
        int newID = (ui->le_addIDProfessor->text()).toInt();
        QString newDepartment = ui->box_addDepartmentProfessor->currentText();

        People *newProfessor = new Professor(newName, newBirthday, newTelephone, newAddress, newID, newDepartment);

        list.append(newProfessor);

        on_cancelProfessor_clicked();

        checkModificationFile = true;
        newTable(list);
    }
    else
    {
        QMessageBox::warning(this, "Attention", "Incorrect data entered");
    }
}

void Table::on_addNewWorker_clicked()
{
    bool notCorrect = false;

    //Проверка id
    if(ui->le_addIDWorker->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addIDWorker->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addIDWorker->setStyleSheet("QLabel { color : black; }");

    QString tempID = ui->le_addIDWorker->text();
    bool correctID = true;
    for(int i = 0; i < list.length(); i++)
    {
        if(list[i]->showID() == tempID)
        {
            correctID = false;
        }
    }
    if(!correctID)
    {
        notCorrect = true;
        ui->lbl_addIDWorker->setStyleSheet("QLabel { color : red; }");
    }

    //Проверка имени
    if(ui->le_addNameWorker->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addNameWorker->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addNameWorker->setStyleSheet("QLabel { color : black; }");

    //Проверка номера корпуса
    if(ui->le_addCaseNumWorker->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addCaseNumWorker->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addCaseNumWorker->setStyleSheet("QLabel { color : black; }");

    //Проверка телефона
    if(ui->le_addTelephoneWorker->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addTelephoneWorker->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addTelephoneWorker->setStyleSheet("QLabel { color : black; }");

    //Проверка адреса
    if(ui->le_addAddressWorker->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_addAddressWorker->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_addAddressWorker->setStyleSheet("QLabel { color : black; }");

    if(!notCorrect)
    {
        QString newName = ui->le_addNameWorker->text();
        QDate newBirthday = ui->de_addBirthdayWorker->date();
        QString newTelephone = ui->le_addTelephoneWorker->text();
        QString newAddress = ui->le_addAddressWorker->text();
        int newID = (ui->le_addIDWorker->text()).toInt();
        int newCaseNum = (ui->le_addCaseNumWorker->text()).toInt();
        QString newPost = ui->box_addPostWorker->currentText();

        People *newWorker = new Worker(newName, newBirthday, newTelephone, newAddress, newID, newPost, newCaseNum);

        list.append(newWorker);

        on_cancelWorker_clicked();

        checkModificationFile = true;
        newTable(list);
    }
    else
    {
        QMessageBox::warning(this, "Attention", "Incorrect data entered");
    }
}

void Table::on_editStudent_clicked()
{
    bool notCorrect = false;

    //Проверка id
    if(ui->le_editIDStudent->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editIDStudent->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editIDStudent->setStyleSheet("QLabel { color : black; }");

    QString tempID = ui->le_editIDStudent->text();
    bool correctID = true;
    for(int i = 0; i < list.length(); i++)
    {
        if(list[i]->showID() == tempID && i != indexEdit)
        {
            correctID = false;
        }
    }
    if(!correctID)
    {
        notCorrect = true;
        ui->lbl_editIDStudent->setStyleSheet("QLabel { color : red; }");
    }

    //Проверка имени
    if(ui->le_editNameStudent->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editNameStudent->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editNameStudent->setStyleSheet("QLabel { color : black; }");

    //Проверка группы
    if(ui->le_editGroupStudent->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editGroupStudent->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editGroupStudent->setStyleSheet("QLabel { color : black; }");

    //Проверка телефона
    if(ui->le_editTelephoneStudent->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editTelephoneStudent->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editTelephoneStudent->setStyleSheet("QLabel { color : black; }");

    //Проверка адреса
    if(ui->le_editAddressStudent->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editAddressStudent->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editAddressStudent->setStyleSheet("QLabel { color : black; }");

    if(!notCorrect)
    {
        QString newName = ui->le_editNameStudent->text();
        QDate newBirthday = ui->de_editBirthdayStudent->date();
        QString newTelephone = ui->le_editTelephoneStudent->text();
        QString newAddress = ui->le_editAddressStudent->text();
        int newID = (ui->le_editIDStudent->text()).toInt();
        QString newGroup = ui->le_editGroupStudent->text();
        QString newEdForm = ui->box_editEdFormStudent->currentText();

        People *editStud = list[indexEdit];

        //Изменение информации о студенте
        editStud->setPeople(newName, newBirthday, newTelephone, newAddress, newID, newGroup, newEdForm, 0);

        on_cancelEditStudent_clicked();

        checkModificationFile = true;
        newTable(list);
    }
    else
    {
        QMessageBox::warning(this, "Attention", "Incorrect data entered");
    }
}

void Table::on_editProfessor_clicked()
{
    bool notCorrect = false;

    //Проверка id
    if(ui->le_editIDProfessor->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editIDProfessor->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editIDProfessor->setStyleSheet("QLabel { color : black; }");

    QString tempID = ui->le_editIDProfessor->text();
    bool correctID = true;
    for(int i = 0; i < list.length(); i++)
    {
        if(list[i]->showID() == tempID && i != indexEdit)
        {
            correctID = false;
        }
    }
    if(!correctID)
    {
        notCorrect = true;
        ui->lbl_editIDProfessor->setStyleSheet("QLabel { color : red; }");
    }

    //Проверка имени
    if(ui->le_editNameProfessor->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editNameProfessor->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editNameProfessor->setStyleSheet("QLabel { color : black; }");

    //Проверка телефона
    if(ui->le_editTelephoneProfessor->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editTelephoneProfessor->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editTelephoneProfessor->setStyleSheet("QLabel { color : black; }");

    //Проверка адреса
    if(ui->le_editAddressProfessor->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editAddressProfessor->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editAddressProfessor->setStyleSheet("QLabel { color : black; }");

    if(!notCorrect)
    {
        QString newName = ui->le_editNameProfessor->text();
        QDate newBirthday = ui->de_editBirthdayProfessor->date();
        QString newTelephone = ui->le_editTelephoneProfessor->text();
        QString newAddress = ui->le_editAddressProfessor->text();
        int newID = (ui->le_editIDProfessor->text()).toInt();
        QString newDepartment = ui->box_editDepartmentProfessor->currentText();

        People *editProf = list[indexEdit];

        //Изменение информации о профессоре
        editProf->setPeople(newName, newBirthday, newTelephone, newAddress, newID, newDepartment, "", 0);

        on_cancelEditProfessor_clicked();

        checkModificationFile = true;
        newTable(list);
    }
    else
    {
        QMessageBox::warning(this, "Attention", "Incorrect data entered");
    }
}

void Table::on_editWorker_clicked()
{
    bool notCorrect = false;

    //Проверка id
    if(ui->le_editIDWorker->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editIDWorker->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editIDWorker->setStyleSheet("QLabel { color : black; }");

    QString tempID = ui->le_editIDWorker->text();
    bool correctID = true;
    for(int i = 0; i < list.length(); i++)
    {
        if(list[i]->showID() == tempID && i != indexEdit)
        {
            correctID = false;
        }
    }
    if(!correctID)
    {
        notCorrect = true;
        ui->lbl_editIDWorker->setStyleSheet("QLabel { color : red; }");
    }

    //Проверка имени
    if(ui->le_editNameWorker->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editNameWorker->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editNameWorker->setStyleSheet("QLabel { color : black; }");

    //Проверка телефона
    if(ui->le_editTelephoneWorker->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editTelephoneWorker->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editTelephoneWorker->setStyleSheet("QLabel { color : black; }");

    //Проверка адреса
    if(ui->le_editAddressWorker->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editAddressWorker->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editAddressWorker->setStyleSheet("QLabel { color : black; }");

    //Проверка номера корпуса
    if(ui->le_editCaseNumWorker->text().isEmpty())
    {
        notCorrect = true;
        ui->lbl_editCaseNumWorker->setStyleSheet("QLabel { color : red; }");
    }
    else ui->lbl_editCaseNumWorker->setStyleSheet("QLabel { color : black; }");

    if(!notCorrect)
    {
        QString newName = ui->le_editNameWorker->text();
        QDate newBirthday = ui->de_editBirthdayWorker->date();
        QString newTelephone = ui->le_editTelephoneWorker->text();
        QString newAddress = ui->le_editAddressWorker->text();
        int newID = (ui->le_editIDWorker->text()).toInt();
        int newCaseNum = (ui->le_editCaseNumWorker->text()).toInt();
        QString newPost = ui->box_editPostWorker->currentText();

        People *editWork = list[indexEdit];

        //Изменение информации о профессоре
        editWork->setPeople(newName, newBirthday, newTelephone, newAddress, newID, newPost, "", newCaseNum);

        on_cancelEditWorker_clicked();

        checkModificationFile = true;
        newTable(list);
    }
    else
    {
        QMessageBox::warning(this, "Attention", "Incorrect data entered");
    }
}

void Table::on_backFind_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Table::on_findNameWidget_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void Table::on_findIDWidget_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void Table::on_findStatusWidget_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}

void Table::on_cancelFindName_clicked()
{
    ui->le_findName->clear();
    ui->stackedWidget->setCurrentIndex(0);
    newTable(list);
}

void Table::on_findName_clicked()
{
    QString findName = ui->le_findName->text();

    if(findName == "")
    {
        QMessageBox::warning(this, "Attention", "Enter data to search");
    }
    else
    {
        List<People*> findList;

        for(int i = 0; i < list.length(); i++)
        {
            if(list[i]->showName().contains(findName, Qt::CaseInsensitive))
            {
                findList.append(list[i]);
            }
        }

        newTable(findList);
    }
}

void Table::on_cancelFindID_clicked()
{
    ui->le_findID->clear();
    ui->stackedWidget->setCurrentIndex(0);
    newTable(list);
}

void Table::on_findID_clicked()
{
    if(ui->le_findID->text() == "")
    {
        QMessageBox::warning(this, "Attention", "Enter data to search");
    }
    else
    {
        List<People*> findList;

        QString findID = ui->le_findID->text();

        for(int i = 0; i < list.length(); i++)
        {
            if(list[i]->showID() == findID)
            {
                findList.append(list[i]);
            }
        }

        newTable(findList);
    }
}


void Table::on_cancelFindStatus_clicked()
{
    ui->box_findStatus->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    newTable(list);
}

void Table::on_findStatus_clicked()
{
    List<People*> findList;

    QString status_post = ui->box_findStatus->currentText();

    if(status_post == "Students")
    {
        for(int i = 0; i < list.length(); i++)
        {
            if(list[i]->status() == 'S')
            {
                findList.append(list[i]);
            }
        }
    }
    else if(status_post == "Professors")
    {
        for(int i = 0; i < list.length(); i++)
        {
            if(list[i]->status() == 'P')
            {
                findList.append(list[i]);
            }
        }
    }
    else if(status_post == "Workers")
    {
        for(int i = 0; i < list.length(); i++)
        {
            if(list[i]->status() == 'W')
            {
                findList.append(list[i]);
            }
        }
    }

    newTable(findList);
}

void Table::on_action_new_triggered()
{
    if(checkModificationFile)
    {
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if(res == QMessageBox::Yes)
        {
            on_action_save_triggered();
        }
    }

    list.clear();
    newTable(list);
    checkModificationFile = false;
    openFile = "";
    clearWidget();
}

void Table::on_action_open_triggered()
{
    if(checkModificationFile)
    {
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if(res == QMessageBox::Yes)
        {
            on_action_save_triggered();
        }
    }

    list.clear();

    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "Text file (*.txt)");

    qDebug() << "";
    if(!fileName.isEmpty())
    {
        openFile = fileName;

        QFile file(fileName);
        file.open(QIODevice::ReadOnly);

        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        int len = (stream.readLine()).toInt();

        for(int i = 0; i < len; i++)
        {
            QString statusString = stream.readLine();

            if(statusString[0] == 'S')
            {
                int newID = (stream.readLine()).toInt();
                QString newName = stream.readLine();
                QDate newBirthday = QDate::fromString(stream.readLine());
                QString newTelephone = stream.readLine();
                QString newAddress = stream.readLine();
                QString newGroup = stream.readLine();
                QString newEdForm = stream.readLine();

                People * stud = new Student(newName, newBirthday, newTelephone, newAddress, newID, newGroup, newEdForm);
                list.append(stud);
            }
            else if(statusString[0] == 'P')
            {
                int newID = (stream.readLine()).toInt();
                QString newName = stream.readLine();
                QDate newBirthday = QDate::fromString(stream.readLine());
                QString newTelephone = stream.readLine();
                QString newAddress = stream.readLine();
                QString newDepartment = stream.readLine();

                People * prof = new Professor(newName, newBirthday, newTelephone, newAddress, newID, newDepartment);
                list.append(prof);
            }
            else if(statusString[0] == 'W')
            {
                int newID = (stream.readLine()).toInt();
                QString newName = stream.readLine();
                QDate newBirthday = QDate::fromString(stream.readLine());
                QString newTelephone = stream.readLine();
                QString newAddress = stream.readLine();
                QString newPost = stream.readLine();
                int newCaseNum = (stream.readLine()).toInt();

                People * work = new Worker(newName, newBirthday, newTelephone, newAddress, newID, newPost, newCaseNum);
                list.append(work);
            }
        }

        file.close();

        newTable(list);
        checkModificationFile = false;
        clearWidget();
    }
}

void Table::on_action_save_triggered()
{
    QFile file;

    if(openFile == "")
    {
        on_action_save_as_triggered();
    }
    else
    {
        file.setFileName(openFile);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        writeToFile(file);
        checkModificationFile = false;
        clearWidget();
        file.close();
    }
}

void Table::on_action_save_as_triggered()
{
    QFile file;

    QString fileName = QFileDialog::getSaveFileName(this, "Save as ...", QDir::homePath(), "Text file (*.txt)");
    if (!fileName.isEmpty())
    {
        openFile = fileName;
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        writeToFile(file);
        checkModificationFile = false;
        clearWidget();
        file.close();
    }
}

void Table::writeToFile(QFile &file)
{
    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    stream << list.length() << "\n";

    for(int i = 0; i < list.length(); i++)
    {
        People * writePeople = list[i];

        if(writePeople->status() == 'S')
        {
            stream << "Student\n";
            stream << writePeople->showID() << "\n";
            stream << writePeople->showName() << "\n";
            stream << writePeople->showBirtday() << "\n";
            stream << writePeople->showTelephone() << "\n";
            stream << writePeople->showAddress() << "\n";
            stream << writePeople->showApp() << "\n";
            stream << writePeople->showBox() << "\n";
        }
        else if(writePeople->status() == 'P')
        {
            stream << "Professor\n";
            stream << writePeople->showID() << "\n";
            stream << writePeople->showName() << "\n";
            stream << writePeople->showBirtday() << "\n";
            stream << writePeople->showTelephone() << "\n";
            stream << writePeople->showAddress() << "\n";
            stream << writePeople->showBox() << "\n";
        }
        else if(writePeople->status() == 'W')
        {
            stream << "Worker\n";
            stream << writePeople->showID() << "\n";
            stream << writePeople->showName() << "\n";
            stream << writePeople->showBirtday() << "\n";
            stream << writePeople->showTelephone() << "\n";
            stream << writePeople->showAddress() << "\n";
            stream << writePeople->showBox() << "\n";
            stream << writePeople->showApp() << "\n";
        }
    }
}

void Table::clearWidget()
{
    on_cancelStudent_clicked();
    on_cancelProfessor_clicked();
    on_cancelWorker_clicked();

    on_cancelEditStudent_clicked();
    on_cancelEditProfessor_clicked();
    on_cancelEditWorker_clicked();

    ui->le_findID->clear();
    ui->le_findName->clear();
    ui->box_findStatus->setCurrentIndex(0);
}

void Table::on_action_quit_triggered()
{
    if(checkModificationFile)
    {
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if(res == QMessageBox::Yes)
        {
            on_action_save_triggered();
        }
    }

    close();
}

void Table::on_action_manual_triggered()
{
    Manual manualWidget;
    manualWidget.setModal(true);
    manualWidget.exec();
}

void Table::on_action_about_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    QString str;
    str = "<b>Information retrieval system \"University\"</b><br>The program is designed to record data on students and university employees<br>";
    str = str + "<br>Developer: Bykov Vladislav";
    str = str + "<br>Email: vlad.bykov2004@mail.ru";

    msgBox.setText(str);
    msgBox.exec();
}
