#include "vocabulary.h"

Vocabulary::Vocabulary(QObject *parent) : QObject(parent), m_database()
{}

void Vocabulary::initializeVocabulary()
{
    m_database.createDatabase();
}


