#include "registration.h"
#include "ui_registration.h"
#include "mainwindow.h"
#include <QRegExp>
#include <QMessageBox>
#include <QDebug>

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    //Name
    QRegExp NameRegExp("^[\u4E00-\u9FA5A-Za-z]+$");
    ui->Name_lineEdit->setValidator(new QRegExpValidator(NameRegExp,this));
    //ID
    QRegExp IDRegExp("^[a-zA-Z0-9_-]{4,16}$");
    ui->Id_lineEdit->setValidator(new QRegExpValidator(IDRegExp,this));
    //Password
    QRegExp PasswordRegExp("^[a-zA-Z0-9]{6,18}$");
    ui->Password_lineEdit->setValidator(new QRegExpValidator(PasswordRegExp,this));
    //Agenda
    ui->Agenda_comboBox->addItem(tr("男"));
    ui->Agenda_comboBox->addItem(tr("女"));
    ui->Agenda_comboBox->addItem(tr("未知"));
    //Age
    QString _temp;
    for(int i = 0; i < 120; i++)
    {
        _temp = QString::number(i,10);
        ui->Age_comboBox->addItem(_temp);
    }
    //Tel
    QRegExp TelRegExp("^((1[3,5,8][0-9])|(14[5,7])|(17[0,6,7,8])|(19[7]))\\d{8}$");
    ui->Tel_lineEdit->setValidator(new QRegExpValidator(TelRegExp,this));
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_Confirm_pushButton_clicked()
{
    if(ui->Name_lineEdit->text()==NULL || ui->Id_lineEdit->text()==NULL
    || ui->Password_lineEdit->text()==NULL || ui->Tel_lineEdit->text() == NULL
    || ui->Address_lineEdit->text()==NULL)
    {
        QMessageBox::warning(NULL, tr("提示"), tr("请检查信息是否完整填写！"));
        return;

    }
    QString _info = ui->Name_label->text() + ui->Name_lineEdit->text() + "\n"
            + ui->Id_label->text() + ui->Id_lineEdit->text() + "\n"
            + ui->Password_label->text() + ui->Password_lineEdit->text() + "\n"
            + ui->Age_label->text() + ui->Age_comboBox->currentText() + "\n"
            + ui->Agenda_label->text() + ui->Agenda_comboBox->currentText() + "\n"
            + ui->Tel_label->text() + ui->Tel_lineEdit->text() + "\n"
            + ui->Address_label->text() + ui->Address_lineEdit->text();

    QMessageBox::StandardButton msgBox = QMessageBox::information(NULL, tr("确认信息"), _info, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(msgBox == QMessageBox::Yes)
    {
        //QMessageBox::aboutQt(NULL, "About Qt");
        qDebug()<<"Ok";
        //Send signal and info to MainWindow
        emit SendRegInfo(QString(ui->Id_lineEdit->text()),
                         QString(ui->Name_lineEdit->text()),
                         QString(ui->Password_lineEdit->text()),
                         QString(ui->Age_comboBox->currentText()),
                         QString(ui->Agenda_comboBox->currentText()),
                         QString(ui->Tel_lineEdit->text()),
                         QString(ui->Address_lineEdit->text()));
        emit IsClosed();
        delete this;
    }
    else
    {
        qDebug()<<"Cancel";
    }
}

void Registration::on_Cancel_pushButton_clicked()
{
    emit IsClosed();//sendMsg
    delete this;//this->close();
}
