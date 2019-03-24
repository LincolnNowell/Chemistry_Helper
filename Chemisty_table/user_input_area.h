#ifndef USER_INPUT_AREA_H
#define USER_INPUT_AREA_H
#include <QObject>
#include <QWidget>
#include <QTextEdit>

class User_Input_Area : public QTextEdit
{
    Q_OBJECT

public:
    User_Input_Area(QWidget *parent = nullptr) :
        QTextEdit(parent)
    {

    }
};

#endif // USER_INPUT_AREA_H
