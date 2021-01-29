#ifndef GALLERYCLIENT_H
#define GALLERYCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QUrl>

#include "imagedata.h"

class GalleryClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ImageData* image READ image NOTIFY imageReceived);
    Q_PROPERTY(ImageData* noimage READ noimage NOTIFY noimageAvailable);

public:
    explicit GalleryClient(const QUrl& url, QObject *parent = nullptr);

signals:
    void imageReceived();
    void noimageAvailable();

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void closed();

public:
    Q_INVOKABLE void onEntry();
    Q_INVOKABLE void onExit();
    Q_INVOKABLE void onTitleEntered(const QString& title);

    ImageData* image();
    ImageData* noimage();

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    ImageData m_image;
};

#endif // GALLERYCLIENT_H
