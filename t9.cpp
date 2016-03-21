#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Note{
	int page, A, M;
	Note(int page, int A, int M){
		this->page = page;
		this->A = A;
		this->M = M;
	}
	Note(){
		page = A = M = 0;
	}
}notes[100000];
int pn = 0;
int WS, cur = 0;

void clock(int x, int M){
	if (pn < WS){
		cur = pn;
		notes[++pn] = Note(x, 1, M);
		return;
	}
	for (int i = 0; i < WS; i++){
		int t = (cur + i) % WS;
		if (notes[t].page == x){
			cur = t;
			notes[t].A = 1;
			notes[t].M |= M;
			return;
		}
	}
	while (true){
		for (int i = 0; i < WS; i++){
			int t = (cur + i) % WS;
			if (notes[t].A == 0 && notes[t].M == 0){
				printf("置换Page%d\n", notes[t].page);
				cur = t;
				notes[t] = Note(x, 1, M);
				return;
			}
		}
		for (int i = 0; i < WS; i++){
			int t = (cur + i) % WS;
			if (notes[t].A == 0 && notes[t].M == 1){
				printf("置换Page%d\n", notes[t].page);
				cur = t;
				notes[t] = Note(x, 1, M);
				return;
			}
			notes[i].A = 0;
		}
	}
}

int main()
{
	freopen("t9.in", "r", stdin);
	freopen("t9.out", "w", stdout);
	scanf("%d", &WS);
	int M, x;
	while (scanf("%d%d", &M, &x) != EOF){
		//M = 1 -> 'write'; M = '0' -> read
		printf("%s %d\n", (M == 1)?"write":"read", x);
		clock(x, M);
		for (int i = 1; i <= pn; ++i){
			if (i < pn)
				printf("(Page=%d, A=%d, M=%d), ", notes[i].page, notes[i].A, notes[i].M);
			else
				printf("(Page=%d, A=%d, M=%d);\n", notes[i].page, notes[i].A, notes[i].M);
		}
	}
	return 0;
}
