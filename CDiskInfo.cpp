#include "CDiskInfo.h"
extern "C"
{
#include <sys/vfs.h>
}
#include <string>

CDiskInfo::CDiskInfo(const std::string &_path)
    : disk_total_capacity(0), disk_used_capacity(0), disk_free_capacity(0), disk_format(DISK_FORMAT_UNKNOW), path(_path)
{
    struct statfs buf;
    int i = statfs(path.c_str(), &buf);
    if (i < 0)
    {
        //printf("get disk infomation faild\n");
    }
    else
    {
        switch (buf.f_type)
        {
            case 0x4d44:
                disk_format = DISK_FORMAT_FAT;
                break;
            case 0x5346544e:
            case 0X65735546:
                disk_format = DISK_FORMAT_NTFS;
                break;
            case 0xEF53:
            case 0xEF51:
                disk_format = DISK_FORMAT_EXT2;
                break;
            default:
                disk_format = DISK_FORMAT_UNKNOW;
                break;
        }
        disk_total_capacity = (((long long)buf.f_bsize * (long long)buf.f_blocks));
        disk_free_capacity = (((long long)buf.f_bsize * (long long)buf.f_bfree));
        disk_used_capacity = disk_total_capacity - disk_free_capacity;
    }
}

CDiskInfo::~CDiskInfo() {}

void CDiskInfo::refreshInfo()
{
    struct statfs buf;
    int i = statfs(path.c_str(), &buf);
    if (i < 0)
    {
        //printf("refresh get disk infomation faild\n");
        return;
    }
    switch (buf.f_type)
    {
        case 0x4d44:
            disk_format = DISK_FORMAT_FAT;
            break;
        case 0x5346544e:
        case 0X65735546:
            disk_format = DISK_FORMAT_NTFS;
            break;
        case 0xEF53:
        case 0xEF51:
            disk_format = DISK_FORMAT_EXT2;
            break;
        default:
            disk_format = DISK_FORMAT_UNKNOW;
            break;
    }

    disk_total_capacity = (((long long)buf.f_bsize * (long long)buf.f_blocks));
    disk_free_capacity = (((long long)buf.f_bsize * (long long)buf.f_bfree));
    disk_used_capacity = disk_total_capacity - disk_free_capacity;
}

long long CDiskInfo::getTotalSize()
{
    return disk_total_capacity;
}

long long CDiskInfo::getUsedSize()
{
    return disk_used_capacity;
}

long long CDiskInfo::getLeftSize()
{
    return disk_free_capacity;
}

DISK_FORMAT CDiskInfo::getDiskFormat()
{
    return disk_format;
}
