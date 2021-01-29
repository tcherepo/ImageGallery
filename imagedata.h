#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <QObject>

class ImageData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

public:
    explicit ImageData(QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString& title);
    QString url() const;
    void setUrl(const QString& url);

signals:
    void titleChanged();
    void urlChanged();

private:
    QString m_title;
    QString m_url;
};

#endif // IMAGEDATA_H
