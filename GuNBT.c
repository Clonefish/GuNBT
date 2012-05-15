#include "GuNBT.h"
#include <errno.h>
#define null 0

char * gnbt_read_name(unsigned char * stream)
{
    char *
}

gnbt_node * gnbt_read_node(unsigned char * stream)
{
    gnbt_node * node = malloc(sizeof(gnbt_node));
    node->type = *++stream;
    node->name = (node->type != gnbt_type_end) ? gnbt_readname(stream) : "END";
    switch (node->type)
    {
        case gnbt_type_end:
            return node;
        case gnbt_type_byte:
            node->data->tag_byte = *++stream;
            break;
        case gnbt_type_short:
            node->data->tag_short = *stream;
            stream += 2;
            break;
        case gnbt_type_int:
            node->data->tag_int = *stream;
            stream += 4;
            break;
        case gnbt_type_long:
            node->data->tag_long = *stream;
            stream += 8;
            break;
        case gnbt_type_float:
            node->data->tag_float = *stream;
            stream += 4;
            break;
        case gnbt_type_double:
            node->data->tag_double = *stream;
            stream += 8;
            break;
        case gnbt_type_byte_array:
            stream += gnbt_read_byte_array(node, stream);
            break;
        case gnbt_type_string:
            stream += gnbt_read_string(node, stream);
            break;
        case gnbt_type_list:
            stream += gnbt_read_list(node, stream);
            break;
        case gnbt_type_short:
            stream += gnbt_read_int_array(node, stream);
            break;

    }
    return node;
}


void gnbt_parse_file(FILE * fp)
{
    unsigned char * stream = null;
    gnbt_node * tree = gnbt_readnode(stream);

}

void gnbt_save_tree(nbt_node * tree, const char * path)
{

}

void gnbt_free(nbt_node)
{

}

gnbt_node * nbt_find_by_name(nbt_node * tree, const char * name)
{

}

gnbt_node * nbt_add_to_compound(nbt_node * tree, nbt_node * node)
{

}
