//.h
typedef struct head* head_t;
typedef struct node note_t;

//.c
struct head{
    node_t first;
    int taille
};

struct node{
    node_t next;
    node_t last;
    note_t prev;
    int element;
}

int main(){
    head_t tete = malloc(sizeof(*head)); // Rérénce vers la structure et non pas le pointeur (pas head_t)
    int i;
    tete->taille=0;
    tete->first=NULL;
    for (i=0;i<10;i++){
        if(tete->taille==0){
            tete->first=malloc(*(tete->first))
            tete->element=i;
            tete->first=tete->last;
            tete->first->next=tete->first;
            tete->last->next=tete->first;
            tete->taille++;
        }
        else{
            node_t elem = malloc(sizeof(*elem));
            tete->last->next=elem;
            tete->first->prev=elem;
            elem->next=tete->first;
            elem->prev=tete->last;
            tete->last=elem;
            elem->element=i;
            tete->taille++;
        }

    }
    return 1;
}