#include <stdio.h>
typedef struct Foo_t Foo;

struct slotsFoo {
  const void *parentVtable;
  void (*destructor)(Foo*);
  int (*a)(Foo*);
};

struct Foo_t { 
  const struct slotsFoo* vtable;
};

void destructFoo(Foo* self) { }
int aFoo(Foo* self) {return 1;}
const struct slotsFoo vtableFoo = {
  0,
  destructFoo,
  aFoo
};

void constructFoo(Foo* self){ 
  self->vtable = &vtableFoo;
}

int main(void){
  Foo x; constructFoo(&x); 
  printf("%d\n", x.vtable->a(&x));
  return 0;
}

