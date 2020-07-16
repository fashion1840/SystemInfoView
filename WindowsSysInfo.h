#ifndef WINDOWSSYSINFO_H
#define WINDOWSSYSINFO_H

#include "ISystemInfoFactory.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QDir>
#include <QFileInfoList>
#include <QHostAddress>
#include <QHostInfo>
#include <QLibrary>
#include <QNetworkAccessManager>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSettings>
#include <QSysInfo>
#include <QTimer>

class WindowsSysInfo : public ISystemInfoFactory
{
    Q_OBJECT

public:
    explicit WindowsSysInfo();
    virtual ~WindowsSysInfo();

    //QString localmachineName(); //获取计算机名称
    //QString localIP();          //获取本地IP
    //QString macAddress();       //获取计算机MAC地址
    //QString publicIP();    //获取外网IP
    virtual QString cpuType();     //获取计算机CPU信息
    virtual QString displayCard(); //获取计算机显卡信息
    virtual QString memory();      //获取计算机内存
    virtual QString osVersion();   //获取计算机操作系统
    virtual QString screen();      //获取计算机屏幕个数以及像素
    virtual QString disk();        //获取计算机硬盘信息
    void checkOffice();            //获取计算机安装的office版本
    bool netWorkLive();            //判断计算机是否可以联网
    void displayCard2();
    QString displayCard3();

private:
    QString m_cpuDescribe;
    double m_totalMem;
    double m_freeMem;
    QString m_memDescribe;
    QString m_osDescirbe;
    QString m_screenDescribe;
    QString m_diskDescribe;
    QString m_officeDecsribe;
    QString describe;
    QString dcard;
    //QString ip;
    //QString machineName;
    QString strIp;
    //QString strMac;
    QSize m_maxScreenSize;
    double m_maxFreeDisk;

    //QString getHtml(QString url);                          //获取网页所有源代码
    std::string WStringToString(const std::wstring &wstr); //wchar_t*转到string
};

#endif // WINDOWSSYSINFO_H
