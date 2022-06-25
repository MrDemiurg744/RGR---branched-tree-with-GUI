#ifndef GUI2022TYPE_H
#define GUI2022TYPE_H
#include <ctype.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <QtGui>
#define NAME_SIZE 15
#define START_AR_SIZE 2
#define NAME_Worker 15
struct Zhek;
struct Profession;
struct Worker;
struct Miskkomunhoz
{
    char name[NAME_SIZE];
    int budget;
    Zhek **child;
    int arLength;
    int capacity;
};
struct Zhek
{
    char Zhek_name[NAME_SIZE];
    int salary;
    int arLength;
    Profession **child;
    int capacity;
};
struct Profession
{
    char name[NAME_SIZE];
    int year;
    int arLength;
    int capacity;
    Worker **child;
};
struct Worker
{
    char name [NAME_Worker];
    int age;
};
Miskkomunhoz* getRoot();
void setRoot(Miskkomunhoz* r);
Miskkomunhoz * createMiskkomunhoz();
void updateMiskkomunhoz(QString name);
void updateZhek( Zhek *pf,QString name);
void updateProfession( Profession *pp,QString name);
void updateWorker(Worker*pg,QString name,int age);
Zhek * createZhek();
void addZhekLast(Miskkomunhoz *pt,Zhek*pf);
Profession *createProfession();
void addProfessionLast(Zhek *pf,Profession*pp);
Worker *createWorker();
void addWorkerSort(Profession *pp, Worker* pg);
void Remove_Miskkomunhoz();
void Remove_Zhek(int index);
void Remove_Profession(Zhek*pf,int index);
void Remove_Worker(Profession*pp,int index);
#endif // GUI2022TYPE_H
