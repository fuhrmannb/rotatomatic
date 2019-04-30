#include "sensorlistmodel.h"

SensorListModel::SensorListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int SensorListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_remoteSensors.size();
}

QVariant SensorListModel::data(const QModelIndex& index, int role) const
{
    RemoteSensor* s = m_remoteSensors[index.row()];

    switch (role) {
    case Qt::DisplayRole:
        return s->name();
    }
    return QVariant::Invalid;
}

void SensorListModel::add(QString name, QString url, const QModelIndex& parent)
{
    beginInsertRows(parent, rowCount(), rowCount());
    RemoteSensor* rs = new RemoteSensor();
    rs->setName(name);
    rs->setUrl(url);
    m_remoteSensors << rs;
    endInsertRows();
}

RemoteSensor* SensorListModel::get(int row) const
{
    if (row < 0 || row >= m_remoteSensors.size()) {
        return nullptr;
    }
    return m_remoteSensors[row];
}

void SensorListModel::remove(int row, const QModelIndex& parent)
{
    if (row < 0 || row >= m_remoteSensors.size()) {
        return;
    }
    beginRemoveRows(parent, row, row);
    delete m_remoteSensors.takeAt(row);
    endRemoveRows();
}
