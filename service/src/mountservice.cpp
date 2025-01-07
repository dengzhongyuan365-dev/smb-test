#include "mountservice.h"
#include <QDir>
#include <QDebug>
#include <sys/mount.h>

MountService::MountService(QObject *parent) : QObject(parent)
{
}

MountService::~MountService() = default;

bool MountService::mount()
{
    const char* source = "//10.8.11.70/share";
    const char* target = "/media/damn/test";
    const char* options = "username=goddamn,password=123,vers=3.0";

    // 创建挂载点
    if (!createMountPoint(target)) {
        qWarning() << "Failed to create mount point";
        return false;
    }

    // 执行挂载
    if (::mount(source, target, "cifs", 0, options) != 0) {
        qWarning() << "Mount failed:" << strerror(errno);
        return false;
    }

    qInfo() << "Mount successful";
    return true;
}

bool MountService::createMountPoint(const QString &path)
{
    QDir dir;
    if (!dir.exists(path)) {
        return dir.mkpath(path);
    }
    return true;
}