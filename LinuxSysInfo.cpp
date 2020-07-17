#include "LinuxSysInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int GB = 1024 * 1024 * 1024;

LinuxSysInfo::LinuxSysInfo() {}

LinuxSysInfo::~LinuxSysInfo() {}

QString LinuxSysInfo::cpuType()
{
    m_cpuDescribe = "";
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (nullptr == fp)
        return m_cpuDescribe;

    char szTest[1000] = { 0 };
    // read file line by line
    while (!feof(fp))
    {
        memset(szTest, 0, sizeof(szTest));
        fgets(szTest, sizeof(szTest) - 1, fp);
        QString str(szTest);
        if (str.contains("model name"))
        {
            QStringList list = str.split(":");
            m_cpuDescribe = list.at(1);
            break;
        }
    }
    fclose(fp);

    return m_cpuDescribe.trimmed();
}

QString LinuxSysInfo::displayCard() {}

QString LinuxSysInfo::memory()
{
    bool bTotal = false;
    bool bFree = false;
    m_memDescribe = "";

    FILE *fp = fopen("/proc/meminfo", "r");
    if (nullptr == fp)
        return m_memDescribe;

    char szTest[1000] = { 0 };
    while (!feof(fp))
    {
        memset(szTest, 0, sizeof(szTest));
        fgets(szTest, sizeof(szTest) - 1, fp);
        QString str(szTest);
        if (str.contains("MemTotal"))
        {
            m_totalMem = getValueByString(szTest);
            bTotal = true;
        }
        else if (str.contains("MemFree"))
        {
            m_freeMem = getValueByString(szTest);
            bFree = true;
        }

        if (bTotal && bFree)
        {
            m_memDescribe = QString("可用 %1 GB / 共 %2 GB").arg(QString::asprintf("%.2f", m_freeMem)).arg(QString::asprintf("%.2f", m_totalMem));
            break;
        }
    }
    fclose(fp);

    return m_memDescribe;
}

QString LinuxSysInfo::osVersion()
{
    m_osDescirbe = "";
    FILE *fp = fopen("/proc/version_signature", "r");
    if (nullptr == fp)
        return m_osDescirbe;

    char szTest[1000] = { 0 };
    while (!feof(fp))
    {
        memset(szTest, 0, sizeof(szTest));
        fgets(szTest, sizeof(szTest) - 1, fp); // leave out \n
        m_osDescirbe = QString(szTest);
        break;
    }
    fclose(fp);

    return m_osDescirbe;
}

QString LinuxSysInfo::screen() {}

QString LinuxSysInfo::disk() {}

double LinuxSysInfo::getValueByString(char *buff)
{
    MEM_OCCUPY *mem = new MEM_OCCUPY;
    sscanf(buff, "%s %lu %s", mem->name, &mem->total, mem->unit_name);
    double total = mem->total * 1.0 / GB;
    delete mem;
    return total;
}
