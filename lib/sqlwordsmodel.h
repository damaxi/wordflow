#ifndef QSQLWORDSMODEL_H
#define QSQLWORDSMODEL_H

#include <QSqlTableModel>

class SqlWordsModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString originfilter READ originfilter WRITE setOriginfilter NOTIFY originfilterChanged)
public:
    explicit SqlWordsModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    QString originfilter() const;
    void setOriginfilter(const QString &filterString);

    Q_INVOKABLE void addWord(const QString &origin, const QString &translated, int vocabulary);
    Q_INVOKABLE void updateWord(int row, const QString &origin, const QString &translated);
    Q_INVOKABLE void updateProgress(int row, int progress);
    Q_INVOKABLE void removeWord(int row);
    Q_INVOKABLE void removeAll();
    Q_INVOKABLE void resetAll();

signals:
    void originfilterChanged();

public slots:

private:
    QString m_filter;
};

#endif // QSQLWORDSMODEL_H
