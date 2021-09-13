#ifndef LIST_H
#define LIST_H
typedef char *String;

typedef struct listNode
{
    String unit_code;
    struct listNode *next;
} * ListNodePtr;

typedef struct list
{
    ListNodePtr head;
} UnitList;

UnitList new_list();

void insert_at_front(UnitList *, String);
void insert_in_order(UnitList *, String);
void print_list(UnitList *);
void delete_list(UnitList *, String);
void destroy_list(UnitList *);

UnitList copy_list(UnitList* self);
void merge_list(UnitList* self, UnitList* other);
ListNodePtr find_list(UnitList* self, String data);

#endif
