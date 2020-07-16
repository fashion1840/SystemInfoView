#include "ISystemInfoFactory.h"
#include <QEventLoop>
#include <QHostInfo>
#include <QNetworkAccessManager>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

ISystemInfoFactory::ISystemInfoFactory() {}

QString ISystemInfoFactory::localmachineName()
{
    return QHostInfo::localHostName();
}

QString ISystemInfoFactory::localIP()
{
    QString ip = "";
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

QString ISystemInfoFactory::publicIP()
{
    QString strIp;

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
}

QString ISystemInfoFactory::macAddress()
{
    QString strMac = "";

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

QString ISystemInfoFactory::getHtml(QString url)
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
}
