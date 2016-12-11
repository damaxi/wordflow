#ifndef TESTING_H
#define TESTING_H

#include <QObject>

class Testing : public QObject
{
    Q_OBJECT
public:
    explicit Testing(QObject *parent = 0);
    Q_INVOKABLE void hello();
signals:

public slots:
};

#endif // TESTING_H
