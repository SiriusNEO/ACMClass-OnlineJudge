#include <cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
class LinkList {
    //TODO
    class Node {
        public:
            int val;
            Node* nxt;
            Node() {
                val = 0;
                nxt = nullptr;
            }
    };

    private:
        Node* first;

    public:
        LinkList() {
            first = nullptr;
        }
        ~LinkList() {
            while (first != nullptr) del();
        }
        void print() {
            Node* ptr = first;
            while (ptr != nullptr) std::cout << ptr->val << ' ', ptr = ptr->nxt;
            puts("");
        }
        void push(int x) {
            Node* ptr = first;
            Node* newNode = new Node;
            newNode->val = x;
            if (ptr == nullptr || ptr->val >= x) {
                newNode->nxt = first;
                first = newNode;
                return;
            }
            while (ptr->nxt != nullptr && ptr->nxt->val < x) ptr = ptr->nxt;
            newNode->nxt = ptr->nxt;
            ptr->nxt = newNode;
        }
        void del() {
            if (first == nullptr) return;
            Node* tmp = first;
            first = first->nxt;
            if (tmp != nullptr) delete tmp, tmp = nullptr; 
        }
        int getKth(int k) {
            Node* ptr = first;
            for (int i = 0; i < k && ptr != nullptr; ++i) ptr = ptr->nxt;
            if (ptr != nullptr) return ptr->val;
            return -1;
        }
        void merge(LinkList* obj) {
            LinkList tmp;
            Node* ptr = first;
            while (ptr != nullptr) tmp.push(ptr->val), ptr=ptr->nxt;
            while (tmp.first != nullptr || obj->first != nullptr) {
                if (tmp.first != nullptr && obj->first == nullptr) tmp.del();
                else if (tmp.first == nullptr && obj->first != nullptr) {
                    push(obj->first->val);
                    obj->del();
                }
                else {
                    if (tmp.first->val < obj->first->val) tmp.del();
                    else {
                        push(obj->first->val);
                        obj->del();
                    }
                }
            } 
        }
};

class LinkListArray {
private:
    int len;
    LinkList **lists;
    
public:
    LinkListArray(int n): len(n) {
        lists = new LinkList*[n];
        for (int i = 0; i < n; ++i) lists[i] = new LinkList;
    }
    ~LinkListArray() {
        for (int i = 0; i < len; ++i) {
            delete lists[i];
        }
        delete []lists;
    }
    
    void insertNumber(int n, int x) {
        lists[n]->push(x);
    }
    int queryNumber(int n, int k) {
        return lists[n]->getKth(k);
    }
    void mergeLists(int p, int q) {
        lists[p]->merge(lists[q]);
    }
};
