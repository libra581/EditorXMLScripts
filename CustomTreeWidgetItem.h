#ifndef CUSTOMTREEWIDGETITEM_H
#define CUSTOMTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include <QDebug>

class CustomTreeWidgetItem : public QTreeWidgetItem
{
public:
    explicit CustomTreeWidgetItem(QTreeWidgetItem *parent, int type, QString name);
    explicit CustomTreeWidgetItem(QTreeWidgetItem *parent, int type, QString name, QString trg);
    explicit CustomTreeWidgetItem(QTreeWidgetItem *parent, int type, QString name, QString src, QString trg);
    explicit CustomTreeWidgetItem(QTreeWidget *view, int type, QString name);

    QString Name();
    QString Target();
    QString Source();
    QString Value();

//Слоты реагирования на добавление объекта для иерархии
public slots:
    //Слот распределены по тегам и свойствам данных тегов
    //Свойства приходят из класса myDialog
    void setTask(QString name);
    void setDelete(QString name, QString target);
    void setStart(QString name, QString target);
    void setCopy(QString name, QString source, QString target);
    void setOpenScen(QString value, QString source);

private:
    QString name;
    QString source;
    QString target;
    QString value;

};

#endif // CUSTOMTREEWIDGETITEM_H
