#include <stdio.h>
#include <stdlib.h>
#include "combinations.h"

void display_help(char *name) {
    printf("Usage: %s k num1 [[[[num2] num3] num4] ... ]\n", name);
}

int main(int argc, char **argv) {

    // In the case where 1. there are 1 argument or less, 2. k > # of nums 
    if ((argc <= 2) || (strtol(argv[1], NULL, 10) > argc-2)){
        display_help(argv[0]);
        exit(0);
    }

    int nums[argc-2];
    int ret_size;
    int k;
    int i;
    int **ret; 
    int input_k = strtol(argv[1], NULL, 10);

    for (i=2; i<argc; i++)
        nums[i-2] = (int) strtol(argv[i], NULL, 10);


    ret = combinations(nums, argc-2, input_k, &ret_size);

    for (i=0; i<ret_size; i++){
        for (k=0; k<input_k; k++)
            printf("%d ", ret[i][k]);
        printf("\n");
    }

    return 0;
}
