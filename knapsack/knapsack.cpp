#include <stdio.h>
#include <stdlib.h>

#define N 10	//切り分けパターンの数
#define L 10	//もともとの金属棒の長さ

void setArrays(int);
void freeArrays(void);
void solve(void);
void backtrack(int,int,int);
int max(int,int);
void print_result(void);

struct InputSet{
	int length;
	int price;
};

struct InputSet inputs[N] =
	 {{1,1},{2,5},{3,8},{4,9},{5,10},{6,17},{7,17},{8,20},{9,24},{10,30}};
int **c = NULL;	//c[i][l]は長さlの金属棒についてi番目の切り分けパターンまで考慮したときの価格の最大値
int result[N+1] = {0};
int length = L;

int main(int argc,char *argv[])
{
	if(argc == 2)length = atoi(argv[1]);
	while(length > 0){
		for(int i = 0;i <= length+1;i++)printf("____ ");
		printf("\nL = %2d : result \n",length);
		setArrays(1);
		solve();
		backtrack(N,length,0);
		print_result();
		freeArrays();
		length--;
	}
	return 0;
}

void setArrays(int change)
{
	c = (int **)malloc(sizeof(int *) * (N + 1));
	for(int i = 0;i <= N;i++){
		c[i] = (int *)malloc(sizeof(int) * (length + 1));
	}
}

void freeArrays()
{
	for(int i = 0;i <= N;i++){
		free(c[i]);
	}
	free(c);
}

void solve()
{
	for(int i = 0;i <= N;i++)c[i][0] = 0;
	for(int l = 0;l <= length;l++)c[0][l] = 0;
	for(int x=0;x<=length+1;x++)printf("**** ");printf("\n");
	
	for(int i = 0;i < N;i++){
		for(int l = 0;l <= length;l++){
			if(l < inputs[i].length ){
				c[i+1][l] = c[i][l];
			}else{
				c[i+1][l] = max(c[i][l],c[i+1][l-inputs[i].length] + inputs[i].price);
			}
		}
		
	}
}

void backtrack(int i, int j, int index)
{
	if(j < 1 || i < 1)return;
	while(c[i--][j] == c[i][j]);
	result[index++] = ++i;
	backtrack(i,j-inputs[i-1].length,index);
}

int max(int a, int b)
{
	if(a>b){
		return a;
	}else {
		return b;
	}
}

void print_result()
{
	for(int i = -1;i <= N;i++){
		for(int l = -1;l <= length;l++){
			if(i < 0 && l < 0){
				printf("     ");
				continue;
			}else if(l < 0 ){
				printf("[%2d]  ",i);
				continue;
			}else if(i < 0){
				printf("[%2d] ",l);
				continue;
			}
			printf("%2d   ",c[i][l]);
		}
		printf("\n");
	}
	printf("\n");

	printf("MAXIMUM PRICE IS [ %2d ]\n\n",c[N][length]);

	printf("Cutting List = [ ");
	for(int i = 0;i <= N;i++){
		if(result[i]) printf("%2d,",result[i]);
	}
	printf("]\n\n");
	for(int i = 0;i <= N;i++){
		result[i] = 0;
	}
}
