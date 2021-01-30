#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include "localstorage.h"

LocalStorage::LocalStorage(QObject *parent) : QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("localstorage.sqlite");
    if(!db.open())
        qWarning() << "LocalStorage cannot create database - ERROR: " << db.lastError().text();

    QSqlQuery query;
    query.exec("create table if not exists entries (title varchar(80) unique, url varchar(240))");
    if(!query.isActive())
        qWarning() << "LocalStorage cannot create table - ERROR: " << query.lastError().text();

}

bool LocalStorage::isEmpty()
{
    QSqlQuery query;
    if ( !query.exec("select * from entries") )
         qWarning() << "LocalStorage cannot execute query (isEmpty) - ERROR: " << query.lastError().text();

    return !query.first();
}

bool LocalStorage::hasRecord(const QString &key)
{
    QSqlQuery query;
    query.prepare("select * from entries where title = ?");
    query.addBindValue(key);

    if(!query.exec())
        qWarning() << "LocalStorage cannot execute query (hasRecord) - ERROR: " << query.lastError().text();

    return query.first();
}

bool LocalStorage::insertRecord(ImageData* record)
{
    if (record->title() == "No Data") return true;
    if (hasRecord(record->title())) return true;

    QSqlQuery query;
    query.prepare("insert into entries (title, url) values (?, ?)");
    query.addBindValue(record->title());
    query.addBindValue(record->url());

    if(!query.exec())
    {
        qWarning() << "LocalStorage cannot execute query (insertRecord) - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

ImageData* LocalStorage::getRecord(const QString &key)
{
    QSqlQuery query;
    query.prepare("select title, url from entries where title = ?");
    query.addBindValue(key);

    if(!query.exec())
        qWarning() << "LocalStorage cannot execute query (getRecord) - ERROR: " << query.lastError().text();

    ImageData* entry = new ImageData();
    if(query.first())
    {
        entry->setTitle(query.value(0).toString());
        entry->setUrl(query.value(1).toString());
    }

    return entry;
}

ImageData* LocalStorage::getRandomRecord()
{
    QSqlQuery query;
    if(!query.exec("select title, url from entries"))
        qWarning() << "LocalStorage cannot execute query (getRandomRecord) - ERROR: " << query.lastError().text();

    ImageData* entry = new ImageData();
    if(query.first())
    {
        entry->setTitle(query.value(0).toString());
        entry->setUrl(query.value(1).toString());
    }

    return entry;
}

void LocalStorage::deleteRecord(const QString &key)
{
    QSqlQuery query;
    query.prepare("delete from entries where title = ?");
    query.addBindValue(key);

    if(!query.exec())
        qWarning() << "LocalStorage cannot execute query (deleteRecord) - ERROR: " << query.lastError().text();
}
