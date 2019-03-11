#include <vector>
#include <QGridLayout>
#include <QApplication>
#include <QToolButton>
#include "element.h"
#include "periodic_table.h"

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

    QToolButton *periodic[9][18];

    for (int button = 0; button < 9; button++) {
        for (int col = 0; col < 18; col++) {
            QToolButton *pushbutton = new QToolButton(centralWidget);
            periodic[button][col] = pushbutton;
        }
    }


    obj.Initialize_Table(periodic);

    QGridLayout *periodic_table = new QGridLayout(centralWidget);
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 18; col++){

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

    return periodic_table;
}
