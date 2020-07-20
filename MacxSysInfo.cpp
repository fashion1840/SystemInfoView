#include "MacxSysInfo.h"
#include "EasyQJson.h"
#include "QTerminalInfo.h"
#include <QDebug>
#include <QProcess>
#include <QSysInfo>
#include <mach/mach.h>
#include <sys/sysctl.h>
#include <sys/types.h>

using namespace EasyQJsonEx;

MacxSysInfo::MacxSysInfo() {}

MacxSysInfo::~MacxSysInfo() {}

QString MacxSysInfo::cpuType()
{
    QString strCpuBrand = GetCpuBrandInfo();
    QString strCpuDesc = strCpuBrand;
    int nProcessorCoreCount = GetProcessorCoreCount();
    if (nProcessorCoreCount > 0)
    {
        strCpuDesc = QString("%1 %2Core(s)").arg(strCpuBrand).arg(nProcessorCoreCount);
    }
    return strCpuDesc;
}

QString MacxSysInfo::displayCard()
{
    QString cardDesc = "";

    QString strCommand = "system_profiler SPDisplaysDataType | grep -i \'Chipset Model\'";

    QString strResult = QTerminalInfo::getResultOfString(strCommand).trimmed();
    QStringList list = strResult.split("\n");
    foreach (QString item, list)
    {
        QStringList tempList = item.split(":");
        cardDesc += tempList.last().trimmed() + "\n";
    }

    cardDesc = cardDesc.trimmed();
    return cardDesc;
}

QString MacxSysInfo::memory()
{
    quint64 mem_free;
    QString mem_total;
    QString strMemDesc = "";
    const int nDiv = MEM_DIV;
    const quint64 nTotalPhisicMemInBytes = GetTotalPhysicMemInBytes();
    const int nPhysicMB = nTotalPhisicMemInBytes / nDiv / nDiv;
    //    if (nPhysicMB < 1024)
    //    {
    //        mem_total = QString("%1MB").arg(nPhysicMB);
    //    }
    //    else
    //    {
    //        mem_total = QString("%1GB").arg(nPhysicMB / nDiv);
    //    }

    mach_port_t host_port = mach_host_self();
    mach_msg_type_number_t host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    vm_size_t pageSize;
    vm_statistics_data_t vm_stat;
    host_page_size(host_port, &pageSize);
    if (host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size) != KERN_SUCCESS)
        mem_free = 0;

    mem_free = vm_stat.free_count * pageSize;

    strMemDesc = QString("可用 %1 GB / 共 %2 GB").arg(mem_free / nDiv / nDiv / nDiv).arg(nPhysicMB / nDiv);

    return strMemDesc;
}

QString MacxSysInfo::osVersion()
{
    QString prettyProductName = QSysInfo::prettyProductName();
    QString strOsBit = Is64BitOS() ? "64-bit" : "32-bit";
    QString osDesc = QString("%1 %2").arg(prettyProductName, strOsBit);

    return osDesc;
}

QString MacxSysInfo::screen()
{
    QString screenDesc = "";

    QString strCommand = "system_profiler SPDisplaysDataType | grep -i Resolution";

    const char *str = strCommand.toUtf8().data();
    FILE *fp = popen(str, "r");
    if (nullptr == fp)
        return screenDesc;

    char name[1024] = { 0 };
    while (!feof(fp))
    {
        memset(name, 0, sizeof(name));
        fgets(name, sizeof(name) - 1, fp);
        QString strName(name);
        if (strName.isEmpty())
            continue;
        QStringList list = strName.split(":");

        list = list.last().trimmed().split(" ");

        screenDesc = QString("(%1像素 x %2像素) x %3个").arg(list.first().trimmed()).arg(list.takeAt(2).trimmed()).arg(1);
    }
    fclose(fp);

    return screenDesc;
}

QString MacxSysInfo::disk()
{
    QString diskDesc = "";
    QString freeStr;
    QString capacityStr;
    QString strCommand = "system_profiler SPStorageDataType -json";

    QString strResult = QTerminalInfo::getResultOfString(strCommand);

    EasyQJson jsonHandl;

    QJsonObject obj = jsonHandl.ReadQStringReturnObject(strResult);

    QJsonValue value = obj.value("SPStorageDataType");
    if (value.isArray())
    {
        QJsonObject dataObj = value.toArray().at(0).toObject();
        double totalSize = dataObj.value("size_in_bytes").toDouble() / 1000 / 1000 / 1000;
        double freeSize = dataObj.value("free_space_in_bytes").toDouble() / 1000 / 1000 / 1000;
        capacityStr = QString::asprintf("%.2f", totalSize);
        freeStr = QString::asprintf("%.2f", freeSize);
        diskDesc = QString("可用 %1 GB / 共 %2 GB").arg(freeStr).arg(capacityStr);
    }

    return diskDesc;
}

bool MacxSysInfo::Is64BitOS()
{
    QString strMachine = "";
    GetSysStringInfo("hw.machine", strMachine);
    return strMachine == "x86_64";
}

bool MacxSysInfo::GetSysStringInfo(QString strName, QString &strValue)
{
    size_t buffLen = 0;
    char *pBuff = nullptr;
    int nRet = sysctlbyname(strName.toLocal8Bit().data(), nullptr, &buffLen, nullptr, 0);
    if (nRet == 0)
    {
        pBuff = new char[buffLen];
    }

    if (pBuff == nullptr)
    {
        return false;
    }

    nRet = sysctlbyname(strName.toLocal8Bit().data(), pBuff, &buffLen, nullptr, 0);
    if (nRet == 0)
    {
        strValue = QString(pBuff);
    }

    delete[] pBuff;

    return nRet == 0;
}

QString MacxSysInfo::GetCpuBrandInfo()
{
    QString strBrandInfo = "";
    bool bRet = GetSysStringInfo("machdep.cpu.brand_string", strBrandInfo);
    Q_ASSERT(bRet);
    return strBrandInfo;
}

int MacxSysInfo::GetProcessorCoreCount()
{
    int nCoreCount = 0;
    bool bRet = GetSysInteger32Info("machdep.cpu.core_count", nCoreCount);
    Q_ASSERT(bRet);
    return nCoreCount;
}

bool MacxSysInfo::GetSysInteger32Info(QString strName, int &nValue)
{
    int sysValue = 0;
    size_t dataLen = sizeof(sysValue);
    int nRet = sysctlbyname(strName.toLocal8Bit().data(), &sysValue, &dataLen, nullptr, 0);
    if (nRet == 0)
    {
        nValue = sysValue;
    }
    return nRet == 0;
}

qint64 MacxSysInfo::GetTotalPhysicMemInBytes()
{
    qint64 nMemSize = 0;
    bool bRet = GetSysInteger64Info("hw.memsize", nMemSize);
    Q_ASSERT(bRet);
    return nMemSize;
}

bool MacxSysInfo::GetSysInteger64Info(QString strName, qint64 &nValue)
{
    qint64 sysValue = 0;
    size_t dataLen = sizeof(sysValue);
    int nRet = sysctlbyname(strName.toLocal8Bit().data(), &sysValue, &dataLen, nullptr, 0);
    if (nRet == 0)
    {
        nValue = sysValue;
    }
    return nRet == 0;
}
