#include <stdio.h> 
#include <stdbool.h>

bool is_equal_arrays(int a[], int b[], size_t length)
{
    for(int i = 0; i < length; i++)
        if(a[i] != b[i]) return false;
    return true;
}

void swap(int *x, int *y) 
{
	int temp; 
	temp = *x; 
	*x = *y; 
	*y = temp; 
} 

bool permut(int a[], int b[], int start, int end, size_t length, int *is_same) 
{
	int i;
	if (start == end && is_equal_arrays(a, b, length)) *is_same = 1;
	else {
		for (i = start; i <= end; i++) { 
			swap((a + start), (a + i));
			permut(a, b, start + 1, end, length, is_same);
			swap((a + start), (a + i));
		}
	}
    if (*is_same) return true;
        return false;
}

int main() 
{
    int is_same = 0;
    int* p = &is_same;
    int n = 8;
    int nums1[n], nums2[n];

	// scanning arrays
	for(int i = 0; i < n; i++) scanf("%d", &nums1[i]);
    for(int i = 0; i < n; i++) scanf("%d", &nums2[i]);

	bool res = permut(nums1, nums2, 0, n - 1, n, p);
    if(res) printf("yes");
    else printf("no");
	return 0;
}
