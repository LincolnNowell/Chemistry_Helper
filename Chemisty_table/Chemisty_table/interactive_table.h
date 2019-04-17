#ifndef INTERACTIVE_TABLE_H
#define INTERACTIVE_TABLE_H
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QString>
#include "user_input_area.h"

/*
 * Custom QPushbutton class that appends it's element on the text area when selected by the user
*/

class Interactive_Table : public QPushButton
{
    Q_OBJECT

public:
    Interactive_Table(QWidget * parent = nullptr) :
        QPushButton(parent), Input_Area(nullptr)
    {
        QObject::connect(this, SIGNAL(clicked()), this, SLOT(change_text()));
    }

    User_Input_Area *Input_Area;
    QString element;
    QString stored_text;

    void get_Input_area(User_Input_Area *input_area){
        Input_Area = input_area;
    }

    void get_text(QString element_name){
        element = element_name;
    }


public slots:
    void change_text();

};

#endif // INTERACTIVE_TABLE_H
