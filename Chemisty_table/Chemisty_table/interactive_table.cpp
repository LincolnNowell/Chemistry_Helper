#include "interactive_table.h"


void Interactive_Table::change_text(){

    /*stores the text entered by user and appends the element on to it*/

    stored_text = Input_Area->toPlainText();
    Input_Area->setText(stored_text + element);
}


