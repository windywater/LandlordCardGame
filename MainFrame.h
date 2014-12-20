#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QDialog>
#include "GamePanel.h"
#include <QResizeEvent>

namespace Ui {
class MainFrame;
}

class MainFrame : public QDialog
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

protected:
    virtual void resizeEvent(QResizeEvent* event);

private:
    Ui::MainFrame *ui;
    GamePanel* m_gamePanel;
};

#endif // MAINFRAME_H
