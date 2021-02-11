#include "myDialog.h"
#include "ui_myDialog.h"

myDialog::myDialog( quint8 type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDialog)
{
    ui->setupUi(this);

    currentType = type;

    ui->label_nameFile->setVisible(false);
    ui->label_openscen_path->setVisible(false);
    ui->label_openscen_value->setVisible(false);

    //Выбор типа диалогового окна
    //SCEN       0
    //TASK       1
    //COPY       2
    //DELETE     3
    //START      4
    //FILE       5
    //OPENSCEN   6
    switch (type)
    {
        case 1:
            this->setWindowTitle("Создать группу задач");
            ui->lineEdit_src->setVisible(false);
            ui->label_src->setVisible(false);
            ui->lineEdit_trgt->setVisible(false);
            ui->label_trgt->setVisible(false);
            break;

        case 2:
            this->setWindowTitle("Копировать файл");
            break;

        case 3:
            this->setWindowTitle("Удалить файл");
            ui->lineEdit_src->setVisible(false);
            ui->label_src->setVisible(false);
            break;
        case 4:
            this->setWindowTitle("Запустить процесс");
            ui->lineEdit_src->setVisible(false);
            ui->label_src->setVisible(false);
            break;
        case 5:
            this->setWindowTitle("Файл");
            ui->label_nameFile->setVisible(true);
            ui->label_trgt->setVisible(false);
            break;

        case 6:
            this->setWindowTitle("Ветвление");
            ui->lineEdit_src->setVisible(false);
            ui->label_src->setVisible(false);
            ui->label_trgt->setVisible(false);
            ui->label_3->setVisible(false);
            ui->label_openscen_path->setVisible(true);
            ui->label_openscen_value->setVisible(true);
            break;
    }
}

myDialog::myDialog( quint8 type, QString name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDialog)
{
    ui->setupUi(this);
    currentType = type;

    ui->label_nameFile->setVisible(false);
    ui->label_openscen_path->setVisible(false);
    ui->label_openscen_value->setVisible(false);

    this->setWindowTitle("Создать группу задач");

    ui->lineEdit_src->setVisible(false);
    ui->label_src->setVisible(false);
    ui->lineEdit_trgt->setVisible(false);
    ui->label_trgt->setVisible(false);

    ui->lineEdit_3->setText(name);
}


myDialog::myDialog( quint8 type, QString name, QString target, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDialog)
{
    ui->setupUi(this);

    ui->label_nameFile->setVisible(false);
    ui->label_openscen_path->setVisible(false);
    ui->label_openscen_value->setVisible(false);

    currentType = type;

    switch (type)
    {
        case 3:
            this->setWindowTitle("Удалить файл");
            ui->lineEdit_src->setVisible(false);
            ui->label_src->setVisible(false);
            ui->lineEdit_3->setText(name);
            ui->lineEdit_trgt->setText(target);
            break;

        case 4:
            this->setWindowTitle("Запустить процесс");
            ui->lineEdit_src->setVisible(false);
            ui->label_src->setVisible(false);
            ui->lineEdit_3->setText(name);
            ui->lineEdit_trgt->setText(target);
            break;

        case 6:
            this->setWindowTitle("Ветвление");
            ui->lineEdit_src->setVisible(false);
            ui->label_src->setVisible(false);
            ui->label_trgt->setVisible(false);
            ui->label_3->setVisible(false);
            ui->label_openscen_path->setVisible(true);
            ui->label_openscen_value->setVisible(true);
            ui->lineEdit_3->setText(name);
            ui->lineEdit_trgt->setText(target);
            break;
    }

}

myDialog::myDialog( quint8 type, QString name, QString target, QString source, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDialog)
{
    ui->setupUi(this);
    currentType = type;

    ui->label_nameFile->setVisible(false);
    ui->label_openscen_path->setVisible(false);
    ui->label_openscen_value->setVisible(false);

    switch (type)
    {
        case COPY:
            this->setWindowTitle("Копировать файл");
            break;

        case FILE:
            this->setWindowTitle("Создание файла");
            ui->label_nameFile->setVisible(true);
            ui->label_trgt->setVisible(false);
            break;
    }

    ui->lineEdit_3->setText(name);
    ui->lineEdit_src->setText(source);
    ui->lineEdit_trgt->setText(target);

}

myDialog::~myDialog()
{
    delete ui;
}

void myDialog::on_buttonBox_accepted()
{
    //Отправление сигналов MainWindow на обработку добалвенного тега
    switch (currentType)
    {
        case 1:
            emit TaskSet(ui->lineEdit_3->text());
            break;
        case 2:
            emit CopySet(ui->lineEdit_3->text(), ui->lineEdit_src->text(), ui->lineEdit_trgt->text());
            break;
        case 3:
            emit DeleteSet(ui->lineEdit_3->text(), ui->lineEdit_trgt->text());
            break;
        case 4:
            emit StartSet(ui->lineEdit_3->text(), ui->lineEdit_trgt->text());
            break;
        case 5:
            emit FileSet(ui->lineEdit_3->text(), ui->lineEdit_src->text(), ui->lineEdit_trgt->text());
            break;
        case 6:
            emit OpenScenSet(ui->lineEdit_3->text(), ui->lineEdit_trgt->text());
            break;
    }
}
