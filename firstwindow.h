#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include "mainwindow.h"

#include <QMainWindow>

//new added
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class FirstWindow;
}

class FirstWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb; //new
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen()
    {

        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/sqlite3/datatable.db");

        if(!mydb.open())
        {
            qDebug()<<("Failed to open timelog database");
            return false;
        }
        else
        {
            qDebug()<<("Connected...");
            return true;
        }

    }

private slots:
    void on_pushButton_clicked();

private:
    Ui::FirstWindow *ui;

    MainWindow *mainwindow;// pointer
    FirstWindow *firstwindow;

};

#endif // FIRSTWINDOW_H
