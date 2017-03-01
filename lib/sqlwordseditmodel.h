#ifndef SQLWORDSEDITMODEL_H
#define SQLWORDSEDITMODEL_H

#include "sqlwordsmodel.h"
#include "sqlstatisticmodel.h"

class SqlWordsEditModel : public SqlWordsModel
{
    Q_OBJECT
    Q_PROPERTY(QString originfilter READ originfilter WRITE setOriginfilter NOTIFY originfilterChanged)
public:
    explicit SqlWordsEditModel(QObject *parent = 0);

    QString originfilter() const;
    void setOriginfilter(const QString &filterString);

    Q_INVOKABLE void addWord(const QString &origin, const QString &translated, int vocabulary);
    Q_INVOKABLE void updateWord(int row, const QString &origin, const QString &translated);
    Q_INVOKABLE void resetWordProgress(int row);
    Q_INVOKABLE void removeWord(int row);
    Q_INVOKABLE void removeAll();
    Q_INVOKABLE void resetAll();

signals:
    void originfilterChanged();

public slots:

protected:
    void mergeFilters() Q_DECL_OVERRIDE;

private:
    QString m_originfilter;
    SqlStatisticModel m_statisticModel;
};

#endif // SQLWORDSEDITMODEL_H
