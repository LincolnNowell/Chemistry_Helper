#include <iostream>
#include <QGridLayout>
#include <QApplication>
#include <periodic_table.h>
#include <QToolButton>
#include "periodic_table.h"
#include "user_input_area.h"
#include "interactive_table.h"
#include "submit_button.h"
#include "Eigen"

QGridLayout *Display_Table(QWidget *);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *centralWidget = new QWidget();


    centralWidget->setLayout(Display_Table(centralWidget));
    centralWidget->show();

    return a.exec();
}

QGridLayout *Display_Table(QWidget *centralWidget){
    Periodic_Table obj;

    User_Input_Area *text_area = new User_Input_Area(centralWidget);
    text_area->zoomIn(10);

    Interactive_Table *periodic[9][18];


    //create a grid of pushbuttons that resemble the periodic table
    for (int button = 0; button < 9; ++button) {
        for (int col = 0; col < 18; ++col) {
            Interactive_Table *pushbutton = new Interactive_Table(centralWidget);
            pushbutton->get_Input_area(text_area); //store the address to text area so it can modify it
            periodic[button][col] = pushbutton;
        }
    }


    obj.Initialize_Table(periodic);


    QGridLayout *periodic_table = new QGridLayout(centralWidget);

    // delete all pushbuttons that have no text so they don't appear
    for(int row = 0; row < 9; ++row){
        for(int col = 0; col < 18; ++col){

            if(periodic[row][col]->text() == "")
            {
                delete periodic[row][col];
            }

            else{
                periodic_table->addWidget(periodic[row][col], row, col);
                periodic_table->setSpacing(0);
            }
        }
    }

    Submit_Button *Submit = new Submit_Button(text_area);
    Submit->setText("Submit");
    Submit->setFixedSize(70,70);

    periodic_table->addWidget(text_area, 10, 2, 1, 10);
    periodic_table->addWidget(Submit, 10, 13, 13, 14);

    return periodic_table;
}

