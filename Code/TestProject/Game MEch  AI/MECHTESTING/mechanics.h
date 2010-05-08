#ifndef MECHANICS_H
#define MECHANICS_H

#include <QObject>
#include "stdio.h"
#include "globalls.h"


class mechanics : public QObject
{
Q_OBJECT
public:
    explicit mechanics(QObject *parent = 0);
    void move(unit *UP, int x, int y);
    bool isValidMove(int a, int b, int c, int d);

signals:

public slots:

};

#endif // MECHANICS_H
