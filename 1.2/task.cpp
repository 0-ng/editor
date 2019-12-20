#include "task.h"

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
Task::Task(QWidget *parent)
    :QDialog(parent)
{
    label_sentences=new QLabel(this);
    label_words=new QLabel(this);
    label_digits=new QLabel(this);
    label_spaces=new QLabel(this);
    label_sentences_nums=new QLabel(this);
    label_words_nums=new QLabel(this);
    label_digits_nums=new QLabel(this);
    label_spaces_nums=new QLabel(this);
    label_sentences->setText(tr("sentences"));
    label_words->setText(tr("words"));
    label_digits->setText(tr("digits"));
    label_spaces->setText(tr("spaces"));
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(label_sentences,0,0);
    mainLayout->addWidget(label_words,0,1);
    mainLayout->addWidget(label_digits,0,2);
    mainLayout->addWidget(label_spaces,0,3);
    mainLayout->addWidget(label_sentences_nums,1,0);
    mainLayout->addWidget(label_words_nums,1,1);
    mainLayout->addWidget(label_digits_nums,1,2);
    mainLayout->addWidget(label_spaces_nums,1,3);

}
Task::~Task()
{

}
void Task::setEdit(QTextEdit *ed){
    edit=ed;
}

void Task::printNums(){
    QString text=edit->toPlainText();
    QStringList ls=text.split('\n');
    text=ls.join("");
    int sentences=0;
    int words=0;
    int digits=0;
    int spaces=0;
    int len=text.size();
    int idx=0;
//    QString mark=".?!,;:";
    QString mark=".?!";
    while(idx<len){
        if(text[idx]==' '){
            spaces++;
            idx++;
        }else if(text[idx].isDigit()){
            while(idx<len&&(text[idx].isDigit()||text[idx]=='.')){
                idx++;
            }
            if(text[idx-1]=='.'){
                idx--;
            }
            digits++;

        }else if(text[idx].isLetter()){
            while(idx<len&&(text[idx].isLetter()||text[idx]=='-')){
                idx++;
            }
            words++;
        }else if(mark.contains(text[idx])){
            sentences++;
            idx++;
        }else{
            idx++;
        }
    }

    label_sentences_nums->setText((QString::number(sentences)));
    label_words_nums->setText((QString::number(words)));
    label_digits_nums->setText((QString::number(digits)));
    label_spaces_nums->setText((QString::number(spaces)));
    QString ans;
    ans.sprintf("sentences:%d ; words:%d ; digits:%d ; spaces:%d\n",sentences,words,digits,spaces);
    this->show();
}
