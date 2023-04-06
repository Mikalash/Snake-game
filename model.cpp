#include "controller.cpp"
#include "objects.cpp"

class model
{
    private:
        class view* vi;
        class controller* cont;

        class snake* sn;
        class border* br;
        class food* fd;

        bool is_game_continue;
    public:
        model(view* in_vi, controller* in_cont, snake* in_sn, border* in_br, food* in_fd)
        {
            vi = in_vi;
            cont = in_cont;
            sn = in_sn;
            br = in_br;
            fd = in_fd;

            is_game_continue = true;
        }

        void draw()
        {
            fd->draw_food(vi);
            sn->draw_body(vi);
            br->draw_border(vi);
        }

        void pull_events()
        {
            int x_head, y_head;
            sn->give_head(&x_head, &y_head);

            if (br->is_border(x_head, y_head) || sn->is_snake(x_head, y_head))
            {
                is_game_continue = false;
                return;
            }
            if (fd->is_food(x_head, y_head))
            {
                fd->del_food(vi);
                sn->add_body();
                fd->spawn(sn);
            }
            else
                sn->move_body(vi);
        }

        void pull_user_action()
        {
            if(vi->is_win_resize())
            {
                vi->clear_win();
                draw();
            }

            switch (cont->get_key())
            {
                case 'w':
                    sn->ch_dir(1);
                    break;
                case 'd':
                    sn->ch_dir(2);
                    break;
                case 's':
                    sn->ch_dir(3);
                    break;
                case 'a':
                    sn->ch_dir(4);
                    break;
            }
        }

        void next_frame()
        {
            pull_events();
            draw();
        }

        bool stop_game()
        {
            return !is_game_continue;
        }
};

