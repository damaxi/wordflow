#ifndef QSQLWORDSMODEL_H
#define QSQLWORDSMODEL_H

#include <QSqlTableModel>

class SqlWordsModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit SqlWordsModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    Q_INVOKABLE void addWord(const QString &origin, const QString &translated, int vocabulary);
    Q_INVOKABLE void updateWord(int row, const QString &origin, const QString &translated);
    Q_INVOKABLE void updateProgress(int row, int progress);
    Q_INVOKABLE void removeWord(int row);
    Q_INVOKABLE void removeAll();
    Q_INVOKABLE void resetAll();
signals:

public slots:
};

#endif // QSQLWORDSMODEL_H
