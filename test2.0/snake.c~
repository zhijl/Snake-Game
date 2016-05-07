//2016年05月05日22:03:45
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <list>

#include "SnakeGame.h"

using	 std::list;

#define   WIDTH   30
#define   HEIGHT  20

#define	  TICK    150  //timer tick


list<Point> Snake;	//snake body
//how to represent words?

Direction  cur_dir = RIGHT;	//current position
Direction  pre_dir = RIGHT;	//previous position

int 	   timer_id;	//global timer id

GtkWidget* word_label;
GtkWidget* seq_label;
GtkWidget* level_label;
GtkWidget* time_label;
GtkWidget* table;

GtkWidget* game_zone[HEIGHT][WIDTH];

GdkPixbuf* pix_bg;	//background
GdkPixbuf* pix_snake;	//snake body
GdkPixbuf* chars[26*2];	//characters [a..z] [A..Z] ?



void init_game_zone()
{
	/*Init backgroud,then need to attach to table*/
	for (int i = 0 ; i < HEIGHT ; ++i)
		for (int j = 0 ; j < WIDTH ; ++j)
			game_zone[i][j] = gtk_image_new_from_pixbuf(pix_bg);


	/*init snake body*/
	Point p(HEIGHT / 2 , WIDTH /2);
	Snake.push_back(p);

	/*show snake*/
	gtk_image_set_from_pixbuf(GTK_IMAGE(game_zone[p.i][p.j]) , pix_snake);
}


int game_run()	//the main
{
	snake_move();

	if( is_dead() ) {
		game_over();
		//other thing
		return FALSE; //so timer stop calling game_run()
	}

	else  {
		snake_show();
		//update score ,words ...etc
	}


	return TRUE;	//so timer repeat calling
}

void game_over()
{
	gtk_timeout_remove(timer_id);

	GtkWidget* dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,
												GTK_BUTTONS_OK,"You Are Dead!\n");

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

	//reinitialize all so prepare to restart?
}

bool is_in_bound(Point& p)
{
	return	(p.i >= 0) && (p.j >= 0) && (p.i < HEIGHT) && (p.j < WIDTH)	;
}


bool is_dead()
{
	return !is_in_bound(*Snake.begin());
}

void snake_move() 
{
	if(cur_dir + pre_dir == 0) cur_dir = pre_dir;   //不能直接回转

    Point head_next(Snake.begin()->i,Snake.begin()->j);

    switch(cur_dir) {	
        case LEFT:
            head_next.j = head_next.j - 1;
            break;
        case RIGHT:
            head_next.j = head_next.j + 1;
            break;
        case UP:
            head_next.i = head_next.i - 1;
            break;
        case DOWN:
            head_next.i = head_next.i + 1;
            break;
    }

   	Snake.push_front(head_next);

    pre_dir = cur_dir;
}


void snake_show()
{
	list<Point>::iterator           head = Snake.begin();
    list<Point>::reverse_iterator   tail = Snake.rbegin();

    gtk_image_set_from_pixbuf(GTK_IMAGE(game_zone[head -> i][head -> j]) , pix_snake);
    gtk_image_set_from_pixbuf(GTK_IMAGE(game_zone[tail -> i][tail -> j]) , pix_bg);

    if(1)	//if(snake doesn't eat right char)
    	Snake.pop_back();
}


void on_keyboard(GtkWidget* ,GdkEventKey *key, gpointer)
{
 	int keyval = key->keyval;

    if(keyval==GDK_KEY_W||keyval==GDK_KEY_w||keyval==GDK_Up)
        cur_dir = UP;

    else if(keyval==GDK_KEY_S||keyval==GDK_KEY_s||keyval==GDK_Down)
        cur_dir = DOWN;

    else if(keyval==GDK_KEY_A||keyval==GDK_KEY_a||keyval==GDK_Left)
        cur_dir = LEFT;

    else if(keyval==GDK_KEY_D||keyval==GDK_KEY_d||keyval==GDK_Right)
        cur_dir = RIGHT;
}


void on_begin_clicked(GtkButton* button, gpointer data)
{
	timer_id = gtk_timeout_add(TICK,(GtkFunction)game_run,NULL);

	//add a "Reset" button?
}


void on_exit_clicked(GtkButton* button, gpointer data)
{
	gtk_main_quit();
}


int main(int argc, char* argv[])
{
	GtkWidget* window;
	GtkWidget* vbox;
	GtkWidget* hbox;
	GtkWidget* button;

	GtkWidget* frame;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_window_set_title(GTK_WINDOW(window), "Snake Game");
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);		//禁止调整窗口大小
	gtk_window_set_position(GTK_WINDOW(window),  GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);	//设置窗口边框厚度
	
	//垂直排放
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	//水平排放
	hbox = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(vbox), hbox);

	//“单词”标签
	frame = gtk_frame_new("单词");
	word_label = gtk_label_new("    Eureka    ");
	
	gtk_container_add(GTK_CONTAINER(frame), word_label);
	gtk_box_pack_start(GTK_BOX(hbox), frame, TRUE, TRUE, 5);

	//“单词序列”标签
	frame = gtk_frame_new("单词序列");
	seq_label = gtk_label_new("       E u r e k a      ");
	gtk_container_add(GTK_CONTAINER(frame), seq_label);
	gtk_box_pack_start(GTK_BOX(hbox), frame, TRUE, TRUE, 3);	

	//游戏LOGO
	GdkPixbuf *pix = NULL;
	GtkWidget *logo;
	pix = gdk_pixbuf_new_from_file("logo.png", NULL);
	logo = gtk_image_new_from_pixbuf(pix);
	gtk_box_pack_start(GTK_BOX(hbox), logo, FALSE, FALSE, 0);		
	
	//水平排放
	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 5);
	
	//30*20表格容器
	table = gtk_table_new(30, 20, FALSE);
	gtk_box_pack_start(GTK_BOX(hbox), table, TRUE, TRUE, 5);

	
	//填充游戏区域（删）modified
	pix_bg = gdk_pixbuf_new_from_file("back.png" , NULL);
	pix_snake = gdk_pixbuf_new_from_file("snake.png" , NULL);

	init_game_zone();

	for (int i = 0; i < HEIGHT ; i += 1)
	{
		for (int j = 0; j < WIDTH ; j += 1)
		{
		
			gtk_table_attach_defaults(GTK_TABLE(table), game_zone[i][j],
				j, j+1, 	
				i, i+1);
				//GTK_FILL | GTK_EXPAND , //if i use gtk_table_attach ,i get error  
				//GTK_FILL | GTK_EXPAND,
				//0, 0);
		}
	}

	//垂直排放
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 3);
	
	//“开始”按钮
	button = gtk_button_new_with_label("开始");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_begin_clicked), NULL);	//on_begin_clicked
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 3);

	//“退出”按钮
	button = gtk_button_new_with_label("退出");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_exit_clicked), NULL);	//on_exit_clicked
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 3);

	//“等级”标签
	frame = gtk_frame_new("等级");
	level_label = gtk_label_new("\n1-1\n\n");
	gtk_container_add(GTK_CONTAINER(frame), level_label);
	gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 3);

	//“时间”标签
	frame = gtk_frame_new("时间");
	time_label = gtk_label_new("\n19:31:51\n");
	gtk_container_add(GTK_CONTAINER(frame), time_label);
	gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 3);

	//keyboard call back
	g_signal_connect(G_OBJECT(window),"key_press_event",G_CALLBACK(on_keyboard),NULL);




	
	gtk_widget_show_all(window);
	gtk_main();

	return FALSE;
}
