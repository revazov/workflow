#include "missiomodel.h"

MissioModel::MissioModel(QSqlDatabase &aDb, QObject *aParent):
    QSqlTableModel(aParent, aDb)
{
    qDebug() << this->metaObject()->className();

    setTable("mission");
    select();
}

void MissioModel::addMission(const Mission &aMission)
{
    if(!isDatabaseReady()){
        return;
    }

    QSqlRecord rec = record();
    rec.setValue("id", aMission.id);
    rec.setValue("name", aMission.name);
    rec.setValue("user_id", aMission.user_id);
    rec.setValue("start_date", aMission.start_date);
    rec.setValue("end_date", aMission.end_date);
    rec.setValue("last_action_date", aMission.last_action_date);
    rec.setValue("finished", aMission.finished);

    insertRecord(-1, rec);
}

void MissioModel::changeMission(const Mission &aMission)
{
    QSqlQuery query;
    query.prepare("update mission set "
                  "name = :name, user_id = :user_id, start_date = :start_date, end_date = :end_date, last_action_date = :last_action_date, finished = :finished "
                  "where id = :id");
    query.bindValue("id", aMission.id);
    query.bindValue("name", aMission.name);
    query.bindValue("user_id", aMission.user_id);
    query.bindValue("start_date", aMission.start_date);
    query.bindValue("end_date", aMission.end_date);
    query.bindValue("last_action_date", aMission.last_action_date);
    query.bindValue("finished", aMission.finished);
    query.exec();
}

void MissioModel::removeMissionId(const unsigned int &aId)
{
    QSqlQuery query;
    query.prepare("delete from mission where id = :id");
    query.bindValue(":id", aId);
    query.exec();
}

QHash<int, QByteArray> MissioModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    // record() returns an empty QSqlRecord
    for (int i = 0; i < record().count(); i ++) {
        roles.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
    }
    return roles;
}

QVariant MissioModel::data(const QModelIndex &index, int role) const
{
    QVariant value;

    if (index.isValid()) {
        if (role < Qt::UserRole) {
            value = QSqlQueryModel::data(index, role);
        } else {
            int columnIdx = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(index.row(), columnIdx);
            value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
    }
    return value;
}

bool MissioModel::isDatabaseReady()
{
    bool isReady = true;

    isReady = database().isValid() && database().isOpen();
    if(!isReady){
        emit error(objectName() + ": " + tr("Databaseis is not ready"));
    }

    return isReady;
}


