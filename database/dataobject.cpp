#include "dataobject.h"

DataObject::DataObject()
{

}

DataObject::~DataObject()
{

}

/*
    Brief: Chuyen kieu du lieu C++ thuong thanh kieu du lieu trong SQL Server
    Parameter: tra ve mot bang tra cuu QHash
*/
QHash<QString,QString> DataObject::createTableType()
{
    QHash<QString,QString> tableType;
    tableType.insert("int","int");
    tableType.insert("qint64","bigint");
    tableType.insert("long","bigint");
    tableType.insert("qlonglong","bigint");
    tableType.insert("unsigned int","int");
    tableType.insert("long long","bigint");
    tableType.insert("float","real");
    tableType.insert("double","real");
    tableType.insert("char","nchar(1)");
    tableType.insert("Qchar","nchar(1)");
    tableType.insert("QDate","date");
    tableType.insert("QTime","time");
    tableType.insert("QDatetime","datetime");
    tableType.insert("QString","ntext");
    tableType.insert("QDateTime","datetime");
    return tableType;
}
/*
    Brief: chuyen doi kieu du lieu cua cac bien trong C++ tuong ung thanh cac kieu du lieu trong SQL luu vao trong list
    Parameter: gia tri tra ve la 1 list cac object Type_Name ( bao gom kieu du lieu va ten cua bien)
*/
QList<Type_Name> DataObject::createProperty()
{
    QList<Type_Name> list;
    QHash<QString,QString> tableType=createTableType();
    for (int i=1;i< metaObject()->propertyCount();i++)// for from 1 de bo property objectname cua class QObject
    {
        Type_Name tmp;
        QString typetmp;
        tmp.setName(metaObject()->property(i).name());
        // qDebug()<<tmp.getName()<<"---"<<i<<metaObject()->propertyCount();
        typetmp = (metaObject()->property(i).typeName());
        // qDebug()<<tmp.getType()<<"---"<<i;
        if (tableType.contains(typetmp))
        {
            tmp.setType(tableType.value(typetmp));
           // qDebug()<<"have key "<<typetmp;
        }
        else
            tmp.setType("ntext");
        list.push_back(tmp);
    }
    return list;
}
/*
     Brief: tao list cac hang cua mot bang.
 */
QList<QSqlRecord> DataObject::listDataOfTable(QString tableName)
{
    if(!tableName.contains("tbl"))
    {
        tableName.prepend("tbl");
    }
    QList<QSqlRecord> list;
    QString command=QString("select * from %1").arg(tableName);
    QSqlQuery query(command);
    while(query.next())
    {
        QSqlRecord rec= query.record();
        for(int i=0;i< rec.count();i++)
        {
            rec.setValue(i,query.value(i));
           // qDebug()<<" value = "<< query.value(i);
        }
        list.push_back(rec);
       // qDebug()<<"next record \n";
    }
    return list;

}
/*
    Brief: Tao bang trong SQL SERVER
    Parameter: tableName: ten cua bang dc tao ra
*/
 bool DataObject::createTable(QString tableName)
 {
     if(!tableName.contains("tbl"))
     {
         tableName.prepend("tbl");
     }
     QList<Type_Name> list= createProperty();
     QSqlQuery query;
     QString command = QString("create table %1 (").arg(tableName);
     for(QList<Type_Name>::const_iterator it = list.cbegin();it!= list.cend();++it)
     {
        Type_Name tmp;
        tmp=*it;
        command+= QString(" %1 %2,")
                .arg(tmp.getName())
                .arg(tmp.getType());
     }
        command.resize(command.size()-1);
        command+=")";// complete command
       // qDebug()<<command;
        if(query.exec(command))
            return true;
        else
            return false;
}
 /*
     Brief: Ghep cac chuoi thanh cau lenh command  trong SQL server de tao bang
     Parameter: tableName ten cua bang.
 */
 bool DataObject :: insertData(QString tableName)
 {
     if(!tableName.contains("tbl"))
     {
         tableName.prepend("tbl");
     }
     QSqlQuery query;
     QList<Type_Name> list= createProperty();
     QString command = QString("insert into %1 (")
             .arg(tableName);
     for(QList<Type_Name>::const_iterator it = list.cbegin();it!= list.cend();++it)
     {
         Type_Name tmp;
         tmp=*it;
         command+=QString(" %1,").arg(tmp.getName());
     }
     command.resize(command.size()-1);
     command+=(") values (");
     for(QList<Type_Name>::const_iterator it = list.cbegin();it!= list.cend();++it)
     {
         Type_Name tmp;
         tmp=*it;
         QString nametmp=tmp.getName();
         if(this->property(qPrintable(nametmp)).isNull())
         {
             command+= " NULL,";
             continue;
         }
         if(tmp.getType()=="ntext")//>> kieu chu cai
         {
             command+=QString(" N'%1',").arg(property(qPrintable(nametmp)).toString());
         }
         else
             if((tmp.getType()=="real")|| (tmp.getType()=="int")||(tmp.getType()=="bigint"))//>> kieu so
             {
               command+=QString(" %1,").arg(property(qPrintable(nametmp)).toString());
             }
            else
             {
               command+=QString(" '%1',").arg(property(qPrintable(nametmp)).toString());//>> cac kieu con lai: date ,time...
             }

     }
     command.resize(command.size()-1);//>> loai bo ky tu , cua gia tri cuoi cung
     command+=")";
    // qDebug()<<command;
     if(query.exec(command))
         return true;
     else
     {
         qDebug()<<"cant insert ";
         return false;
     }
 }
 /*
     Brief: Xoa bo bang trong database
     Parameter: tableName: ten cua bang can xoa
 */
 bool DataObject::dropTable(QString tableName)
 {
     if(!tableName.contains("tbl"))
     {
         tableName.prepend("tbl");
     }
     QSqlQuery query;
     QString command = "drop table " + tableName;
     if(query.exec(command))
         return true;
     else
         return false;

 }
 /*
     Brief: Xoa bo tat ca du lieu trong bang
     Parameter: tableName: ten cua bang can xoa du lieu
 */
 bool DataObject::deleteDataInTable(QString tableName)
 {
     if(!tableName.contains("tbl"))
     {
         tableName.prepend("tbl");
     }
     QSqlQuery query;
     QString command = "delete " + tableName;
     if(query.exec(command))
         return true;
     else
         return false;
 }
 /*
  * Brief: xap xep cac hang trong table theo mot tieu chi SAP XEP TU BE DEN LON
  * Parameter: tableName: ten cua bang can sap xep
  * field: ten truong chi tieu
  */
 QList<QSqlRecord> DataObject::sortAllTable(QString tableName,QString field)
 {
     if(!tableName.contains("tbl"))
     {
         tableName.prepend("tbl");
     }
    QList<QSqlRecord> list;
    QSqlQuery query(QString("select %1 from %2").arg(field).arg(tableName));
    if(query.next())
    {
    // qDebug()<< " have field " << field << "in "<< tableName;
    }
    else
    {
        qDebug()<<" dotn have "<< field << "in "<< tableName;
        return list;
    }
    list= listDataOfTable(tableName);
    sortRecord comparator(field);
    qSort(list.begin(),list.end(),comparator);
    return list;
 }
 /*
  * Brief: xap xep cac record trong list theo mot tieu chi SAP XEP TU BE DEN LON
  * Parameter: list danh sach cac record
  * field: ten truong chi tieu
  */
 int DataObject::sortListRecord(QList<QSqlRecord>& list ,QString field)
 {
     QList<QSqlRecord>::const_iterator ite=list.cbegin();
     QSqlRecord rec=*ite;
     if( !rec.contains(field))
         return -1;//>> khong ton tai truong field trong record
     sortRecord comparator(field);
     qSort(list.begin(),list.end(),comparator);
     return 1;
 }
 /*
  * Brief: Find cac row thoa man dieu kien
  *
  *
  */
 QList<QSqlRecord> DataObject::findObject(QString tableName,QString condition)
 {
     if(!tableName.contains("tbl"))
     {
         tableName.prepend("tbl");
     }
     QList<QSqlRecord> list;
     if (condition.contains("tbl"))
     {
         condition.resize(0);
         qDebug()<<"have tbl in condition injection attack";
     }
     QString command =QString("select * from %1 where %2").arg(tableName).arg(condition);
    // qDebug()<<command;
     QSqlQuery query(command);
    while (query.next())
    {
        QSqlRecord rec= query.record();
        for(int i=0;i< rec.count();i++)
        {
            rec.setValue(i,query.value(i));
            //qDebug()<<" value = "<< query.value(i);
        }
        list.push_back(rec);
    }
    return list;
 }
 /*
  * Brief: delete cac row thoa man dieu kien
  *
  *
  */
 bool DataObject::deleteObject(QString tableName,QString condition)
 {

     if(!tableName.contains("tbl"))
     {
         tableName.prepend("tbl");
     }
     QList<QSqlRecord> list;
     if (condition.contains("tbl"))
     {
         condition.resize(0);
         qDebug()<<"have tbl in condition may be have injection attack";
     }
     QString command =QString("delete from %1 where %2").arg(tableName).arg(condition);
     QSqlQuery query;
     if(query.exec(command))
         return true;
     else
         return false;
 }
 bool DataObject::deleteAnObject(QString tableName)
 {
     if(!tableName.contains("tbl"))
     {
         tableName.prepend("tbl");
     }
     QSqlQuery query;
     QList<Type_Name> lstProperty = this->createProperty();
     QString command=QString("delete from %1 where ").arg(tableName);
     for(QList<Type_Name>::const_iterator it=lstProperty.cbegin();it!=lstProperty.cend();++it)
     {
         Type_Name tmp;
         tmp=*it;
         if((tmp.getType()=="int") || (tmp.getType()=="bigint") || (tmp.getType()=="real") )
         {
             command+= QString("%1= %2 and ")
                     .arg(tmp.getName())
                     .arg(property(qPrintable(tmp.getName())).toString());
         }
         else
         {
             if(tmp.getType()=="ntext")
             {
                 command+= QString("convert(nvarchar(max),%1)=N'%2' and ")
                         .arg(tmp.getName())
                         .arg(property(qPrintable(tmp.getName())).toString());
             }
             else
             {
                 command+= QString("%1='%2' and ")
                         .arg(tmp.getName())
                         .arg(property(qPrintable(tmp.getName())).toString());
             }
         }
     }
     command.resize(command.size()-4);// xoa dau cach va chu "and" cuoi cung
     //qDebug()<< command;
     if(query.exec(command))
         return true;
     else
         return false;
 }
