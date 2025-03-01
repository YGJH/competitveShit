#include <stdio.h>
#include <stdlib.h>
void merge(int *arr , int *arr_end) {

    int* aa = arr , *bb = arr_end;


    const int * middle = arr + ((arr_end - arr) / 2);
    int * i = arr;
    int * j = arr + ((arr_end - arr) / 2);
    int * temp = (int*)malloc(sizeof((*arr)) * (arr_end - arr));
    int * tmp = temp;
    int * fr = temp;
    while(i < middle && j < arr_end) {
        if(*i < *j) {
            *temp = *i;
            i++;
        }
        else {
            *temp = *j;
            j++;
        }
        temp++;
    }
    while(i < middle) {
        *temp = *i;
        temp++;
        i++;
    }
    while(j < arr_end) {
        *temp = *j;
        temp++;
        j++;
    }
    while(arr != arr_end) {
        *arr = *tmp;
        arr++;
        tmp++;
    }
    free(fr);
    return ;
}
void divide(int * arr , int * arr_end){
    if(arr_end - arr <= 1) {
        return ;
    }
    else {
        divide(arr , arr + ((arr_end-arr)/2));
        divide(arr + (arr_end - arr)/2 , arr_end);
        merge((arr) , (arr_end));
    }
}

signed main() {
    int * arr = (int*)malloc(50003 * sizeof(int));
    int * arr_end = arr;
    int * fr = arr;
    while(scanf("%d" , arr_end++) != EOF);
    arr_end--;
    divide(arr , arr_end);
    while(arr != arr_end) {
        printf("%d " , *arr );
        arr++;
    }
    putchar('\n');
    free(fr);
    return 0;
}
