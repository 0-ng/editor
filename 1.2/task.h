#ifndef SEARCH_H
#define SEARCH_H

#endif // SEARCH_H
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
#include <QtEvents>
#include <qtextcodec.h>
#include"showwidget.h"
class Task : public QDialog
{
    Q_OBJECT
public:
    Task(QWidget *parent=0);
    void setEdit(QTextEdit *ed);
    ~Task();
    void printNums();
private:
    QTextEdit *edit;
    QLabel *label_sentences;
    QLabel *label_words;
    QLabel *label_digits;
    QLabel *label_spaces;
    QLabel *label_sentences_nums;
    QLabel *label_words_nums;
    QLabel *label_digits_nums;
    QLabel *label_spaces_nums;
};
