#include "EditProcessor.h"
#include <QApplication>
#include <QFrame>
#include <QPixmap>
#include <QPalette>
#include <QBitmap>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont f("ZYSong18030",12);
    a.setFont(f);
    EditProcessor w;
    w.resize(1800,1000);
    w.show();




    return a.exec();
}
