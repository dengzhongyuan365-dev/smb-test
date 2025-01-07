#ifndef MOUNTSERVICE_H
#define MOUNTSERVICE_H

#include <QObject>
#include <QDBusContext>

class MountService : public QObject, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.deepin.test.Mount")

public:
    explicit MountService(QObject *parent = nullptr);
    ~MountService() override;

public slots:
    bool mount();

private:
    bool createMountPoint(const QString &path);
};

#endif // MOUNTSERVICE_H