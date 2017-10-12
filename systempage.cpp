#include "systempage.h"
#include "ui_systempage.h"
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QStringList>
#include <QDebug>

SystemPage::SystemPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemPage)
{
    ui->setupUi(this);
    setWindowTitle(tr("洗衣店管理系统"));
    //Connect to DB
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("DataBase.db");
        db.setUserName("cqupt2016214290");
        db.setPassword("cqupt123456");
        db.open();
        bool isConnected = db.open();
        if(isConnected)
        {
            QSqlQuery sql_query;
            QString select_sql = "select id, name,leader,tel,address,postcode from store";
            if(!sql_query.exec(select_sql))
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                int row = 0;

                QList<QString>* StoreNameQSList = new QList<QString>();
                QList<QString>* StoreLeaderQSList = new QList<QString>();

                QList<QString>* StoreTelQSList = new QList<QString>();

                QList<QString>* StoreAddressQSList = new QList<QString>();

                QList<QString>* StorePostcodeQSList = new QList<QString>();

                while(sql_query.next())
                {
                    int id = sql_query.value(0).toInt();
                    QString name = sql_query.value(1).toString();
                    QString leader = sql_query.value(2).toString();
                    QString tel = sql_query.value(3).toString();
                    QString address = sql_query.value(4).toString();
                    QString postcode = sql_query.value(5).toString();


                    StoreNameQSList->append(name);
                    StoreLeaderQSList->append(leader);
                    StoreTelQSList->append(tel);
                    StoreAddressQSList->append(address);
                    StorePostcodeQSList->append(postcode);

                    //qDebug()<<StoreNameQSList->count();
                    qDebug()<<QString("id:%1    name:%2    leader:%3    tel:%4    address:%5    postcode:%6").arg(id).arg(name).arg(leader).arg(tel).arg(address).arg(postcode);
                    row++;
                    //StoreModel->insertRow(row,QList()<<name<<leader<<tel<<address<<postcode);
                }
                qDebug()<<QString("Total:%1").arg(row);
                QStandardItemModel *StoreModel = new QStandardItemModel(row,5,NULL);
                StoreModel->setHeaderData(0,Qt::Horizontal,tr("店名"));
                StoreModel->setHeaderData(1,Qt::Horizontal,tr("负责人"));
                StoreModel->setHeaderData(2,Qt::Horizontal,tr("电话"));
                StoreModel->setHeaderData(3,Qt::Horizontal,tr("地址"));
                StoreModel->setHeaderData(4,Qt::Horizontal,tr("邮编"));

                StoreModel->setItem(0,0,new QStandardItem("xxx"));

                QList<QString>* _listPointer = NULL;

                for(int _row = 0; _row < row; _row++)
                {
                    for(int _col = 0; _col < 5; _col++)
                    {
                        switch (_col) {

                        case 0:
                            _listPointer = StoreNameQSList;
                            break;
                        case 1:
                            _listPointer = StoreLeaderQSList;
                            break;
                        case 2:
                            _listPointer = StoreTelQSList;
                            break;
                        case 3:
                            _listPointer = StoreAddressQSList;
                            break;
                        case 4:
                            _listPointer = StorePostcodeQSList;
                            break;

                        default:
                            _listPointer = NULL;
                            break;
                        }
                        StoreModel->setItem(_row, _col, new QStandardItem(_listPointer->value(_row)));


                    }

                }
//                for(int _row = 0; _row < row; _row++)
//                {
//                    for(int _col = 0; _col < 5; _col++)
//                    {
//                            switch (_col) {
//                            case 0:
//                                StoreModel->setItem(_row, 0, new QStandardItem(StoreNameQSList->value(_row)));
//                                break;
//                            case 1:
//                                StoreModel->setItem(_row, 1, new QStandardItem(StoreLeaderQSList->value(_row)));
//                                break;
//                            case 2:
//                                StoreModel->setItem(_row, 2, new QStandardItem(StoreTelQSList->value(_row)));
//                                break;
//                            case 3:
//                                StoreModel->setItem(_row, 3, new QStandardItem(StoreAddressQSList->value(_row)));
//                                break;
//                            case 4:
//                                StoreModel->setItem(_row, 4, new QStandardItem(StorePostcodeQSList->value(_row)));
//                                break;
//                            default:
//                                break;
//                            }
//                    }
//                }

                ui->StoreManagement_tableView->setModel(StoreModel);

            }
        }
    }
    //店面管理
    {
        //实时刷新
        ui->StoreManagement_tableView->setUpdatesEnabled(true);
        ui->MemberManagement_tableView->setUpdatesEnabled(true);
        ui->ChargeManagement_tableView->setUpdatesEnabled(true);
        //Store Model
//        {
//            QStandardItemModel *StoreModel = new QStandardItemModel;
//            StoreModel->setColumnCount(5);
//            StoreModel->setHorizontalHeaderLabels(QStringList()<<QString("店名")<<QString("负责人")<<QString("电话")<<QString("地址")<<QString("邮编"));
//            StoreModel->setRowCount(20);
//            ui->StoreManagement_tableView->setModel(StoreModel);
//        }
    }
}

SystemPage::~SystemPage()
{
    delete ui;
}

