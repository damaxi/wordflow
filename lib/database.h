#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QPair>
#include <QObject>
#include <QVariantList>
#include <limits>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    virtual ~Database();
    void openDatabase();
    Q_INVOKABLE void createDatabase();
    Q_INVOKABLE bool createVocabulary(QString vocabulary, QString description);
    Q_INVOKABLE bool createWord(QString origin, QString translated, int vocabulary_id = 0);
    Q_INVOKABLE bool updateProgress(QString origin, int vocabulary_id, int progress);
    Q_INVOKABLE bool updateProgressById(int word_id, int progress);
    Q_INVOKABLE QVariantList listWords(int vocabulary, int limit = std::numeric_limits<int>::max(), bool sort = true);
    Q_INVOKABLE QVariantList listVocabularies();
    void cleanTables();
    void removeDatabase();
    QString path() const;
private:
    void runSql();

    QString m_path;
    QSqlDatabase m_database;
    QSqlQuery m_query;

    const QString m_database_name;
};

#endif // DATABASE_H
