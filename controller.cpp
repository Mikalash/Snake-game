#include <unistd.h>
#include <poll.h>
#include <termios.h>

#include <stdio.h>

class controller
{
    public:
        virtual char get_key()
        {}
};

class t_controller : public controller
{
    private:
        struct termios stdin_param_save;
        struct termios stdin_param;
    public:
        t_controller() : controller()
        {
            tcgetattr(STDIN_FILENO, &stdin_param_save);
            tcgetattr(STDIN_FILENO, &stdin_param);

            cfmakeraw(&stdin_param);
            stdin_param.c_lflag |= ISIG;
            tcsetattr(STDIN_FILENO, TCSANOW, &stdin_param);
        }

        char get_key()
        {
            char c;
            struct pollfd keyb = {0, POLLIN, 0};
            int bytes_read = 0;

            while (poll(&keyb, 1, 0) == 1)
                bytes_read = read(0, &c, 1);

            return c;
        }

        ~t_controller()
        {
            tcsetattr(STDIN_FILENO, TCSANOW, &stdin_param_save);
        }
};
