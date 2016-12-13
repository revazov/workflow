#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QMetaClassInfo>
#include <QDebug>

class UserModel : public QSqlTableModel
{
    Q_OBJECT
    Q_CLASSINFO("author", "Zaur Kadokhov")
    Q_CLASSINFO("email", "kadokhovzaur@yandex.ru")
public:
    struct User{
        unsigned int id = 0;
        QString fName = "";
        QString lName = "";
    };

    UserModel(QSqlDatabase &db, QObject *parent = Q_NULLPTR);
    void addUser(const User &user);
    bool isDatabaseReady();

signals:
    void error(QString);
public slots:

};

#endif // USERMODEL_H
