#include "CustomTreeWidgetItem.h"

CustomTreeWidgetItem::CustomTreeWidgetItem(QTreeWidget *view, int type, QString name)
    :QTreeWidgetItem(view,type)
{
    this->name = name;
    this->setText(0, name);
}

CustomTreeWidgetItem::CustomTreeWidgetItem(QTreeWidgetItem *parent, int type, QString name)
    :QTreeWidgetItem(parent,type)
{
    this->name = name;
    this->setText(0, name);
}

CustomTreeWidgetItem::CustomTreeWidgetItem(QTreeWidgetItem *parent, int type, QString name, QString trg)
    :QTreeWidgetItem(parent,type)
{
    this->name = name;
    this->target = trg;
    this->setText(0, name);
}

CustomTreeWidgetItem::CustomTreeWidgetItem(QTreeWidgetItem *parent, int type, QString name, QString src, QString trg)
    :QTreeWidgetItem(parent,type)
{
    this->name = name;
    this->source = src;
    this->target = trg;
    this->setText(0, name);
}

QString CustomTreeWidgetItem::Name()
{
    return name;
}
QString CustomTreeWidgetItem::Target()
{
    return target;
}
QString CustomTreeWidgetItem::Source()
{
    return source;
}

QString CustomTreeWidgetItem::Value()
{
    return value;
}

void CustomTreeWidgetItem::setTask(QString name)
{
    this->name = name;
    this->setText(0, name);
}

void CustomTreeWidgetItem::setCopy(QString name, QString source, QString target)
{
    this->name = name;
    this->target = target;
    this->source = source;
    this->setText(0, name);
}

void CustomTreeWidgetItem::setOpenScen(QString value, QString target)
{
    this->name = value;
    this->value = value;
    this->target = target;
    this->setText(0, value);
}

void CustomTreeWidgetItem::setDelete(QString name, QString target)
{
    this->name = name;
    this->target = target;
    this->setText(0, name);
}

void CustomTreeWidgetItem::setStart(QString name, QString target)
{
    this->name = name;
    this->target = target;
    this->setText(0, name);
}
