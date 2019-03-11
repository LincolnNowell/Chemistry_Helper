#include "Periodic_Table.h"


Periodic_Table::Periodic_Table()
{

}


void Periodic_Table::Initialize_Table(QToolButton* table[][18])
{
    int row = 0;
    int col = 0;


    QFile elements(":/MyFile/Periodic table elements.txt");
    if (elements.open(QIODevice::ReadOnly))
    {
        //store the contents of the file in a QString object
        QTextStream in(&elements);


        while (!in.atEnd())
        {

            QString element = in.readLine();

            if(element == table_space)
            {
                col++;
                continue;
            }

            //set pushbutton text to element name
            table[row][col]->setText(element);
            table[row][col]->setFixedSize(75,75);

            col++;
            if (col == 18)
            {
                row++;
                col = 0;
            }
        }
    }
    else
    {
        QMessageBox *error = new QMessageBox();
        error->setText("Error Reading File");
        delete  error;
    }

    elements.close();

}


Periodic_Table::~Periodic_Table()
{
}
