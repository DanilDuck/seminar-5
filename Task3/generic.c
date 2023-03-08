/* generic_list.c */

#include <stdint.h>
#include <inttypes.h>

void int64_t_print(int64_t x)
{
    printf("%" PRId64, x);
}
void int32_t_print(int32_t x)
{
    printf("%" PRId32, x);
}
void double_print(double x)
{
    printf("%f", x);
} 

#define print(x)                                                        \
  _Generic((x),                                                         \
           struct list_int64_t* : list_int64_t_print(x),                                  \
           struct list_int32_t* : list_int32_t_print(x),                                  \
           struct list_double* : list_double_print(x),                                    \
           default : error("Unsupported operation"))

#define push(list, val)                                                 \
  _Generic((list),                                                      \
           struct list_int64_t* : list_int64_t_push(list, val),                           \
           struct list_int32_t* : list_int32_t_push(list, val),                           \
           struct list_double* : list_double_push(list, val),                             \
           default : error("Unsupported operation"))

#define DEFINE_LIST(type)                                               \
  struct list_##type {                                                  \
    type value;                                                         \
    struct list_##type* next;                                           \
  };                                                                    \
                                                                        \
  void list_##type##_push(struct list_##type* list, type val){          \
    struct list_##type* new = malloc(sizeof(struct list_##type));       \
    new->value = val;                                                   \
    new->next = 0;                                                      \
    while(list->next != 0){                                             \
      list = list->next;                                                \
    }                                                                   \
    list->next = new;                                                   \
  }                                                                     \
                                                                        \
  void list_##type##_print(struct list_##type* list){                   \
    while(list){                                                        \
      type##_print(list->value);                                        \
      printf(" ");                                                      \
      list = list->next;                                                \
    }                                                                   \
    printf("\n");                                                       \
  }

  
DEFINE_LIST(int64_t)
DEFINE_LIST(int32_t)
DEFINE_LIST(double)

int main(){
  // struct list_int64_t* list_int64_t = malloc(sizeof(struct list_int64_t));
  // list_int64_t->value = 1;
  // list_int64_t->next = 0;
  // list_int64_t_push(list_int64_t, 2);
  // list_int64_t_push(list_int64_t, 3);
  // list_int64_t_print(list_int64_t);

  struct list_int32_t* list_int32_t = malloc(sizeof(struct list_int32_t));
  list_int32_t->value = 4;
  list_int32_t->next = 0;
  push(list_int32_t, 13);
  push(list_int32_t, 6);
  print(list_int32_t);

  struct list_double* list_double = malloc(sizeof(struct list_double));
  list_double->value = 8.9;
  list_double->next = 0;
  push(list_double, 2.1);
  push(list_double, 5.9);
  print(list_double);
}
