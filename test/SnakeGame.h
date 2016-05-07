#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

typedef enum Direction { UP=1,DOWN=-1,LEFT=2,RIGHT=-2} Direction;

struct Point
{
    int i,j;

    Point():i(0),j(0){}
    Point(int a,int b):i(a),j(b){}
    bool operator==(const Point& p){return (i == p.i) && (j == p.j);}
    bool operator!=(const Point& p){return !operator==(p);}
};


bool is_out_bound(Point&);
bool is_dead();

void init_game_zone();
void snake_move();
void snake_show();


int game_run();
void game_over();

//call backs 
void on_keyboard(GtkWidget* ,GdkEventKey *,gpointer);
#endif