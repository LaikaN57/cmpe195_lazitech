// point

typedef struct {
  uint32_t x;
  uint32_t y;
} point_t;

point_t point_add(point_t * a, point_t * b);
point_t point_sub(point_t * a, point_t * b);
point_t point_mul(point_t * a, point_t * b);
point_t point_div(point_t * a, point_t * b);



point_t point_add(point_t * a, point_t * b) {
  return (point_t) {a.x + b.x, a.y + b.y};
}

point_t point_sub(point_t * a, point_t * b) {
  return (point_t) {a.x - b.x, a.y - b.y};
}

point_t point_mul(point_t * a, point_t * b) {
  return (point_t) {a.x * b.x, a.y * b.y};
}

point_t point_div(point_t * a, point_t * b) {
  if(b.x && b.y) {
    return (point_t) {a.x / b.x, a.y / b.y};
  }

  return (point_t) {0, 0};
}



// stack

#define STACK_MAX 256

typedef struct {
  void** elements;
  uint32_t len;
} stack_t;

int stack_push(stack_t * stack, void * element);
void * stack_pop(stack_t * stack);

void * stack_push(stack_t * stack, void * element) {
  if(stack.len >= STACK_MAX) {
    return ((void *) 0);
  }

  return stack.elements[stack.len++] = &element;
}

void * stack_pop(stack_t * stack) {
  if(stack.len) {
    return stack.elements[--stack.len];
  }
  
  return ((void *) 0);
}
