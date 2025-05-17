#include "utils.h"

int min(int a, int  b){
    return a<b ? a : b;
}

void swap(int* tab, int index1, int index2){
    int temp = tab[index1];
    tab[index1] = tab[index2];
    tab[index2] = temp;
}

int swap_shift_right(int* tab,int start,int end, unsigned long long int* counter){
    if(end-start<0){
        return 1;
    }
    else if(end==start){
        return 0;
    }
    else{
        int end_value = tab[end];
        int i;
        for(i=end-1;i>=start;i--){
            tab[i+1]=tab[i];
            // Faut-il comptabiliser le shift ?
            //(*counter)++; 
        }
        tab[start]=end_value;
    }
}