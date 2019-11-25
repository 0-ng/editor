#include "EditProcessor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont f("ZYSong18030",12);
    a.setFont(f);
    EditProcessor w;
    w.resize(1500,1000);
//    w.setWindowIcon(QIcon(":/new/prefix1/img/oops.jpg"));
    w.show();

    return a.exec();
}
