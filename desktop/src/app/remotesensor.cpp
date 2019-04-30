#include "remotesensor.h"
#include "displayconfig.h"

#include <KScreen/Output>

RemoteSensor::RemoteSensor(QObject* parent)
    : QObject(parent)
    , m_name()
    , m_url()
    , m_offset(0)
    , m_screen()
{
}

RemoteSensor::~RemoteSensor()
{
    // Stop socket if needed
    if (m_webSocket.state() != QAbstractSocket::UnconnectedState) {
        m_webSocket.close();
    }
}

void RemoteSensor::open()
{
    QObject::connect(&m_webSocket, &QWebSocket::connected, this, &RemoteSensor::onConnected);
    QObject::connect(&m_webSocket, &QWebSocket::disconnected, this, &RemoteSensor::onDisconnected);
    m_webSocket.open(QUrl(m_url));
}

void RemoteSensor::close()
{
    m_webSocket.close();
}

void RemoteSensor::setUrl(const QUrl& url)
{
    if (m_url == url)
        return;

    m_url = url;

    // If socket is listening, close it and restart connection
    if (m_webSocket.state() != QAbstractSocket::UnconnectedState) {
        QObject::connect(&m_webSocket, &QWebSocket::disconnected,
            this, [&]() {
                m_webSocket.open(QUrl(m_url));
            });
        m_webSocket.close();
    }

    emit urlChanged(url);
}

void RemoteSensor::onConnected()
{
    QObject::connect(&m_webSocket, &QWebSocket::textMessageReceived,
        this, &RemoteSensor::onTextReceived);
    QObject::connect(this, &RemoteSensor::rotationChanged,
        this, &RemoteSensor::onRotationReceived);
}

void RemoteSensor::onDisconnected()
{
    QObject::disconnect(&m_webSocket, &QWebSocket::textMessageReceived,
        this, &RemoteSensor::onTextReceived);
}

void RemoteSensor::onTextReceived(const QString message)
{
    emit rotationChanged(message.toInt());
}

void RemoteSensor::onRotationReceived(int rotation)
{
    if (!m_screen || rotation == -1) {
        return;
    }
    rotation = (rotation + m_offset) % 360;

    KScreen::Output::Rotation screenRot;
    if (rotation < 45 || rotation > 315) {
        screenRot = KScreen::Output::Rotation::None;
    } else if (rotation > 225) {
        screenRot = KScreen::Output::Rotation::Left;
    } else if (rotation > 135) {
        screenRot = KScreen::Output::Rotation::Inverted;
    } else {
        screenRot = KScreen::Output::Rotation::Right;
    }
    m_screen->setRotation(screenRot);
    DisplayConfig::instance()->updateConfig();
}
