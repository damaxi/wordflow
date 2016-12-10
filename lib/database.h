#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
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
    Q_INVOKABLE void create_vocabulary(QString, QString) const;
    Q_INVOKABLE QVariantList list_vocabularies() const;
    void clean_tables() const;
    void remove_database() const;
private:
    QString m_path;
    QSqlDatabase m_database;

    const QString m_database_name;
};

#endif // DATABASE_H
