#include "displayconfig.h"

#include <KScreen/Config>
#include <KScreen/GetConfigOperation>
#include <KScreen/Output>
#include <KScreen/SetConfigOperation>

#include <QUrl>

DisplayConfig* DisplayConfig::instance()
{
    static DisplayConfig* inst;
    if (inst == nullptr) {
        inst = new DisplayConfig();
    }
    return inst;
}

DisplayConfig::DisplayConfig(QObject* parent)
    : QObject(parent)
{
    QObject::connect(
        new KScreen::GetConfigOperation(), &KScreen::GetConfigOperation::finished,
        this, &DisplayConfig::displayReady);
}

void DisplayConfig::setConfig(KScreen::ConfigPtr cfg)
{
    QObject::connect(
        new KScreen::SetConfigOperation(cfg), &KScreen::SetConfigOperation::finished,
        this, &DisplayConfig::displayReady);
}

void DisplayConfig::displayReady(KScreen::ConfigOperation* op)
{
    // Store screen config
    m_screenConfig = op->config();
    // Notify config change
    emit configChanged(m_screenConfig);
}
