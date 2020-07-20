#ifndef MACXSYSINFO_H
#define MACXSYSINFO_H

#include "ISystemInfoFactory.h"
#include <QObject>

#define MEM_DIV 1024

class MacxSysInfo : public ISystemInfoFactory
{
    Q_OBJECT

public:
    explicit MacxSysInfo();
    virtual ~MacxSysInfo();

    virtual QString cpuType();     //获取计算机CPU信息
    virtual QString displayCard(); //获取计算机显卡信息
    virtual QString memory();      //获取计算机内存
    virtual QString osVersion();   //获取计算机操作系统
    virtual QString screen();      //获取计算机屏幕个数以及像素
    virtual QString disk();        //获取计算机硬盘信息

private:
    bool Is64BitOS();
    bool GetSysStringInfo(QString strName, QString &strValue);
    QString GetCpuBrandInfo();
    int GetProcessorCoreCount();
    bool GetSysInteger32Info(QString strName, int &nValue);
    qint64 GetTotalPhysicMemInBytes();
    bool GetSysInteger64Info(QString strName, qint64 &nValue);
};

#endif // MACXSYSINFO_H
