#ifndef SQLVOCABULARYMODEL_H
#define SQLVOCABULARYMODEL_H

#include <QSqlQueryModel>
#include <QSqlTableModel>

class SqlVocabularyModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit SqlVocabularyModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

signals:

public slots:
};

class SqlVocabularyModel2 : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit SqlVocabularyModel2(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // SQLVOCABULARYMODEL_H
