#include "LinuxSysInfo.h"
#include "CDiskInfo.h"
#include <fcntl.h>
#include <linux/fb.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/types.h>
#include <xcb/xcb.h>

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
            m_totalMem = getValueByString(str);
            bTotal = true;
        }
        else if (str.contains("MemFree"))
        {
            m_freeMem = getValueByString(str);
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

QString LinuxSysInfo::screen()
{
    QString screenInfo = "";

#if 1
    int i, screenNum;
    xcb_connection_t *connection = xcb_connect(nullptr, &screenNum);

    /* Get the screen whose number is screenNum */
    const xcb_setup_t *setup = xcb_get_setup(connection);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);

    // we want the screen at index screenNum of the iterator
    for (i = 0; i < screenNum; ++i)
    {
        xcb_screen_next(&iter);
    }

    xcb_screen_t *screen = iter.data;

    /* report */

    qDebug("Informations of screen %ld:\n", screen->root);
    qDebug("  width.........: %d\n", screen->width_in_pixels);
    qDebug("  height........: %d\n", screen->height_in_pixels);
    qDebug("  white pixel...: %ld\n", screen->white_pixel);
    qDebug("  black pixel...: %ld\n", screen->black_pixel);
    screenInfo = QString("%1像素 x %2像素) x %3个").arg(screen->width_in_pixels).arg(screen->height_in_pixels).arg(1);
#else
    int w, h, bpp;
    int *fbmem;

    int fd;
    struct fb_var_screeninfo fb_var;
    fd = open("/dev/fb0", O_RDWR);
    ioctl(fd, FBIOGET_VSCREENINFO, &fb_var);
    w = fb_var.xres;
    h = fb_var.yres;
    bpp = fb_var.bits_per_pixel;
    printf("Framebuffer %d*%d-%dbpp\n", w, h, bpp);
    screenInfo = QString("%1像素 x %2像素) x %3个").arg(w).arg(h).arg(1);
    fbmem = mmap(0, w * h * bpp / 8, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

#endif

    return screenInfo;
}

QString LinuxSysInfo::disk()
{
    m_diskDescribe = "";
#if 0
    struct statfs diskInfo;
    statfs("/", &diskInfo);
    unsigned long long totalBlocks = diskInfo.f_bsize;
    unsigned long long freeDisk = diskInfo.f_bfree * totalBlocks;
    unsigned long long totalDisk = diskInfo.f_bsize * totalBlocks;

    m_diskDescribe = QString("%1G / %2G").arg(freeDisk).arg();
#else
    CDiskInfo diskInfo("/");
    m_diskDescribe = QString("%1G / %2G").arg(diskInfo.getLeftSize()).arg(diskInfo.getTotalSize());
#endif

    return m_diskDescribe;
}

double LinuxSysInfo::getValueByString(char *buff)
{
    MEM_OCCUPY *mem = new MEM_OCCUPY;
    sscanf(buff, "%s %lu %s", mem->name, &mem->total, mem->unit_name);
    double total = mem->total * 1.0 / GB;
    delete mem;
    return total;
}
