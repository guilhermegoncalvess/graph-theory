typedef struct list {
    int no;
    struct list *prox;
    struct list *ant;
} List;

typedef struct head 
{
  List* begin;
  List* last;
}Head;

List* newNode( int x )
{
  List* novo = ( List* )malloc( 1*sizeof( List ));

  if( novo == NULL )
  {
    printf("ERRO \n");
    exit(1);
  }

  novo->no = x;
  novo->prox = NULL;
  novo->ant = NULL;

  return novo;
}

void insertList( Head* l, int x )
{
  List *p = l->begin;
  List *u = l->last;
  List* new = newNode( x );
  
  if( new != NULL )
  {
    if( l->begin == NULL && l->last == NULL )
    {
      l->begin = new;
      l->last = new;
    }
    else 
    {
      l->last->prox = new;
      new->ant = l->last;
      l->last = new;
    }
  }
}   


int searchList( Head* l, int x )
{
  List* p = l->begin;
  List* aux = l ->begin->prox;

  while ( p != NULL && p->no != x)
  { 
    p = p->prox;
  }

  return p == NULL ? 0 : 1;
  
}

void removeList( Head* l, int x )
{
  List* p = l->begin;
  List* aux = l ->begin->prox;

  while ( p != NULL && p->no != x)
  { 
    p = p->prox;
    aux = aux->prox;
  }
  
  if( p == l->begin )
  {
    l->begin = aux;
    free( p );
  }
  else
  {
    if(aux != NULL && p->no == x )
    {
      p->ant->prox = aux;
      aux->ant = p->ant;
      free( p );
    }
    
    if( aux == NULL && p->no == x )
    {
      l->last = p->ant;
      free( p );
    } 
  }
}