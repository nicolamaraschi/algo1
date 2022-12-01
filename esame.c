void* upo_ht_sepchain_put(upo_ht_sepchain_t ht,void* key,void* value){
  if(ht==NULL || ht->slots==NULL) return NULL
  void* old_value=NULL;
  size_t h = ht->key_hash(ket,ht->capacity);
  upo_ht_sepchain_list_node_t* n = ht->slots[h].head;
  while(n!=NULL && key!=n->key) n=n->next;
  if(n==NULL){
    n=malloc(sizeof(upo_ht_sepchain_list_node_t));
    n->key=key;
    n->next= ht->slots[h].head;
    ht->slots[h].head=n:
    ht->size++:
  }
  else{
    old_value=n->value;
    n->value=value;
  }
  return old_value;
}

// leggenda usiamo n: come nodo di scorrimento e a:come nodo ausigliario
void upo_ht_sepchain_delete(upo_ht_sepchain_t ht. const void* key, int destroy_data){
  if(ht==NULL || ht->slots==NULL) return;
  size_t h= key_hash(key,ht->capacity);
  upo_ht_sepchain_list_node_t* n= ht->slots[h].head;
  upo_ht_sepchain_list_node_t* a= NULL;
  while(n!=NULL && key!= n->key){
    a=n;
    n=n->next;
  }
  if(n!=NULL){
    if(a==NULL) ht->slots[h].head=n->next;
    else a->next= n->next;
  }
  if(destroy_data){
    free(n->key);
    free(n->value);
  }
  free(n);
  ht->size--;
}

void* upo_ht_sepchain_countCollision(const upo_ht_sepcian_t ht, const void* key){
  int counter=0;
  if(ht==NULL || ht->slots==NULL) return NULL;
  size_t h= ht->key_hash(key,ht->capacity);
  upo_ht_sepchain_list_node_t* n= ht->slots[h].head;
  while(n!=NULL && key!=n->key){
    counter++;
    n=n->next;
  }
  if(n!=NULL) return counter;
  return 0;
}



      |--------------------------linprob------------------------------------------|
      
void* upo_ht_linprob_put(upo_ht_linprob_t ht,void* key, void* value){
  if(ht==NULL || ht->slots == NULL) return NULL;
  void* old_value=NULL;
  if (upo_ht_linprob_load_factor(ht) >= 0.5) upo_ht_linprob_resize(ht, ht->capacity * 2);
  size_t h= ht->key_hash(key,ht->capacity);
  size_t found_tomb=0;
  size_t h_tomb=0:
  while((ht->slots[h].key!=NULL && key!=ht->slots[h].key)|| ht->slots[h].tombstone==1){
    if(ht->slots[h].tombstone && found_tomb ==0){
      found_tomb=1;
      h_tomb=h;
    }
    h=(h+1)%ht->capacity;
  }
  if(ht->slots[h].key==NULL){
    if(found_tomb) h =h_tomb;
    ht->slots[h].key=key;
    ht->slots[h].value=value;
    ht->slots[h].tombstone=0;
    ht->size++;
  }
  else{
    old_value=ht->slots[h].value;
    ht->slots[h].value=value;
  }
  return old_value;
}

void upo_ht_linprob_delite(upo_ht_linprob_t ht const void* key,int destroy_data){
  if(ht== NULL || ht->slots==NULL) return;
  size_t h = ht->key_hash(key,ht->capacity);
  while((ht->slots[h].key!=NULL && key!= ht->slots[[h].key) || ht->slots[h].tombstone==1) h=(h+1)%ht->capacity;
  if(ht->slots[h].key !=NULL){
    ht->slots[h].kwy=NULL;
    ht->slots[h].value=NULL;
    ht->slots[h].tombstone=1;
    ht->size--;
    if (upo_ht_linprob_load_factor(ht) <= 0.125) upo_ht_linprob_resize(ht, ht->capacity / 2);
    if (destroy_data) free(ht->slots + h);
  }
}
