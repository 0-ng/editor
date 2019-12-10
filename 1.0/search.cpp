#include "search.h"

#include<QImage>
#include<QTextList>
#include<QLabel>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QComboBox>
#include<QSpinBox>
#include<QToolBar>
#include<QFontComboBox>
#include<QToolButton>
#include<QTextCharFormat>
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QColorDialog>
#include<QColor>
#include<QPrinter>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QPrintDialog>
#include <QFileDevice>
#include <QTextStream>
#include<QtEvents>
#include <qtextcodec.h>
#include<QGridLayout>
#include<QPushButton>
#include<QDebug>
#include<QStringList>
Search::Search(QWidget *parent)
    :QDialog(parent)
{
    label1=new QLabel(this);
    label2=new QLabel(this);
    label3=new QLabel(this);
    label1->setText(tr("输入匹配字符串: "));
    label2->setText(tr("本文中出现次数: "));
    lineEdit = new QLineEdit(this);
    lineEdit->resize(600,30);
    up = new QPushButton(this);
    down = new QPushButton(this);
    up->setText(tr("up"));
    down->setText(tr("down"));
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(label1,0,0);
    mainLayout->addWidget(lineEdit,0,1);
    mainLayout->addWidget(label2,1,0);
    mainLayout->addWidget(label3,1,1);
    mainLayout->addWidget(up,0,2);
    mainLayout->addWidget(down,1,2);
    connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(showNum()));
}
Search::~Search()
{

}
void Search::setEdit(QTextEdit *ed){
    edit=ed;
}

void Search::showNum()
{
    if(lineEdit->text()=="")
        return ;
    QString str = edit->toPlainText();
    QStringList ls=str.split('\n');
    str=ls.join("");
    int num = str.split(lineEdit->text()).size()-1;
    label3->setText(QString::number(num));
    qDebug()<<num;
}
