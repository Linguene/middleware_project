#ifndef TUPLE_H
#define TUPLE_H

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define tuple_element_type_template_bit 0x8

typedef enum TupleElementType {
    tuple_int,
    tuple_float,
    tuple_string,
    tuple_int_template = tuple_int | tuple_element_type_template_bit,
    tuple_float_template = tuple_float | tuple_element_type_template_bit,
    tuple_string_template = tuple_string | tuple_element_type_template_bit
} TupleElementType;

typedef union TupleElementData {
    int32_t data_int;
    float data_float;
    char* data_string;
} TupleElementData;

typedef struct TupleElement {
    TupleElementType type;
    TupleElementData data;
} TupleElement;

typedef struct Tuple {
    uint32_t element_count;
    TupleElement* elements;
} Tuple;

/* Stringi są brane na własność, są głęboko kopiowane. */
Tuple tuple_new(uint32_t element_count, ...);
void tuple_free(Tuple tuple);

int32_t tuple_get_int(Tuple const* tuple, size_t index);
float tuple_get_float(Tuple const* tuple, size_t index);
char const* tuple_get_string(Tuple const* tuple, size_t index);

bool tuple_match(Tuple const* t1, Tuple const* t2);

char* tuple_serialise(Tuple const* tuple, char* buffer);
char const* tuple_deserialise(Tuple* tuple, char const* buffer);
size_t tuple_serialised_length(Tuple const* tuple);

char const* tuple_to_string(Tuple const* tuple);

#endif
