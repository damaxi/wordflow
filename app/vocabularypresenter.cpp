#include "vocabularypresenter.h"
#include <QDebug>

VocabularyPresenter::VocabularyPresenter(QObject *parent) : Database(parent)
{

}

bool VocabularyPresenter::checkIfVocabularyExist()
{
    return listVocabularies().size() > 0;
}
