#ifndef GALLERY_H
#define GALLERY_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QPair>

class Title : public QObject
{
    Q_OBJECT
    QString m_title;

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)

signals:
    void titleChanged(const QString& title);

public:
    explicit Title(QObject *parent = nullptr);

    QString title();
    void setTitle(const QString& title);
};

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
