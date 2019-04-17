#include "periodic_table.h"


Periodic_Table::Periodic_Table()
{

}

void Periodic_Table::Initialize_Table(Interactive_Table* table[][18])
{
    int row = 0;
    int col = 0;


    QFile elements(":/MyFile/Periodic table elements.txt");
    if (elements.open(QIODevice::ReadOnly))
    {
        //store the contents of the file in a QString object
        QTextStream line(&elements);


        while (!line.atEnd())
        {

            QString element = line.readLine();

            if(element == table_space)
            {
                col++;
                continue;
            }

            table[row][col]->setText(element);
            table[row][col]->get_text(element);
            table[row][col]->setFixedSize(75,75);

            ++col;
            if (col == 18)
            {
                ++row;
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
