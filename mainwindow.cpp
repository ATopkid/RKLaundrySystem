#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ID and Password RegExp
    {
        //ID
        QRegExp IDRegExp("^[a-zA-Z0-9_-]{4,16}$");
        ui->UserId_lineEdit->setValidator(new QRegExpValidator(IDRegExp,this));
        //Password
        QRegExp PasswordRegExp("^[a-zA-Z0-9]{6,18}$");
        ui->Password_lineEdit->setValidator(new QRegExpValidator(PasswordRegExp,this));
    }

    //init page
    registrationPage = new Registration;
    systemPage = new SystemPage;
    //Signal and Slot
    {
        //When Registration Page is closed;
        connect(registrationPage, SIGNAL(IsClosed()), this, SLOT(reshowMainWindow()));//Must be put after init
        //Send User registered information
        connect(registrationPage, SIGNAL(SendRegInfo(QString,QString,QString,QString,QString,QString,QString)), this, SLOT(RegisterUser(QString,QString,QString,QString,QString,QString,QString)));
    }
    //Connect to SQlite
    ConnectToDatabase();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectToDatabase()
{
    //SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("DataBase.db");
    db.setUserName("cqupt2016214290");
    db.setPassword("cqupt123456");
    db.open();
    bool isConnected = db.open();
    if(isConnected)
    {
        qDebug()<<"Connect to DB";
    }
    else
    {
        qDebug()<<"Fail to connect to DB";
    }
}

void MainWindow::reshowMainWindow()
{
    this->show();
}
void MainWindow::RegisterUser(QString _id,QString _name,QString _password,QString _age,QString _agenda,QString _tel,QString _address)
{
    //SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("DataBase.db");
    db.setUserName("cqupt2016214290");
    db.setPassword("cqupt123456");
    db.open();
    bool isConnected = db.open();
    if(isConnected)
    {
        /*
        qDebug()<<_id;
        qDebug()<<_name;
        qDebug()<<_password;
        qDebug()<<_age;
        qDebug()<<_agenda;
        qDebug()<<_tel;
        qDebug()<<_address;
        */
        QSqlQuery sql_query;
        QString create_sql = "create table member (id int primary key, name char(30), password char(30), age char(30), agenda char(30), tel int, address char(120))";
        QString insert_sql = "insert into member values(?,?,?,?,?,?,?)";

        QString select_all_sql = "select * from member";

        sql_query.prepare(create_sql); //创建表
        if(!sql_query.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table Create failed");
            qDebug()<<sql_query.lastError();
        }
        else
        {
            qDebug()<< "Table Created" ;
            //插入数据
            sql_query.prepare(insert_sql);

            QVariantList GroupIDs;
            GroupIDs.append(_id);

            QVariantList GroupNames;
            GroupNames.append(_name);

            QVariantList GroupPasswords;
            GroupPasswords.append(_password);

            QVariantList GroupAges;
            GroupAges.append(_age);

            QVariantList GroupAgendas;
            GroupAgendas.append(_agenda);

            QVariantList GroupTels;
            GroupTels.append(_tel);

            QVariantList GroupAddresses;
            GroupAddresses.append(_address);

            sql_query.addBindValue(GroupIDs);
            sql_query.addBindValue(GroupNames);
            sql_query.addBindValue(GroupPasswords);
            sql_query.addBindValue(GroupAges);
            sql_query.addBindValue(GroupAgendas);
            sql_query.addBindValue(GroupTels);
            sql_query.addBindValue(GroupAddresses);


            if(!sql_query.execBatch())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"插入记录成功";
            }

            //查询所有记录
            sql_query.prepare(select_all_sql);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();

            }
            else
            {
                while(sql_query.next())
                {
                    QString id = sql_query.value(0).toString();
                    QString name = sql_query.value(1).toString();
                    QString password = sql_query.value(2).toString();
                    QString age = sql_query.value(3).toString();
                    QString agenda = sql_query.value(4).toString();
                    QString tel = sql_query.value(5).toString();
                    QString address = sql_query.value(6).toString();
                    qDebug()<<QString("ID:%1  Name:%2  Password:%3  Age:%4 Agenda:%5  Tel:%6  Address:%7").arg(id).arg(name).arg(password).arg(age).arg(agenda).arg(tel).arg(address);
                }
            }
        }
    }
    else
        return;
}

void MainWindow::on_Register_pushButton_clicked()
{
    this->hide();
    registrationPage->show();
}

void MainWindow::on_Login_pushButton_clicked()
{

    QString _id = ui->UserId_lineEdit->text();
    QString _password = ui->Password_lineEdit->text();
    //SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("DataBase.db");
    db.setUserName("cqupt2016214290");
    db.setPassword("cqupt123456");
    db.open();
    bool isConnected = db.open();
    if(isConnected)
    {
        QSqlQuery sql_query;
        QString select_sql = "select id, password from member";
        if(!sql_query.exec(select_sql))
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                QString id = sql_query.value(0).toString();
                QString password = sql_query.value(1).toString();
                qDebug()<<QString("id:%1    password:%2").arg(id).arg(password);
                if(_id == id && _password == password)
                {
                    QMessageBox::information(NULL,tr("提示"),tr("登陆成功"));
                    this->hide();
                    systemPage->show();
                }
                else
                {
                    QMessageBox::information(NULL,tr("提示"),tr("密码错误"));
                }
            }
        }
    }
    else
        return;
}
