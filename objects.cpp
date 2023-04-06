#include <stdlib.h>
#include <vector>
#include <time.h>
#include "view.cpp"

class snake
{
    private:
        std::vector <std::pair <int, int>> body;
        int x_dir;
        int y_dir;
    public:
        snake(int pix_x, int pix_y)
        {
            body.push_back(std::pair(pix_x / 2, pix_y / 2));
            x_dir = 0;
            y_dir = -1;
        }

        void add_body()
        {
            body.push_back(std::pair(body[body.size() - 1].first + x_dir, body[body.size() - 1].second + y_dir));
        }

        void move_body(struct view* vi)
        {
            vi->draw(body[0].first, body[0].second, bc_pix);
            for (int i = 0; i < body.size() - 1; i++)
                body[i] = body[i + 1];

            body[body.size() - 1].first += x_dir;
            body[body.size() - 1].second += y_dir;
        }

        void ch_dir(int dir)
        {
            if (body.size() > 1)
                if (body[body.size() - 1].first + x_dir == body[body.size() - 2].first
                && body[body.size() - 1].second + y_dir == body[body.size() - 2].second)
                    return;
            switch(dir)
            {
                case 1:
                    x_dir = 0;
                    y_dir = -1;
                    break;
                case 2:
                    x_dir = 1;
                    y_dir = 0;
                    break;
                case 3:
                    x_dir = 0;
                    y_dir = 1;
                    break;
                case 4:
                    x_dir = -1;
                    y_dir = 0;
                    break;
            }
        }

        void draw_body(struct view* vi)
        {
            for (int i = 0; i <= body.size(); i++)
                vi->draw(body[i].first, body[i].second, sn_pix);
        }

        void give_head(int* x, int* y)
        {
            *x = body[body.size() - 1].first;
            *y = body[body.size() - 1].second;
        }

        bool is_snake(int x, int y)
        {
            for (int i = 0; i < body.size() - 1; i++)
                if(body[i].first == x && body[i].second == y)
                    return true;
            return false;
        }
};

class border
{
    private:
        int x_len;
        int y_len;
    public:
        border(int pix_x, int pix_y)
        {
            x_len = pix_x;
            y_len = pix_y;
        }

        void draw_border(struct view* vi)
        {
            for(int i = 1; i <= x_len; i++)
            {
                vi->draw(i, 1, br_pix);
                vi->draw(i, y_len, br_pix);
            }
            for(int i = 1; i <= y_len; i++)
            {
                vi->draw(1, i, br_pix);
                vi->draw(x_len, i, br_pix);
            }
        }

        bool is_border(int x, int y)
        {
            if (x <= 1 || x >= x_len || y <= 1 || y >= y_len)
                return true;
            return false;
        }
};

class food
{
    private:
        int x;
        int y;
        int x_len;
        int y_len;
    public:
        food(int pix_x, int pix_y, class snake* sn)
        {
            x_len = pix_x;
            y_len = pix_y;

            srand(time(NULL));
            spawn(sn);
        }

        void spawn(class snake* sn)
        {
            while (1)
            {
                int rand_x = rand() % (x_len - 2) + 2;
                int rand_y = rand() % (y_len - 2) + 2;
                if (!sn->is_snake(rand_x, rand_y))
                {
                    x = rand_x;
                    y = rand_y;
                    break;
                }
            }
        }

        void draw_food(struct view* vi)
        {
            vi->draw(x, y, fd_pix);
        }

        void del_food(struct view* vi)
        {
            vi->draw(x, y, bc_pix);
        }

        bool is_food(int in_x, int in_y)
        {
            if (x == in_x && y == in_y)
            {
                return true;
            }
            return false;
        }
};
