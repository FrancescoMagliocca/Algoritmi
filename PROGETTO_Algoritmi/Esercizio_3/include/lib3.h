#pragma once

typedef int (*hashFunction) (void*);
typedef int (*hashCmp) (void*,void*);

typedef struct _node Node;
typedef struct _table Hashmap;

Hashmap* hashmap_create(int capacity, hashFunction hash, hashCmp compare);

void hashmap_free(Hashmap* hm);

int hashmap_empty(Hashmap* hm);

int hashmap_size(Hashmap* hm);

int hashmap_capacity(Hashmap* hm);

void hashmap_flush(Hashmap* hm);

int hashmap_contain_key(Hashmap* hm, void* key);

void hashmap_insert(Hashmap* hm, void* key, void* val);

void* hashmap_get_value(Hashmap* hm, void* key);

void hashmap_delete_key(Hashmap* hm, void* key);

void** hashmap_get_keys(Hashmap* hm);
