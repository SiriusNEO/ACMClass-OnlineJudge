#include <bits/stdc++.h> 

using namespace std;

const int N = 100005, M = 200005, INF = 1000000002;

int n, m, q, nxt[M<<1], toPos[M<<1], cnt;
int que[N], head, tail;
bool hasOddRing;

struct Node {
    int num, w, first, col;
    bool operator < (const Node& obj) const  {
		return w < obj.w;
    }
    bool operator == (const Node& obj) const {
		return w == obj.w && col == obj.col;
    }
}node[N];

void link(int n1, int n2) {
    toPos[++cnt] = n2;
    nxt[cnt] = node[n1].first;
    node[n1].first = cnt;
    toPos[++cnt] = n1;
    nxt[cnt] = node[n2].first;
    node[n2].first = cnt;
}

class PriorityQueue {
private:
    int hp[N<<4], last;
public:
    PriorityQueue():last(0) {
        memset(hp, 127, sizeof(hp));
    }
    int top() {return hp[1];}
    void insert(int val) {
        hp[++last] = val;
        int ptr = last;
        while (ptr != 1 && hp[ptr>>1] > hp[ptr]) {
            swap(hp[ptr>>1], hp[ptr]);
            ptr >>= 1;
        }
    }
    void pop() {
        swap(hp[1], hp[last]);
        int ptr = 1;
        --last;
        while ((ptr<<1) < last) {
            if (hp[ptr] <= hp[ptr<<1] && hp[ptr] <= hp[ptr<<1|1]) break;
            else {
                if (hp[ptr<<1] < hp[ptr<<1|1]) swap(hp[ptr], hp[ptr<<1]);
                else swap(hp[ptr], hp[ptr<<1|1]);
            }
        }
    }
    void print() {
		puts("Priority Queue.");
        for (int i = 1; i <= last; ++i) cout << hp[i] << ' ';
        puts("");
    }
};

class Treap {
private:
    struct treeNode {
        Node data;
		int randomValue, size, cnt;
        treeNode *leftSon, *rightSon;
        treeNode(Node _data, int _randomValue):
                data(_data), randomValue(_randomValue), size(1), cnt(1), leftSon(nullptr), rightSon(nullptr){}
    };
    typedef treeNode* nodeStar;
    nodeStar root;
    void pushUp(nodeStar& now) {
        now->size = now->cnt;
        if (now->leftSon) now->size += now->leftSon->size;
        if (now->rightSon) now->size += now->rightSon->size;
    }
    void treeInsert(nodeStar& nowRoot, Node val) {
        if (val == nowRoot->data) {
            nowRoot->cnt++;
            nowRoot->size++;
            return;
        }
        else if (val < nowRoot->data) {
            if (nowRoot->leftSon == nullptr)
                nowRoot->leftSon = new treeNode(val, rand());
            else treeInsert(nowRoot->leftSon, val);
            if (nowRoot->leftSon->randomValue < nowRoot->randomValue)
                rightRotate(nowRoot);
        }
        else {
            if (nowRoot->rightSon == nullptr)
                nowRoot->rightSon = new treeNode(val, rand());
            else treeInsert(nowRoot->rightSon, val);
            if (nowRoot->rightSon->randomValue < nowRoot->randomValue)
                leftRotate(nowRoot);
        }
        pushUp(nowRoot);
    }
    void rightRotate(nodeStar& u) {
        nodeStar v = u->leftSon;
        u->leftSon = v->rightSon;
        v->rightSon = u;
        pushUp(u);
        pushUp(v);
        swap(u, v);
    }
    void leftRotate(nodeStar& u) {
        nodeStar v = u->rightSon;
        u->rightSon = v->leftSon;
        v->leftSon = u;
        pushUp(u);
        pushUp(v);
        swap(u, v);
    }
    void treeDelete(nodeStar& nowRoot, Node val) {
        if (nowRoot->data == val) {
            if (!nowRoot->cnt) {
                if (nowRoot->leftSon == nullptr && nowRoot->rightSon == nullptr) {
                    delete nowRoot, nowRoot = nullptr;
                    return;
                } else if (nowRoot->leftSon && nowRoot->rightSon == nullptr) {
                    rightRotate(nowRoot);
                    treeDelete(nowRoot, val);
                } else if (nowRoot->rightSon && nowRoot->leftSon == nullptr) {
                    leftRotate(nowRoot);
                    treeDelete(nowRoot, val);
                } else {
                    if (nowRoot->leftSon->randomValue < nowRoot->rightSon->randomValue)
                        rightRotate(nowRoot), treeDelete(nowRoot, val);
                    else leftRotate(nowRoot), treeDelete(nowRoot, val);
                }
            }
            else {
                nowRoot->cnt--;
                nowRoot->size--;
                if (nowRoot->cnt == 0) treeDelete(nowRoot, val);
                return;
            }
        }
        else if (val < nowRoot->data) treeDelete(nowRoot->leftSon, val);
        else treeDelete(nowRoot->rightSon, val);
        pushUp(nowRoot);
    }
    Node treeGetPre(nodeStar nowRoot, int val) {
        if (nowRoot->data.w == val) return nowRoot->data;
        if (nowRoot->data.w > val && nowRoot->leftSon) return treeGetPre(nowRoot->leftSon, val);
        Node ret = nowRoot->data;
        if (ret.w < val) {
            if (nowRoot->rightSon) ret = max(ret, treeGetPre(nowRoot->rightSon, val));
            return ret;
        }
        ret.w = -INF;
        return ret;
    }
    Node treeGetNxt(nodeStar nowRoot, int val) {
        if (nowRoot->data.w == val) return nowRoot->data;
        if (nowRoot->data.w < val && nowRoot->rightSon) return treeGetNxt(nowRoot->rightSon, val);
        Node ret = nowRoot->data;
        if (ret.w > val) {
            if (nowRoot->leftSon) ret = min(ret, treeGetNxt(nowRoot->leftSon, val));
            return ret;
        }
        ret.w = INF;
        return ret;
    }
    /*
    void treePrint(const nodeStar& nowRoot) {
        cout << '(' << nowRoot->data << ',' << nowRoot->cnt << ',' << nowRoot->randomValue << ')' << ' ';
        if (nowRoot->leftSon) treePrint(nowRoot->leftSon);
        if (nowRoot->rightSon) treePrint(nowRoot->rightSon);
    }
    */

public:
    Treap() {root = nullptr;}
    void insert(Node val) {
        if (root == nullptr) root = new treeNode(val, rand());
        else treeInsert(root, val);
    }
    void del(Node val) {
        if (root == nullptr) printf("what");
        treeDelete(root, val);
    }
    Node getpre(int val) {
        if (root == nullptr) {
        	Node ret;
        	ret.w = -INF;
			return ret;
		}
		else return treeGetPre(root, val);
    }
    Node getnxt(int val) {
        if (root == nullptr) {
        	Node ret;
        	ret.w = INF;
			return ret;
		}
        else return treeGetNxt(root ,val);
    }
    /*
    void print() {
        if (root == nullptr) puts("Treap is empty.");
        else {
			puts("Treap.");
			treePrint(root), putchar('\n');
		}
	}
	*/
}data;

PriorityQueue pq;
int delCnt[10000002];

int main() {
    srand(time(0));
	cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int tmp;
        cin >> tmp;
        node[i] = (Node){i, tmp, 0, 0};
    }
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        link(u, v);
    }
    //Black-White Coloring
    head = 1;
    que[++tail] = 1;
    node[1].col = 1;
    while (head <= tail) {
        int tp = que[head++];
        for (int i = node[tp].first; i; i=nxt[i])
            if (!node[toPos[i]].col) {
                node[toPos[i]].col = node[tp].col%2+1;
                que[++tail] = toPos[i];
            }
            else if (node[toPos[i]].col != node[tp].col%2 + 1) {
                hasOddRing = true;
            }
    }
    for (int i = 1; i <= n; ++i) {
    	if (node[i].col == 1) data.insert(node[i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (node[i].col == 2) {
			Node pr = data.getpre(node[i].w), nx = data.getnxt(node[i].w);
			if (pr.col == 1) pq.insert(abs(pr.w - node[i].w));
			if (nx.col == 1) pq.insert(abs(nx.w - node[i].w));
		}
		data.insert(node[i]);
    }
	cin >> q;
    while (q--) {
        int opt, xx, yy;
        cin >> opt >> xx >> yy;
        if (!opt) {
			data.del(node[xx]);
			Node pr = data.getpre(node[i].w), nx = data.getnxt(node[i].w);		
			if (pr.col == 1) del[(abs(pr.w - node[i].w))]++;
			if (nx.col == 1) del[(abs(nx.w - node[i].w))]++;
		}
        else {
            if (hasOddRing) puts("0");
            else if (node[xx].col == node[yy].col) puts("0");
            else {
                while (del[pq.top()]) del[pq.top()]--, pq.pop();
                cout << pq.top() << '\n';
            }
        }
	}
	
	
	/*
	for (int i=1;i<=4;++i)
		pq.insert(0), delset.insert(0);
	pq.insert(20);
	pq.insert(999999999);
	pq.print();
	delset.print();
	
	while(delset.getpre(pq.top()) == pq.top()) {
		cout << delset.getpre(pq.top()) << '\n';
		delset.del(pq.top());
		pq.pop();
	}
	*/
    return 0;
}
