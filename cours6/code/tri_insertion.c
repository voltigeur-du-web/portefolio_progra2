void shift(int* tab, int j, int i){
    int tmp = tab[i];
    while(i>j){
        tab[i] = tab[i-1];
        i--;
    }
    tab[j] = tmp;
}

void insert_sorted(int* tab,int i){
    int j = 0;
    while(j<i){
        if(tab[j]>tab[i]){
            int tmp = tab[i];
            shift(tab,j,i);
            tab[j] = tmp;
        }
        j++;
    }
}

int tri_insertion(int* tab, int size) {
    int nb_op = 0;
    if(size>2 && tab[0]>tab[1]){
        swap(tab,0,1);
    }
    int i=2;
    while(i<size){
        insert_sorted(tab,i);
        i++;
    }
    return nb_op;
}