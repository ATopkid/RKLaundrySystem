#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = 0);
    ~Registration();

private slots:
    void on_Confirm_pushButton_clicked();

    void on_Cancel_pushButton_clicked();
signals:
    void IsClosed();//check if it is closed
    //---------------ID------Name----Password-Age----Agenda--Tel-----Address
    void SendRegInfo(QString,QString,QString,QString,QString,QString,QString);
private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
