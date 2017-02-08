#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QDir>
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
    Q_INVOKABLE bool createVocabulary(QString vocabulary, QString description);
    Q_INVOKABLE bool createWord(QString origin, QString translated, int vocabulary_id = 0);
    Q_INVOKABLE bool updateWord(int word_id, QString origin, QString translated);
    Q_INVOKABLE bool deleteWord(int word_id);
    Q_INVOKABLE bool deleteAll(int vocabulary_id);
    Q_INVOKABLE bool updateProgress(int word_id, int progress);
    Q_INVOKABLE bool resetProgresses(int vocabulary_id);
    Q_INVOKABLE int countWords(int vocabulary_id);
    Q_INVOKABLE QVariantList listWords(int vocabulary, int limit = std::numeric_limits<int>::max(), bool sort = false, bool onlyNotCompleted = false);
    Q_INVOKABLE QVariantList listVocabularies();
    void cleanTables();
    void removeDatabase();
    QString path() const;
private:
    void runSql();

    const QDir m_path;
    QSqlDatabase m_database;
    QSqlQuery m_query;

    const QString m_database_name;
};

#endif // DATABASE_H
