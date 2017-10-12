#ifndef SYSTEMPAGE_H
#define SYSTEMPAGE_H

#include <QWidget>
//SQLite
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

namespace Ui {
class SystemPage;
}

class SystemPage : public QWidget
{
    Q_OBJECT

public:
    explicit SystemPage(QWidget *parent = 0);
    ~SystemPage();
private:


private:
    Ui::SystemPage *ui;
};

#endif // SYSTEMPAGE_H
