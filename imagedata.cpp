#include "imagedata.h"

ImageData::ImageData(QObject *parent) : QObject(parent)
{
}

QString ImageData::title() const
{
    return m_title;
}

void ImageData::setTitle(const QString &title)
{
    m_title = title;
}

QString ImageData::url() const
{
    return m_url;
}

void ImageData::setUrl(const QString &url)
{
    m_url = url;
}
