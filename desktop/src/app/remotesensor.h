#ifndef REMOTESENSOR_H
#define REMOTESENSOR_H

#include <QObject>

#include <QtWebSockets/QtWebSockets>

#include <KScreen/ConfigOperation>

class RemoteSensor : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(quint16 offset READ offset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(KScreen::OutputPtr screen READ screen WRITE setScreen NOTIFY screenChanged)

public:
    explicit RemoteSensor(QObject* parent = nullptr);
    ~RemoteSensor();

    void open();
    void close();

    inline QString name() const { return m_name; }
    inline QUrl url() const { return m_url; }
    inline quint16 offset() const { return m_offset; }
    inline KScreen::OutputPtr screen() const { return m_screen; }

public slots:
    inline void setName(const QString& name)
    {
        if (m_name == name)
            return;

        qDebug() << "changed! " << name;
        m_name = name;
        emit nameChanged(m_name);
    }

    void setUrl(const QUrl& url);

    inline void setOffset(quint16 offset)
    {
        if (m_offset == offset)
            return;

        m_offset = offset;
        emit offsetChanged(offset);
    }

    inline void setScreen(const KScreen::OutputPtr& screen)
    {
        if (m_screen == screen)
            return;

        m_screen = screen;
        emit screenChanged(screen);
    }

signals:
    void nameChanged(QString m_name);
    void urlChanged(QUrl url);
    void offsetChanged(quint16 offset);
    void screenChanged(KScreen::OutputPtr screen);

    void rotationChanged(int value);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextReceived(QString message);

    void onRotationReceived(int rotation);

private:
    QString m_name;
    QUrl m_url;
    quint16 m_offset;
    KScreen::OutputPtr m_screen;

    QWebSocket m_webSocket;
};

#endif // REMOTESENSOR_H
