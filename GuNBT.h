#ifndef GUNBT_H
#define GUNBT_H
typedef struct gnbt_node {
    gnbt_type type;
    char * name;

    union
    {
        int8_t  tag_byte;
        int16_t tag_short;
        int64_t tag_long;

        struct gnbt_byte_array {
            unsigned char * data;
            int32_t length;
        } gtag_byte_array;

        struct gnbt_list {
            struct nbt_node * data;
        } * gtag_compound;
    } gnbt_payload;
} gnbt_node;

void gnbt_parse_file(FILE * fp);
void gnbt_save_tree(nbt_node * tree, const char * path);
void gnbt_free(nbt_node);
gnbt_node * nbt_find_by_name(nbt_node * tree, const char * name);
gnbt_node * nbt_add_to_compound(nbt_node * tree, nbt_node * node);
#endif
