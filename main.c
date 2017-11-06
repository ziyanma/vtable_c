#include <stdio.h>
typedef struct Foo_t Foo;

//The vtable class for Foo
struct slotsFoo {
  const void *parentVtable;

  //virtual destructor
  void (*destructor)(Foo*);
  
  //Virtual function
  int (*a)(Foo*);
};

//Foo class
struct Foo_t { 
  const struct slotsFoo* vtable;
};

//Destructor implementation
void destructFoo(Foo* self) { }

//A memeber functionn a's implementation
int aFoo(Foo* self) {return 1;}

//a constant virtual table for foo
const struct slotsFoo vtableFoo = {
  0,
  destructFoo,
  aFoo
};

//Constructor of Foo class 
void constructFoo(Foo* self){ 
  self->vtable = &vtableFoo;
}


typedef struct Bar_t {
  Foo base;
} Bar;

void destructBar(Bar* self){}
int aBar(Bar* self) {return 2;}
const struct slotsFoo vtableBar = {
  &vtableFoo,
  (void(*)(Foo*)) destructBar,
  (int(*)(Foo*)) aBar
};

void constructBar(Bar* self){
  self->base.vtable = &vtableBar;
}

int main(void){
  Foo x; 
  constructFoo(&x); 
  printf("%d\n", x.vtable->a(&x));

  Bar y;
  constructBar(&y);
  printf("%d\n", y.base.vtable->a(&(y.base)));

  return 0;
}

