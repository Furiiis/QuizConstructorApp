#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QObject>

class Tag
{
//    Q_OBJECT

public:
    int id;
    QString name_;
};

Q_DECLARE_METATYPE(Tag)

#endif // TAG_H
