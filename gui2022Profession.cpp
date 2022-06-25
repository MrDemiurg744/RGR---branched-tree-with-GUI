#include "mainwindow.h"
#include "gui2022type.h"
void updateProfession(Profession *pp,QString name)
{
    strncpy(pp->name, qPrintable(name),NAME_SIZE-1);
}
Profession *createProfession()
{
    Profession *pp=new Profession;
    pp->child=NULL;
    pp->capacity=0;
    return pp;
}
void addProfessionLast(Zhek *pf,Profession*pp)
{
    if(pf->child==NULL)
    {
        pf->child=new Profession*[100];
        pf->capacity=1;
        pf->child[pf->capacity-1]=pp;
    }
    else
    {
        pf->capacity++;
        pf->child[pf->capacity-1]=pp;
    }
}
void Remove_Profession(Zhek*pf,int index)
{
    Profession*pp=pf->child[index];
    for(int b=0;b<pp->capacity;b++){delete(pp->child[b]);}
    delete[](pp->child);
    delete pp;
    pf->capacity--;
    for(int i=index;i<pf->capacity;i++){pf->child[i]=pf->child[i+1];}
    pf->child[pf->capacity]=NULL;
}
