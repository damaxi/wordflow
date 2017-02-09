#ifndef SQLLEARNINGWORDSMODEL_H
#define SQLLEARNINGWORDSMODEL_H

#include "sqlwordsmodel.h"

class SqlLearningWordsModel : public SqlWordsModel
{
    Q_OBJECT
    Q_PROPERTY(bool ordersort READ ordersort WRITE setOrdersort NOTIFY ordersortChanged)
    Q_PROPERTY(int limit READ limit WRITE setLimit NOTIFY limitChanged)
    Q_PROPERTY(int maxprogress READ maxprogress WRITE setMaxprogress NOTIFY maxprogressChanged)
public:
    explicit SqlLearningWordsModel(QObject *parent = 0);

    Q_INVOKABLE void setProgressEasy(int row);
    Q_INVOKABLE void setProgressGood(int row);
    Q_INVOKABLE void setProgressHard(int row);
    Q_INVOKABLE void setProgressAgain(int row);

    Q_INVOKABLE int countWords() const;

    void setOrdersort(bool ordersort);
    bool ordersort() const;

    Q_DECL_UNUSED void setLimit(int limit);
    Q_DECL_UNUSED int limit() const;

    void setMaxprogress(int maxprogress);
    int maxprogress() const;

signals:
    void ordersortChanged(bool ordersort);
    void limitChanged(int limit);
    void maxprogressChanged(int maxprogress);

public slots:

protected:
    void mergeFilters() Q_DECL_OVERRIDE;
    void immediatetelySubmitDefaultProperties() Q_DECL_OVERRIDE;

private:
    static constexpr int EasyProgress{ 100 };
    static constexpr int GoodProgress{ 75 };
    static constexpr int HardProgress{ 50 };
    static constexpr int AgainProgress{ 25 };

    bool m_ordersort;
    int m_limit;
    int m_maxprogress;
};

#endif // SQLLEARNINGWORDSMODEL_H
