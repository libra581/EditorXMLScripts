#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QTreeWidgetItem>
#include <QTime>

#include "CustomTreeWidgetItem.h"
#include "myDialog.h"
#include "myXmlHighlighter.h"
#include "myScene.h"

//#define gsgf        "Скопировать файл"
//#define pathSrc     "Путь к файл"
//#define pathTrgt    "Директория назначения"
#define DATA	"DATA/"
#define BIN		"BIN/"
#define TMI_TXT "TMI_TXT/"
#define CONFIG	"CONFIG/"
#define NSI		"NSI/"
#define ERR     "ERR/"

namespace Ui {
class myMainWindow;
}

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit myMainWindow(QWidget *parent = 0);
    ~myMainWindow();

    void makeXMLText(CustomTreeWidgetItem *item);
    CustomTreeWidgetItem *citem2;
    QXmlStreamReader *parseXML(QXmlStreamReader *xmlReader, CustomTreeWidgetItem *parent, int type, QString str);
public slots:
    void setTask(QString name);
    void setDelete(QString name, QString target);
    void setStart(QString name, QString target);
    void setCopy(QString name, QString source, QString target);
    void setOpenScen(QString value, QString source);


private slots:

    void TaskItem(QString name);
    void StartItem(QString name, QString target);
    void CopyItem(QString name, QString source, QString target);
    void DeleteItem(QString name, QString target);
    void FileItem(QString name, QString source, QString target);
    void OpenScenItem(QString value, QString source);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_actionTask_triggered();
    void on_actionDelete_triggered();
    void on_actionCopy_triggered();
    void on_actionStart_triggered();
    void on_actionSave_triggered();
    void on_actionFile_triggered();
    void on_actionDel_triggered();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actionFile_2_triggered();

    void on_actionOpenScen_triggered();

    void onFind(QString txt, int numberBlock);

    void on_checkBox_released();

private:
    Ui::myMainWindow *ui;
    myXMLHighlighter *m_myXmlHighlighter;   //объект работы с подсветкой в тексте
    myScene *pScene;    //Сцена для отображения блок-схемы
    QList<QColor> lstColor; // Цвета для отображения тега TASK

    myDialog *md = nullptr; //Указатель на нудный тип диалогового окна

    void parseXMLForAlgth();
};

#endif // MYMAINWINDOW_H
