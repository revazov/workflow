#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSettings>
#include "usermodel.h"
#include "missiomodel.h"

bool createTables(QSqlDatabase &db)
{
    bool isSuccess = true;
    QSettings settings("workflow", QSettings::IniFormat);
    QSqlQuery query(db);

    //User table
    isSuccess &= query.exec("create table if not exists user"
                            "(id int primary key, firstname text, lastname text);");
    query.prepare("insert into user values(1, :firstname, :secondname);");
    query.bindValue(":firstname", settings.value("firstname").toString());
    query.bindValue(":secondname", settings.value("secondname").toString());
    isSuccess &= query.exec();

    //Mission table
    isSuccess &= query.exec("create table if not exists mission"
                            "(id int primary key, name text, user_id int, start_date text, end_date text, last_action_date text, finished int);");

    return isSuccess;

}

void createSettings()
{
    QSettings settings("workflow", QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.setValue("firstname", "Заур");
    settings.setValue("secondname", "Кадохов");
    settings.sync();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);



    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("base.sqlite");
    if (!db.open()) {
        qDebug() << "can't open database";
        return app.exec();
    }

    createTables(db);

    UserModel userModel(db);
//    User user;
//    user.id = 2;
//    user.fName = "Test";
//    user.lName = "Testsson";
//    userModel.addUser(user);
//    userModel.removeUserId(user.id);

    MissioModel missionModel(db);
//    Mission mission;
//    qDebug() << mission.start_date;


    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    return app.exec();
}
