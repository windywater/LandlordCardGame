#ifndef MARKBOARD_H
#define MARKBOARD_H

#include <QWidget>

namespace Ui {
class MarkBoard;
}

class MarkBoard : public QWidget
{
    Q_OBJECT
public:
    explicit MarkBoard(QWidget *parent = 0);
    ~MarkBoard();

    void SetMarks(int me, int left, int right);
private:
    Ui::MarkBoard *ui;
};

#endif // MARKBOARD_H
