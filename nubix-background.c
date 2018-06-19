#include "nubix-background.h"

static struct nubix_background background;

GtkWindow* nubix_background_get_wrapper()
{
    return background.wrapper;
}

int nubix_background_setup(gint width, gint height)
{
    background.wrapper = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    background.scene = gtk_fixed_new();
    smlogifo("preparing nubix-backgrund core terminated");

	gtk_widget_set_name(GTK_WIDGET(background.wrapper), "win_background");
    gtk_widget_set_size_request(GTK_WIDGET(background.wrapper), width, height);
    gtk_window_set_decorated(background.wrapper, FALSE);
    gtk_window_set_resizable(background.wrapper, FALSE);
    
    gtk_container_add(GTK_CONTAINER(background.wrapper), background.scene);
    gtk_widget_set_name(GTK_WIDGET(background.scene), "lay_background");
    smlogifo("adjusting nubix-background terminated");

    gtk_widget_show_all(GTK_WIDGET(background.wrapper));
    return 0;
}