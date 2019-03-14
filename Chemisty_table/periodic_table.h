#ifndef PERIODIC_TABLE_H
#define PERIODIC_TABLE_H
#include <QToolButton>
#include <QString>
#include <QLineEdit>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QPushButton>
#include "interactive_table.h"

class Periodic_Table
{
public:
    Periodic_Table();

    void Initialize_Table(Interactive_Table* table[][18]);

    ~Periodic_Table();

private:
    const QString table_space = "space";
};

#endif // PERIODIC_TABLE_H
