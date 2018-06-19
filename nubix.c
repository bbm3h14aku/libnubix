/*
 * nubix.c
 *
 *  Created on: 13.06.2018
 *      Author: jan
 */
#include "nubix.h"

void nubix_set_mouse_pos(int did)
{
	Display *display;
	Window root;
	display = XOpenDisplay(did);
	root = XRootWindow(display, 0);
	XSelectInput(display, root, KeyReleaseMask);
	XWarpPointer(display, None, root, 0, 0, 0, 0, 100, 100);
	XFlush(display);
}

void nubix_widget_get_preferred_size(GtkWidget *target, gint *height, gint *width)
{
	gint tmp;
	GTK_WIDGET_GET_CLASS(target)->get_preferred_height(target, height, &tmp);
	GTK_WIDGET_GET_CLASS(target)->get_preferred_width(target, width, &tmp);
}

static gboolean update_clockstr(gpointer data)
{
	struct nubix_clock* clock = (struct nubix_clock *) data;
	char *timebuf = gettimestamp();
	if(timebuf != NULL)
	{
		gtk_label_set_text(clock->label, timebuf);
		free(timebuf);
		return clock->cont;
	}
}

void clock_start(struct nubix_clock *ptr)
{
	smlogifo("\tcreating new nubix clock");
	g_timeout_add_seconds(1, update_clockstr, (gpointer) ptr);
	ptr->cont = TRUE;
	ptr->start = TRUE;
}

void nubix_error(const char *message)
{
	//TODO: implement my logging librarie
	//printf("%s\n", message);
	smlogerre(message);
}

int nubix_get_screen_resolution(struct _screen_resolution *display)
{
	GdkScreen *screen = gdk_screen_get_default();
	display->height = gdk_screen_get_height(screen);
	display->width = gdk_screen_get_width(screen);

	if(display->height > 0 && display->width > 0)
		return 0;
	return 1;
}

int nubix_xprobe()
{
	return (XOpenDisplay(NULL) ? 0 : 1);
}