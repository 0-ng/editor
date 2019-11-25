#include "EditProcessor.h"
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
int Flag_isOpen = 0;       //标记：判断是否打开或创建了一个文件
int Flag_IsNew = 0;        //标记：如果新建了文件就为1，初始值为0
QString Last_FileName;     //最后一次保存的文件的名字
QString Last_FileContent;  //最后一次保存文件的内容

EditProcessor::EditProcessor(QWidget *parent)
    : QMainWindow(parent)
{

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    setWindowTitle(tr("My Word"));

    /* 创建放置图像QLabel和文本编辑框QTextEdit的QWidget对象showWidget, 并将该QWidget对象设置为中心部件 */
    showWidget = new ShowWidget(this);
    setCentralWidget(showWidget);

    /*************************************************************/
//    setCentralWidget(showWidget);
    //在工具栏上嵌入控件
    //设置字体
    fontLabel1 = new QLabel(tr("字体:"));
    fontComboBox = new QFontComboBox;
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);
    fontLabel2 = new QLabel(tr("字号:"));
    sizeComboBox = new QComboBox;
    QFontDatabase db;
    foreach (int size, db.standardSizes()) {
        sizeComboBox->addItem(QString::number(size));
    }
    boldBtn = new QToolButton;
    boldBtn->setIcon(QIcon(":/new/prefix1/img/bold.png"));
    boldBtn->setToolTip(tr("加粗"));
//    openFileAction = new QAction(QIcon(":/new/prefix1/img/open.png"),tr("打开"),this);//在创建"打开文件"动作的同时,指定了此动作使用的图标\名称及父窗口
    boldBtn->setCheckable(true);
    italicBtn = new QToolButton;
    italicBtn->setIcon(QIcon(":/new/prefix1/img/italic.png"));
    italicBtn->setToolTip(tr("斜体"));
    italicBtn->setCheckable(true);
    underlineBtn = new QToolButton;
    underlineBtn->setIcon(QIcon(":/new/prefix1/img/underline.png"));
    underlineBtn->setToolTip(tr("下划线"));
    underlineBtn->setCheckable(true);
    colorBtn = new QToolButton;
    colorBtn->setIcon(QIcon(":/new/prefix1/img/color.png"));
    colorBtn->setToolTip(tr("字体颜色"));
    colorBtn->setCheckable(true);

    /*************************************************************/



    /* 创建动作\菜单\工具栏的函数 */
    createActions();
    createMenus();
    createToolBars();



    /*************************************************************/
    connect(fontComboBox,SIGNAL(activated(QString)),this,SLOT(ShowFontComboBox(QString)));
    connect(sizeComboBox,SIGNAL(activated(QString)),this,SLOT(ShowSizeSpinBox(QString)));
    connect(boldBtn,SIGNAL(clicked(bool)),this,SLOT(ShowBoldBtn()));
    connect(italicBtn,SIGNAL(clicked(bool)),this,SLOT(ShowItalicBtn()));
    connect(underlineBtn,SIGNAL(clicked(bool)),this,SLOT(ShowUnderlineBtn()));
    connect(colorBtn,SIGNAL(clicked(bool)),this,SLOT(ShowColorBtn()));
    connect(showWidget->text,SIGNAL(currentCharFormatChanged(QTextCharFormat&)),this,SLOT(ShowCurrentFormatChanged(QTextCharFormat&)));
    /*************************************************************/
    /*************************************************************/
//    connect(listComboBox,SIGNAL(activated(int)),this,SLOT(ShowList(int)));
    connect(showWidget->text->document(),SIGNAL(undoAvailable(bool)),undoAction,SLOT(setEnabled(bool)));
    connect(showWidget->text->document(),SIGNAL(redoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(showWidget->text,SIGNAL(cursorPositionChanged()),this,SLOT(ShowCursorPositionChanged()));
    connect(showWidget->text,SIGNAL(cursorPositionChanged()),this,SLOT(searchHide()));

    /*************************************************************/

}

EditProcessor::~EditProcessor()
{

}

void EditProcessor::createActions()
{
    // "打开" 动作
    openFileAction = new QAction(QIcon(":/new/prefix1/img/open.png"),tr("打开"),this);//在创建"打开文件"动作的同时,指定了此动作使用的图标\名称及父窗口
    openFileAction->setShortcut(tr("Ctrl+O"));//设置此动作的组合键
    openFileAction->setToolTip(tr("打开一个文件"));//设置了状态栏显示,当鼠标光标移至次动作对应的菜单条目或工具栏按钮上时,在状态栏上显示"打开一个文件"的提示
    // "新建" 动作
    NewFileAction = new QAction(QIcon(":/new/prefix1/img/new.png"),tr("新建"),this);
    NewFileAction->setShortcut(tr("Ctrl+N"));
    NewFileAction->setToolTip(tr("新建一个文件"));
    // "查找" 动作
    search = new Search;
    search->setEdit(showWidget->text);
//    connect(search,SLOT(textChanged(QString)),)
    findAction = new QAction(QIcon(":/new/prefix1/img/find.png"),tr("查找"),this);
    findAction->setShortcut(tr("Ctrl+F"));
    findAction->setToolTip(tr("查找目标出现次数"));

    // "保存" 动作
    saveFileAction = new QAction(QIcon(":/new/prefix1/img/save.png"),tr("保存"),this);
    saveFileAction->setShortcut(tr("Ctrl+S"));
    saveFileAction->setToolTip(tr("保存一个文件"));
    // "另存为" 动作
    saveFileAsAction = new QAction(QIcon(":/new/prefix1/img/saveAs.png"),tr("另存为"),this);
    saveFileAsAction->setShortcut(tr("Shift+Ctrl+S"));
    saveFileAsAction->setToolTip(tr("另存为一个文件"));

    // "退出" 动作
    exitAction = new QAction(QIcon("qrc:/new/prefix1/luffy.png"),tr("退出"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setToolTip(tr("退出程序"));
    connect(exitAction,SIGNAL(triggered(bool)),this,SLOT(close()));
    // "复制" 动作
    copyAction = new QAction(QIcon(":/new/prefix1/img/copy.png"),tr("复制"),this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setToolTip(tr("复制文件"));
    connect(copyAction,SIGNAL(triggered(bool)),showWidget->text,SLOT(copy()));
    // "剪切" 动作
    cutAction = new QAction(QIcon(":/new/prefix1/img/cut.png"),tr("剪切"),this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("剪切文件"));
    connect(cutAction,SIGNAL(triggered(bool)),showWidget->text,SLOT(cut()));
    // "粘贴" 动作
    pasteAction = new QAction(QIcon(":/new/prefix1/img/paste.png"),tr("粘贴"),this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setToolTip(tr("粘贴文件"));
    connect(pasteAction,SIGNAL(triggered(bool)),showWidget->text,SLOT(paste()));
    // "关于" 动作
//    aboutAction = new QAction(QIcon("about.png"),tr("关于"),this);
//    connect(aboutAction,SIGNAL(triggered(bool)),this,SLOT(QApplication::aboutQt()));

    //实现打印文本和图像\图像缩放\旋转和镜像的动作的代码
    PrintTextAction = new QAction(QIcon(":/new/prefix1/img/print.png"),tr("打印文本"),this);
    PrintTextAction->setStatusTip(tr("打印一个文本"));

    //实现撤销和恢复动作(Action)
    //撤销和恢复
    undoAction = new QAction(QIcon(":/new/prefix1/img/undo.png"),"撤销",this);
    connect(undoAction,SIGNAL(triggered(bool)),showWidget->text,SLOT(undo()));
    redoAction = new QAction(QIcon(":/new/prefix1/img/redo.png"),"重做",this);
    connect(redoAction,SIGNAL(triggered(bool)),showWidget->text,SLOT(redo()));

    connect(NewFileAction,SIGNAL(triggered(bool)),this,SLOT(ShowNewFile()));
    connect(openFileAction,SIGNAL(triggered(bool)),this,SLOT(ShowOpenFile()));

    /*************************************************************************/
    connect(findAction,SIGNAL(triggered(bool)),this,SLOT(ShowFind()));
    connect(saveFileAction,SIGNAL(triggered(bool)),this,SLOT(ShowSaveFile()));
    connect(saveFileAsAction,SIGNAL(triggered(bool)),this,SLOT(ShowSaveFileAs()));
    /*************************************************************************/

    connect(PrintTextAction,SIGNAL(triggered(bool)),this,SLOT(ShowPrintText()));
    /*************************************************************************/
    //排序: 左对齐\右对齐\居中和两端对齐
    actGrp = new QActionGroup(this);
    leftAction = new QAction(QIcon(":/new/prefix1/img/left.png"),"左对齐",actGrp);
    leftAction->setCheckable(true);
    rightAction = new QAction(QIcon(":/new/prefix1/img/right.png"),"右对齐",actGrp);
    rightAction->setCheckable(true);
    centerAction = new QAction(QIcon(":/new/prefix1/img/center.png"),"居中",actGrp);
    centerAction->setCheckable(true);
    justifyAction = new QAction(QIcon(":/new/prefix1/img/justify.png"),"两端对齐",actGrp);
    justifyAction->setCheckable(true);
    connect(actGrp,SIGNAL(triggered(QAction*)),this,SLOT(ShowAlignment(QAction*)));
    /*************************************************************************/
}

void EditProcessor::createMenus()
{
    //文件菜单
    fileMenu = menuBar()->addMenu(tr("文件"));//直接调用QMainWindow的menuBar()函数即可得到主窗口的菜单栏指针, 再调用菜单栏QMenuBar的addMenu()函数, 即可完成在菜单栏中插入一个新菜单file Menu, fileMenu为一个QMenu类对象
    fileMenu->addAction(openFileAction);//调用QMenu的addMenu()函数在菜单中加入菜单条目"打开""新建""打印文本""打印图像".
    fileMenu->addAction(NewFileAction);
     /*************************************************************************/
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveFileAsAction);
    fileMenu->addAction(findAction);
     /*************************************************************************/
    fileMenu->addAction(PrintTextAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    //缩放菜单
    zoomMenu = menuBar()->addMenu(tr("编辑"));
    zoomMenu->addAction(copyAction);
    zoomMenu->addAction(cutAction);
    zoomMenu->addAction(pasteAction);
//    zoomMenu->addAction(aboutAction);
    zoomMenu->addSeparator();
}

void EditProcessor::createToolBars()
{
    //文件工具条
    fileTool = addToolBar("File");//直接调用QMainWindow的addToolBar()函数即可获得主窗口的工具条对象,每新增一个工具条就调用一次addToolBar()函数,赋予不同的名称,即可在主窗口中新增一个工具条
    fileTool->addAction(openFileAction);//调用QToolBar的addAction()函数在工具条中插入属于本工具条的动作.类似地,实现"编辑工具条"、"旋转工具条"、"撤销和重做工具条".工具条的显示可以由用户进行选择,在工具栏上单击鼠标右键将弹出工具条显示的选择菜单,用户对需要显示的工具条进行选择即可
    fileTool->addAction(NewFileAction);
    /*************************************************************************/
    fileTool->addAction(saveFileAction);
    fileTool->addAction(saveFileAsAction);
    fileTool->addAction(findAction);
    /*************************************************************************/
    fileTool->addAction(PrintTextAction);
    //编辑工具条
    zoomTool = addToolBar("Edit");
    zoomTool->addAction(copyAction);
    zoomTool->addAction(cutAction);
    zoomTool->addAction(pasteAction);
    zoomTool->addSeparator();
    //撤销和重做工具栏
    doToolBar = addToolBar("doEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addAction(redoAction);

    /**************************************/
    //字体工具条
    fontToolBar = addToolBar("Font");
    fontToolBar->addWidget(fontLabel1);
    fontToolBar->addWidget(fontComboBox);
    fontToolBar->addWidget(fontLabel2);
    fontToolBar->addWidget(sizeComboBox);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(boldBtn);
    fontToolBar->addWidget(italicBtn);
    fontToolBar->addWidget(underlineBtn);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(colorBtn);
    /**************************************/
    /**************************************/
    //排序工具条
    listToolBar = addToolBar("list");
    listToolBar->addWidget(listLabel);
    listToolBar->addSeparator();
    listToolBar->addActions(actGrp->actions());
    /**************************************/
}

void EditProcessor::ShowNewFile()
{

    showWidget->text->clear();              //清除原先文件内容
    showWidget->text->setHidden(false);     //显示文本框
    Flag_IsNew = 1;                 //新文件标记位设为1
    Flag_isOpen = 1;


    /*
    ImgProcessor *newImgProcessor = new ImgProcessor;
    newImgProcessor->show();
    */
}

void EditProcessor::ShowOpenFile()
{
    QString fileName;
       fileName = QFileDialog::getOpenFileName(this,tr("Open File"),tr(""),tr("Text File (*.txt)"));
       if(fileName == "")                  //如果用户直接关闭了文件浏览对话框，那么文件名就为空值，直接返回
       {
           return;
       }
       else
       {
          QFile file(fileName);
          if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
          {
              QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
              return;
          }
          else
          {
              if(!file.isReadable())
              {
                  QMessageBox::warning(this,tr("错误"),tr("该文件不可读"));
              }
              else
              {
                  QTextStream textStream(&file);       //读取文件，使用QTextStream
                  while(!textStream.atEnd())
                  {
                      showWidget->text->setPlainText(textStream.readAll());
//                      showWidget->text->append(textStream.readLine());
                  }
                  showWidget->text->show();
                  file.close();
                  Flag_isOpen = 1;
                  Last_FileName = fileName;

              }
          }
       }


    /*
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        if(showWidget->text->document()->isEmpty())
        {
            loadFile(fileName);
        }
        else
        {
            ImgProcessor *newImgProcessor = new ImgProcessor;
            newImgProcessor->show();
            newImgProcessor->loadFile(fileName);
        }
    }*/
}

/*************************************************************************/

void EditProcessor::ShowSaveFile()
{
    if(Flag_IsNew)                  //如果新文件标记位为1，则弹出保存文件对话框
    {
        if(showWidget->text->toPlainText() == "")
        {
            QMessageBox::warning(this,tr("警告"),tr("内容不能为空!"),QMessageBox::Ok);
        }
        else
        {
            QFileDialog fileDialog;
            QString str = fileDialog.getSaveFileName(this,tr("save"),"/home",tr("Text File(*.txt)"));
            if(str == "")
            {
                return;
            }
            QFile filename(str);
            if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,tr("错误"),tr("保存文件失败"),QMessageBox::Ok);
                return;
            }
            else
            {
                QTextStream textStream(&filename);
                QString str = showWidget->text->toPlainText();
                textStream<<str;
                Last_FileContent = str;
            }
            QMessageBox::information(this,"保存文件","保存文件成功",QMessageBox::Ok);
            filename.close();
            Flag_IsNew = 0;     //新文件标记位记为0
            Last_FileName = str;//保存文件内容
        }
    }
    else                        //否则，新文件标记位是0，代表是旧文件，默认直接保存覆盖源文件
    {
        if(Flag_isOpen)         //判断是否创建或打开了一个文件
        {
            QFile file(Last_FileName);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,tr("警告"),tr("保存文件失败"));
                return;
            }
            else
            {


                QTextStream textStream(&file);
                QString str = showWidget->text->toPlainText();
                textStream<<str;
                Last_FileContent = str;
                file.close();
            }
        }
        else
        {
            QMessageBox::warning(this,tr("警告"),tr("请先创建或者打开文件"));
            return;
        }
    }

}

void EditProcessor::ShowSaveFileAs()     //另存为
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,tr("save as"),"/home",tr("Text File(*.txt)"));
    if(fileName == "")
    {
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("错误"),tr("另存文件失败"));
        return;
    }
    else
    {
        QTextStream textStream(&file);
        QString str = showWidget->text->toPlainText();
        textStream<<str;
        QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
        Last_FileContent = str;
        Last_FileName = fileName;
        Flag_IsNew = 0;
        file.close();
    }
}



/*************************************************************************/
void EditProcessor::loadFile(QString filename)
{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())
        {
            showWidget->text->append(textStream.readLine());
        }
    }
}

void EditProcessor::ShowPrintText()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec())
    {
        //获得QTextEdit对象的文档
        QTextDocument *doc = showWidget->text->document();
        doc->print(&printer);
    }
}



void EditProcessor::ShowFontComboBox(QString comboStr)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(comboStr);
    mergeFormat(fmt);
}

void EditProcessor::mergeFormat(QTextCharFormat format)
{
    QTextCursor cursor = showWidget->text->textCursor();
    if(!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    showWidget->text->mergeCurrentCharFormat(format);
}

void EditProcessor::ShowSizeSpinBox(QString spinValue)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(spinValue.toFloat());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void EditProcessor::ShowBoldBtn()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(boldBtn->isChecked()?QFont::Bold:QFont::Normal);
    showWidget->text->mergeCurrentCharFormat(fmt);

}

void EditProcessor::ShowItalicBtn()
{

    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void EditProcessor::ShowUnderlineBtn()
{

    QTextCharFormat fmt;
    fmt.setFontUnderline(underlineBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void EditProcessor::ShowColorBtn()
{
    QColor color = QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        showWidget->text->mergeCurrentCharFormat(fmt);

    }
}

void EditProcessor::ShowCurrentFormatChanged(const QTextCharFormat &fmt)
{
    fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamily()));
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.fontPointSize())));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.fontItalic());
    underlineBtn->setChecked(fmt.fontUnderline());
}

void EditProcessor::ShowAlignment(QAction *act)
{
    if(act==leftAction)
        showWidget->text->setAlignment(Qt::AlignLeft);
    if(act==rightAction)
        showWidget->text->setAlignment(Qt::AlignRight);
    if(act==centerAction)
        showWidget->text->setAlignment(Qt::AlignCenter);
    if(act==justifyAction)
        showWidget->text->setAlignment(Qt::AlignJustify);
}

void EditProcessor::ShowCursorPositionChanged()
{
    if(showWidget->text->alignment()==Qt::AlignLeft)
        leftAction->setChecked(true);
    if(showWidget->text->alignment()==Qt::AlignRight)
        rightAction->setChecked(true);
    if(showWidget->text->alignment()==Qt::AlignCenter)
        centerAction->setChecked(true);
    if(showWidget->text->alignment()==Qt::AlignJustify)
        justifyAction->setChecked(true);
}


void EditProcessor::ShowFind()
{
//    search->resize(150,30);
    search->setWindowFlags(Qt::FramelessWindowHint);
    search->lineEdit->clear();
    search->show();
}

void EditProcessor::searchHide()
{
    search->setHidden(true);
}





