#ifndef SUBMIT_BUTTON_H
#define SUBMIT_BUTTON_H

#include <string>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include "user_input_area.h"
#include "input_parser.h"

class Submit_Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Submit_Button(User_Input_Area* input){
        QObject::connect(this, SIGNAL(clicked()), this, SLOT(parse_text()));
        Input_area = input;
    }



public slots:
    void parse_text(){
        QString text = Input_area->toPlainText();

        std::string str_text = text.toUtf8().constData();

        parse(str_text);
    }

private:
    User_Input_Area *Input_area;
};

#endif // SUBMIT_BUTTON_H
