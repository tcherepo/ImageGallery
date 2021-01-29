#include "gallery.h"
#include "galleryserver.h"

GalleryServer::GalleryServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer("Gallery Server", QWebSocketServer::NonSecureMode, this))
{
    Gallery::GetEntry(Gallery::readTitles().at(0), m_entry);

    if (m_pWebSocketServer->listen(QHostAddress::LocalHost, port))
    {
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &GalleryServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &GalleryServer::closed);
    }
}

void GalleryServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &GalleryServer::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &GalleryServer::socketDisconnected);

    QString message = m_entry.first + "\n" + m_entry.second;
    pSocket->sendTextMessage(message);
}

void GalleryServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    QPair<QString, QString> entry("No Image", "");
    Gallery::GetEntry(message, entry);
    QString response = entry.first + "\n" + entry.second;

    if (pClient) {
        pClient->sendTextMessage(response);
    }
}

void GalleryServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        pClient->deleteLater();
    }
}

void GalleryServer::closed()
{
    m_pWebSocketServer->close();
}

void GalleryServer::onItemChanged(const QString &itemkey)
{
    Gallery::GetEntry(itemkey, m_entry);
}
