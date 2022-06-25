#include "mainwindow.h"
#include "gui2022type.h"
void updateZhek(Zhek *pf,QString name)
{
    strncpy(pf->Zhek_name, qPrintable(name),NAME_SIZE-1);
}
Zhek * createZhek()
{
    Zhek *pf=new Zhek;
    pf->child=NULL;
    pf->capacity=0;
    return pf;
}
void addZhekLast(Miskkomunhoz *pt,Zhek *pf)
{
    if (pt->child==NULL)
    {
        pt->child=new Zhek*[100];
        pt->capacity=1;
        pt->child[pt->capacity-1]=pf;
    }
    else
    {
        pt->capacity++;
        pt->child[pt->capacity-1]=pf;
    }
}
void Remove_Zhek(int index)
{
    Zhek*pf=getRoot()->child[index];
    for(int i=0;i<pf->capacity;i++)
    {
        Profession*pp=pf->child[i];
        for(int b=0;b<pp->capacity;b++){delete(pp->child[b]);}
        delete[](pp->child);
        delete(pf->child[i]);
    }
    delete[](pf->child);
    delete pf;
    getRoot()->capacity--;
    for(int i=index;i<getRoot()->capacity;i++){getRoot()->child[i]=getRoot()->child[i+1];}
    getRoot()->child[getRoot()->capacity]=NULL;
}
