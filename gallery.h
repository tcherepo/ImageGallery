#ifndef GALLERY_H
#define GALLERY_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QPair>

#include "title.h"

class Gallery : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> titles READ getTitles NOTIFY titlesChanged)

    static QMap<QString, QString> m_gallery;

public:
    explicit Gallery(QObject *parent = nullptr);

signals:
    void titlesChanged(const QList<QObject*>& titles);

public:
    QList<QObject*> getTitles();
    static QList<QString> readTitles();
    static bool GetEntry(const QString& key, QPair<QString, QString>& entry);
};

#endif // GALLERY_H
