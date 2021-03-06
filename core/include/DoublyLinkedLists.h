#pragma once

//Many of these functions have a define with the cast integrated for faster use at the bottom of this document

struct doubly_list_node
{
    struct doubly_list_node *prev;
    struct doubly_list_node *next;
};

struct doubly_list_node *doubly_list_get_tail(struct doubly_list_node **head);
struct doubly_list_node *doubly_list_append(struct doubly_list_node **head, struct doubly_list_node *item);
struct doubly_list_node *doubly_list_pop(struct doubly_list_node **head);
struct doubly_list_node *doubly_list_remove(struct doubly_list_node **head, struct doubly_list_node *item);

/*
* This function will add an item after another one in the list
*
* @param head The head of the list
* @param item Item after which we want to add the new one
* @param item_to_add New item we want to add
*/
struct doubly_list_node *doubly_insert_after_item(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *item_to_add);

/*
* This function will add an item before another one in the list
*
* @param head The head of the list
* @param item Item before which we want to add the new one
* @param item_to_add New item we want to add
*/
struct doubly_list_node *doubly_insert_before_item(struct doubly_list_node **head, struct doubly_list_node *item, struct doubly_list_node *item_to_add);

int take_list_items_count(struct doubly_list_node **head);
struct doubly_list_node *take_list_item(struct doubly_list_node **head, int element_index);
struct doubly_list_node *shuffle_doublylist(struct doubly_list_node **head, int number_of_shuffles);


struct doubly_string_item
{
    struct doubly_list_node node;
    const char *string;
};

struct doubly_string_item *doubly_string_item_new(const char *string);
void clear_myelement(struct doubly_string_item **item);

#define doubly_list_node_doubleptr(obj) (struct doubly_list_node **)obj
#define doubly_list_node_ptr(obj) (struct doubly_list_node*)obj

#define doubly_list_get_tail_casting(list) doubly_list_get_tail(doubly_list_node_doubleptr(list))
#define doubly_list_append_casting(list, item) doubly_list_append(doubly_list_node_doubleptr(list), doubly_list_node_ptr(item))
#define doubly_list_pop_casting(list) doubly_list_pop(doubly_list_node_doubleptr(list))  
#define doubly_list_remove_casting(list, item) doubly_list_remove(doubly_list_node_doubleptr(list), doubly_list_node_ptr(item))   
#define doubly_insert_after_item_cast(list, item, item_to_add) doubly_insert_after_item(doubly_list_node_doubleptr(list), doubly_list_node_ptr(item), doubly_list_node_ptr(item_to_add))       
#define doubly_insert_before_item_cast(list, item, item_to_add) doubly_insert_before_item(doubly_list_node_doubleptr(list), doubly_list_node_ptr(item), doubly_list_node_ptr(item_to_add))
#define doubly_take_list_items_count_cast(list) take_list_items_count(doubly_list_node_doubleptr(list))
#define doubly_take_list_item_cast(list, index) take_list_item(doubly_list_node_doubleptr(list), index)
#define doubly_shuffle_list_cast(list, num) shuffle_doublylist(doubly_list_node_doubleptr(list), num)