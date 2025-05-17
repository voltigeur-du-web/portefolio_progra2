#include "tri.h"
#include "queue.h"

void merge_right_left(Queue_t queue_main, Queue_t queue_left, Queue_t queue_right, unsigned long long int* counter){
    if(size_queue(queue_main)>0){
        fprintf(stderr, "Encore des éléments dans la queue main\n");
        exit(1);
        }
    int value_left,value_right;
    while(size_queue(queue_left)>0 || size_queue(queue_right)>0){
        if(size_queue(queue_left)==0){
            enqueue(queue_main,dequeue(queue_right));
        }
        else if (size_queue(queue_right)==0){
            enqueue(queue_main,dequeue(queue_left));
        }
        else{
            value_left=peek_queue(queue_left);
            value_right=peek_queue(queue_right);
            if(value_right==value_left){
                enqueue(queue_main,dequeue(queue_right));
                enqueue(queue_main,dequeue(queue_left));
            }
            else if(value_left<value_right){
                enqueue(queue_main,dequeue(queue_left));
            }
            else{
                enqueue(queue_main,dequeue(queue_right));
            }
        }
        (*counter)++;
    }
}

int merge_sort(Queue_t queue_main, int start, int end, unsigned long long int* counter)
{
    if (start < end) {
        int pos_pivot = start + (end - start) / 2;

        // Sort first and second halves
        Queue_t queue_left = new_queue();
        Queue_t queue_right = new_queue();
        
        int i;
        for(i=start;i<=end;i++){
            if(i<=pos_pivot){
                enqueue(queue_left,dequeue(queue_main));
            }
            else{
                enqueue(queue_right,dequeue(queue_main));
            }
            (*counter)++;
        }
        if(size_queue(queue_main)>0){
            printf("Encore des éléments dans la queue main\n");
            return(1);
        }

        merge_sort(queue_left, start, pos_pivot, counter);
        merge_sort(queue_right, pos_pivot + 1, end, counter);

        merge_right_left(queue_main,queue_left,queue_right, counter);

        destroy_queue(queue_left);
        destroy_queue(queue_right);
    }
}

unsigned long long int sort(int* tab, int size){
    unsigned long long int counter=0;
    Queue_t queue_main = new_queue();
    int i;
    for(i=0;i<size;i++){
        enqueue(queue_main,tab[i]);
    }
    merge_sort(queue_main,0,size-1,&counter);
    for(i=0;i<size;i++){
        tab[i]=dequeue(queue_main);
    }
    free(queue_main);
    return counter;
}