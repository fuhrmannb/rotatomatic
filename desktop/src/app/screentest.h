#ifndef SCREENTEST_H
#define SCREENTEST_H

#include <KScreen/ConfigOperation>
#include <QObject>

class ScreenTest : public QObject {
    Q_OBJECT
public:
    explicit ScreenTest(QObject* parent = nullptr);

signals:

public slots:
    void loaded(KScreen::ConfigOperation* op);
};

#endif // SCREENTEST_H
