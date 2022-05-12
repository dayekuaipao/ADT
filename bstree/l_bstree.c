#include "bstree.h"
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <assert.h>
typedef struct BSTREE_NODE{
    BSTREE_DATA_TYPE value;
    struct BSTREE_NODE* left;
    struct BSTREE_NODE* right;
}BSTreeNode;

static BSTreeNode* root;

void insert(int value)
{
    BSTreeNode** current = &root;
    while((*current)!=NULL)
    {
        if((*current)->value<value)
        {
            current = &(*current)->right;
        }
        else if((*current)->value>value)
        {
            current = &(*current)->left;
        }
        else 
        {
            return;
        }
    }
    BSTreeNode* new = malloc(sizeof(BSTreeNode));
    assert(new!=NULL);
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    *current = new;
}

int delete(BSTREE_DATA_TYPE value)
{
    BSTreeNode** pfind = find(value);
    if(pfind==NULL)
        return 0;
    if((*pfind)->left==NULL&&(*pfind)->right==NULL)
    {
        free((*pfind));
        (*pfind)=NULL;
        return 1;
    }
    else
    {
        BSTreeNode* current;
        BSTreeNode* next;
        if((*pfind)->left!=NULL)
        {
            current = (*pfind)->left;
            while((next=current->right)!=NULL)
            {
                current=next;
            }
        }
        else
        {
            current = (*pfind)->right;
            while((next=current->left)!=NULL)
            {
                current=next;
            }
        }
        BSTREE_DATA_TYPE value=current->value;
        delete(value);
        (*pfind)->value=value;
        return 1;
    } 
}

void* find(BSTREE_DATA_TYPE value)
{
    BSTreeNode** current = &root;
    while((*current)!=NULL)
    {
        if((*current)->value<value)
        {
            current=&(*current)->right;
        }
        else if((*current)->value>value)
        {
            current=&(*current)->left;
        }
        else
        {
            return current;
        }
    }
    return NULL;
}

void do_pre_order_traverse(BSTreeNode* current,void (*callback)(BSTREE_DATA_TYPE value))
{
    if(current!=NULL)
    {
        callback(current->value);
        do_pre_order_traverse(current->left, callback);
        do_pre_order_traverse(current->right, callback);
    }

}

void pre_order_traverse(void (*callback)(BSTREE_DATA_TYPE value))
{
    do_pre_order_traverse(root, callback);
}

void do_in_order_traverse(BSTreeNode* current,void (*callback)(BSTREE_DATA_TYPE value))
{
    if(current!=NULL)
    {
        do_in_order_traverse(current->left, callback);
        callback(current->value);
        do_in_order_traverse(current->right, callback);
    }

}

void in_order_traverse(void (*callback)(BSTREE_DATA_TYPE value))
{
    do_in_order_traverse(root, callback);
}

void do_post_order_traverse(BSTreeNode* current,void (*callback)(BSTREE_DATA_TYPE value))
{
    if(current!=NULL)
    {
        do_post_order_traverse(current->left, callback);
        do_post_order_traverse(current->right, callback);
        callback(current->value);
    }

}

void post_order_traverse(void (*callback)(BSTREE_DATA_TYPE value))
{
    do_post_order_traverse(root, callback);
}

typedef struct BSTREENODEQUEUE{
    BSTreeNode* value;
    struct BSTREENODEQUEUE* next;
}BSTreeNodeQueue;
static BSTreeNodeQueue* bstree_front = NULL;
static BSTreeNodeQueue** bstree_rear = NULL;
static void bstree_enque(BSTreeNode *value)
{
    BSTreeNodeQueue* new = malloc(sizeof(BSTreeNodeQueue));
    assert(new!=NULL);
    if(bstree_front==NULL)
    {
        bstree_front = new;
        bstree_rear = &bstree_front; 
    }
    new->value = value;
    new->next = NULL;
    *bstree_rear = new;
    bstree_rear = &new->next;
}

BSTreeNode* bstree_deque(void)
{
    BSTreeNodeQueue* first=bstree_front;
    BSTreeNode* value = first->value;
    bstree_front = bstree_front->next;
    free(first);
    first=NULL;
    return value;
}

void breath_first_traverse(void (*callback)(BSTREE_DATA_TYPE value))
{
    BSTreeNode* current=root;
    bstree_enque(current);
    while(bstree_front!=NULL)
    {
        current=bstree_deque();
        callback(current->value);
        if(current->left!=NULL)
            bstree_enque(current->left);
        if(current->right!=NULL)
            bstree_enque(current->right);
    }
}
