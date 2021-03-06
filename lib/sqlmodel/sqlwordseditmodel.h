#ifndef SQLWORDSEDITMODEL_H
#define SQLWORDSEDITMODEL_H

#include "sqlstatisticmodel.h"
#include "sqltotalwordsstatisticmodel.h"
#include "sqlwordsmodel.h"

class SqlWordsEditModel : public SqlWordsModel {
  Q_OBJECT
  Q_PROPERTY(QString originfilter READ originfilter WRITE setOriginfilter NOTIFY
                 originfilterChanged)
public:
  explicit SqlWordsEditModel(QObject *parent = 0);

  QString originfilter() const;
  void setOriginfilter(const QString &filterString);

  Q_INVOKABLE void addWord(const QString &origin, const QString &translated);
  Q_INVOKABLE bool ifExist(const QString &origin);
  Q_INVOKABLE void updateWord(int row, const QString &origin,
                              const QString &translated);
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
  SqlTotalWordsStatisticModel m_totalStatisticModel;
};

#endif // SQLWORDSEDITMODEL_H
