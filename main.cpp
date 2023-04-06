#include <iostream>

#include "model.cpp"

int main()
{
    class t_view vi(20, 10);
    class t_controller cont;

    class snake sn(20, 10);
    class border br(20, 10);
    class food fd(20, 10, &sn);

    class model mod(&vi, &cont, &sn, &br, &fd);

    while (1)
    {
        mod.pull_user_action();
        mod.next_frame();
        if (mod.stop_game())
        {
            std::cout << "END";
            break;
        }
        usleep(400000);
    }
}
