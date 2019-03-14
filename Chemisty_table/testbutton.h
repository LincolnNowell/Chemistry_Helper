#ifndef TESTBUTTON_H
#define TESTBUTTON_H
#include <QPushButton>
#include <QLabel>

class testbutton : QLabel
{
    Q_OBJECT

public:
    explicit testbutton(const QString &text, QWidget *parent = nullptr);
};

#endif // TESTBUTTON_H
