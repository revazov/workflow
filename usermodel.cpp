#include "usermodel.h"

UserModel::UserModel(QSqlDatabase &aDb, QObject *aParent):
    QSqlTableModel(aParent, aDb)
{
    qDebug() << this->metaObject()->className();

    setTable("user");
    select();
}

void UserModel::addUser(const User &aUser)
{
    if(!isDatabaseReady()){
        return;
    }

    QSqlRecord rec = record();
    rec.setValue("id", aUser.id);
    rec.setValue("firstname", aUser.fName);
    rec.setValue("lastname", aUser.lName);

    insertRecord(-1, rec);
}

void UserModel::removeUserId(const unsigned int &aId)
{
    QSqlQuery query;
    query.prepare("delete from user where id = :id");
    query.bindValue(":id", aId);
    query.exec();
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
