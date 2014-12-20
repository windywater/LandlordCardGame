#include "CardPic.h"
#include <QPainter>
#include "Player.h"

CardPic::CardPic(QWidget *parent) :
    QWidget(parent)
{
    m_owner = NULL;
    m_selected = false;
    m_frontSide = true;
}

void CardPic::SetPic(const QPixmap& pic, const QPixmap& back)
{
    m_pic = pic;
    m_back = back;

    resize(pic.size());
    update();
}

QPixmap CardPic::GetPic()
{
    return m_pic;
}

void CardPic::SetOwner(Player* owner)
{
    m_owner = owner;
}

Player* CardPic::GetOwner()
{
    return m_owner;
}

void CardPic::SetCard(Card card)
{
    m_card = card;
}

Card CardPic::GetCard()
{
    return m_card;
}

void CardPic::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if (m_frontSide)
    {
        painter.drawPixmap(rect(), m_pic);
    }
    else
    {
        painter.drawPixmap(rect(), m_back);
    }

}

void CardPic::mousePressEvent(QMouseEvent* event)
{
    emit NotifySelected(event->button());

    QWidget::mousePressEvent(event);
}

void CardPic::SetFrontSide(bool frontSide)
{
    if (m_frontSide != frontSide)
    {
        m_frontSide = frontSide;
        update();
    }
}

bool CardPic::IsFrontSide()
{
    return m_frontSide;
}

void CardPic::SetSelected(bool selected)
{
    m_selected = selected;
}

bool CardPic::IsSelected()
{
    return m_selected;
}
