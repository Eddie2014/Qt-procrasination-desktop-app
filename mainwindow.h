#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QMainWindow>

//new added
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

//#include "firstwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSqlDatabase mydb;

private slots:
    void on_pushButton_clicked();
   //void  timer_timeout(); // not sure why added
   void update();
   void stop();

   void on_pushButton_3_clicked();

   void on_pushButton_2_clicked();

   void on_pushButton_4_clicked();

   void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
   // FirstWindow *firstwindow;
};

#endif // MAINWINDOW_H
