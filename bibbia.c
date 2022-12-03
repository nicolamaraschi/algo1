void upo_ht_sepchain_get(upo_ht_sepchain_t ht, void *key, void *value)
{
  if(ht!=null && ht->slots!=null)
  {
    // h rappresenta indice dello slot calcolato con funzione di hash
    size_t h= ht->key_hash(key,ht->capacity)
    // trovo la testa della lista di collisione allo slot attraverso la mia funzione di hash
    upo_ht_sepchain_list_node_t* nodo= ht->slots[h].head;
    //scorro finche non trovo la fine della lista di collisione E ho trovato la mia chiave
    while(nodo!= NULL && ht->key_cmp(key,nodo->key)!=0) nodo=nodo->next;
    // se il nodo non è null ossia non è la fine ho trovato il nodo
    if(nodo!=NULL) return nodo->value;
    //se invece è il nodo è nullo ho raggiunto la fine
    else return NULL;
  }
  return NULL;
}

void* upo_ht_linprob_get(const upo_ht_linprob_t ht, const void *key)
{
  // se la mia hash table non è vuota
	if(ht!= NULL)
  {
    // utillizo la funzione hash per determinare l'indice h dello slot
    size_t h= ht->key_hash(key,ht->capacity)
    // se lo slot ha la chiave NULL E la funzione di comparazione trova la chiave O lo slot ha tomstone 1 e quindi è gia stato usato
    while((ht->slots[h].key!=NULL && ht->key_cmp(key,ht->slots[h].key))|| ht->slots[h].tombostone!=0) h=(h+1)%ht->capacity;
    // se lo slot non ha la chiave NULL ritorno il valore di quello slots
    if(ht->slots[h].key!=NULL) return ht->slots[h].value;
    // se no allora quello slot ha chiave nulla allora esco
    else return NULL;
  }
  // else allora la mia hashtable è vuota e quindi ritorno null
  return NULL;
}


void upo_ht_sepchain_insert(upo_ht_sepchain_t ht, void *key, void *value)
{
  // controllo che la ht e gli slots non siano nulli
  if(ht!=NULL && ht->slots!=NULL)
  {
    // h rappresenta indice dello slot calcolato con funzione di hash
    size_t h = ht->key_hash(key,->capacity)
    // ottengo il nodo in testa alla lista di collisione
    upo_ht_sepchain_list_node_t* nodo= ht->slots[h].head;
    //scorro la lista di collisione finche il nodo non è arrivato alla fine(NULL) E non ho travato la mia stesas chiave che devo inserire
    while(nodo!=NULL && ht->key_cmp(key,nodo->key)!=0) nodo=nodo->next;
    // se non hai trovato la stessa chiave
    if(nodo==NUL)
    {
      // creo il nodo della lista di collisione
      nodo=malloc(sizeof(upo_ht_sepchain_list_node_t));
      // assegno la chiave al mio nodo della lista di collisione
      nodo->key=key;
      // assegno il valore al mio nodo della lista di collisione
      nodo->value=value;
      // colleggo il mio nodo al puntatore di testa dello slot
      nodo->next= ht->slots[h]->head;
      // collego il puntatore di testa dello slot al mio nodo
      ht->slots[h].head=nodo;
      // visto che inserisco un nodo devo aumentare size se no la funzioe hash non funziona più
      ht->size++;
    }
    return nodo;
  }
}

void upo_ht_linprob_insert(upo_ht_linprob_t ht, void *key, void *value)
{
  if(ht!=NULL)
  {
    // h rapprenta l'indice dello slot ricavato da funzione di hash
    size_t h=ht->key_hash(key,ht->capacity);
    // h_tomb rappresenta la variabile di tombstone
    size_t h_tomb   =0;
    // flag tombstone
    int found_tomb  =0;
    // condizione che controlla il fattore di carico se non va bene fa il resize
    if(upo_ht_linprob_load_factor(ht)>=0.5) upo_ht_linprob_resize(ht,2*ht->capacity);
    // scorro gli slots fino che non arrivo alla fine E se trovo la mia chiave nello slot O il tombstone è a 1
    while((ht->slots[h].key!=NULL && ht->key_cmp(key,ht->slots[h].key)!=0)|| ht->slots[h].tombstone!=0
    {
      if(ht->slots[h].tombstone!=0 && found_tomb)
    }
  }
}

void upo_ht_linprob_delete(upo_ht_linprob_t ht, const void *key, int destroy_data)
{
  //controlla che hash table esista
  if(ht!=NULL)
  {
    //calcola indice h dello slot attraverso la funzione hash
    size_t h = key_hash(key,ht->capacity);
    // se lo slot e nullo E presente la  chiave corrisponde O il tombstone dello slot e a 1 quindi gia usato, ricalcola un nuovo slot
    while((ht->slots[h].key!=NULL && ht->key_cmp(key,ht->slots[h].key)!=0)||ht->slots[h].tombstone!=0) h=(h+1)%ht->capacity;
    // se lo slot non ha chiave NULL
    if(ht->slots[h].key!=NULL)
    {
      // se destroy data è fleggata a 1 oltre a settare tutto a NULL dealloco la memoria
      if(destroy_data)
      {
        //dealloco la chiave
        free(ht->slots[h].key);
        //dealloco il valore
        free(ht->slots[h].value)
        // si imposta sempre il tombstone 1 per dire che è uno slot usato
        ht->slots[h].tombstone=1;
      }
      // imposto la chiave a NULL
      ht->slots[h].key=NULL;
      // imposto il valore a NULL
      ht->slots[h].value=NULL;
      // imposto il tombstone a 1 per dire che è uno slots usato
      ht->slots[h].tomstone=1;
      // dopo la cancellazione devo reinpostare la size se no non mi va piu la funzione hash
      ht->size--;
      // dopo che cancello devo controllolare il fattore di carico della ht
      if(upo_ht_linprob_lead_factor(ht)<=0.125)
      {
        // visto che cancello degli slot/valori devo fare resize dell'ht
        size_t res= ht->capacity/2;
        upo_ht_linprob_resize(ht,res);
      }
    }
  }
}

void upo_ht_sepchain_delete(upo_ht_sepchain_t ht, const void *key, int destroy_data)
{
  if(ht!=NULL && ht->slots!= NULL)
  {
    size_t index = ht->key_hash(key,ht->capacity);
    upo_ht_sepchain_list_node_t* node = (ht->slots + index)->head;
    upo_ht_sepchain_list_node_t* p= NULL;
    while(node!=NULL && ht->key_cmp(key,node->key)!=0)
    {
      p=node;
      node=node->next;
    }
    if(node!=NULL)
    {
      if(p==NULL) (hy->slots+index)->head=nodo->next;
      else p->next=node->next;
      if(destroy_data==1)
      {
        free(nodo->key);
        free(nodo->next);
        free(node->value);
      }
      free(node);
      ht->size--;
    }
  }
}

// non va bene
void upo_ht_sepchain_delete(upo_ht_sepchain_t ht, const void *key, int destroy_data)
{
  //determino indice h dello slot di ht attraverso la funzione hash
  size_t h=ht->key_hash(key,ht->capacity)
  //imposta la flag della testa a 1
  size_t testa=1;
  //istanzio un nodo e lo faccio puntare alla testa della lista di collisione
  upo_ht_sepchain_list_node_t* nodo   = ht->slots[h].head;
  //
  upo_ht_sepchain_list_node_t* nodoApp= NULL;
  // controllo che hash table non sia vuota
  if(ht!=NULL)
  {
    //
    if(upo_ht_sepchain_contains(ht,key))
    {
      if(testa && ht->key_cmp(key,nodo->key)==0 && nodo!=NULL)
      {
        nodoApp=nodo->next;
        ht->slots[h].head=nodoApp;
        testa=0;
        ht->size--;
      }
      nodoApp=nodo;
      nodo=nodo->next;
      if(!testa)
      {
        while(nodo!=NULL)
        {
          if(ht->key_cmp(key,nodo->key)==0)
          {
            nodoApp->next=nodo->next;
            if(destroy_data)
            {
              free(nodo->value);
              free(nodo->key);
              free(nodo->next);
            }
            free(nodo);
            ht->size--;
          }
          nodo=nodo->next;
        }
      }
    }
  }
}

void upo_ht_linprob_merge(upo_ht_linprob_t dest_ht, upo_ht_linprob_t src_ht)
{
  if(dest_ht != NULL && src_ht != NULL && dest_ht->slots != NULL && src_ht->slots != NULL)
  {
    for(size_t i=0; i<src_ht->capacity; i++)
    {
      if(src_ht->slots[i].key !=NULL && src_ht->slots[i].tomstone==0)
      {
        if(upo_ht_linprob_load_factor(dest_ht)>= 0.5) upo_ht_linprob_resize(dest_ht,2+dest_ht->capacity);
        size_t h= dest_ht-> key_hash(src_ht->slots[i].key,dest_ht->capacity);
        size_t h_tomb = 0;
        int found_tombstone=0;
        while((dest_ht->slots[h].key != NULL && dest_ht-> key_cmp(src_ht ->slots[i].key) != 0) || dest_ht->slots[h].tomstone != 0)
        {
          if(dest_ht->slots[h].tombstone != 0 && !found_tombstone)
          {
            h_tomb=h;
            found_tombstone=1;
          }
          h=(h+1) % dest_ht->capacity;
        }
        if(dest_ht->slots[h].key == NULL)
        {
          if(found_tombstone) h= h_tomb;
          dest_ht->slots[h].key= src_ht -> slots[i].key;
          dest_ht->slots[h].value= src_ht -> slots[i].value;
          dest_ht->slots[h].tombstone=0;
          dest_ht->slots[h]+=1;
        }
      }
    }
  }

}

void upo_ht_linprob_resize(upo_ht_linprob_T ht, size_t n)
{
  assert(n>0);
  if(ht != NULL)
  {
    size_t i=0;
    upo_ht_hasher_t new_ht= NULL;
    new_ht= upo_bst_linprob_create(n,ht->key_hash,ht->key_cmp);
    if(new_ht == NULL)
    {
      perror("");
      abort();
    }
    for(int i=0;i < ht->capacity;++i)
    {
      if(ht->slots[i].key != NULL) upo_ht_linprob_put(new_ht,ht->slots[i].key,ht->slots[i].value);
    }
    upo_swap(&ht->slots,&new_ht->slots,sizeof ht->slots);
    upo_swap(&ht->capacity,& new_ht->capacity,sizeof ht->capacity);
    upo_swap(&ht->size,& new_ht->size,sizeof ht->size);
    upo_ht_linprob_destroy(new_ht,0);
  }
}

// fa una pulizia delle chiavi della bst
void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data)
{
  if(node!=NULL)
  {
    upo_bst_clear_impl(node->left,destroy_data);
    upo_bst_clear_impl(node->right,destroy_data);
    if(destroy_data)
    {
     free(node->key);
     free(node->value);
    }
    free(node);
  }
}

//inserire una chiave nella bst
void upo_bst_insert_impl(upo_bst_node_t *node, void* key, void* value,upo_bst_comparator_t cmp)
{
  if(node==NULL)
  {
    node=malloc(sizeof(struct upo_bst_node_s));
    node->key=key;
    node->value=value;
    node->left=NULL;
    node->right=NULL;
  }
  else
    if(cmp(key,node->key)<0) node->left= upo_bst_get_impl(node->left,key,value,cmp);
    else
      if(cmp(key,node->key)>0) node->right= upo_bst_get_impl(node->right,key,value,cmp);
      return node;
}
// ricerca di una specifica chiave nella bst
void* upo_bst_get_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp) {
{
  if(node==NULL) return NULL;
  if(cmp(node,node->key)<0) node->left=upo_bst_get_impl(node->left,key,cmp);
  else
    if(cmp(node,node->key)>0) node->right=upo_bst_get_impl(node->right,key,cmp);
    else return node;
}
// implementa la cancellazione di un nodo, sapendo che in nodo può avere 0 o 1 o 2 figli
upo_bst_node_t* upo_bst_delete_impl(upo_bst_node_t *node,const void *key, upo_bst_comparator_t key_cmp,int destroy_data)
{
  if(node!=NULL)
  {
    // cmp chiave di comparazione di chiavi
    int cmp =key_cmp(key,node->key);
    // se la chiave insetita e minore della chiave del nodo si va a sisnistra
    if(cmp<0) node->left= upo_bst_delite_impl(node->left,key,key_cmp,destroy_data);
    else // se la chiave insetita e maggiore della chiave del nodo si va a destra
      if(cmp>0) node->right= upo_bst_delite_impl(node->right,key,key_cmp,destroy_data);
      else // la chiave inserita corrisponde alla chiave del nodo
      {
        //1 CONDIZIONE: SE ENTRAMBI I PUNTATORI DEL NODO NON SONO NULL ALLORA IL NODO POSSIEDE 2 FIGLI
        if(node->left !=NULL && node->right !=NULL)
        {
          //determino il nodo con key più grande
          upo_bst_node_t* max_node = upo_bst_max_impl(node->left)
          //se il flag destroy data è su 1 va de allocato i campi del nodo
          if(destroy_data)
          {
            free(node->key);
            free(node->value);
          }
          node->key=max_node->key;
          node->value=max_node->value;
          node->left=upo_bst_delete_impl(node->left, node->key, key_cmp, 0);
        }
        else // 2 CONDIZIONE: ELSE QUINDI SE NON SIAMO IN PRESENZA DI 2 NODI FIGLI ALLORA o NE ABBIAMO 1 o 0 perche foglia
        {
          //conservo l'indirizzo del nodo da cancellare
          upo_bst_node_t* old_node=node;
          //se il puntatore sinistro del nodo è NULL
          if(node->left==NULL) node=node->right;
          //Else: quindi con il primo if sappiamo che non 2 figli con il secondo if sappiamo o a 1 nodo a destra o nessuno
          else node=node->left;
          //se ho attivo il flag destroy data dealloco la memoria di chiave e valore
          if(destroy_data)
          {
            //dealloco la chiave
            free(old_node->key);
            //dealloco il valore
            free(old_node->value);
          }
          //dealloco in nodo da cancellare
          free(old_value);
        }
      }
  }
  // ritorno il nodo
  return node;
}

// fornisce la chiave piu grande nella bst
upo_bst_node_t* upo_bst_max_impl(upo_bst_node_t *node)
{
  //caso base
  if(node==NULL) return node;
  else
  {
    //per trovare il nodo con k piu grande vado semre a destra finche non trovo il puntatore del nodo di destra null
    if(node->right) node->right=upo_bst_max_impl(node->right);
    //vado in else quando sono arrivato all'ultimo nodo che il puntatore di destra nullo
    else return node;
  }
}

// fornisce la quantita totale numerica di chiavi nella bst
size_t upo_bst_size_impl(upo_bst_node_t *node)
{
  //caso base
  if(node==NULL) return NULL;
  // se non sei nel caso base ogni chiamata ricorsiva di destra e sinistra sommi 1
  else return 1 + upo_bst_size_impl(node->left) + upo_bst_size_impl(node->right)
}

// la funzione rank restituisce tutte le chiavi più piccole della chiave inserita
size_t upo_bst_rank_impl(upo_bst_node_t *node, const void* key,upo_bst_comparator_t cmp)
{
  // caso base ATTENZIONE ritornando un valore numero il RETURN e settato a 0
  if(node==NULL) return 0;
  else 
  {
    if(cmp(key,node->key)<0) node->left=upo_bst_rank_impl(node->left,key,cmp)
    return 1 + upo_bst_rank_impl(node->left,key_cmp);
    upo_bst_rank_impl(node->right,key,cmp);
  }
}
//data una chiave determinare la sua profondità
void* upo_bst_get_value_deph(upo_bst_node_t* node,const void* key,long* depth, upo_bst_node_t cmp)
{
  // caso base se il il nodo è nulla default depth -1
  if(node==NULL)
  {
    return NULL;
    *depth=-1;
  }
  if(cmp(node->key,key)<0)
  {
    *depth+=1;
    return upo_bst_get_value_deph(node->left,key,depth,cmp);
  }
  if(cmp(node->key,key)>0)
  {
    *depth+=1;
    return upo_bst_get_value_deph(node->right,key,depth,cmp);
  }
  return node;
}

// standard pre funzione per impl
upo_bst_key_list_t upo_bst_keys_le(const upo_bst_t bst, const void *key)
{
  if(bst == NULL) return NULL;
  return upo_bst_keys_le_impl(bst -> root,key,bst -> key_cmp);
}

//funzione che prende tutte le chiavi di bst e le mette in una lista
 upo_bst_key_list_t upo_bst_key_le_impl (upo_bst_node_t* node,const void* key, upo_bst_node_t cmp)
 {
   // caso base
   if(node==NULL) return NULL;
   //
   upo_bst_key_list_t list_node_left=NULL, list_node_right=NULL;
   if(cmp(node->key,key)>=0)
   {
     //
     list_node_left=malloc(sizeof(struct upo_bst_node_s));
     list_node_left->key=node->key;
     list_node_right=upo_bst_key_le_impl(node->left,key,cmp);
     if(list_node_right!=NULL)
     {
       list_node_left->left=list_node_right;
       while(list_node_right->next!=NULL) list_node_right=list_node_right->next;
       list_node_right->next=upo_bst_key_le_impl(node->left,key_cmp);
     }
     Else list_node_right->next=upo_bst_key_le_impl(node->left,key_cmp);
   }
   else upo_bst_key_le_impl(node->left,key_cmp);
   return list_node_left;
 }

// la funzione trova il predessore della chiave inserita, il predecessore è la chiave con il numero(minore alla chiave) che più si avvicina alla chiave inserita
 void* upo_bst_predecessor(const upo_bst_t tree, const void *key)
 {
     if(tree==NULL) return NULL;
     upo_bst_node_t *node = upo_bst_get_impl(tree->root, key, tree->key_cmp);
     if (node!=NULL)
     {
         node = upo_bst_max_impl2(tree -> root,node,tree -> key_cmp);
         return node->key;
     }
     return NULL;
 }

 // la funziona ritorna il totale di foglie del sottolbero alla chiave data a una determinata profondita data
size_t upo_bst_subtree_count_leaves_depth_impl(cost upo_bst_node_t* node, const void* key, size_t leaves_depth, size_t cur_depth,int subtree_found)
{
  //caso base
  if(node==NULL) return 0;
  // controllo la profondita corrente con la profondita ella foglia
  if(cur_depth>leaves_depth) return 0;
  // itero in ricorsione finche il flag non è settato a 1
  if(subtree_found)
  {
    // se il nodo è una foglia o è arrivato alla profondita scelta
    if(upo_bst_node_is_leaf(node) && cur_depth==leaves_depth) return 1;
    return upo_bst_subtree_count_leaves_depth_impl(node->left,key,leaves_depth,cur_depth+1,subtree_found,key_cmp) + upo_bst_subtree_count_leaves_depth_impl(node->right,key,leaves_depth,cur_depth+1,subtree_found,key_cmp);
    else
    {
      int cmp= key_cmp(key,node->key);
      if(cmp>0) upo_bst_subtree_count_leaves_depth_impl(node->right,key,leaves_depth,cur_depth+1,subtree_found,key_cmp);
      else
        if(cmp<0) upo_bst_subtree_count_leaves_depth_impl(node->left,key,leaves_depth,cur_depth+1,subtree_found,key_cmp);
      upo_bst_subtree_count_leaves_depth_impl(node,key,leaves_depth,cur_depth,1,key_cmp);
    }
  }
}

// la funzione floor prende la chiave appena piu grande della chiave inserita
void* upo_bst_floor(const upo_bst_t tree, const void *key)
{
  if (tree != NULL)
  {
    upo_bst_node_t *node = upo_bst_floor_impl(tree->root, key, tree->key_cmp);
    if (node!=NULL)return node->key;
  }
  return NULL;
}

// la funzione floor determina la chiave(bst) appena piu grande della chiave inserita
void* upo_bst_floor_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp)
{
  //finche il nodo non è NULL
  if(node != NULL)
  {
    if(cmp(key, node->key) < 0) return upo_bst_floor_impl(node->left, key, cmp);
    else
      if (cmp(key, node->key) > 0)
      {
        upo_bst_node_t* floor_node = upo_bst_floor_impl(node->right, key, cmp);
        return (floor_node != NULL) ? floor_node : node;
      }
      else return node;
    }
  return NULL;
}

void* upo_bst_ceiling(const upo_bst_t tree, const void *key)
{
  if (tree != NULL)
  {
    upo_bst_node_t* node = upo_bst_ceiling_impl(tree->root, key, tree->key_cmp);
    if (node!=NULL)return node->key;
  }
  return NULL;
}
// funzione che determina chiave appena più piccola di quella data
void* upo_bst_ceiling_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp)
{
  if(node != NULL)
  {
    if(cmp(key, node->key) > 0) return upo_bst_ceiling_impl(node->right, key, cmp);
    else
      if (cmp(key, node->key) < 0)
      {
        upo_bst_node_t *floor_node = upo_bst_ceiling_impl(node->left, key, cmp);
        return (floor_node != NULL) ? floor_node : node;
      }
      else return node;
    }
  return NULL;
}

//
void upo_bst_keys_range_impl(upo_bst_node_t* node, const void* low_key, const void* high_key, upo_bst_comparator_t cmp, upo_bst_key_list_t *key_list)
{
  if(node == NULL) return;
  upo_bst_keys_range_impl(node->left, low_key, high_key, cmp, key_list);
  if(cmp(node->key, low_key) >= 0 && cmp(node->key, high_key) <= 0)
  {
    upo_bst_key_list_node_t *list = malloc(sizeof(struct upo_bst_key_list_node_s));
    list->key = node->key;
    list->next = *key_list;
    *key_list = list;
  }
  upo_bst_keys_range_impl(node->right, low_key, high_key, cmp, key_list);
}

// (professore)funzione che calcola la quantita di nodi interni
size_t upo_bst_subtree_count_inner_impl(upo_bst_node_t* node, const void* key)
{
  if(node==NULL) return 0;
  n=upo_bst_get_impl(node,key);
  if(n!=NULL) return upo_bst_size_impl(n);
  else return 0;
}

//funzione che trova la chiave più piccola
void* upo_bst_min_impl(upo_bst_node_t *node)
{
    if(node == NULL) return NULL;
    if(node->left != NULL) return upo_bst_min_impl(node->left);
    return node;
}

void* upo_bst_max(const upo_bst_t tree)
{
    if (tree == NULL) return NULL;
    upo_bst_node_t *max = upo_bst_max_impl(tree->root);
    if(max != NULL) return max->key;
    return NULL;
}

// funzione che determina la chiave più grande
void* upo_bst_max_impl(upo_bst_node_t *node,)
{
    if(node == NULL) return NULL;
    if(node->right != NULL) return upo_bst_max_impl(node->right);
    return node;
}

// funzione che elimina la chiave minore
void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
  if(tree!=NULL)
  {
    upo_bst_node_t *min = upo_bst_min(tree);
    if (min != NULL) upo_bst_delete(tree, min, destroy_data);
  }
}

// funzione che determina altezza nodo
size_t upo_bst_height_impl(upo_bst_node_t *node)
{
  if (node == NULL || upo_bst_is_leaf_impl(node)) return 0;
  size_t left = 0, right = 0;
  left = upo_bst_height_impl(node->left);
  right = upo_bst_height_impl(node->right);
  return 1 + (left >  right ? left : right);
}

size_t upo_bst_height(const upo_bst_t tree)
{
    if(tree!= NULL) return upo_bst_height_impl(tree->root);
    return 0;
}
