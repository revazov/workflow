#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMetaClassInfo>
#include <QDebug>

struct User{
    unsigned int id = 0;
    QString fName = "";
    QString lName = "";
};

class UserModel : public QSqlTableModel
{
    Q_OBJECT
    Q_CLASSINFO("author", "Zaur Kadokhov")
    Q_CLASSINFO("email", "kadokhovzaur@yandex.ru")

public:
    UserModel(QSqlDatabase &aDb, QObject *aParent = Q_NULLPTR);
    void addUser(const User &aUser);
    void removeUserId(const unsigned int &aId);
    bool isDatabaseReady();

signals:
    void error(QString);
public slots:

};

#endif // USERMODEL_H
