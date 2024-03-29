#ifndef TUPLE_SPACE_H
#define TUPLE_SPACE_H

#include "tuple.h"

#include "arduino.h"

#ifndef PSIR_ARDUINO

#include <threads.h>

/* TupleSpace zarządza zasobami wszystkich krotek w tablicy tuples,
 * więc nie zwalniamy samemu krotek (również template), 
 * które zostały wstawione do TupleSpace,
 * ale zwalniamy te, które wzięliśmy z TupleSpace. */
typedef struct TupleSpace {
    size_t tuple_count;
    Tuple* tuples;
    mtx_t tuples_mtx;
    cnd_t tuples_cnd;
} TupleSpace;

#endif

typedef enum TupleSpaceOperationBlockingMode {
    tuple_space_blocking, tuple_space_nonblocking
} TupleSpaceOperationBlockingMode;

typedef enum TupleSpaceOperationStatus {
    tuple_space_success, tuple_space_failure
} TupleSpaceOperationStatus;

typedef struct TupleSpaceOperationResult {
    TupleSpaceOperationStatus status;
    Tuple tuple;
} TupleSpaceOperationResult;

typedef enum TupleSpaceOperationRemovePolicy {
    tuple_space_remove, tuple_space_keep
} TupleSpaceOperationRemovePolicy;

#ifndef PSIR_ARDUINO

TupleSpace tuple_space_new();
void tuple_space_free(TupleSpace tuple_space);

void tuple_space_insert(TupleSpace* tuple_space, Tuple tuple);
TupleSpaceOperationResult tuple_space_get(TupleSpace* tuple_space, Tuple const* tuple_template, TupleSpaceOperationBlockingMode blocking_mode, TupleSpaceOperationRemovePolicy remove_policy);

char const* tuple_space_to_string(TupleSpace const* tuple_space);

#endif

#endif
