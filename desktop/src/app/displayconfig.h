#ifndef DISPLAYCONFIG_H
#define DISPLAYCONFIG_H

#include <QObject>

#include <KScreen/ConfigOperation>

class DisplayConfig : public QObject {
    Q_OBJECT
    Q_PROPERTY(KScreen::ConfigPtr screenConfig READ config WRITE setConfig NOTIFY configChanged)

public:
    static DisplayConfig* instance();

    Q_INVOKABLE inline KScreen::ConfigPtr config() const
    {
        return m_screenConfig;
    }

    inline void updateConfig()
    {
        setConfig(m_screenConfig);
    }

signals:
    void configChanged(KScreen::ConfigPtr cfg);

public slots:
    void setConfig(KScreen::ConfigPtr);

private slots:
    void displayReady(KScreen::ConfigOperation* op);

private:
    explicit DisplayConfig(QObject* parent = nullptr);

    KScreen::ConfigPtr m_screenConfig;
};

#endif // DISPLAYCONFIG_H
