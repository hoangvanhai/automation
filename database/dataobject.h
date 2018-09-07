#ifndef DATAOBJECT_H
#define DATAOBJECT_H
#include<QSqlDatabase>
#include<QMetaObject>
#include<QMetaProperty>
#include<QMetaClassInfo>
#include<QSqlQuery>
#include<QString>
#include<QHash>
#include<QList>
#include<QObject>
#include<QDebug>
#include<type_name.h>
#include<QVariant>
#include <QSqlError>
#include<QSqlRecord>
class DataObject: public QObject
{
public:
    DataObject();
    ~DataObject();
    class sortRecord
    {
    public:
        sortRecord(const QString& field):_field(field){}
        bool operator()(const QSqlRecord& x, const QSqlRecord& y)
        {
            QVariant xValue,yValue;
            xValue=x.value((_field));
            yValue=y.value((_field));
            return xValue < yValue;
        }
        ~sortRecord(){}
     private:
        QString _field;
    };

   /*
       Brief: Tao bang trong SQL SERVER
       Parameter: tableName: ten cua bang dc tao ra
       CHECK: CHECKED AND PASSED
   */
   bool createTable(QString tableName);
   /*
       Brief: ghi du lieu vao bang trogn  SQL SERVER
       Parameter: tableName: ten cua bang can ghi du lieu vao
   */
   bool insertData(QString tableName);
   /*
       Brief: Xoa bo bang trong database
       Parameter: tableName: ten cua bang can xoa
   */
   bool dropTable(QString tableName);
   /*
       Brief: Xoa bo tat ca du lieu trong bang
       Parameter: tableName: ten cua bang can xoa du lieu
   */
   bool deleteDataInTable(QString tableName);
   /*
        Brief: tao list cac hang cua mot bang.
    */
   QList<QSqlRecord> listDataOfTable(QString tableName);
   /*
    * Brief: xap xep cac hang trong table theo mot tieu chi SAP XEP TU BE DEN LON
    * Parameter: tableName: ten cua bang can sap xep
    * field: ten truong chi tieu
    * Result: tra ve 1 list ca record duoc sap xep
    * PASSED
    */
   QList<QSqlRecord> sortAllTable(QString tableName,QString Field);
   /*
    * Brief: xap xep cac record trong list theo mot tieu chi SAP XEP TU BE DEN LON
    * Parameter: list danh sach cac record
    * field: ten truong chi tieu
    * PASED
    */
  int sortListRecord(QList<QSqlRecord>& list ,QString field);

   /*
    * Brief: Find cac row thoa man dieu kien
    *PASSED
    *
    */
   QList<QSqlRecord> findObject(QString tableName,QString condition);
   /*
    * Brief: delete 1 object trong bang table name
    *  object.deleteAnObject( +tableName+) xoa this object
    *
    */
   bool deleteAnObject(QString tableName);

   /*
    * Brief: delte cac row thoa man dieu kien
    *Parameter tableName: ten cua bang can xoa
    *
    */
   bool deleteObject(QString tableName,QString condition);
private:
   /*
       Brief: Chuyen kieu du lieu C++ thuong thanh kieu du lieu trong SQL Server
       Parameter: tra ve mot bang tra cuu QHash
       CHECK: CHECKED AND PASSED
   */
    QHash<QString,QString> createTableType();
    /*
        Brief: chuyen doi kieu du lieu cua cac bien trong C++ tuong ung thanh cac kieu du lieu trong SQL luu vao trong list
        Parameter: gia tri tra ve la 1 list cac object Type_Name ( bao gom kieu du lieu va ten cua bien)
        CHECK: CHECKED AND PASSED
    */
    QList<Type_Name> createProperty();
};

#endif // DATAOBJECT_H
