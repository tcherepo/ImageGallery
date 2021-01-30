#ifndef TITLE_H
#define TITLE_H

#include <QObject>

class Title : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    explicit Title(QObject *parent = nullptr);

    QString title();
    void setTitle(const QString& title);

signals:
    void titleChanged();

private:
    QString m_title;
};

#endif // TITLE_H
