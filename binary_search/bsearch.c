#include <stdio.h>
#include <stdlib.h>

//low參數應該要在high左邊
void* binarySearch(void* arr[],int low,int high,void*x,int (*compare)(void*,void*)) {
    if(high - low > 0) {
        if(arr == NULL) return NULL;

        int mid = (high + low)/2;
        
        if(compare(arr[mid],x) == 0) {
            return x;
        } else if(compare(arr[mid],x) < 0){
            return binarySearch(arr,mid+1,high,x,compare);
        } else {
            return binarySearch(arr,low,mid-1,x,compare);
        }
    }
}