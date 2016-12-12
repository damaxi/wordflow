#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <QObject>
#include <database.h>

class Vocabulary : public QObject
{
    Q_OBJECT
public:
    explicit Vocabulary(QObject *parent = 0);

    Q_INVOKABLE void initializeVocabulary();

signals:

public slots:

private:
    Database m_database;
};

#endif // VOCABULARY_H
