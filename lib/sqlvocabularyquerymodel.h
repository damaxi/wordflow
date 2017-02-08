#ifndef SQLVOCABULARYQUERYMODEL_H
#define SQLVOCABULARYQUERYMODEL_H

#include <QSqlQueryModel>

class SqlVocabularyQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit SqlVocabularyQueryModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    Q_INVOKABLE int getItemId(int rowIndex) const;
    Q_INVOKABLE void refresh();

signals:

public slots:

};

#endif // SQLVOCABULARYQUERYMODEL_H
