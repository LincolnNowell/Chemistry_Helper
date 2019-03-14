#ifndef USER_INPUT_AREA_H
#define USER_INPUT_AREA_H
#include <QString>
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
        static int id = 1;
        _id = id++;
    }

    int _id = 0;
    char identifier;

    //QString text;

    int its_me() { return _id; }
    void get_identifier(char identity) { identifier = identity; }
    char get_identity() { return identifier; }
};

#endif // USER_INPUT_AREA_H
