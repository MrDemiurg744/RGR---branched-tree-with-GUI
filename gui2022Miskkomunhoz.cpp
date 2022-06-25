#include "mainwindow.h"
#include "gui2022type.h"
void updateMiskkomunhoz(QString name)
{
    strncpy(getRoot()->name, qPrintable(name),NAME_SIZE-1);
}
Miskkomunhoz *createMiskkomunhoz()
{
    Miskkomunhoz*pt=new Miskkomunhoz;
    pt->child=NULL;
    pt->capacity=0;
    return pt;
}
void Remove_Miskkomunhoz()
{
    for(int n=0;n<getRoot()->capacity;n++)
    {
        Zhek*pf=getRoot()->child[n];
        for(int i=0;i<pf->capacity;i++)
        {
            Profession*pp=pf->child[i];
            for(int b=0;b<pp->capacity;b++){delete(pp->child[b]);}
            delete[](pp->child);
            delete(pf->child[i]);
        }
        delete[](pf->child);
        delete(getRoot()->child[n]);
    }
    delete[](getRoot()->child);
    delete getRoot();
    setRoot(NULL);
}
