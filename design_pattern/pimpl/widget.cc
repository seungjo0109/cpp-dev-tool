#include "widget.h"

void Widget::Draw() const
{
    pimpl_->Draw(*this);
}

void Widget::Draw()
{
    pimpl_->Draw(*this);
}