#include <iostream>

extern "C"
{
    int __stdcall getmin(int*, int);
    int __stdcall getmax(int*, int);
}

int main()
{
    int arr[10] = { 56, 2, 8, -22, 100, 98, 71, -11, 7, 14 };
    int min = 0, max = 0, sum = 0;
    min = getmin(arr, 10);
    max = getmax(arr, 10);
    sum = min + max;
    std::cout << "getmax + getmin = " << sum << std::endl;
}