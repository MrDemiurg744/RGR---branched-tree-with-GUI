#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui2022type.h"
MainWindow::MainWindow(QWidget *parent):
        QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setButtonState(false,false,true);
    ui->Find_Button->setVisible(false);
    ui->Query_edit->setVisible(false);
    ui->treeWidget_find->setVisible(false);
    ui->box_Query_2->setVisible(false);
    ui->label_Query_2->setVisible(false);
}
void MainWindow::setButtonState(bool store, bool update, bool exit)
{
    ui->store->setVisible(store);
    ui->exit->setVisible(exit);
    ui->Update->setVisible(update);
}
void MainWindow::showMiskkomunhoz()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMiskkomunhoz);
    Miskkomunhoz*pt=getRoot();
    if(pt!=NULL){ui->lineEditSysName->setText(pt->name);}
    else{ui->lineEditSysName->setText("");}
}
void MainWindow::showZhek(Zhek*pf)
{
    ui->stackedWidget->setCurrentWidget(ui->pageZhek);
    ui->lineEdit_Name_Zhek->setText(pf->Zhek_name);
}
void MainWindow::showProfession(Profession *pp)
{
    ui->stackedWidget->setCurrentWidget(ui->pageProfession);
    ui->lineEdit_Name_Profession->setText(pp->name);
}
void MainWindow::showWorker(Worker *pg)
{
    ui->stackedWidget->setCurrentWidget(ui->pageWorker);
    ui->lineEdit_Name_Worker->setText(pg->name);
    ui->lineEdit_age->setText(QString::number(pg->age));
}
void  MainWindow::showTree()
{
    delete ui->treeWidget->takeTopLevelItem(0);
    showMiskkomunhoz();
    if(getRoot()==NULL){return;}
    QTreeWidgetItem *rootItem=new QTreeWidgetItem(ui->treeWidget);
    rootItem->setText(0,getRoot()->name);
    Zhek **ZhekArr=getRoot()->child;
    int ZhekCount=getRoot()->capacity;
    if(ZhekArr==NULL||ZhekCount==0)return;
    for(int iF=0;iF<ZhekCount;iF++){
        Zhek*pF=ZhekArr[iF];
        QTreeWidgetItem *fItem=new QTreeWidgetItem(rootItem);
        fItem->setText(0,pF->Zhek_name);
        Profession **ProfessionArr=pF->child;
        int ProfessionCount=pF->capacity;
        if(ProfessionArr==NULL||ProfessionCount==0)continue;
        for(int iP=0;iP<ProfessionCount;iP++)
        {
            Profession*pp=ProfessionArr[iP];
            QTreeWidgetItem *pItem=new QTreeWidgetItem(fItem);
            pItem->setText(0,pp->name);
            Worker **WorkerArr=pp->child;
            int WorkerCount=pp->capacity;
            if(WorkerArr==NULL||WorkerCount==0){continue;}
            for(int iG=0;iG<WorkerCount;iG++)
            {
                Worker*pg=WorkerArr[iG];
                QTreeWidgetItem *gItem=new QTreeWidgetItem(pItem);
                gItem->setText(0,pg->name);
            }
        }
    }
    ui->treeWidget->expandAll();
}
int MainWindow::Selectedlevel()
{
    QTreeWidgetItem *item = ui->treeWidget->selectedItems().at(0);
    int level=0;
    while((item =item->parent())!=NULL){level++;}
    return level;
}
int MainWindow::SelectedIndex(int offset)
{
    QTreeWidgetItem *item = ui->treeWidget->selectedItems().at(0);
    for(int i=0; i<offset;i++){item=item->parent();}
    return item->parent()->indexOfChild(item);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionCreate_root_triggered()
{
    ui->box_Query_2->setVisible(false);
    ui->label_Query_2->setVisible(false);
    ui->Find_Button->setVisible(false);
    ui->Query_edit->setVisible(false);
    ui->treeWidget_find->setVisible(false);
    ui->stackedWidget->setVisible(true);
    if(getRoot()!=NULL)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Root already exist");
        errorMessage.exec();
        return;
    }
    Miskkomunhoz *pt= createMiskkomunhoz();
    setRoot(pt);
    QTreeWidgetItem *rootitem=new QTreeWidgetItem (ui->treeWidget);
    rootitem->setSelected(true);
    ui->treeWidget->setCurrentItem(rootitem);
    ui->stackedWidget->setCurrentWidget(ui->pageMiskkomunhoz);
    setButtonState(false,true,false);
}
void MainWindow::on_Update_clicked()
{
    setButtonState(false,false,false);
    int level=Selectedlevel();
    if(level==0){updateMiskkomunhoz(ui->lineEditSysName->text());}
    else if(level==1)
    {
        int idxF=SelectedIndex(0);
        Zhek *pf=getRoot()->child[idxF];
        updateZhek(pf,ui->lineEdit_Name_Zhek->text());
    }
    else if(level==2)
    {
        int idxF=SelectedIndex(1);
        Zhek *pf=getRoot()->child[idxF];
        //        int idxP=SelectedIndex(0);
        Profession*pp=pf->child[idxF];
        updateProfession(pp,ui->lineEdit_Name_Profession->text());
    }
    else if(level==3)
    {
        int idxF=SelectedIndex(2);
        Zhek *pf=getRoot()->child[idxF];
        int idxP=SelectedIndex(1);
        Profession*pp=pf->child[idxP];
        int idxG=SelectedIndex(0);
        Worker*pg=pp->child[idxG];
        updateWorker(pg,ui->lineEdit_Name_Worker->text(),ui->lineEdit_age->text().toInt());
    }
    showTree();
}
void MainWindow::on_actionEdit_triggered()
{
    ui->box_Query_2->setVisible(false);
    ui->label_Query_2->setVisible(false);
    ui->Find_Button->setVisible(false);
    ui->Query_edit->setVisible(false);
    ui->treeWidget_find->setVisible(false);
    ui->stackedWidget->setVisible(true);
    if(ui->treeWidget->selectedItems().count()==0)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Node was not selected");
        errorMessage.exec();
        return;
    }
    setButtonState(false,true,false);
}
void MainWindow::on_actionAdd_triggered()
{
    ui->box_Query_2->setVisible(false);
    ui->label_Query_2->setVisible(false);
    ui->Find_Button->setVisible(false);
    ui->Query_edit->setVisible(false);
    ui->treeWidget_find->setVisible(false);
    ui->stackedWidget->setVisible(true);
    if(ui->treeWidget->selectedItems().count()==0)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Node was not selected");
        errorMessage.exec();
        return;
    }
    setButtonState(true,false,true);
    int level=Selectedlevel();
    if(level==0){ui->stackedWidget->setCurrentWidget(ui->pageZhek);}
    else if(level==1){ui->stackedWidget->setCurrentWidget(ui->pageProfession);}
    else if(level==2){ui->stackedWidget->setCurrentWidget(ui->pageWorker);}
    else if(level==3)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("No more parts of tree");
        errorMessage.exec();
    }
}
void MainWindow::on_store_clicked()
{
    setButtonState(false,false,false);
    int level=Selectedlevel();
    if(level==0)
    {
        Zhek *pf=createZhek();
        updateZhek(pf,ui->lineEdit_Name_Zhek->text());
        addZhekLast(getRoot(),pf);
    }
    if(level==1)
    {
        int idxP=SelectedIndex(0);
        Zhek*pf=getRoot()->child[idxP];
        Profession *pp=createProfession();
        updateProfession(pp,ui->lineEdit_Name_Profession->text());
        addProfessionLast(pf,pp);
    }
    if(level==2)
    {
        int idxF=SelectedIndex(1);
        Zhek *pf=getRoot()->child[idxF];
        int idxP=SelectedIndex(0);
        Profession*pp=pf->child[idxP];
        Worker*pg=createWorker();
        updateWorker(pg,ui->lineEdit_Name_Worker->text(),ui->lineEdit_age->text().toInt());
        addWorkerSort(pp,pg);
    }
    showTree();
}
void MainWindow::on_treeWidget_clicked(QModelIndex index)
{
    setButtonState(false,false,false);
    int level=Selectedlevel();
    if(level ==0){showMiskkomunhoz();}
    else if(level==1)
    {
        int idxF=SelectedIndex(0);
        Zhek *pf=getRoot()->child[idxF];
        showZhek(pf);
    }
    else if(level==2)
    {
        int idxF=SelectedIndex(1);
        Zhek *pf=getRoot()->child[idxF];
        int idxP=SelectedIndex(0);
        Profession *pp=pf->child[idxP];
        showProfession(pp);
    }
    else if(level==3)
    {
        int idxF=SelectedIndex(2);
        Zhek *pf=getRoot()->child[idxF];
        int idxP=SelectedIndex(1);
        Profession *pp=pf->child[idxP];
        int idxG=SelectedIndex(0);
        Worker *pg=pp->child[idxG];
        showWorker(pg);
    }
}
void MainWindow::on_actionRemove_triggered()
{
    ui->box_Query_2->setVisible(false);
    ui->label_Query_2->setVisible(false);
    ui->Find_Button->setVisible(false);
    ui->Query_edit->setVisible(false);
    ui->treeWidget_find->setVisible(false);
    ui->stackedWidget->setVisible(true);
    if(ui->treeWidget->selectedItems().count()==0)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Node was not selected");
        errorMessage.exec();
        return;
    }
    int level=Selectedlevel();
    if(level==0){Remove_Miskkomunhoz();}
    else if(level==1)
    {
        int idxF=SelectedIndex(0);
        Remove_Zhek(idxF);
    }
    else if(level==2)
    {
        int idxF=SelectedIndex(1);
        Zhek*pf=getRoot()->child[idxF];
        int idxP=SelectedIndex(0);
        Remove_Profession(pf,idxP);
    }
    else if(level==3)
    {
        int idxF=SelectedIndex(2);
        Zhek*pf=getRoot()->child[idxF];
        int idxP=SelectedIndex(1);
        Profession*pp=pf->child[idxP];
        int idxG=SelectedIndex(0);
        Remove_Worker(pp,idxG);
    }
    showTree();
}
void MainWindow::on_actionQuery1_triggered()
{
    if(getRoot()==NULL)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("No tree");
        errorMessage.exec();
        return;
    }
    ui->box_Query_2->setVisible(false);
    ui->label_Query_2->setVisible(false);
    setButtonState(false,false,true);
    ui->Find_Button->setVisible(true);
    ui->Query_edit->setVisible(true);
    ui->treeWidget_find->setVisible(true);
    ui->stackedWidget->setVisible(false);
}
void MainWindow::on_Find_Button_clicked()
{
    ui->treeWidget_find->clear();
    Miskkomunhoz*pft=new Miskkomunhoz;
    pft->child=NULL;
    pft->capacity=0;
    strncpy(pft->name, qPrintable(ui->Query_edit->text()),NAME_SIZE-1);
    Zhek*pff=new Zhek;
    pff->child=NULL;
    pff->capacity=0;
    strncpy(pff->Zhek_name, qPrintable(ui->Query_edit->text()),NAME_SIZE-1);
    Profession*pfp=new Profession;
    pfp->child=NULL;
    pfp->capacity=0;
    strncpy(pfp->name, qPrintable(ui->Query_edit->text()),NAME_SIZE-1);
    Worker*pfg=new Worker;
    strncpy(pfg->name, qPrintable(ui->Query_edit->text()),NAME_SIZE-1);
    Miskkomunhoz*pf=getRoot();
    if(pft->name[0]==pf->name[0])
    {
        QTreeWidgetItem *rootItem=new QTreeWidgetItem(ui->treeWidget_find);
        rootItem->setText(0,pf->name);
    }
    for(int i=0;i<getRoot()->capacity;i++)
    {
        Zhek*pf0=getRoot()->child[i];
        if(pff->Zhek_name[0]==pf0->Zhek_name[0])
        {
            QTreeWidgetItem *rootItem=new QTreeWidgetItem(ui->treeWidget_find);
            rootItem->setText(0,pf0->Zhek_name);
        }
        for(int x=0;x<getRoot()->child[i]->capacity;x++)
        {
            Profession*pf1=getRoot()->child[i]->child[x];
            if(pfp->name[0]==pf1->name[0])
            {
                QTreeWidgetItem *rootItem=new QTreeWidgetItem(ui->treeWidget_find);
                rootItem->setText(0,pf1->name);
            }
            for(int y=0;y<getRoot()->child[i]->child[x]->capacity;y++)
            {
                Worker*pf2=getRoot()->child[i]->child[x]->child[y];
                if(pfg->name[0]==pf2->name[0])
                {
                    QTreeWidgetItem *rootItem=new QTreeWidgetItem(ui->treeWidget_find);
                    rootItem->setText(0,pf2->name);
                }
            }
        }
    }
}
void MainWindow::on_actionQuery2_triggered()
{
    if(getRoot()==NULL)
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("No tree");
        errorMessage.exec();
        return;
    }
    else
    {
        ui->stackedWidget->setVisible(false);
        ui->box_Query_2->setVisible(true);
        ui->box_Query_2->clear();
        ui->label_Query_2->setVisible(true);
        float num=0,value=0;
        for(int i=0;i<getRoot()->capacity;i++)
        {
            Zhek*pf=getRoot()->child[i];
            for(int d=0;d<pf->capacity;d++)
            {
                Profession*pp=pf->child[d];
                for(int c=0;c<pp->capacity;c++)
                {
                    Worker*pg=pp->child[c];
                    num+=pg->age;
                    value++;
                }
            }
        }
        ui->box_Query_2->insertPlainText(QString::number(num/value));
    }
}
