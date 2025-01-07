#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QDebug>
#include <QThread>    
#include "mountservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 先尝试取消注册已存在的服务
    QDBusConnection::systemBus().unregisterService("com.deepin.test");

    MountService service;
    QDBusConnection connection = QDBusConnection::systemBus();

    // 确保连接有效
    if (!connection.isConnected()) {
        qCritical() << "Cannot connect to the D-Bus system bus";
        return 1;
    }

    // 注册服务
    if (!connection.registerService("com.deepin.test")) {
        // 如果注册失败，先等待一下再重试一次
        QThread::msleep(500);
        if (!connection.registerService("com.deepin.test")) {
            qCritical() << "Failed to register DBus service:"
                        << connection.lastError().message();
            return 1;
        }
    }

    // 注册对象
    if (!connection.registerObject("/com/deepin/test",
                                 &service,
                                 QDBusConnection::ExportAllSlots)) {
        qCritical() << "Failed to register DBus object:"
                    << connection.lastError().message();
        return 1;
    }

    // 注册成功
    qInfo() << "Mount service started";

    // 确保程序退出时正确注销服务
    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&]() {
        connection.unregisterService("com.deepin.test");
    });

    return a.exec();
}