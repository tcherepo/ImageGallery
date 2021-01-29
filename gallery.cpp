#include "gallery.h"

Title::Title(QObject *parent) : QObject(parent)
{
}

QString Title::title()
{
    return m_title;
}

void Title::setTitle(const QString& title)
{
    m_title = title;
}

QMap<QString, QString> Gallery::m_gallery {
    { "Yellow Flower", "gallery/DSC00204.JPG"},
    { "Orange Flower", "gallery/DSC00205.JPG"},
    { "Orange Flower 2", "gallery/DSC00206.JPG"},
    { "Yellow Flowers", "gallery/DSC00207.JPG"},
    { "Yellow Flower 2", "gallery/DSC00208.JPG"},
    { "More Yellow Flowers", "gallery/DSC00210.JPG"},
    { "Small Yellow Flowers", "gallery/DSC00211.JPG"},
    { "Violet Flower", "gallery/DSC00212.JPG"},
    { "Big Violet Flower", "gallery/DSC00213.JPG"},
    { "White Flowers", "gallery/DSC00214.JPG"}
};

Gallery::Gallery(QObject *parent) : QObject(parent)
{
}

QList<QObject*> Gallery::getTitles()
{
    QString title;
    QList<QObject*> result;
    foreach (title, readTitles())
    {
        Title* item = new Title();
        item->setTitle(title);
        result.append(item);
    }

    return result;
}

QList<QString> Gallery::readTitles()
{
    return m_gallery.keys();
}

bool Gallery::GetEntry(const QString &key, QPair<QString, QString> &entry)
{
    if ( m_gallery.contains(key) )
    {
        entry.first = key;
        entry.second = m_gallery.value(key);
        return true;
    }

    return false;
}
