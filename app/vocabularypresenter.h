#ifndef VOCABULARYPRESENTER_H
#define VOCABULARYPRESENTER_H

#include <QObject>
#include "database.h"

class VocabularyPresenter : public Database
{
    Q_OBJECT
public:
    explicit VocabularyPresenter(QObject *parent = 0);
    Q_INVOKABLE bool checkIfVocabularyExist();
signals:

public slots:
};

#endif // VOCABULARYPRESENTER_H
