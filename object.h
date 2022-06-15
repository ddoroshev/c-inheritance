#pragma once

#include <stddef.h>

#define OBJECT(T) \
    Object object; \
    void (*Repr)(T*, char*); \
    void (*Str)(T*, char*); \
    void (*Print_Repr)(T*); \
    void (*Print_Str)(T*);

#define INIT_OBJECT(x, T) \
    x->object.Print_Repr = Object_Print_Repr; \
    x->object._offset_Repr = offsetof(T, Repr); \
    x->object.Print_Str = Object_Print_Str; \
    x->object._offset_Str = offsetof(T, Str); \
    x->Print_Repr = (void (*) (T*)) Object_Print_Repr; \
    x->Print_Str = (void (*) (T*)) Object_Print_Str; \
    x->Repr = T ## _Repr; \
    x->Str = T ## _Str

#define OBJECT_FUNC(x, F) *(void **)((void*) x + x->_offset_ ## F)

typedef struct Object Object;

typedef void *(Repr)(Object *, char*);
typedef void *(Str)(Object *, char*);

struct Object {
    size_t _offset_Repr;
    void (*Print_Repr)(Object*);

    size_t _offset_Str;
    void (*Print_Str)(Object*);
};

void Object_Print_Repr(Object *object) {
    Repr *repr_func = OBJECT_FUNC(object, Repr);
    char buf[80];
    repr_func(object, buf);
    printf("%s\n", buf);
}

void Object_Print_Str(Object *object) {
    Str *str_func = OBJECT_FUNC(object, Str);
    char buf[80];
    str_func(object, buf);
    printf("%s\n", buf);
}
