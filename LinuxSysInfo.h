#ifndef LINUXSYSINFO_H
#define LINUXSYSINFO_H

#include "ISystemInfoFactory.h"
#include <QObject>

class LinuxSysInfo : public QObject, public ISystemInfoFactory
{
    Q_OBJECT

    typedef struct MEM_PACKED
    {
        char name{ 20 };
        unsigned long total;
        char unit_name{ 20 };
    } MEM_OCCUPY;

public:
    explicit LinuxSysInfo();
    virtual ~LinuxSysInfo();

    virtual QString cpuType();     //获取计算机CPU信息
    virtual QString displayCard(); //获取计算机显卡信息
    virtual QString memory();      //获取计算机内存
    virtual QString osVersion();   //获取计算机操作系统
    virtual QString screen();      //获取计算机屏幕个数以及像素
    virtual QString disk();        //获取计算机硬盘信息

private:
    QString m_osDescirbe;
    QString m_cpuDescribe;
    double m_totalMem;
    double m_freeMem;
    QString m_memDescribe;
    QString m_diskDescribe;

    double getValueByString(char *buff);
};

#endif // LINUXSYSINFO_H
