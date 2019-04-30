#include "outputlistmodel.h"

#include "displayconfig.h"

#include <KScreen/Output>

OutputListModel::OutputListModel(QObject* parent)
    : QAbstractListModel(parent)
{
    connect(DisplayConfig::instance(), &DisplayConfig::configChanged,
        this, [&](KScreen::ConfigPtr cfg) {
            beginResetModel();
            m_config = cfg;
            endResetModel();
        });
}

int OutputListModel::rowCount(const QModelIndex& parent) const
{
    qDebug() << "RowCount";
    if (parent.isValid() || m_config == nullptr)
        return 0;
    qDebug() << m_config->outputs().size();
    return m_config->outputs().size();
}

QVariant OutputListModel::data(const QModelIndex& index, int role) const
{
    qDebug() << "data";
    if (m_config == nullptr) {
        return QVariant::Invalid;
    }
    KScreen::OutputPtr output = m_config->outputs().values().at(index.row());

    qDebug() << output->name();
    switch (role) {
    case Qt::DisplayRole:
        return output->name();
    }
    return QVariant::Invalid;
}
