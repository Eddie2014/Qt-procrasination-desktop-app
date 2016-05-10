#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firstwindow.h"

#include <QTimer>
#include <QMessageBox>
#include <QWaitCondition>

QTimer *timer; //create pointer to timer

//global variable for count
int count;
bool pause_resume=false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //testing
    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/sqlite3/datatable.db");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //initiates timer when button is pressed

    timer= new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000);
    pause_resume=true;

}

void MainWindow::stop()
{


}

void MainWindow::update()
{

    //updating the count
    count++;
    ui->lcdNumber->display(count);
    if(count==10)
    {

        FirstWindow conn;

        QString number;
        number=25;

        conn.connOpen();
        QSqlQuery qry;
        //qry.prepare("insert into datatable (row,activity,hours) values('1','1','1')");

      //  qry.prepare("UPDATE table set col = 1 WHERE id = (SELECT MAX(id) FROM table)");
        qry.prepare("UPDATE datatable set hours = 25 WHERE rowid = (SELECT MAX(rowid) FROM datatable)");

        if(!qry.exec())
        {
             QMessageBox::critical(this,tr("error::"),qry.lastError().text());

        }
        else
        {
        timer->stop();
        conn.connClose();
        }

    }
}



void MainWindow::on_pushButton_2_clicked()
{



    timer->stop();
    if(pause_resume==true)
    {
        timer->stop();
        pause_resume=false;
    }
    else
    {
        timer->start();
    }


}

void MainWindow::on_pushButton_3_clicked()
{
    FirstWindow *firstwindow; //interesting

    timer->stop();
    count=0;
    ui->lcdNumber->display(count);
    this->hide();
    firstwindow = new FirstWindow(this);
    firstwindow->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    timer->stop();
}

void MainWindow::on_pushButton_5_clicked()
{
    timer->stop();
    //reset the lcd
    count=0;
    ui->lcdNumber->display(count);

   //open connection to dupe last row
    FirstWindow conn;

    conn.connOpen();
    QSqlQuery x;
    x.prepare("insert into datatable (row,activity,hours) values(last_insert_id())");

    if(x.exec())
    {
        this->hide();
        conn.connClose(); //close after inserting another
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),x.lastError().text());
    }




}
