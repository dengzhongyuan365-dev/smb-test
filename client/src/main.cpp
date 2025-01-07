#include <QCoreApplication>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 创建DBus接口
    QDBusInterface interface("com.deepin.test",
                           "/com/deepin/test",
                           "com.deepin.test.Mount",
                           QDBusConnection::systemBus());

    if (!interface.isValid()) {
        qCritical() << "Failed to create interface:"
                    << QDBusConnection::systemBus().lastError().message();
        return 1;
    }

    // 调用挂载方法
    QDBusReply<bool> reply = interface.call("mount");
    if (!reply.isValid()) {
        qCritical() << "Call failed:" << reply.error().message();
        return 1;
    }

    qInfo() << "Mount" << (reply.value() ? "successful" : "failed");
    return 0;
}