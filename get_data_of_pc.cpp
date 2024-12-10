#include <QString>
#include <QHostInfo>

QString getSystemModel()
{
    return QHostInfo::localHostName();
}
