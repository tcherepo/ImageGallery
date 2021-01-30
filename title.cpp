#include "title.h"

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
    emit titleChanged();
}
