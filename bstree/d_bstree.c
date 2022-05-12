#include"bstree.h"
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include <stdio.h>
static BSTREE_DATA_TYPE *bstree;
static int* bstree_used;
static size_t bstree_size;

static size_t left_child(size_t current)
{
    return current*2+1;
}

static size_t right_child(size_t current)
{
    return current*2+2;
}

static size_t parent(size_t current)
{
    return (current+1)/2-1;
}

void insert(BSTREE_DATA_TYPE value)
{
    size_t current = 0;
    if(bstree_size==0)
    {
        bstree_size=1;
        bstree = malloc(bstree_size*sizeof(BSTREE_DATA_TYPE));
        bstree_used = malloc(bstree_size*sizeof(int));
        bstree_used[0] = 0;
    }
    while(bstree_used[current]!=0)
    {
        if(bstree[current]<value)
            current=right_child(current);
        else if(bstree[current]>value)
            current=left_child(current);
        else
            return;
        if(current>=bstree_size)
        {
            size_t old_size = bstree_size;
            bstree_size = current+1;
            bstree = realloc(bstree,bstree_size*sizeof(BSTREE_DATA_TYPE));
            bstree_used = realloc(bstree_used,bstree_size*sizeof(int));
            memset(bstree_used+old_size,0,(bstree_size-old_size)*sizeof(int));
        }
    }
    bstree[current]=value;
    bstree_used[current]=1;
}

int delete(BSTREE_DATA_TYPE value)
{
    BSTREE_DATA_TYPE* pfind = find(value);
    if(pfind==NULL)
        return 0;
    size_t index = pfind-bstree;
    if(right_child(index)>=bstree_size||(bstree_used[left_child(index)]==0&&bstree_used[right_child(index)]==0))
    {
        bstree_used[index]=0;
    }
    else 
    {
        size_t current;
        size_t next;
        if(bstree_used[left_child(index)]!=0)
        {
            current = left_child(index);
            next = right_child(current);
            while(next<bstree_size&&bstree_used[next]!=0)
            {
                current = next;
                next = right_child(current);
            }
        }
        else 
        {
            current = right_child(index);
            next = left_child(current);
            while(next<bstree_size&&bstree_used[next]!=0)
            {
                current = next;
                next = left_child(current);
            }            
        }
        BSTREE_DATA_TYPE value = bstree[current];
        delete(value);
        bstree[index] = value;
    }
    return 1;
}

void* find(BSTREE_DATA_TYPE value)
{
    size_t current = 0;
    while(current<bstree_size&&bstree_used[current]!=0)
    {
        if(bstree[current]<value)
        {
            current = right_child(current);
        }
        else if (bstree[current]>value)
        {
            current = left_child(current);
        }
        else 
        {
            return &bstree[current];
        }
    }
    return NULL;
}

void do_pre_order_traverse(size_t current,void (*callback)(BSTREE_DATA_TYPE value))
{
    if(current<bstree_size&&bstree_used[current]!=0)
    {
        callback(bstree[current]);
        do_pre_order_traverse(left_child(current), callback);
        do_pre_order_traverse(right_child(current), callback);
    }

}

void pre_order_traverse(void (*callback)(BSTREE_DATA_TYPE value))
{
    do_pre_order_traverse(0, callback);
}

void do_in_order_traverse(size_t current,void (*callback)(BSTREE_DATA_TYPE value))
{
    if(current<bstree_size&&bstree_used[current]!=0)
    {
        do_in_order_traverse(left_child(current), callback);
        callback(bstree[current]);
        do_in_order_traverse(right_child(current), callback);
    }

}

void in_order_traverse(void (*callback)(BSTREE_DATA_TYPE value))
{
    do_in_order_traverse(0, callback);
}

void do_post_order_traverse(size_t current,void (*callback)(BSTREE_DATA_TYPE value))
{
    if(current<bstree_size&&bstree_used[current]!=0)
    {
        do_post_order_traverse(left_child(current), callback);
        do_post_order_traverse(right_child(current), callback);
        callback(bstree[current]);
    }

}

void post_order_traverse(void (*callback)(BSTREE_DATA_TYPE value))
{
    do_post_order_traverse(0, callback);
}

void breath_first_traverse(void (*callback)(BSTREE_DATA_TYPE value))
{
    for(int i=0;i<bstree_size;i++)
    {
        if(bstree_used[i]!=0)
        {
            callback(bstree[i]);
        }
    }
}
