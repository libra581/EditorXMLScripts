#include "myMainWindow.h"
#include "ui_myMainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QtXml>
#include <QCommonStyle>

myMainWindow::myMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myMainWindow)
{
    ui->setupUi(this);

    lstColor.insert(0, QColor("#FFFFFF"));

    setWindowIcon(QIcon(":/img/iconPNG.png"));
    setWindowTitle("XML редактор");

    pScene = new myScene(QRect(0, -50, ui->viewAlgth->geometry().width()+100, ui->viewAlgth->geometry().height()+150), ui->viewAlgth);

    ui->viewAlgth->setScene(pScene);
    ui->viewAlgth->setRenderHint(QPainter::Antialiasing, true);

    CustomTreeWidgetItem *item = new CustomTreeWidgetItem(ui->treeWidget, SCEN, "Новый сценарий");
    this->parseXMLForAlgth();
    item->setSelected(true);

    //Настройка элементов Toolbar
    QCommonStyle style;
    ui->actionFile->setIcon(style.standardIcon(QStyle::SP_DialogOpenButton));
    ui->actionSave->setIcon(style.standardIcon(QStyle::SP_DriveFDIcon));
    ui->actionDel->setIcon(style.standardIcon(QStyle::SP_TrashIcon));

    m_myXmlHighlighter = new myXMLHighlighter(ui->plainTextEdit->document());

    QObject::connect(ui->plainTextEdit, &myPlainTextEdit::onClickString,
                this, &myMainWindow::onFind);

}

myMainWindow::~myMainWindow()
{
    delete ui;

    if(pScene != nullptr)
       delete pScene;

    if(m_myXmlHighlighter != nullptr)
       delete m_myXmlHighlighter;
}

void myMainWindow::onFind(QString txt, int numberBlock)
{
    if( m_myXmlHighlighter )
        m_myXmlHighlighter->setHighlightedString( txt, numberBlock );
}

//Добавление тега TASK
void myMainWindow::TaskItem(QString name)
{
    CustomTreeWidgetItem *item = new CustomTreeWidgetItem(ui->treeWidget->currentItem(), TASK, name);

    //Выбор случайного цвета блока блок-схемы TASK
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    int r = qrand() % 150+79;
    int g = qrand() % 200;
    int b = qrand() % 200;

    QColor newColor;
    newColor.setRgb(r, g, b);

    lstColor.insert(0, newColor);

    this->parseXMLForAlgth();

    Q_UNUSED(item);
}

//Событие создания тега START
void myMainWindow::StartItem(QString name, QString target)
{
    CustomTreeWidgetItem *item = new CustomTreeWidgetItem(ui->treeWidget->currentItem(), START, name, target);
    this->parseXMLForAlgth();
    Q_UNUSED(item);
}

//Событие создания тега COPY
void myMainWindow::CopyItem(QString name, QString source, QString target)
{
    CustomTreeWidgetItem *item = new CustomTreeWidgetItem(ui->treeWidget->currentItem(), COPY, name, source, target);
    this->parseXMLForAlgth();
    Q_UNUSED(item);
}

//Событие создания тега DELETE
void myMainWindow::DeleteItem(QString name, QString target)
{
    CustomTreeWidgetItem *item = new CustomTreeWidgetItem(ui->treeWidget->currentItem(), DELETE, name, target);
    this->parseXMLForAlgth();
    Q_UNUSED(item);
}

//Событие создания тега FILE
void myMainWindow::FileItem(QString name, QString source, QString target)
{
    CustomTreeWidgetItem *item = new CustomTreeWidgetItem(ui->treeWidget->currentItem(), FILE, name, source, target);
    this->parseXMLForAlgth();
    Q_UNUSED(item);
}

//Событие создания тега OPENSCEN
void myMainWindow::OpenScenItem(QString value, QString source)
{
    CustomTreeWidgetItem *item = new CustomTreeWidgetItem(ui->treeWidget->currentItem(), OPENSCEN, value, source);
    this->parseXMLForAlgth();
    Q_UNUSED(item);
}

void myMainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    CustomTreeWidgetItem *citem = dynamic_cast<CustomTreeWidgetItem*>(item);

    // Активация/деактивация кнопок в зависимости от типа тега
    switch (citem->type())
    {
        case 0:
            ui->actionTask->setEnabled(true);
            ui->actionCopy->setEnabled(false);
            ui->actionDelete->setEnabled(false);
            ui->actionStart->setEnabled(false);
            break;

        case 1:
            ui->actionTask->setEnabled(true);
            ui->actionCopy->setEnabled(true);
            ui->actionDelete->setEnabled(true);
            ui->actionStart->setEnabled(true);
            break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            ui->actionTask->setEnabled(false);
            ui->actionCopy->setEnabled(false);
            ui->actionDelete->setEnabled(false);
            ui->actionStart->setEnabled(false);
            break;
    }
}

void myMainWindow::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(item);
    Q_UNUSED(column);

    ui->plainTextEdit->clear();

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
    {
        CustomTreeWidgetItem *citem = dynamic_cast<CustomTreeWidgetItem*>(ui->treeWidget->topLevelItem(i));
        ui->plainTextEdit->insertPlainText("<Scen name=\"" + citem->Name() + "\">\n");
        if (ui->treeWidget->topLevelItem(i)->childCount() > 0)
        {
            for (int j = 0 ; j < ui->treeWidget->topLevelItem(i)->childCount(); ++j)
            {
                CustomTreeWidgetItem *citem = dynamic_cast<CustomTreeWidgetItem*>(ui->treeWidget->topLevelItem(i)->child(j));
                makeXMLText(citem);
            }
        }
    }

    ui->plainTextEdit->insertPlainText("</Scen>\n");
}

//Метод дабавления в текст сценария код тега
void myMainWindow::makeXMLText (CustomTreeWidgetItem *item)
{
    /*  Тег    Номер
        SCEN     0
        TASK     1
        COPY     2
        DELETE   3
        START    4
        FILE     5
        OPENSCEN 6
    */
    switch (item->type())
    {
        case 1:
           // this->setWindowTitle("Создать группу задач");
            ui->plainTextEdit->insertPlainText("<Task name=\"" + item->Name() + "\">\n");
                if (item->childCount() > 0)
                {
                    for (int i = 0; i < item->childCount(); ++i)
                    {
                        CustomTreeWidgetItem *citem = dynamic_cast<CustomTreeWidgetItem*>(item->child(i));
                        makeXMLText(citem);
                    }
                }
            ui->plainTextEdit->insertPlainText("</Task> <!-- " + item->Name() + "-->\n");
            break;
        case 2:
            ui->plainTextEdit->insertPlainText("\t<Copy name=\"" + item->Name() + "\">\n");
            ui->plainTextEdit->insertPlainText("\t\t<Var source=\"" + item->Source() + "\"></Var>\n");
            ui->plainTextEdit->insertPlainText("\t\t<Var target=\"" + item->Target() + "\"></Var>\n");
            ui->plainTextEdit->insertPlainText("\t</Copy> <!-- " + item->Name() + "-->\n");
            break;
        case 3:
            ui->plainTextEdit->insertPlainText("\t<Delete name=\"" + item->Name() + "\">\n");
            ui->plainTextEdit->insertPlainText("\t\t<Var target=\"" + item->Target() + "\"></Var>\n");
            ui->plainTextEdit->insertPlainText("\t</Delete> <!-- " + item->Name() + "-->\n");
            break;
        case 4:
            ui->plainTextEdit->insertPlainText("\t<Start name=\"" + item->Name() + "\">\n");
            ui->plainTextEdit->insertPlainText("\t\t<Var target=\"" + item->Target() + "\"></Var>\n");
            ui->plainTextEdit->insertPlainText("\t</Start> <!-- " + item->Name() + "-->\n");
            break;
        case 5:
            ui->plainTextEdit->insertPlainText("\t<File name=\"" + item->Name() + "\">\n");
            ui->plainTextEdit->insertPlainText("\t\t<Var files=\"" + item->Target() + "\" source=\"" + item->Source() + "\"></Var>\n");
            ui->plainTextEdit->insertPlainText("\t</File> <!-- " + item->Name() + "-->\n");
            break;
        case 6:
            ui->plainTextEdit->insertPlainText("\t<OpenScen>\n");
            ui->plainTextEdit->insertPlainText("\t\t<Var value=\"" + item->Name() + "\" path=\"" + item->Target() + "\"></Var>\n");
            ui->plainTextEdit->insertPlainText("\t\t<!-- N переменных вставить сюда -->\n");
            ui->plainTextEdit->insertPlainText("\t</OpenScen>\n");
            break;
    }
}

void myMainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    citem2 = dynamic_cast<CustomTreeWidgetItem*>(item);

    if(md != nullptr)
        delete md;

    switch (citem2->type())
    {
        case 1:
            md = new myDialog(citem2->type(), citem2->Name(), this);
            connect(md, &myDialog::TaskSet, this, &myMainWindow::setTask);
            md->show();
            break;

        case 2:
            md = new myDialog(citem2->type(), citem2->Name(), citem2->Target(), citem2->Source(), this);
            md->show();
            connect(md, &myDialog::CopySet, this, &myMainWindow::setCopy);
            break;

        case 3:
            md = new myDialog(citem2->type(), citem2->Name(), citem2->Target(), this);
            md->show();
            connect(md, &myDialog::DeleteSet, this, &myMainWindow::setDelete);
            break;

        case 4:
            md = new myDialog(citem2->type(), citem2->Name(), citem2->Target(), this);
            md->show();
            connect(md, &myDialog::StartSet, this, &myMainWindow::setStart);
            break;

        case 5:
            md = new myDialog(citem2->type(), citem2->Name(), citem2->Target(), citem2->Source(), this);
            md->show();
            connect(md, &myDialog::FileSet, this, &myMainWindow::setCopy); //setCopy - Похож с тегом Copy
            break;

        case 6:
            md = new myDialog(citem2->type(), citem2->Name(), citem2->Target(), this);
            md->show();
            connect(md, &myDialog::OpenScenSet, this, &myMainWindow::setOpenScen);
            break;
    }
}

void myMainWindow::setTask (QString name)
{
    citem2->setTask(name);
    emit ui->treeWidget->itemChanged(citem2, 0);
}

void myMainWindow::setCopy (QString name, QString source, QString target)
{
    citem2->setCopy(name, source, target);
    emit ui->treeWidget->itemChanged(citem2, 0);
}

void myMainWindow::setOpenScen(QString value, QString source)
{
    citem2->setOpenScen(value, source);
    emit ui->treeWidget->itemChanged(citem2, 0);
}

void myMainWindow::setDelete (QString name, QString target)
{
    citem2->setDelete(name, target);
    emit ui->treeWidget->itemChanged(citem2, 0);
}

void myMainWindow::setStart (QString name, QString target)
{
    citem2->setStart(name, target);
    emit ui->treeWidget->itemChanged(citem2, 0);
}

void myMainWindow::on_actionTask_triggered()
{
    myDialog *md = new myDialog(TASK, this);
    md->show();

    connect(md,     SIGNAL  (TaskSet   (QString)),
            this,   SLOT    (TaskItem  (QString)) );
}

void myMainWindow::on_actionDelete_triggered()
{
    myDialog *md = new myDialog(DELETE, this);
    md->show();
    connect(md,     SIGNAL  (DeleteSet   (QString, QString)),
            this,   SLOT    (DeleteItem  (QString, QString)) );
}

void myMainWindow::on_actionCopy_triggered()
{
    myDialog *md = new myDialog(COPY, this);
    md->show();
    connect(md,     SIGNAL  (CopySet    (QString, QString, QString)),
            this,   SLOT    (CopyItem   (QString, QString, QString)) );
}

void myMainWindow::on_actionStart_triggered()
{
    myDialog *md = new myDialog(START, this);
    md->show();
    connect(md,     SIGNAL  (StartSet   (QString, QString)),
            this,   SLOT    (StartItem  (QString, QString)) );
}

void myMainWindow::on_actionFile_2_triggered()
{
    myDialog *md = new myDialog(FILE, this);
    md->show();
    connect(md,     SIGNAL  (FileSet   (QString, QString, QString)),
            this,   SLOT    (FileItem  (QString, QString, QString)) );
}

void myMainWindow::on_actionOpenScen_triggered()
{
    myDialog *md = new myDialog(OPENSCEN, this);
    md->show();
    connect(md,     SIGNAL  (OpenScenSet   (QString, QString)),
            this,   SLOT    (OpenScenItem  (QString, QString)) );
}

void myMainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("XML Файл (*.xml)"));

    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this,tr("Ошибка"),tr("Невозможно открыть файл"));
            return;
        }
        else
        {
            QTextStream stream(&file);
            stream << ui->plainTextEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void myMainWindow::on_actionFile_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Открыть файл"),"",tr("XML Файл (*.xml)"));

    if (fileName !="")
    {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::critical(this,tr("Ошибка"),tr("Невозможно открыть файл"));
            return;
        }

        ui->treeWidget->clear();

        QXmlStreamReader *xmlReader = new QXmlStreamReader();
        xmlReader->setDevice(&file);

        while (!xmlReader->atEnd() && !xmlReader->hasError())
        {
            if (!xmlReader->name().toString().isEmpty())
            {
                QString name = xmlReader->attributes().at(0).value().toString();
                CustomTreeWidgetItem *item = new CustomTreeWidgetItem(ui->treeWidget, SCEN, name);
                xmlReader->readNext();
                xmlReader = parseXML(xmlReader, item, SCEN, "");
            }
            xmlReader->readNext();
        }

        file.close();
    }
}

QXmlStreamReader* myMainWindow::parseXML(QXmlStreamReader *xmlReader, CustomTreeWidgetItem* parent, int type, QString str)
{
    CustomTreeWidgetItem *item = parent;
    QString name = str;
    QString source = "";
    QString target = "";

    foreach(const QXmlStreamAttribute &attr, xmlReader->attributes())
    {
        if (attr.name().toString().toUpper() == "NAME")
        {
            name = attr.value().toString();
        }
        else
        if (attr.name().toString().toUpper() == "SOURCE")
        {
            source = attr.value().toString();
        }
        else
        if (attr.name().toString().toUpper() == "TARGET")
        {
            target = attr.value().toString();
        }
    }

    if (xmlReader->name().toString().toUpper() == "TASK")
    {
        item = new CustomTreeWidgetItem(parent, TASK, name);
    }
    else
    if (xmlReader->name().toString().toUpper() == "COPY")
    {
        type = COPY;
    }
    else
    if (xmlReader->name().toString().toUpper() == "DELETE")
    {
        type = DELETE;
    }
    else
    if (xmlReader->name().toString().toUpper() == "START")
    {
        type = START;
    }
    else
    if (xmlReader->name().toString().toUpper() == "FILE")
    {
        type = FILE;
    }
    else
    if (xmlReader->name().toString().toUpper() == "OPENSCEN")
    {
        type = OPENSCEN;
    }
    else
    if (xmlReader->name().toString().toUpper() == "VAR")
    {
        item = new CustomTreeWidgetItem(parent, type, name, source, target);
    }

    xmlReader->readNext();

    while (!xmlReader->isEndElement() && !xmlReader->hasError())
    {
        if (xmlReader->isStartElement())
        {
            xmlReader = parseXML(xmlReader, item, type, name);
        }
        xmlReader->readNext();
    }

    return xmlReader;
}

void myMainWindow::on_actionDel_triggered()
{
    if(ui->treeWidget->currentItem()->type() == 1)
    {
        lstColor.removeAt(0);
    }

    delete ui->treeWidget->currentItem();

    on_treeWidget_itemChanged(ui->treeWidget->currentItem(),0);

    this->parseXMLForAlgth();
}

void myMainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
   Q_UNUSED(previous)

   CustomTreeWidgetItem * p =  dynamic_cast<CustomTreeWidgetItem*> (current);

   if(p != nullptr)
   {
        if (p->Name().compare("Новый сценарий") >= 0)
        {
             ui->actionDel->setEnabled(false);
        }
        else
        {
             ui->actionDel->setEnabled(true);
        }
   }
}


void myMainWindow::on_checkBox_released()
{
    ui->textEdit->setEnabled(!ui->textEdit->isEnabled());
}

//Метод отрисовки сценария взависимости от типа тега блока в блок-схеме
void myMainWindow::parseXMLForAlgth()
{
    int iter = lstColor.size()-1;

    QString script = ui->plainTextEdit->toPlainText();

    pScene->clearAllBlocks();

    if(script.left(script.indexOf(">")).contains("<Scen"))
    {
        pScene->drawBlockScen(0, lstColor.at(iter));

        script = script.right(script.length() - script.indexOf(">")-1);

        while(script.length() > 5)
        {
            QString tmp_str = script.left(script.indexOf(">"));

            if(tmp_str.contains("<Task"))
            {
                iter--;
                pScene->drawBlockTask(lstColor.at(iter));
            }
            else if(tmp_str.contains("</Task"))
            {
            }
            else if(tmp_str.contains("<Delete"))
            {
                pScene->drawBlockDeleteCopyStart("Delete", lstColor.at(iter));
            }
            else if(tmp_str.contains("<Copy"))
            {
                pScene->drawBlockDeleteCopyStart("Copy", lstColor.at(iter));
            }
            else if(tmp_str.contains("<Start"))
            {
                pScene->drawBlockDeleteCopyStart("Start", lstColor.at(iter));
            }
            else if(tmp_str.contains("<OpenScen"))
            {
                pScene->drawBlockCondition(3, lstColor.at(iter));
            }
            else if(tmp_str.contains("<File"))
            {
                pScene->drawBlockFile(lstColor.at(iter));
            }
            else if(tmp_str.contains("</Task"))
            {
                pScene->drawBlockDeleteCopyStart("Start", lstColor.at(iter));
            }

            script = script.right(script.length() - script.indexOf(">")-1);
        }

        iter = lstColor.size()-1;
        pScene->drawBlockScen(1, lstColor.at(iter));
    }
}
