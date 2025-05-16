#include <stdio.h>

// Fonction pour effectuer un tri par sélection
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Trouver l'indice du plus petit élément dans la partie non triée
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        // Échanger le plus petit élément avec le premier élément non trié
        if (min_index != i) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

// Fonction principale pour tester le tri par sélection
int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Tableau avant tri : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    selection_sort(arr, n);

    printf("Tableau après tri : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}