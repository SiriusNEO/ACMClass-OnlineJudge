#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

int *tmp;

int Rnd(int l, int r) {
	return	(rand()%(r-l+1)) + l;
}

void MergeSort(int *arr, int l, int r, bool (*cmp)(const int &x, const int &y)) {
	if (l == r) {
		return ;	
	}
	int mid = (l + r) >> 1;
	MergeSort(arr, l, mid, cmp);
	MergeSort(arr, mid + 1, r, cmp);
	int cnt = 0;
	for (int i = l, j = mid + 1; i <= mid || j <= r ; ) {
		if ((i <= mid && cmp(arr[i], arr[j])) || (j > r)) {
			tmp[++cnt] = arr[i];
			++i;
		}
		else if ((j <= r && !cmp(arr[i], arr[j])) || (i > mid)) {
			tmp[++cnt] = arr[j];
			++j;
		}
	}
	for (int i = 1; i <= cnt; ++i) arr[i+l-1] = tmp[i];
}

void sort(int *bg, int *ed, bool (*cmp)(const int &x, const int &y)) {
	tmp = new int [ed-bg+3];
	MergeSort(bg, 0, ed-bg-1, cmp);
	delete [] tmp;
}

int Partition(int *arr, int l, int r, bool (*cmp)(const int &x, const int &y)) {
	 srand(time(NULL));
	 int rr = Rnd(l, r);
	 std::swap(arr[r], arr[rr]);
	 int i = l-1;
	 for (int j = l; j < r; ++j) {
			if (cmp(arr[j], arr[r])) {
				++i;
				std::swap(arr[j], arr[i]);
			}
	 }
	 std::swap(arr[i+1], arr[r]);
	 return i+1;
}

void Select(int *arr, int l, int r, bool (*cmp)(const int &x, const int &y), int k) {
	int m = Partition(arr, l, r, cmp);
	int tmp = m-l+1;
	if (k == tmp) return ;
	else if (k < tmp) Select(arr, l, m-1, cmp, k);
	else if (k > tmp) Select(arr, m+1, r, cmp, k-tmp);
}
 
void nth_element(int *bg, int *md, int *ed, bool (*cmp)(const int &x, const int &y)) {
	Select(bg, 0, ed-bg-1, cmp, md-bg+1);
}

int a[9] = {1, 5, 6, 2, 7, 3, 9, 4, 8};

bool cmp(const int &x, const int &y){return x > y;}

int main() {
	//std::cout << Partition(a, 0, 8, cmp) << '\n';
	nth_element(a, a + 5, a + 9, cmp);
	//std::cout << *(a + 5) << std::endl;// 4
	//sort(a, a+9, [](const int &x, const int &y){return x < y;}); 
	for (int i = 0; i < 9; ++i) std::cout << a[i] << ' ';std::cout << '\n';
	return 0;
}


