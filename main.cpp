#include <QtGui/QApplication>
#include "mainwindow.h"
#include "gui2022type.h"
Miskkomunhoz *root=NULL;
Miskkomunhoz *getRoot()
{
    return root;
}
void setRoot(Miskkomunhoz* r)
{
    root=r;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
