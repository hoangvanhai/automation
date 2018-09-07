#include "databaseconnection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseConnection::DatabaseConnection(const QString &server,
                                       const QString &driver,
                                       const QString &user,
                                       const QString &password,
                                       const QString &databaseName,
                                       bool trustedConnection)
{
    m_database = QSqlDatabase::addDatabase("QODBC");
    m_server=server;
    m_driver=driver;
    m_user = user;
    m_password = password;
    m_databaseName = databaseName;
    m_trustedConnection = trustedConnection;
}

bool DatabaseConnection::openDatabase()
{
    QString error;
    m_database.setDatabaseName(QString("DRIVER={%1};SERVER=%2;"
                                       "DATABASE=%3;UID=%4;"
                                       "PWD=%5;")//Trusted_Connection=%6;")
                               .arg(m_driver)
                               .arg(m_server)
                               .arg(m_databaseName)
                               .arg(m_user)
                               .arg(m_password));
                              // .arg(m_trustedConnection ? "Yes" : "No"));
    qDebug()<<" OPEN DATA BASE";
    if(!m_database.open()) {

            error = m_database.lastError().text();
            qDebug()<<" CAN'T OPEN DATABASE";
            qDebug()<< error;

        return false;
    }


//    qDebug() << "drivers name: " << m_database.drivers();
//    qDebug() << "driver name: " << m_database.driver();
   // qDebug() << "connectionName name: " << m_database.connectionName();
   // qDebug() << "connectionNames name: " << m_database.connectionNames();
   // qDebug() << "connectOptions name: " << m_database.connectOptions();
   // qDebug() << "databaseName name: " << m_database.databaseName();
   // qDebug() << "user name: " << m_database.userName();
   // qDebug() << "password: " << m_database.password();
   // qDebug() << "host name: " << m_database.hostName();
   // qDebug() << "port: " << m_database.port();
   // qDebug() << "Table" << m_database.tables();

    return true;

}

