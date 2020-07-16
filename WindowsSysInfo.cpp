#include "WindowsSysInfo.h"
#include <DXGI.h>
#include <QApplication>
#include <QVector>
#include <Windows.h>

const int GB = 1024 * 1024 * 1024;

#pragma execution_character_set("utf-8")

WindowsSysInfo::WindowsSysInfo() {}

WindowsSysInfo::~WindowsSysInfo() {}

/*QString WindowsSysInfo::localmachineName()
{
    machineName = QHostInfo::localHostName();
    return machineName;
}

QString WindowsSysInfo::localIP()
{
    QList<QNetworkInterface> interFaceList = QNetworkInterface::allInterfaces();
    for (int i = 0; i < interFaceList.size(); i++)
    {
        QNetworkInterface info = interFaceList.at(i);
        if (info.flags().testFlag(QNetworkInterface::IsRunning))
        {
            QList<QNetworkAddressEntry> entryList = info.addressEntries();
            foreach (QNetworkAddressEntry entry, entryList)
            {
                if (QAbstractSocket::IPv4Protocol == entry.ip().protocol() && entry.ip() != QHostAddress::LocalHost
                    && entry.ip().toString().startsWith("192.168."))
                {
                    ip = entry.ip().toString();
                    break;
                }
            }
        }
    }

    return ip;
}

QString WindowsSysInfo::macAddress()
{

    QList<QNetworkInterface> netList = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface item, netList)
    {
        if ((QNetworkInterface::IsUp & item.flags()) && (QNetworkInterface::IsRunning & item.flags()))
        {
            if (strMac.isEmpty() || strMac < item.hardwareAddress())
            {
                strMac = item.hardwareAddress();
            }
        }
    }

    return strMac;
}
QString WindowsSysInfo::publicIP()
{
    QString webCode = getHtml("http://whois.pconline.com.cn/");

    if (!webCode.isEmpty())
    {
        QString web = webCode.replace(" ", "");
        web = web.replace("\r", "");
        web = web.replace("\n", "");
        QStringList list = web.split("<br/>");
        QString tar = list[3];
        QStringList ip = tar.split("=");
        strIp = ip[1];
    }
    else
        strIp = "无法获取公网ip";

    return strIp;
}*/

QString WindowsSysInfo::cpuType()
{
    QSettings *CPU = new QSettings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", QSettings::NativeFormat);
    m_cpuDescribe = CPU->value("ProcessorNameString").toString();
    delete CPU;

    return m_cpuDescribe;
}

QString WindowsSysInfo::displayCard()
{
    // 参数定义
    IDXGIFactory *pFactory;
    IDXGIAdapter *pAdapter;
    QVector<IDXGIAdapter *> vAdapters; // 显卡

    // 显卡的数量
    int iAdapterNum = 0;

    // 创建一个DXGI工厂
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)(&pFactory));
    if (FAILED(hr))
        return nullptr;

    // 枚举适配器
    while (pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND)
    {
        vAdapters.push_back(pAdapter);
        ++iAdapterNum;
    }

    for (size_t i = 0; i < vAdapters.size(); i++)
    {
        // 获取信息
        DXGI_ADAPTER_DESC adapterDesc;
        vAdapters[i]->GetDesc(&adapterDesc);
        std::string desc = WStringToString(adapterDesc.Description);
        if (i == 0)
            dcard = QString::fromStdString(desc);
        else
            dcard = dcard + "\n" + QString::fromStdString(desc);
    }
    vAdapters.clear();

    return dcard;
}

void WindowsSysInfo::displayCard2()
{
    // 参数定义
    IDXGIFactory *pFactory;
    IDXGIAdapter *pAdapter;
    QVector<IDXGIAdapter *> vAdapters; // 显卡

    // 显卡的数量
    int iAdapterNum = 0;

    // 创建一个DXGI工厂
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)(&pFactory));

    if (FAILED(hr))
        return;

    // 枚举适配器
    while (pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND)
    {
        vAdapters.push_back(pAdapter);
        ++iAdapterNum;
    }

    // 信息输出
    qDebug() << "===============获取到" << iAdapterNum << "块显卡===============";
    for (size_t i = 0; i < vAdapters.size(); i++)
    {
        // 获取信息
        DXGI_ADAPTER_DESC adapterDesc;
        vAdapters[i]->GetDesc(&adapterDesc);

        // 输出显卡信息
        qDebug() << "系统视频内存:" << adapterDesc.DedicatedSystemMemory / 1024 / 1024 << "M";
        qDebug() << "专用视频内存:" << adapterDesc.DedicatedVideoMemory / 1024 / 1024 << "M";
        qDebug() << "共享系统内存:" << adapterDesc.SharedSystemMemory / 1024 / 1024 << "M";
        qDebug() << "设备描述:" << QString::fromStdString(WStringToString(adapterDesc.Description));
        qDebug() << "设备ID:" << adapterDesc.DeviceId;
        qDebug() << "PCI ID修正版本:" << adapterDesc.Revision;
        qDebug() << "子系统PIC ID:" << adapterDesc.SubSysId;
        qDebug() << "厂商编号:" << adapterDesc.VendorId;

        // 输出设备
        IDXGIOutput *pOutput;
        QVector<IDXGIOutput *> vOutputs;
        // 输出设备数量
        int iOutputNum = 0;
        while (vAdapters[i]->EnumOutputs(iOutputNum, &pOutput) != DXGI_ERROR_NOT_FOUND)
        {
            vOutputs.push_back(pOutput);
            iOutputNum++;
        }

        qDebug() << "-----------------------------------------";
        qDebug() << "获取到" << iOutputNum << "个显示设备:";

        for (size_t n = 0; n < vOutputs.size(); n++)
        {
            // 获取显示设备信息
            DXGI_OUTPUT_DESC outputDesc;
            vOutputs[n]->GetDesc(&outputDesc);

            // 获取设备支持
            UINT uModeNum = 0;
            DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
            UINT flags = DXGI_ENUM_MODES_INTERLACED;

            vOutputs[n]->GetDisplayModeList(format, flags, &uModeNum, 0);
            DXGI_MODE_DESC *pModeDescs = new DXGI_MODE_DESC[uModeNum];
            vOutputs[n]->GetDisplayModeList(format, flags, &uModeNum, pModeDescs);

            qDebug() << "显示设备名称:" << outputDesc.DeviceName;
            qDebug() << "显示设备当前分辨率:" << outputDesc.DesktopCoordinates.right - outputDesc.DesktopCoordinates.left << "*"
                     << outputDesc.DesktopCoordinates.bottom - outputDesc.DesktopCoordinates.top;

            // 所支持的分辨率信息
            qDebug() << "分辨率信息:";
            for (UINT m = 0; m < uModeNum; m++)
            {
                qDebug() << "== 分辨率:" << pModeDescs[m].Width << "*" << pModeDescs[m].Height << "     刷新率"
                         << (pModeDescs[m].RefreshRate.Numerator) / (pModeDescs[m].RefreshRate.Denominator);
            }
        }
        vOutputs.clear();
    }
    vAdapters.clear();
}

QString WindowsSysInfo::displayCard3()
{
    QSettings *DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\services\\nvlddmkm\\Device0", QSettings::NativeFormat);
    QString type = DCard->value("Device Description").toString();
    delete DCard;

    QString dType = type.simplified();
    if (!dType.isEmpty())
        dcard = dType;

    DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\igfx\\Device0", QSettings::NativeFormat);
    type = DCard->value("Device Description").toString();
    delete DCard;

    dType = type.simplified();
    if (!dType.isEmpty())
        dcard = dcard + "\n" + dType;

    DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\amdkmdap\\Device0", QSettings::NativeFormat);
    type = DCard->value("Device Description").toString();
    delete DCard;

    dType = type.simplified();
    if (!dType.isEmpty())
        dcard = dcard + "\n" + dType;

    dcard = dcard.simplified();

    return dcard;
}

QString WindowsSysInfo::memory()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    m_totalMem = statex.ullTotalPhys * 1.0 / GB;
    m_freeMem = statex.ullAvailPhys * 1.0 / GB;

    m_memDescribe = QString("可用 %1 GB / 共 %2 GB").arg(QString::asprintf("%.2f", m_freeMem)).arg(QString::asprintf("%.2f", m_totalMem));

    return m_memDescribe;
}

QString WindowsSysInfo::osVersion()
{
    typedef BOOL(WINAPI * LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);
    LPFN_ISWOW64PROCESS fnIsWow64Process;
    BOOL bIsWow64 = FALSE;
    fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");
    if (NULL != fnIsWow64Process)
    {
        fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
    }
    QString sysBit = "unknown";
    if (bIsWow64)
        sysBit = "64位";
    else
        sysBit = "32位";

    m_osDescirbe = QSysInfo::prettyProductName() + " " + sysBit;
    return m_osDescirbe;
}

QString WindowsSysInfo::screen()
{
    m_screenDescribe = "";
    QList<QSize> screenSizeList;
    QList<int> screenCountList;

    for (int i = 0; i < QApplication::desktop()->screenCount(); i++)
    {
        QRect screenRect = QApplication::desktop()->screenGeometry(i);
        QSize size(screenRect.width(), screenRect.height());

        bool bExist = false;
        for (int j = 0; j < screenSizeList.length(); j++)
        {
            QSize existSize = screenSizeList.at(j);
            if (size == existSize)
            {
                screenCountList[j]++;
                bExist = true;
                break;
            }
        }

        if (!bExist)
        {
            screenSizeList.append(size);
            screenCountList.append(1);
        }
    }

    m_maxScreenSize = screenSizeList.at(0);
    for (int i = 0; i < screenSizeList.length(); i++)
    {
        int width = screenSizeList.at(i).width();
        int height = screenSizeList.at(i).height();

        if (width > m_maxScreenSize.width() && height > m_maxScreenSize.height())
            m_maxScreenSize = screenSizeList.at(i);

        m_screenDescribe += QString("(%1像素 x %2像素) x %3个").arg(width).arg(height).arg(screenCountList.at(i));
        if (i != screenSizeList.length() - 1)
            m_screenDescribe += "、 ";
    }

    return m_screenDescribe;
}

QString WindowsSysInfo::disk()
{
    m_diskDescribe = "";
    QFileInfoList list = QDir::drives();
    foreach (QFileInfo dir, list)
    {
        QString dirName = dir.absolutePath();
        dirName.remove("/");
        LPCWSTR lpcwstrDriver = (LPCWSTR)dirName.utf16();
        ULARGE_INTEGER liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;
        if (GetDiskFreeSpaceEx(lpcwstrDriver, &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes))
        {
            QString free = QString::number((double)liTotalFreeBytes.QuadPart / GB, 'f', 1);
            free += "G";
            QString all = QString::number((double)liTotalBytes.QuadPart / GB, 'f', 1);
            all += "G";

            QString str = QString("%1 %2/%3  ").arg(dirName, free, all);
            m_diskDescribe += str;

            double freeMem = (double)liTotalFreeBytes.QuadPart / GB;

            if (freeMem > m_maxFreeDisk)
                m_maxFreeDisk = freeMem;
        }
    }

    return m_diskDescribe;
}

void WindowsSysInfo::checkOffice()
{
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\excel.exe", QSettings::NativeFormat);
    QString path = settings.value("Path").toString();
    if (!path.isEmpty())
    {
        QSettings versionSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Classes\\Excel.Application\\CurVer", QSettings::NativeFormat);
        QString version = versionSettings.value(".").toString();
        if (!version.isEmpty())
        {
            version = version.split(".").last();
            int versionNum = version.toInt();
            switch (versionNum)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    m_officeDecsribe = "Office 95以前版本";
                    break;
                case 6:
                    m_officeDecsribe = "Office 95";
                    break;
                case 8:
                    m_officeDecsribe = "Office 97";
                    break;
                case 9:
                    m_officeDecsribe = "Office 2000";
                    break;
                case 10:
                    m_officeDecsribe = "Office XP";
                    break;
                case 11:
                    m_officeDecsribe = "Office 2003";
                    break;
                case 12:
                    m_officeDecsribe = "Office 2007";
                    break;
                case 13:
                case 14:
                    m_officeDecsribe = "Office 2010";
                    break;
                case 15:
                    m_officeDecsribe = "Office 2013";
                    break;
                case 16:
                case 17:
                case 18:
                case 19:
                    m_officeDecsribe = "Office 2013以后版本";
                    break;
                default:
                    break;
            }

            if (versionNum >= 13) //office 2010
            {
                describe = "已安装Office 版本：" + m_officeDecsribe;
            }
            else
            {
                describe = "建议安装Microsoft Offce2010以上版本。";
            }
        }
        else
        {
            describe = "建议安装Microsoft Offce2010以上版本。";
        }
    }
    else
    {
        describe = "建议安装Microsoft Offce2010以上版本。";
    }
}

bool WindowsSysInfo::netWorkLive()
{
    //能接通百度IP说明可以通外网
    QTcpSocket tcpClient;
    tcpClient.abort();
    tcpClient.connectToHost("202.108.22.5", 80);

    //100毫秒没有连接上则判断不在线
    return tcpClient.waitForConnected(100);
}

/*QString WindowsSysInfo::getHtml(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);

    connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    connect(timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));

    timer->start(300);
    eventLoop.exec();
    responseData = reply->readAll();

    delete timer;

    return QString(responseData);
}*/

std::string WindowsSysInfo::WStringToString(const std::wstring &wstr)
{
    std::string str(wstr.length(), ' ');
    std::copy(wstr.begin(), wstr.end(), str.begin());
    return str;
}
