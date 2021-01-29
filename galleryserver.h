#ifndef GALLERYSERVER_H
#define GALLERYSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QList>
#include <QPair>

class GalleryServer : public QObject
{
    Q_OBJECT

    QWebSocketServer* m_pWebSocketServer;
    QPair<QString, QString> m_entry;

public:
    explicit GalleryServer(quint16 port, QObject *parent = nullptr);

signals:

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void socketDisconnected();
    void closed();

public:
    Q_INVOKABLE void onItemChanged(const QString& itemkey);
};

#endif // GALLERYSERVER_H
