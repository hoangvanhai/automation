#ifndef TYPE_NAME_H
#define TYPE_NAME_H
#include"macro.h"
#include<QList>
#include<QString>
#include<QObject>
#include<QVariant>


class Type_Name
{
public:
    Type_Name(){}
    ~Type_Name(){}
    void setName(QString nametmp)
    {
        name= nametmp;
    }
    void setType(QString typetmp)
    {
        type= typetmp;
    }
    QString getName()
    {
        return name;
    }
    QString getType()
    {
        return type;
    }

private:
    QString name, type;
};

#endif // TYPE_NAME_H
