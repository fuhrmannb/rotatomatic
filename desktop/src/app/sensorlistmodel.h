#ifndef SENSORLISTMODEL_H
#define SENSORLISTMODEL_H

#include "remotesensor.h"

#include <QAbstractListModel>
#include <QObject>

class SensorListModel : public QAbstractListModel {
    Q_OBJECT

public:
    SensorListModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void add(QString name, QString url, const QModelIndex& parent = QModelIndex());
    Q_INVOKABLE RemoteSensor* get(int row) const;
    Q_INVOKABLE void remove(int row, const QModelIndex& parent = QModelIndex());

private:
    QList<RemoteSensor*> m_remoteSensors;
};

#endif // SENSORLISTMODEL_H
