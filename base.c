#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void print_int_arr(int *arr, int arr_size){
    int i;
    for (i=0; i<arr_size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int combinations_size(int n, int k){
    int k_larger;
    int k_smaller;
    int i;
    int ret = 1;

    k_larger = MAX(k, n-k);
    k_smaller = MIN(k, n-k);

    for (i=k_larger+1; i<=n; i++) {
        ret *= i;
    }

    for (i=1; i<=k_smaller; i++) {
        ret /= i;
    }
    return ret;
}

int **combinations(int *nums, int num_size, int k, int *ret_size){
    *ret_size = combinations_size(num_size, k);
    int **ret = (int **) malloc(sizeof(int *) * (*ret_size));

    // k represents the # of value we will pick from nums
    if ((k == 0) || (k > num_size)) {
        printf("\n");
        return ret;
    }
    if (k == num_size) {
        int *this_ret = (int *)malloc(sizeof(int)*k);
        int i;
        for (i=0; i<k; i++) {
            this_ret[i] = nums[i];
        }
        ret[0] = this_ret;
        return ret;
    }

    // calculate the size of the return_array

    int indicies[k];
    int max_ref[k];
    int val;
    int i;

    for (i=0; i<k; i++){
        indicies[i] = i;
        max_ref[k-i-1] = num_size-i-1;
    }

    int turn = 0;
    while(1) {
        int *this_ret = (int *)malloc(sizeof(int)*k);
        for (i=0; i<k; i++){
            this_ret[i] = nums[indicies[i]];
        }
        ret[turn] = this_ret;
        
        i = k - 1;
        while ((i != -1) && (indicies[i] == max_ref[i])){
            i--;
        }
        if (i == -1) {
            // max_ref has been reached: function is complete and we have 
            // explored every combinations
            return ret;
        }

        // the completion of while loop means we point at the first index 
        // to be incremented
        val = indicies[i]+1;
        for (; i<k; i++){
            indicies[i] = val;
            val++;
        }

        // update turn: the value that keeps track of ret's index
        turn++;
    }
}


int **subsets(int *nums, int num_size, int *return_size, int **ret_subset_size){
    *return_size = 1 << num_size;
    *ret_subset_size = (int *) malloc(sizeof(int) * (*return_size));
    int **ret = (int **) malloc((*return_size) * sizeof(int*));
    int c;
    int j;
    int combo_size;
    int ret_index = 0;
    int **this_ret;
    for (c=0;c<=num_size;c++){
        this_ret = combinations(nums, num_size, c, &combo_size);
        for (j=0; j<combo_size; j++) {
            ret[ret_index] = this_ret[j];
            (*ret_subset_size)[ret_index] = c;

            // print_int_arr(ret[ret_index], c);
            // free(this_ret[j]);

            ret_index++;
        }
        free(this_ret);
    }
    return ret;
}
