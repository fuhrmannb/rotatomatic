#include "screentest.h"

#include <QDebug>

#include <KScreen/Config>
#include <KScreen/Output>
#include <KScreen/SetConfigOperation>

ScreenTest::ScreenTest(QObject* parent)
    : QObject(parent)
{
}

void ScreenTest::loaded(KScreen::ConfigOperation* op)
{
    const KScreen::ConfigPtr cfg = op->config();
    if (cfg == nullptr) {
        qDebug() << "null";
    } else {
        foreach (KScreen::OutputPtr o, cfg->outputs()) {
            qDebug() << o->name() << o->size() << o->rotation();
            if (o->name() == "HDMI1") {
                o->setRotation(KScreen::Output::Rotation::Left);
                new KScreen::SetConfigOperation(cfg);
            }
        }
    }
}
