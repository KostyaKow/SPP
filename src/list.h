#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
//STILL MORE READABLE THEN C++ TEMPLATES! ok, maybe not...
//I will probably switch to Linux kernel lists when I am tired of playing with preprocessor.

//Usage:

//To make a new list, you can do something like this:

NEW_LIST_OF int NAMED lst INITIALIZE;         //declare list of integers named lst, and initialize it so it will be ready for usage.
NEW_LIST_OF char NAMED *lst2 INITIALIZE_PTR;  //pointer to char list named lst2. notice INITIALIZE_PTR

//makes two lists for ints -- ptr to lst3 and lst4
NEW_LIST_OF int NAMED *lst3 INITIALIZE_PTR, lst4 INITIALIZE;

//you should probably follow the syntax of declaration or you will get errors, but you can also do:
NEW_LIST_OF int
    NAMED *lst3 INITIALIZE_PTR, lst4 INITIALIZE;

sample:

LIST_OF int  IS_TYPE int_list_t;
LIST_OF char IS_TYPE char_list_t;

char_list_t* str_to_lst(const char* str, int len) {
   char_list_t* lst = &NEW_LIST(char_list_t);

   if (len == 0)
      len = strlen(str);

   for (int i = 0; i < len; i++)
      LIST_PUSH(*lst, str[i]);

   return lst;
}

void print(list lst) {
   for_each(c in CAST(char_list_t, lst))
      printf("%c", *c);
}

int main() {
   char_list_t* hello_str = str_to_lst("hello", 0);
   print(LIST_CAST(*hello_str));
   DELETE_LIST(hello_str);
   return 0;
}

*/

//do *NOT* use this structure!
typedef struct __list {
   int length, size;
   void** data;
} list;

#define CAST(type, val) (*((type*)(&(val))))
#define LIST_CAST(val) (*((list*)(&(val)))) //cast to default list


#define PASTE(x, y) x ## _ ## y
#define NEW_NAME_(x) PASTE(random_var, x)
#define NEW_NAME NEW_NAME_(__LINE__)
///-------------------------------------

#define LIST_OF \
   struct { \
      int length, size; \

#define IS_TYPE \
   * data; } NEW_NAME; \
   typedef __typeof__(NEW_NAME)

#define NAMED \
   * data; }

inline __list* __new_list() {
   __list *lst = (__list*)malloc(sizeof(__list));
   lst->length = 0;
   lst->size = 3;
   lst->data = (__typeof__(lst->data)) malloc(sizeof(lst->data) * lst->length);
   return lst;
}

#define NEW_LIST(type)     (*((type*)__new_list()))

#define INITIALIZE_PTR = (__typeof__(NEW_NAME)*)__new_list()
#define INITIALIZE = NEW_LIST(__typeof__(NEW_NAME))

///-------------------------------------

#define LIST_FOR_EACH_(lst, elem) \
   for (__typeof__(lst->data) elem = lst->data; &(*elem) != &(lst->data[lst->length]); elem++)

#define LIST_FOR_EACH_FUNC_(lst, f) do { \
      LIST_FOR_EACH_(lst, elem) \
         f(*elem); \
   } while (0)

#define LIST_PUSH_(lst, elem) \
   do { \
      if (lst.length >= lst.size) { \
         lst.size *= 2; \
         lst.data = (__typeof__(lst.data))realloc(lst.data, lst.size * sizeof(lst.data)); \
      } \
      lst.data[lst.length++] = elem; \
   } while (0)

#define LIST_GET_(lst, elem) (lst->data[elem])

#define LIST_PUSH_ARRAY_(lst, arr, arr_length) do { \
      if (lst->length + arr_length >= lst->size) { \
         lst->size = arr_length + lst->size * 2; \
         lst->data = (__typeof__(lst->data)) realloc(lst->data, lst->size * sizeof(lst->data)); \
      } \
      for (int i = 0; i < arr_length; i++, lst->length++) \
         lst->data[lst->length] = arr[i]; \
   } while (0)

#define LIST_SHRINK_TO_FIT_(lst) do { \
      if (lst->length > lst->size) { \
         lst->size = lst->length; \
         lst = (__typeof__(lst))realloc(lst->data, lst->size); \
      } \
   } while (0)

//inline function is so it will be 1 statement
inline void* __list_pop(__list* lst) {
   void* ret = lst->data[lst->length--];
   LIST_SHRINK_TO_FIT_((lst));
   return ret;
}

#define LIST_POP_(lst) \
   (*((__typeof__(lst->data[0])*) __list_pop( (__list*)lst)))

inline void** __list_pop_num(__list* lst, int num) {
    void** ret = (void**)malloc(num * sizeof(void*));

    for (int i = 0; i < num; i++)
        ret[i] = lst->data[lst->length--];

    LIST_SHRINK_TO_FIT_((lst));

    return ret;
}

#define LIST_POP_NUM_(lst, num) \
   (*((__typeof__(lst->data)*) __list_pop_num((__list*)lst, num)))


#define DELETE_LIST_(lst) do { \
      free(lst->data); \
      free(lst); \
   } while (0)


#define DELETE_LIST_REC_(lst) do { \
      LIST_FOR_EACH_(lst, elem) \
         free(*elem); \
      free(lst->data); \
      free(lst); \
   } while (0)


#define DELETE_LIST_REC_FUNC_(lst, f) do { \
      LIST_FOR_EACH_(lst, elem) \
         f(*elem); \
      free(lst->data); \
      free(lst); \
   } while (0)

#define LIST_FOR_EACH(lst, elem)                LIST_FOR_EACH_       ((lst), elem)
#define LIST_FOR_EACH_FUNC(lst, f)              LIST_FOR_EACH_FUNC_  ((lst), (f))
#define LIST_PUSH(lst, elem)                    LIST_PUSH_           ((lst), (elem))
#define LIST_GET(lst, elem)                     LIST_GET_            ((lst), (elem))
#define LIST_PUSH_ARRAY(lst, arr, arr_length)   LIST_PUSH_ARRAY_     ((lst), (arr), (arr_length))
#define LIST_SHRINK_TO_FIT(lst)                 LIST_SHRINK_TO_FIT_  ((lst))
#define LIST_POP(lst)                           LIST_POP_            ((lst))
#define LIST_POP_NUM(lst, num)                  LIST_POP_NUM_        ((lst), (num))
#define DELETE_LIST(lst)                        DELETE_LIST_         ((lst))
#define DELETE_LIST_REC(lst)                    DELETE_LIST_REC_     ((lst))                          //delete list and all its members
#define DELETE_LIST_REC_FUNC(lst, f)            DELETE_LIST_REC_FUNC_((lst), (f))                     //uses custom callback f to delete each element

//nice syntactic sugar you may want to use
#define auto
#define in ,
#define for_each_(b, a) LIST_FOR_EACH(&a, b)
#define for_each(b) for_each_(b)

