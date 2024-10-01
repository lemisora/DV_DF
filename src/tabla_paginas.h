#ifndef TABLA_H
#define TABLA_H

typedef struct entrada table_entry_t;

struct entrada{
    int b_permiso;
    int b_ref;
    int b_mod;
    int b_pres_aus;
    int b_cache;
    int n_frame;
};

#endif
