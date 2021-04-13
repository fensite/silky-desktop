#include "widget.h"
#include "getApp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //UkuiMenuInterface *pUkuiMenuInterface=new UkuiMenuInterface;
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
