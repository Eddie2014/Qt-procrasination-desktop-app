#include "firstwindow.h"
#include "mainwindow.h"
#include "ui_firstwindow.h"
#include <QMessageBox>

FirstWindow::FirstWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstWindow)
{
    ui->setupUi(this);

    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/sqlite3/datatable.db");

    if(!mydb.open())
        ui->label_2->setText("Failed to open timelog database");
    else
        ui->label_2->setText("Connected...");

}

FirstWindow::~FirstWindow()
{
    delete ui;
}

void FirstWindow::on_pushButton_clicked()
{
    FirstWindow conn;

    QString rowid,Activity;
    Activity=ui->lineEdit->text();
    rowid=3;
    int thehours=1;

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into datatable (row,activity,hours) values('"+rowid+"','"+Activity+"','1')");

    //if this is good
    if(qry.exec())
    {
        this->hide();//hiding current ui
        mainwindow = new MainWindow(this);
        mainwindow->show();


        conn.connClose(); //close after inserting another
    }
    //if this is bad
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }







}

