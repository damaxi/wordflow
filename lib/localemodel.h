#ifndef LOCALEMODEL_H
#define LOCALEMODEL_H

#include <QAbstractListModel>
#include <QSet>
#include <QString>
#include <QDebug>

class LocaleModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LocaleModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QList<QString> m_languages;
};

#endif // LOCALEMODEL_H
