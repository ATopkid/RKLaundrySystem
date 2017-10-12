#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registration.h"
#include "systempage.h"
#include <QApplication>
//SQLite
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Register_pushButton_clicked();
    void on_Login_pushButton_clicked();
    void reshowMainWindow();
    void RegisterUser(QString,QString,QString,QString,QString,QString,QString);//Register user

private:
    Ui::MainWindow *ui;
    //UI Page
    Registration *registrationPage;
    SystemPage *systemPage;
    //SQLite
    QSqlDatabase db;
    void ConnectToDatabase();//Connect to DB

};

#endif // MAINWINDOW_H
