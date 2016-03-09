#include<iostream>
#include<cstdio>
#define SIZE 4096
using namespace std;

int mem[SIZE];

void print(int head){
	for (int i = 0; i < 32 ; i++)
		printf("%d ", mem[head + i]);
	printf("\n");
}

void work(int va){
	printf("Virtual Address 0x%04x\n", va);
	
	int pde_index = ((va >> 10) & 0x1f);
	int pde = mem[0x220 + pde_index];
	int pde_valid = (pde & 0x80) >> 7;
	int pde_addr = (pde & 0x7f);
	printf("  --> pde index:0x%02x  pde contents:(valid %d, pfn 0x%02x)\n",
		pde_index, pde_valid, pde_addr); 
	if (!pde_valid){
		printf("    --> Fault (page directory entry not valid)\n"); 
		return;
	}
	int pte_index = ((va >> 5) & 0x1f); 
	int pte = mem[pde_addr * 32 + pte_index];
	int pte_valid = (pte & 0x80) >> 7; 
	int pte_addr = (pte & 0x7f); 
	printf("    --> pte index:0x%02x  pte contents:(valid %d, pfn 0x%02x)\n",
		pte_index, pte_valid, pte_addr);
	if (!pte_valid){
		printf("      --> Fault (page table entry not valid)\n");
		return;
	}
	int offset = (va & 0x1f);
	int paddr = pte_addr * 32 + offset;
	int data = mem[paddr];
	printf("      --> Translates to Physical Address 0x%04x --> Value: 0x%02x\n", paddr, data);
}

int main(){
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	for (int i = 0; i < 128; i++){
		char s[128];
		scanf("%s", s);
		scanf("%s", s);
		for (int j = 0; j < 32; j++){ 
			scanf("%x", mem + i * 32 + j);
			//printf("%x ", mem[i*32+j]); 
		}
	}
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int addr;
		scanf("%x", &addr);
		work(addr);
	}
	
	return 0;
}
