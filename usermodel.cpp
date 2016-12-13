#include "usermodel.h"

UserModel::UserModel(QSqlDatabase &db, QObject *parent):
    QSqlTableModel(parent, db)
{
    qDebug() << this->metaObject()->className();

    setTable("user");
    select();
}

void UserModel::addUser(const User &user)
{
    if(!isDatabaseReady()){
        return;
    }

    QSqlRecord rec = record();
    rec.setValue("id", user.id);
    rec.setValue("firstname", user.fName);
    rec.setValue("lastname", user.lName);

    insertRecord(-1, rec);
}


bool UserModel::isDatabaseReady()
{
    bool isReady = true;

    isReady = database().isValid() && database().isOpen();
    if(!isReady){
        emit error(objectName() + ": " + tr("Databaseis is not ready"));
    }

    return isReady;
}
