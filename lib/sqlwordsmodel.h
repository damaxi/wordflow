#ifndef QSQLWORDSMODEL_H
#define QSQLWORDSMODEL_H

#include <QSqlTableModel>

class SqlWordsModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int vocabularyfilter READ vocabularyfilter WRITE setVocabularyfilter NOTIFY vocabularyfilterChanged)
public:
    explicit SqlWordsModel(QObject *parent = 0);
    virtual ~SqlWordsModel() = default;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    int vocabularyfilter() const;
    void setVocabularyfilter(int vocabularyId);

    Q_INVOKABLE void updateProgress(int row, int progress);

signals:
    void vocabularyfilterChanged();

public slots:

protected:
    virtual void mergeFilters();

    int m_vocabularyfiter;
};

#endif // QSQLWORDSMODEL_H
