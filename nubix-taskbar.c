#include "nubix-taskbar.h"

static gboolean _start_timer = FALSE;
static gboolean continue_timer = FALSE;
static gboolean f_startmenu = FALSE;

static GtkWindow *startmenu;

struct nubix_taskbar taskbar;

static gboolean update_timestr(gpointer data)
{
    GtkLabel *tmp = taskbar.datetime;
	char *timestr = gettimestamp();
    //smlogdbge("updating timestr ", timestr);
	gtk_label_set_text(tmp, timestr);
	free(timestr);
	return continue_timer;
}

void start_timer()
{
	smlogifo("installing timer set timet interval to 1 Second");
	g_timeout_add_seconds(1, update_timestr, NULL) ;
	_start_timer =TRUE;
	continue_timer = TRUE;
}

static void win_startmenu_destroy(gpointer data)
{
    f_startmenu = FALSE;
    gtk_widget_destroy(GTK_WIDGET(data));
}

static void win_startmenu_show()
{
    smlogifo("received signal to open startmenu");
    if(f_startmenu == FALSE)
    {
        GtkBuilder *builder = gtk_builder_new_from_file("res/desktop_wid.ui");
        GtkWindow *startmenu = GTK_WINDOW(gtk_builder_get_object(builder, "win_startmenu"));

        GtkButton *poweroff = GTK_BUTTON(gtk_builder_get_object(builder, "btn_poweroff"));
        g_signal_connect(poweroff, "clicked", gtk_main_quit, NULL);
        g_signal_connect(startmenu, "destroy", win_startmenu_destroy, (gpointer) startmenu);

        gtk_widget_show_all(GTK_WIDGET(startmenu));
        f_startmenu = TRUE;
    }
    else
    {
        smlogifo("startmenu is already open");
    }
}

void nubix_taskbar_set_pos(gint parent_w, gint parent_h)
{
    gtk_window_move(taskbar.wrapper, 0, parent_h - 25);
}

int nubix_taskbar_setup(gint width, gint height)
{
    GtkBuilder *builder = gtk_builder_new_from_file("../nubix-desktop-env/res/desktop_wid.ui");
    smlogifo("preparing gtk-builder terminated");
    
    taskbar.wrapper = GTK_WINDOW(gtk_builder_get_object(builder, "win_taskbar"));
    gtk_widget_set_size_request(GTK_WIDGET(taskbar.wrapper), width, height);
    gtk_window_set_decorated(taskbar.wrapper, FALSE);
    gtk_window_set_resizable(taskbar.wrapper, FALSE);
    //gtk_window_set_transient_for(taskbar.wrapper, parent);
    gtk_widget_set_name(GTK_WIDGET(taskbar.wrapper), "win_taskbar");
    smlogifo("setting up taskbar core terminated");

    taskbar.datetime = GTK_LABEL(gtk_builder_get_object(builder, "lbl_datetime"));
    gtk_widget_set_name(GTK_WIDGET(taskbar.datetime), "tb_datetime");
    taskbar.starter = GTK_BUTTON(gtk_builder_get_object(builder, "btn_starter"));
    gtk_widget_set_name(GTK_WIDGET(taskbar.starter), "tb_starter");
    smlogifo("setting up taskbar elements terminated");
    
    startmenu = GTK_WINDOW(gtk_builder_get_object(builder, "win_startmenu"));
    g_signal_connect(taskbar.starter, "clicked", win_startmenu_show, NULL);
    g_signal_connect(taskbar.wrapper, "destroy", gtk_main_quit, NULL);
    smlogifo("setting up taskbar widgets terminated");
    
    gtk_widget_show_all(GTK_WIDGET(taskbar.wrapper));
    start_timer();
    g_object_unref(builder);
    smlogifo("setting up taskbar complete");
}
/* 
int main(int argc, char **argv)
{  
    gtk_init(&argc, &argv);
    nubix_taskbar_setup();
    gtk_main();
}
*/