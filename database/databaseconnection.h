#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>
#include<QString>

class DatabaseConnection
{
public:
    DatabaseConnection(const QString &server,
                       const QString &driver,
                       const QString &user,
                       const QString &password,
                       const QString &databaseName,
                       bool trustedConnection = true);

    bool openDatabase();

private:
    QSqlDatabase m_database;
    QString m_server;
    QString m_driver;
    QString m_user;
    QString m_password;
    QString m_databaseName;
    bool    m_trustedConnection;
};

#endif // DATABASECONNECTION_H
