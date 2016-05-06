//2016年05月05日22:03:45
#include <gtk/gtk.h>

GtkWidget* word_label;
GtkWidget* seq_label;
GtkWidget* level_label;
GtkWidget* time_label;
GtkWidget* table;



void on_begin_clicked(GtkButton* button, gpointer data)
{
	
}


void on_exit_clicked(GtkButton* button, gpointer data)
{

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

	
	//填充游戏区域（删）
	pix = gdk_pixbuf_new_from_file("back.png", NULL);
	for (int i = 0; i < 30; i += 1)
	{
		for (int j = 0; j < 20; j += 1)
		{
			logo = gtk_image_new_from_pixbuf(pix);
			gtk_table_attach(GTK_TABLE(table), logo,
				i, i+1, 
				j, j+1,
				GTK_FILL | GTK_EXPAND , 
				GTK_FILL | GTK_EXPAND,
				0, 0);
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







	
	gtk_widget_show_all(window);
	gtk_main();

	return FALSE;
}
