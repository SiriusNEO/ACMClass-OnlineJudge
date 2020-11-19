#include <iostream>
#include <stdio.h>
using namespace std;
 
struct Node {
	int data;
	Node *next;
};
 
struct LinkList {
  	// TODO: Define some variables of struct LinkList here.
  	Node *head;
  	int size;
  
  	void Initialize(int *a, int n) {
    // TODO: use a[0 ... n-1] to initialize the link list.
    	head = new Node;
    	head->data = a[0];
    	Node *tmp = head;
    	for (int i = 1; i < n; ++i) {
    		tmp->next = new Node;
    		tmp->next->data = a[i];
    		tmp = tmp->next;
		}
		tmp->next = NULL;
		size = n;
  	}
  	void Insert(int i, int x) {
    // TODO: insert element x after i-th element.
		Node *ntr = new Node, *tmp = head;
		ntr->data = x;
		if (i == 0) {
			ntr->next = head;
			head = ntr;
			++size;
			return ;
		}
		for (int j = 1; j < i; ++j) {
			tmp = tmp->next;
		}
		ntr->next = tmp->next;
		tmp->next = ntr;
		++size;
  	}
  	void Delete(int i) {
    // TODO: delete element i
    	Node *tmp = head, *tmp1;
    	if(i == 1) {
    		head = tmp->next;
    		delete tmp;
    		--size;
    		return ;
		}
		for (int j = 1; j < i - 1; ++j) {
			tmp = tmp->next;
		}
		tmp1 = tmp->next;
		tmp->next = tmp->next->next;
		delete tmp1;
		--size;
  	}
  	void EvenOddSwap() {
    // TODO: Swap the even-indexed element with the corresponding odd-indexed element.
   	 	Node *tmp1 = head, *tmp2 = head->next;
    	int tmp;
    	if (tmp2 == NULL) {
    		return ;
		}
    	for (int i = 1; i < size; i += 2) {
    		tmp = tmp1->data;
			tmp1->data = tmp2->data;
			tmp2->data = tmp;
			if(tmp2->next == NULL) break;
			tmp1 = tmp1->next->next;
			tmp2 = tmp2->next->next;
		}
  	}
  	void Query(int i) {
    // TODO: Print the value of the i-th element on the screen.
    	Node *tmp = head;
		for (int j = 1; j < i; ++j) {
			tmp = tmp->next;
		}
		cout << tmp->data << endl;
  	}
  	void QueryAll() {
    // TODO: Print the link list on the screen.
    	Node *tmp = head;
    	while (tmp != NULL) {
    		cout << tmp->data << " ";
    		tmp = tmp->next;
		}
		cout << endl;
  	}
  	void ClearMemory() {
    // TODO: Clear the memory.
    	while (size > 0) Delete(1);
  	}
};

LinkList L;

int main() {
    ios :: sync_with_stdio(false);
  	cin.tie(0); cout.tie(0);

  	int n, *a;
  	cin >> n;
  	a = new int [n];
  	for (int i = 0; i < n; ++ i) cin >> a[i];
  	L.Initialize(a, n);
  	delete [] a;

  	int m, op, i, x;
  	cin >> m;
  	while (m --) {
	    cin >> op;
	    switch(op) {
	      case 1:
	        cin >> i >> x;
	        if (i >= 0 && i <= L.size) {
	        	L.Insert(i, x);
			}
	        break;
	      case 2:
	        cin >> i;
	        if (i >= 1 && i <= L.size) {
	        	L.Delete(i);
			}
	        break;
	      case 3:
	        L.EvenOddSwap();
	        break;
	      case 4:
	        cin >> i;
	        L.Query(i);
	        break;
	      case 5:
	        L.QueryAll();
	        break;
	    }
  	}
  	L.ClearMemory();
  	return 0;
}
