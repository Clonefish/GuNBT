#ifndef GUNBT_H
#define GUNBT_H
typedef enum gnbt_type : unsigned char {
    gnbt_type_end,
    gnbt_type_byte,
    gnbt_type_short,
    gnbt_type_int,
    gnbt_type_long,
    gnbt_type_float
    gnbt_type_double,
    gnbt_type_byte_array,
    gnbt_type_string,
    gnbt_type_list,
    gnbt_type_compound,
    gnbt_type_int_array
} gnbt_type;

typedef struct gnbt_node {
    gnbt_type type;
    char * name;

    union data
    {
        int8_t  tag_byte;
        int16_t tag_short;
        int32_t tag_int;
        int64_t tag_long;
        float tag_float;
        double tag_double;

        struct nbt_byte_array {
            unsigned char * data;
            int32_t length;
        } tag_byte_array;

        struct nbt_string {
            char * tag_string;
            int32_t length;
        } tag_string;

        struct nbt_list {
            gnbt_node * data;
            int8_t type;
            int32_t length;
        } tag_list;

        struct nbt_compound {
            gnbt_node * data;
            int32_t length;
        } tag_compiund;

        struct nbt_int_array {
            int32_t * data;
            int32_t length;
        } tag_int_array;

    } nbt_payload;
} gnbt_node;

void gnbt_parse_file(FILE * fp);
void gnbt_save_tree(nbt_node * tree, const char * path);
void gnbt_free(nbt_node);
gnbt_node * nbt_find_by_name(nbt_node * tree, const char * name);
gnbt_node * nbt_add_to_compound(nbt_node * tree, nbt_node * node);
#endif
