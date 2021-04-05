#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int MaxN = 100005;
const int BLOCK_SIZE = 500;
const int MaxBlock = 1000;

int N, M, start, last, blockN, siz[MaxBlock];
bool del[MaxN];

inline int findBlock(int pos) {
	return (pos-1)/BLOCK_SIZE+1;
}

void Delete(int pos) {
	del[pos] = true;
	int blo = findBlock(pos);
	siz[blo]--;
	if (last == pos) {
		for (int i = pos-1; i >= 1; --i) 
		if (!del[i]) {
			last = i;
			break;
		}
	}
	if (start == pos) {
		for (int i = pos+1; i <= N; ++i)
		if (!del[i]) {
			start = i;
			break;
		}
	}
}

int getNext(int now, int step) {
	while (step > 0 && now % BLOCK_SIZE != 0) {
		now++;
		if (!del[now]) step--;
	}
	if (step == 0) return now;
	int i;
	for (i = findBlock(now)+1; i < findBlock(last) && step > siz[i]; ++i)
		step -= siz[i];
	now = (i-1)*BLOCK_SIZE + 1;
	if (!del[now]) step--;
	while (step > 0) {
		now++;
		if (!del[now]) step--;
	}
	return now;
}

int getPre(int now, int step) {
	while (step > 0 && now % BLOCK_SIZE != 1) {
		now--;
		if (!del[now]) step--;
	}
	if (step == 0) return now;
	int i;
	for (i = findBlock(now)-1; i > findBlock(start) && step > siz[i]; --i)
		step -= siz[i];
	now = i*BLOCK_SIZE;
	if (!del[now]) step--;
	while (step > 0) {
		now--;
		if (!del[now]) step--;
	}
	return now;
}

int getDis(int pos1, int pos2) {
	int ret = 0;
	while (pos1 % BLOCK_SIZE != 0 && pos1 != pos2) {
		pos1++;
		if (!del[pos1]) ret++;
	}
	if (pos1 == pos2) return ret;
	while (pos2 % BLOCK_SIZE != 1) {
		pos2--;
		if (!del[pos2]) ret++;
	}
	for (int i = findBlock(pos1)+1; i < findBlock(pos2); ++i)
		ret += siz[i];
	return ret+1;
}

int main() {
	scanf("%d %d", &N, &M);
	if (N == 1) {
		puts("1");
		return 0;
	}
	blockN = N/BLOCK_SIZE + (N%BLOCK_SIZE > 0);
	start = 1, last = N;
	for (int i = 1; i < blockN; ++i) siz[i] = BLOCK_SIZE;
	siz[blockN] = (N % BLOCK_SIZE == 0) ? BLOCK_SIZE : N%BLOCK_SIZE;
	/*
	Delete(7);
	printf("%d %d %d", getNext(3, 10), getPre(19, 12), getEnd(6));
	*/
	int nowPos = 1, dir = 0, nn = N;
	while (nn > 1) {
		int nowM = (M-1)%(2*nn-2), dis;
		Beg:
		/*
		printf("total:%d %d %d %d\n", nowPos, nowM, start, last);
		for (int i = 1; i <= N; ++i)
			if (!del[i]) printf("%d ", i);
		puts("");
		for (int i = 1; i <= blockN; ++i)
			std::cout << size[i] << ' ';
		puts("");
		*/
		if (!dir) {
			dis = getDis(nowPos, last);
			//printf("right:%d %d\n", nowPos, dis);
			if (nowM <= dis) nowPos = getNext(nowPos, nowM);
			else {
				nowPos = last;
				nowM = nowM - dis;
				dir = 1;
				goto Beg;
			}
		}
		else {
			dis = getDis(start, nowPos);
			//printf("left:%d %d\n", nowPos, dis);
			if (nowM <= dis) nowPos = getPre(nowPos, nowM);
			else {
				nowPos = start;
				nowM = nowM - dis;
				dir = 0;
				goto Beg;
			}
		}
		if (!dir) {
			if (nowPos == last) {
				Delete(nowPos);
				nowPos = last;
			}
			else {
				Delete(nowPos);
				while (del[++nowPos]);
			}
		}
		else {
			if (nowPos == start) {
				Delete(nowPos);
				nowPos = start;
			}
			else {
				Delete(nowPos);
				while (del[--nowPos]);
			}
		}
		--nn;
	}
	printf("%d\n", last);
	return 0;
} 
