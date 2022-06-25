#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "gui2022type.h"
namespace Ui
{
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    void setButtonState(bool,bool,bool);
    void showMiskkomunhoz();
    void showZhek(Zhek*);
    void showProfession(Profession*);
    void showWorker(Worker*);
    void showTree();
    int Selectedlevel();
    int SelectedIndex(int);
private slots:
    void on_actionQuery2_triggered();
    void on_Find_Button_clicked();
    void on_actionQuery1_triggered();
    void on_actionRemove_triggered();
    void on_treeWidget_clicked(QModelIndex index);
    void on_store_clicked();
    void on_actionAdd_triggered();
    void on_actionEdit_triggered();
    void on_Update_clicked();
    void on_actionCreate_root_triggered();
};
#endif // MAINWINDOW_H
