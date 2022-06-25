#include "mainwindow.h"
#include "gui2022type.h"
Worker *createWorker()
{
    Worker *pg=new Worker;
    return pg;
}
void updateWorker(Worker*pg,QString name,int age)
{
    strncpy(pg->name, qPrintable(name),NAME_Worker-1);
    pg->age=age;
}
void addWorkerSort(Profession *pp, Worker* pg)
{
    if(pp->child==NULL)
    {
        pp->child=new Worker*[100];
        pp->capacity=1;
        pp->child[pp->capacity-1]=pg;
    }
    else
    {
        pp->capacity++;
        pp->child[pp->capacity-1]=pg;
    }
}
void Remove_Worker(Profession *pp,int index)
{
    Worker*pg=pp->child[index];
    delete pg;
    pp->capacity--;
    for(int i=index;i<pp->capacity;i++){pp->child[i]=pp->child[i+1];}
    pp->child[pp->capacity]=NULL;
}
