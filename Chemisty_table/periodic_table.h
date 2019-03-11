#ifndef PERIODIC_TABLE_H
#define PERIODIC_TABLE_H
#include <QToolButton>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "element.h"

class Periodic_Table
{
public:
    Periodic_Table();

    void Initialize_Table(QToolButton* table[][18]);

    ~Periodic_Table();

private:
    const QString table_space = "space";
};

#endif // PERIODIC_TABLE_H
