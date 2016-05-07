//2016年05月05日22:03:45
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#define BACK -1

//上下左右四个方向
typedef enum
{
	LEFT, UP, RIGHT, DOWN
}Dir;

//相对位置
typedef struct
{
	int x, y;
}Point;

//定义小蛇
typedef struct
{
	Point head;			//小蛇头部
	Point tail;			//小蛇尾部
	gint len;			//小蛇长度	
	Dir dir;			//运动方向
}Snake;


GtkWidget* word_label;		//单词标签
GtkWidget* seq_label;		//序列标签
GtkWidget* level_label;		//等级标签
GtkWidget* scores_label;	//总分标签
GtkWidget* time_label;		//时间标签
GtkWidget* table;			//30*20表格
GdkPixbuf* pix_snake;		//小蛇图片
GdkPixbuf* pix_back;		//背景图片
GtkWidget* area[30][20];	//活动区域

Snake snake;				//小蛇
gint stat[30][20];			//存储状态


//填涂(x, y)区域
void PutPix(gint s, gint x, gint y)
{
	switch (s)
	{
	case BACK:
		gtk_image_set_from_pixbuf(GTK_IMAGE(area[x][y]), pix_back);	
		break;
	default:
		gtk_image_set_from_pixbuf(GTK_IMAGE(area[x][y]), pix_snake);	
		break;
	}
}

//更新小蛇尾部坐标
void UpTail()
{
	switch (stat[snake.tail.x][snake.tail.y])
	{
	case LEFT:
		stat[snake.tail.x][snake.tail.y] = BACK;
		snake.tail.x--;
		break;
	case RIGHT:
		stat[snake.tail.x][snake.tail.y] = BACK;
		snake.tail.x++;
		break;
	case UP:
		stat[snake.tail.x][snake.tail.y] = BACK;
		snake.tail.y--;
		break;
	case DOWN:
		stat[snake.tail.x][snake.tail.y] = BACK;
		snake.tail.y++;
		break;
	}
}

//移动
void Move()
{
	switch (snake.dir)
	{
		case LEFT:
			PutPix(BACK, snake.tail.x, snake.tail.y);		//清除尾部
			UpTail();										//更新尾部
			PutPix(LEFT, snake.head.x-1, snake.head.y);		//填充头部
			stat[snake.head.x][snake.head.y] = LEFT;		//更新头部
			snake.head.x--;		
			break;
		case UP:
			PutPix(BACK, snake.tail.x, snake.tail.y);		//清除尾部
			UpTail();										//更新尾部
			PutPix(LEFT, snake.head.x, snake.head.y-1);		//填充头部
			stat[snake.head.x][snake.head.y] = UP;			//更新头部
			snake.head.y--;	
			break;			
		case RIGHT:
			PutPix(BACK, snake.tail.x, snake.tail.y);		//清除尾部
			UpTail();										//更新尾部
			PutPix(LEFT, snake.head.x+1, snake.head.y);		//填充头部
			stat[snake.head.x][snake.head.y] = RIGHT;		//更新头部
			snake.head.x++;	
			break;
		case DOWN:
			PutPix(BACK, snake.tail.x, snake.tail.y);		//清除尾部
			UpTail();										//更新尾部
			PutPix(LEFT, snake.head.x, snake.head.y+1);		//填充头部
			stat[snake.head.x][snake.head.y] = DOWN;		//更新头部
			snake.head.y++;	
			break;
	}
}


//上下左右按键读入
void KeyPress(GtkWidget* widget, GdkEventKey* event, gpointer data)
{
	switch (event->keyval)
	{
	case GDK_Up:
		if (snake.dir != DOWN)	snake.dir = UP;
		break;
	case GDK_Down:
		if (snake.dir != UP)	snake.dir = DOWN;
		break;
	case GDK_Left:
		if (snake.dir!= RIGHT)	snake.dir = LEFT;
		break;
	case GDK_Right:
		if (snake.dir != LEFT)	snake.dir = RIGHT;
		break;
	}
}


//初始化小蛇活动区域
void AreaInit()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			area[i][j] = gtk_image_new_from_pixbuf(pix_back);
			gtk_table_attach(GTK_TABLE(table), area[i][j],
								i, i+1, 
								j, j+1,
								GTK_FILL | GTK_EXPAND , 
								GTK_FILL | GTK_EXPAND,
								0, 0);
		}
	}
}

//初始化
void Init()
{

	for (int i = 0; i < 30; i++)			//初始化状态
		for (int j = 0; j < 20; j++)
			stat[i][j] = BACK;

	snake.len = 3;								//初始化小蛇
	snake.head.x = 3;
	snake.head.y = 3;
	snake.tail.x = 1;
	snake.tail.y = 3;
	snake.dir = RIGHT;

	stat[3][3] = stat[2][3] = stat[1][3] = RIGHT;	//修改状态

	//载入图片
	pix_snake = gdk_pixbuf_new_from_file("snake.png", NULL);		//小蛇图片
	pix_back = gdk_pixbuf_new_from_file("back.png", NULL);			//背景图片

	AreaInit();				//初始化30*20活动区域

	gtk_image_set_from_pixbuf(GTK_IMAGE(area[3][3]), pix_snake);	//初始化小蛇图像
	gtk_image_set_from_pixbuf(GTK_IMAGE(area[2][3]), pix_snake);
	gtk_image_set_from_pixbuf(GTK_IMAGE(area[1][3]), pix_snake);
}



//开始
void Start()
{
	Init();

}







gint choose = 0;

//开始（暂停）按钮
void on_begin_clicked(GtkButton* button, gpointer data)
{
	static gint timer;
	if (0 == choose)
	{
		timer = gtk_timeout_add(200, (GtkFunction)Move, NULL);
		gtk_button_set_label(button, "暂停");
		choose = 1;
	}
	else
	{
		gtk_timeout_remove(timer);
		gtk_button_set_label(button, "开始");
		choose = 0;
	}
}



//退出按钮
void on_exit_clicked(GtkButton* button, gpointer data)
{
//	draw_exit_window();
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
	g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(KeyPress), NULL);		//按键信号

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
/*
	//游戏LOGO
	GtkWidget *logo;
	pix = gdk_pixbuf_new_from_file("logo.png", NULL);
	logo = gtk_image_new_from_pixbuf(pix);
	gtk_box_pack_start(GTK_BOX(hbox), logo, FALSE, FALSE, 0);		
*/	
	//水平排放
	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 5);
	
	//30*20表格容器
	table = gtk_table_new(30, 20, FALSE);
	gtk_box_pack_start(GTK_BOX(hbox), table, TRUE, TRUE, 5);

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




	Start();
	
	gtk_widget_show_all(window);
	gtk_main();

	return FALSE;
}

