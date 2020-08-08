#include "test/test.h"
#include "tiny/allocator/defalloc.h"

#include <vector>
#include <iostream>

void test_defalloc() {
    int arr[5] = {0, 1, 2, 3, 4};
    std::vector<int, tiny::allocator<int> >iv(arr, arr+5);
    for (size_t i=0; i<iv.size(); ++i) {
        std::cout << iv[i] << '\t';
    }
    std::cout << std::endl;
}