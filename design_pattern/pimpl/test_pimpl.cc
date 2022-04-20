#include "widget.h"

int main()
{
    Widget widget_nonconst(1);
    const Widget widget_const(2);

    widget_nonconst.Draw();
    widget_const.Draw();

    return 0;
}