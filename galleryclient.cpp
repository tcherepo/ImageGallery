#include <QList>
#include <QPair>

#include "galleryclient.h"

GalleryClient::GalleryClient(const QUrl& url, QObject *parent) :
    QObject(parent),
    m_url(url)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &GalleryClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &GalleryClient::closed);
}

void GalleryClient::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &GalleryClient::onTextMessageReceived);
}

void GalleryClient::onTextMessageReceived(QString message)
{
    QList<QString> items = message.split("\n");
    m_image.setTitle(items.at(0));
    m_image.setUrl(items.at(1));

    emit imageReceived();
}

void GalleryClient::closed()
{
    m_webSocket.close();
}

void GalleryClient::onEntry()
{
    m_webSocket.open(m_url);
}

void GalleryClient::onExit()
{
    m_webSocket.close();
}

void GalleryClient::onTitleEntered(const QString &title)
{
    if (!title.isEmpty())
    {
        m_webSocket.sendTextMessage(title);
    }
}

ImageData* GalleryClient::image()
{
    ImageData* fill = new ImageData();
    fill->setTitle(m_image.title());
    fill->setUrl(m_image.url());
    return fill;
}

ImageData *GalleryClient::noimage()
{
    ImageData* blank = new ImageData();
    blank->setTitle("No Image");
    blank->setUrl("");
    return blank;
}
