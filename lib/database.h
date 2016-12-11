#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QPair>
#include <QObject>
#include <QVariantList>

class Database : public QObject
{
    Q_OBJECT
public:
    Database();
    ~Database();
    void openDatabase();
    void createDatabase();
    void createVocabulary(QString, QString);
    QVariantList listVocabularies() const;
    void clean_tables() const;
    void removeDatabase();
    QString path() const;
private:
    QString m_path;
    QSqlDatabase m_database;
    QSqlQuery m_query;

    const QString m_database_name;
};

#endif // DATABASE_H
