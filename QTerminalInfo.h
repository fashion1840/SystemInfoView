#ifndef QTERMINALINFO_H
#define QTERMINALINFO_H

#include <QProcess>

enum ResultTypeEnum
{
    TYPE_STRING = 0,
    TYPE_FILE
};

class QTerminalInfo
{
public:
    static QString getResultOfString(const QString &cmd, ResultTypeEnum type = TYPE_STRING)
    {
        QString dosRet;
        QProcess process;
        QStringList arguments;
        arguments << "-c" << cmd;
        if (type == TYPE_FILE)
        {
            dosRet = "ouptputfile.txt";
            process.setStandardOutputFile(dosRet);
        }
        process.start("/bin/bash", arguments);
        process.waitForFinished();

        if (type == TYPE_STRING)
            dosRet = QString::fromLocal8Bit(process.readAllStandardOutput());

        return dosRet;
    }
};

#endif // QTERMINALINFO_H
