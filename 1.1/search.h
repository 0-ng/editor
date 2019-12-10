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
class Search : public QDialog
{
    Q_OBJECT
public:
    Search(QWidget *parent=0);
    void setEdit(QTextEdit *ed);
    QLineEdit *lineEdit;
    ~Search();
private:
    QTextEdit *edit;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QPushButton *up;
    QPushButton *down;
protected slots:
    void showNum();
};
