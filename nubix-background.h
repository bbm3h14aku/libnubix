#ifndef _LIBNUBIX_NUBIX_BACKGROUND_H
#define _LIBNUBIX_NUBIX_BACKGROUND_H

#include "nubix.h"

struct nubix_background {
    GtkWindow *wrapper;
    GtkFixed *scene;
};

typedef struct nubix_background nubix_background_t;

int nubix_background_setup(gint width, gint height);

#endif // _LIBNUBIX_NUBIX_BACKGROUND_H