#ifndef LOCALSTORAGE_H
#define LOCALSTORAGE_H

#include <QObject>
#include <QPair>

#include "imagedata.h"

class LocalStorage : public QObject
{
    Q_OBJECT
public:
    explicit LocalStorage(QObject *parent = nullptr);

signals:

public:
    Q_INVOKABLE bool isEmpty();
    Q_INVOKABLE bool hasRecord(const QString& key);
    Q_INVOKABLE bool insertRecord(ImageData* record);
    Q_INVOKABLE ImageData* getRecord(const QString& key);
    Q_INVOKABLE ImageData* getRandomRecord();
    Q_INVOKABLE void deleteRecord(const QString& key);
};

#endif // LOCALSTORAGE_H
