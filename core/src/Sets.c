#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Sets.h"

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;    
}

struct set_table *set_table_new(const size_t hashmap_size)  
{
    struct set_table *table = malloc(sizeof(struct set_table));

    if(!table)
    {
        return NULL;
    }

    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));  

    if(!table->nodes)
    {
        free(table);
        return NULL;
    }

    return table;
}

struct set_node *set_search(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;  

    struct set_node *node_to_find = table->nodes[index];

    if(!node_to_find)
    {
        return NULL;
    }
    else
    {
        while(node_to_find)
        {
            if(node_to_find->key_len == key_len)
            {
                if(strcmp(node_to_find->key, key) == 0)
                    break;
                else
                    node_to_find = node_to_find->next;
            }
            else
                node_to_find = node_to_find->next;
        }    
    } 
    
    return node_to_find;  
}

struct set_node *set_insert(struct set_table *table, const char *key, const size_t key_len)
{
    struct set_node *control_node = set_search(table, key, key_len);

    if(control_node)
        return NULL;
    
    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;  

    struct set_node *head = table->nodes[index];  

    if(!head)
    {
        table->nodes[index] = malloc(sizeof(struct set_node));

        if(!table->nodes[index])
        {
            return NULL;
        }

        table->nodes[index]->key = key;
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->prev = NULL;
        table->nodes[index]->next = NULL;

        return table->nodes[index];
    }

    struct set_node *new_item = malloc(sizeof(struct set_node));

    if(!new_item)
    {
        return NULL;
    }

    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = NULL;

    struct set_node *tail = head;

    while(head)
    {
        tail = head;
        head = head->next;
    }

    tail->next = new_item;
    new_item->prev = tail;

    return new_item;
}

struct set_node *set_remove(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;  

    struct set_node *node_to_remove = set_search(table, key, key_len);

    if(!node_to_remove)
    {
        return NULL;
    }
    
    struct set_node *prev_node = node_to_remove->prev;
    struct set_node *next_node = node_to_remove->next;

    if(!prev_node)
    {
        if(next_node)
        {
            table->nodes[index] = next_node;
            next_node->prev = NULL;            
        }
        else
            table->nodes[index] = NULL;       
    }
    else
    {
        if(!next_node)
        {
            prev_node->next = NULL;
        }
        else
        {
            prev_node->next = next_node;    
            next_node->prev = prev_node;    
        }
    }        

    node_to_remove->next = NULL;
    node_to_remove->prev = NULL; 

    return node_to_remove;
}

void print_table(struct set_table *table, const size_t hashmap_size)
{
    for (size_t i = 0; i < hashmap_size; i++)
    {
        struct set_node *head = table->nodes[i]; 
        
        if(!head)
        {
            continue;
        }

        while(head)
        {
            printf("Index: %zu, Key: %s\n", i, head->key);
            head = head->next;
        }
    }    
}