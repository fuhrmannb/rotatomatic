#ifndef OUTPUTLISTMODEL_H
#define OUTPUTLISTMODEL_H

#include <QAbstractListModel>

#include <KScreen/Config>

class OutputListModel : public QAbstractListModel {
    Q_OBJECT

public:
    OutputListModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
    KScreen::ConfigPtr m_config;
};

#endif // OUTPUTLISTMODEL_H
