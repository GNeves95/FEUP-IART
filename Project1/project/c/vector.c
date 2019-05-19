//
// Created by linuxlite on 05-04-2019.
//

#include <stdlib.h>

#include "vector.h"

item * p_at(vector *vec, unsigned int pos){
    if(pos >= vec->size)
        return 0;
    if(pos == 0)
        return vec->first;
    else if(pos == vec->size - 1)
        return (*vec).last;
    else{
        if(pos > vec->size/2){
            item *ret = vec->last;
            for(unsigned int i=vec->size-1; i > pos; i--){
                ret = ret->prev;
            }
            return ret;
        } else {
            item *ret = vec->first;
            for(unsigned int i=0; i < pos; i++){
                ret = ret->next;
            }
            return ret;
        }
    }
}

void * at(vector *vec, unsigned int pos){
    if(pos >= vec->size)
        return 0;
    if(pos == 0)
        return vec->first->value;
    else if(pos == vec->size - 1)
        return vec->last->value;
    else{
        if(pos > vec->size/2){
            item *ret = vec->last;
            for(unsigned int i=vec->size-1; i > pos; i--){
                ret = ret->prev;
            }
            return ret->value;
        } else {
            item *ret = vec->first;
            for(unsigned int i=0; i < pos; i++){
                ret = ret->next;
            }
            return ret->value;
        }
    }
}

void insert(vector *vec, void *itm, int key){
    item *aux = (item *)malloc(sizeof(item));
    aux->value = itm;
    aux->next = 0;
    aux->prev = 0;
    if(vec->size == 0){
        add(vec, itm);
    } else {
        if (key <= 0) {
            vec->first->prev = aux;
            aux->next = vec->first;
            vec->first = aux;
        } else if (key >= vec->size) {
            vec->last->next = aux;
            aux->prev = vec->last;
            vec->last = aux;
        } else {
            item *prev = p_at(vec, (unsigned int) (key - 1));
            item *next = p_at(vec, (unsigned int) key);
            aux->prev = prev;
            aux->next = next;
            prev->next = aux;
            next->prev = aux;
        }
        vec->size++;
    }
}

void add(vector *vec, void *itm){
    item *aux = (item *)malloc(sizeof(item));
    aux->value = itm;
    if(vec->size == 0){
        vec->first = aux;
        vec->last = aux;
    } else {
        vec->last->next = aux;
        aux->prev = vec->last;
        vec->last = aux;
    }
    vec->size++;
}

void *rem(vector *vec, unsigned int pos){
    item *ret = 0;
    ret = p_at(vec, (unsigned int)pos);
    if(ret != 0) {
        if (pos == 0) {
            if (vec->size == 1) {
                vec->first = 0;
                vec->last = 0;
            } else {
                vec->first = ret->next;
                vec->first->prev = 0;
            }
        } else if (pos == vec->size - 1) {
            vec->last = ret->prev;
            vec->last->next = 0;
        } else {
            ret->prev->next = ret->next;
            ret->next->prev = ret->prev;
        }
    }
    if(ret == 0)
        return 0;
    else {
        vec->size--;
        return ret->value;
    }
}