#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QDebug>

//Типы диалогового окна
#define SCEN       0
#define TASK       1
#define COPY       2
#define DELETE     3
#define START      4
#define FILE       5
#define OPENSCEN   6

namespace Ui {
class myDialog;
}

class myDialog : public QDialog
{
    Q_OBJECT
signals:
    void TaskSet    (QString);
    void DeleteSet  (QString, QString);
    void StartSet   (QString, QString);
    void CopySet    (QString, QString, QString);
    void FileSet    (QString, QString, QString);
    void OpenScenSet    (QString, QString);

public:
    explicit myDialog(quint8 type, QWidget *parent = 0);
    explicit myDialog( quint8 type, QString name, QWidget *parent = 0);
    explicit myDialog( quint8 type, QString name, QString target, QWidget *parent = 0);
    explicit myDialog( quint8 type, QString name, QString target, QString source, QWidget *parent = 0);
    ~myDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::myDialog *ui;    
    quint8 currentType; //Тип диалогового окна по тегу
                        //SCEN       0
                        //TASK       1
                        //COPY       2
                        //DELETE     3
                        //START      4
                        //FILE       5
                        //OPENSCEN   6
};

#endif // MYDIALOG_H
