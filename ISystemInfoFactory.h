#ifndef ISYSTEMINFOFACTORY_H
#define ISYSTEMINFOFACTORY_H

#include <QObject>
#include <QString>
class ISystemInfoFactory : public QObject
{
    Q_OBJECT

public:
    ISystemInfoFactory();
    virtual QString localmachineName(); //获取计算机名称
    virtual QString localIP();          //获取本地IP
    virtual QString publicIP();         //获取外网IP
    virtual QString macAddress();       //获取计算机MAC地址
    virtual QString cpuType() = 0;      //获取计算机CPU信息
    virtual QString displayCard() = 0;  //获取计算机显卡信息
    virtual QString memory() = 0;       //获取计算机内存
    virtual QString osVersion() = 0;    //获取计算机操作系统
    virtual QString screen() = 0;       //获取计算机屏幕个数以及像素
    virtual QString disk() = 0;         //获取计算机硬盘信息

protected:
    virtual ~ISystemInfoFactory() {}

private:
    QString getHtml(QString url); //获取网页所有源代码
};

#endif // ISYSTEMINFOFACTORY_H
