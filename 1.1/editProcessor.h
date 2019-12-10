#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include<QImage>
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
#include"showwidget.h"
#include"search.h"
class EditProcessor : public QMainWindow
{
    Q_OBJECT

public:
    EditProcessor(QWidget *parent = 0);
    ~EditProcessor();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat);
private:
    QMenu *fileMenu;
    QMenu *zoomMenu;
    QMenu *aboutMenu;
    QAction *coffeeAction;
    QLabel *coffeeImg;
    QFrame *frame;
    QPalette *palette;
//    QMenu *rotateMenu;
//    QMenu *mirrorMenu;
    QImage img;
    QImage *coffee;
    QWidget *coffeeshow;
    QString fileName;
    ShowWidget *showWidget;

    QAction *openFileAction;
    QAction *NewFileAction;

    QAction *findAction;
    Search *search;
    QAction *saveFileAction;
    QAction *saveFileAsAction;

    QAction *PrintTextAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *undoAction;
    QAction *redoAction;
    QToolBar *fileTool;
    QToolBar *zoomTool;
    QToolBar *rotateTool;
    QToolBar *mirrorTool;
    QToolBar *doToolBar;
    QLabel *fontLabel1;
    QLabel *fontLabel2;
    QFontComboBox *fontComboBox;
    QComboBox *sizeComboBox;
    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underlineBtn;
    QToolButton *colorBtn;
    QToolBar *fontToolBar;
    QLabel *listLabel;
    QComboBox *listComboBox;
    QActionGroup *actGrp;
    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;
    QToolBar *listToolBar;

protected slots:
    void ShowNewFile();
    void ShowOpenFile();
    void ShowFind();

    void ShowSaveFile();
    void ShowSaveFileAs();

    void ShowPrintText();
    void ShowFontComboBox(QString comboStr);
    void ShowSizeSpinBox(QString spinValue);
    void ShowBoldBtn();
    void ShowItalicBtn();
    void ShowUnderlineBtn();
    void ShowColorBtn();
    void ShowCurrentFormatChanged(const QTextCharFormat &fmt);

    void ShowAlignment(QAction *act);
    void ShowCursorPositionChanged();
    void searchHide();

    void showCoffee();
};

#endif // IMAGEPROCESSOR_H
