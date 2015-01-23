#include <stdio.h>
#include <stdlib.h>

#define N 10	//切り分けパターンの数
#define L 10	//もともとの金属棒の長さ

void setArrays(void);
void freeArrays(void);
void solve(void);
void backtrack(int,int,int);
void print_result(void);

struct InputSet{
	int length;
	int price;
};

struct InputSet s[N+1] =
	 {{0,0},{1,1},{2,5},{3,8},{4,9},{5,10},{6,17},{7,17},{8,20},{9,24},{10,30}};
struct InputSet *ms = NULL;	//個数制限無しのナップサック問題用に，修正した入力をここに保存
int **c = NULL;	//c[i][l]は長さlの金属棒についてi番目の切り分けパターンまで考慮したときの価格の最大値
int result[N+1] = {0};
int length = L;
int newsize;

int main(int argc,char *argv[])
{
	if(argc == 2)length = atoi(argv[1]);
	while(length > 0){
		for(int i = 0;i <= length+1;i++)printf("____ ");
		printf("\nL = %2d : result \n",length);
		setArrays();
		solve();
		backtrack(newsize,length,0);
		print_result();
		freeArrays();
		length--;
	}
	return 0;
}

void setArrays()
{
	newsize = 0;
	for(int i = 1;i <= N;i++)newsize += (int)(length/s[i].length);
	ms = (struct InputSet *)malloc(sizeof(struct InputSet) * (newsize + 1));
	printf("NEWSIZE = %3d\n",newsize);
	ms[0] = {0,0};

	int currentIndex = 1;
	for(int i = 1;i <= N;i++){
		int count = (int)(length / s[i].length);
		for(int x = 0;x < count;x++)ms[x+currentIndex] = {s[i].length,s[i].price};
		currentIndex += count;
	}
	printf("MODIFIED INPUT IS \n[ ");
	for(int i = 0;i <= newsize;i++){
		printf("{%2d,%2d} ",ms[i].length,ms[i].price);
		if(i % length == 0)printf("\n");
	}
	printf("]\n\n");
	
	c = (int **)malloc(sizeof(int *) * (newsize + 1));
	for(int i = 0;i <= newsize;i++){
		c[i] = (int *)malloc(sizeof(int) * (length + 1));
	}
}

void freeArrays()
{
	free(ms);
	for(int i = 0;i <= newsize;i++){
		free(c[i]);
	}
	free(c);
}

void solve()
{
	for(int i = 0;i <= newsize;i++)c[i][0] = 0;
	for(int l = 0;l <= length;l++)c[0][l] = 0;
	for(int x=0;x<=length+1;x++)printf("**** ");printf("\n");
	
	for(int i = 1;i <= newsize;i++){
		for(int l = 1;l <= length;l++){
			if(ms[i].length <= l){
				if(ms[i].price + c[i-1][l-ms[i].length] > c[i-1][l]){
					c[i][l] = ms[i].price + c[i-1][l-ms[i].length];
				}else{
					c[i][l] = c[i-1][l];
				}
			}else{
				c[i][l] = c[i-1][l];
			}
		}
	}
}

void backtrack(int i, int j, int index)
{
	if(j < 1 || i < 1)return;
	while(c[i--][j] == c[i][j]);
	result[index++] = ms[++i].length;
	backtrack(i,j-ms[i].length,index);
}

void print_result()
{
	for(int i = -1;i <= newsize;i++){
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

	printf("MAXIMUM PRICE IS [ %2d ]\n\n",c[newsize][length]);

	printf("Cutting List = [ ");
	for(int i = 0;i <= N;i++){
		if(result[i]) printf("%2d,",result[i]);
	}
	printf("]\n\n");
	for(int i = 0;i <= N;i++){
		result[i] = 0;
	}
}