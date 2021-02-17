#include <stdio.h>
#include "combinations.h"

int main() {
    int nums[] = {1,2,3,4,5};
    int ret_size;

    int **ret; 
    // int *nums, int num_size, int k, int *ret_size
    ret = combinations(nums, 5, 3, &ret_size);
    int k;
    int i;

    for (i=0; i<ret_size; i++){
        for (k=0; k<3; k++)
            printf("%d ", ret[i][k]);
        printf("\n");
    }
    return 0;
}
