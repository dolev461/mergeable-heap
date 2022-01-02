#pragma once

typedef enum op_id_e {
    UNKNOWN = -1,
    MAKEHEAP = 0,
    INSERT = 1,
} op_id_t;

typedef struct op_makeheap_s {
    op_id_t id;
} op_makeheap_t;

typedef struct op_insert_s {
    op_id_t id;
    int value;
} op_insert_t;

typedef union op_t {
    op_id_t id;
    op_makeheap_t makeheap;
    op_insert_t insert;
} op_t;
