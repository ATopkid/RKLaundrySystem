#ifndef STOREMANAGEMENTMODEL_H
#define STOREMANAGEMENTMODEL_H

#include <QObject>

class StoreManagementModel : public QObject
{
    Q_OBJECT
public:
    explicit StoreManagementModel(QObject *parent = nullptr);
    ~StoreManagementModel();
private:
    //Store Page Model
    void StoreManage();
    void MemberManage();
    void ChargeManage();
    //Member Page Model
    //Order Page Model
    //Laundry Page Model
signals:

public slots:
};

#endif // STOREMANAGEMENTMODEL_H
