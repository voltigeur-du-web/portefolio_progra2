quick_sort(int* tab, int i, int j) {
    if(i >= j) {
        int max=j;
        int min=i;
        int pivot = tab[i];
        while(i < j) {
            if(tab[i] < pivot) {
                swap(tab, i, i + 1);
                i++;
            } 
            else {
                swap(tab, i, j);
                j--;
            }
        }
        quick_sort(tab, min, j-1);
        quick_sort(tab, i, max);
    }
    else {
        return 0;
    }
}