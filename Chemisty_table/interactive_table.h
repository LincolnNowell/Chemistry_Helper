#ifndef INTERACTIVE_TABLE_H
#define INTERACTIVE_TABLE_H
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QString>
#include "user_input_area.h"


class Interactive_Table : public QPushButton
{
    Q_OBJECT

public:
    Interactive_Table(User_Input_Area *input)
    {
        Input_Area = input;
        QObject::connect(this, SIGNAL(clicked()), this, SLOT(change_text()));
    }

    User_Input_Area *Input_Area;
    QString element;

    void get_text(QString element_name){
        element = element_name;
    }



public slots:
    void change_text();
};

#endif // INTERACTIVE_TABLE_H
