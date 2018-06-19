#ifndef _NUBIX_DESKTOP_ENV_TASKBAR
#define _NUBIX_DESKTOP_ENV_TASKBAR
#include <gtk/gtk.h>

#include "smlog.h"

struct nubix_taskbar {
    GtkWindow *wrapper;
    GtkHBox *layout;
    GtkLabel *datetime;
    GtkButton *starter;
    GtkButtonBox *tasklist;
};

typedef struct nubix_taskbar nubix_taskbar_t;

extern nubix_taskbar_t taskbar;

int nubix_taskbar_setup(gint width, gint height);

#endif // _NUBIX_DESKTOP_ENV_TASKBAR