#include <stdio.h>
#include "sorts.h"

int main() {
    int nums[] = { 4, -1, 3, 7, 2 };
    const int len = sizeof(nums) / sizeof(int);
    display_array(nums, len);
    selection_sort(nums, len);
    display_array(nums, len);
    return 0;
}
