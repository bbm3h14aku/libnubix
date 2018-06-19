/*
 * nubix.h
 *
 *  Created on: 13.06.2018
 *      Author: jan
 */

#ifndef _NUBIX_H
#define _NUBIX_H

#include <gtk/gtk.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>


#include "smlog.h"

struct nubix_clock {
	gboolean *cont;
	gboolean *start;
	GtkLabel *label;
};

struct _screen_resolution {
	gint height;
	gint width;
};

typedef struct nubix_clock nubix_clock_t;

void nubix_set_mouse_pos(int did);
void nubix_error(const char *message);
int nubix_get_screen_resolution(struct _screen_resolution *display);
int nubix_xprobe();
void nubix_enable_theming();
void nubix_widget_get_preferred_size(GtkWidget *target, gint *height, gint *width);

void clock_start(struct nubix_clock *ptr);

#define nubix_new_window(window, title, h, w) \
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); \
	gtk_window_set_title(window, title); \
	gtk_window_set_size_request(window, h, w); \

extern GtkWidget* nubix_new_bar();

#include "nubix-taskbar.h"

#endif // _NUBIX_H


