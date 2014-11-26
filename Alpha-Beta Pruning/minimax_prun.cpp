/* Programmed By Zeyu Zhao *
 * Date: Nov 25, 2014      *
 * ALL RIGHTS RESERVED     */

#include<iostream>
#include<stdio.h>
#include<cstring>
#include<stdlib.h>
using namespace std;
struct gameboard
{
	char p[4][4];
} board;

typedef struct movenode *pnode;
struct movenode
{
	pnode fchild;
	pnode nsibl;
	int m[2];
	int u; //utility
};
int dfsmax(pnode from,int minn, int maxx); //search for node in the range (minn,maxx)
int n;
char role; //computer plays role;
int nextmove[2];
pnode current;

int chkend()//check if game end
{
	int i,j;
	for(i=0;i<n;i++) //check row
	{
		if(board.p[i][0]!='-' && board.p[i][0]==board.p[i][1] && board.p[i][1]==board.p[i][2])
			if(n==4) {
				if(board.p[i][2]==board.p[i][3])
					if(board.p[i][3]=='X') return 2;
					else return 1;
			} else {
				if(board.p[i][2]=='X') return 2; else return 1;
			}
	}
	for(i=0;i<n;i++) //check column
	{
		if(board.p[0][i]!='-' && board.p[0][i]==board.p[1][i] && board.p[1][i]==board.p[2][i])
			if(n==4) {
				if(board.p[2][i]==board.p[3][i])
					if(board.p[3][i]=='X') return 2;
					else return 1;
			} else {
				if(board.p[2][i]=='X') return 2; else return 1;
			}
	}
	if(board.p[0][0]!='-' && board.p[0][0]==board.p[1][1] && board.p[1][1]==board.p[2][2])

		if(n==4) {
				if(board.p[2][2]==board.p[3][3])
					if(board.p[3][3]=='X') return 2;
					else return 1;
			} else {
				if(board.p[2][2]=='X') return 2; else return 1;
			}
	if(n==4)
	{
		if(board.p[0][3]!='-' && board.p[0][3]==board.p[1][2] && board.p[1][2]==board.p[2][1] && board.p[2][1]==board.p[3][0])
			if (board.p[0][3]=='X') return 2; else return 1;
	} else
	{
		if(board.p[0][2]!='-' && board.p[0][2]==board.p[1][1] && board.p[1][1]==board.p[2][0])
			if (board.p[0][2]=='X') return 2; else return 1;
	}
	for(i=0;i<n;i++)for(j=0;j<n;j++) if(board.p[i][j]=='-') return -1;
	return 0;
} //return 2--X win; 1--O win; 0--DRAW; -1--Not end

int dfsmin(pnode from,int minn,int maxx)
{
	int min,i,j,g,k;
	pnode p1,p2;
	min=999; //infinity
	max=maxx;
	p2=NULL;
	for(i=0;i<n;i++) for(j=0;j<n;j++)
	{
		if(board.p[i][j]=='-')
		{
			board.p[i][j]='O'+'X'-role;
			p1=(pnode)malloc(sizeof(struct movenode));
			p1->fchild=NULL; p1->nsibl=NULL;
			p1->m[0]=i; p1->m[1]=j;
			if(from->fchild==NULL) from->fchild=p1; else p2->nsibl=p1;
			p2=p1;
			if(chkend()<0) g=dfsmax(p2,min,max);
			else {
				k=chkend(); g=k;
				if(k==2 && role=='O') g=-1;
				if(k==1 && role=='X') g=-1;
				if(k==2 && role=='X') g=1;
			}
			min=(g<min)?g:min;
			p1->u=g;
			max=(max>min)?min:max;
			board.p[i][j]='-';
			if(min<=minn) return min;
		}
	}
	return min;
}
int dfsmax(pnode from,int minn, int maxx)
{
	int max,i,j,g,k;
	max=-999;//infinity
	min=minn;
	pnode p1,p2;
	p2=NULL;
	for(i=0;i<n;i++) for(j=0;j<n;j++)
	{
		if(board.p[i][j]=='-')
		{
			board.p[i][j]=role;
			p1=(pnode)malloc(sizeof(struct movenode));
			p1->fchild=NULL; p1->nsibl=NULL;
			p1->m[0]=i; p1->m[1]=j;
			if(from->fchild==NULL) from->fchild=p1; else p2->nsibl=p1;
			p2=p1;
			if(chkend()<0) g=dfsmin(p2,min,max);
			else {
				k=chkend(); g=k;
				if(k==2 && role=='O') g=-1;
				if(k==1 && role=='X') g=-1;
				if(k==2 && role=='X') g=1;
			}
			max=(g>max)?g:max;
			p1->u=g;
			min=(min<max)?max:min;
			board.p[i][j]='-';
			if(max>=maxx) return max;
		}
	}
	return max;
}
void freemovenode(pnode move)
{
	if(move==NULL) return;
	freemovenode(move->fchild);
	freemovenode(move->nsibl);
	free(move);
}
void outputsibl(pnode p1, int modifymove,char gamer)
{
	if(p1==NULL) return;
	cout<<"MOVE: "<<gamer<<"("<<p1->m[0]<<","<<p1->m[1]<<") Utility="<<p1->u<<endl;
	if(modifymove==p1->u) {nextmove[0]=p1->m[0];nextmove[1]=p1->m[1];}
	outputsibl(p1->nsibl,modifymove,gamer);
}
void outputtree(pnode current, int modifymove,int minmax)
{
	pnode p1;
	p1=current->fchild;
	if(p1==NULL) return;
	if(minmax) {cout<<"MAX["<<role<<"]  Branch of node [movement: (";
	printf("%c",'X'+'O'-role);
	cout<<")("<<current->m[0]<<","<<current->m[1]<<")]"<<endl;
	}
	else {
		cout<<"MIN[";
		printf("%c",'X'+'O'-role);
		cout<<"]  Branch of node [movement: ("<<role<<")("<<current->m[0]<<","<<current->m[1]<<")]"<<endl;
	}
	outputsibl(p1,(modifymove)?current->u:-999,(minmax)?role:'O'+'X'-role);
	cout<<"**********************************"<<endl;
	while(p1) {outputtree(p1,0,1-minmax);p1=p1->nsibl;}
}
	
int main(int argc, char *argv[])
{
	FILE* ifp;
	int i,j,k;
	if(argc<2) {cout<<"Please specify the input file"<<endl;exit(0);} //get file name
	ifp=fopen(argv[1],"rt");
	if(ifp==NULL)
	{cout<<"Can't open the file"<<endl;exit(1);} //open file
	
	fscanf(ifp,"SIZE: %d ",&n);
	fscanf(ifp,"PLAYER: %c",&role);
	if(role!='X' && role!='O') {cout<<"File Format Error (player should be either X or O)"<<endl;exit(1);}
	for(i=0;i<n;i++) for (j=0;j<n;j++)
	{
		if(fscanf(ifp,"%c",&board.p[i][j])<=0) {cout<<"File Format Error"<<endl;exit(1);}
		while(board.p[i][j]!='X' && board.p[i][j]!='O' && board.p[i][j]!='-')
		{
			if(fscanf(ifp,"%c",&board.p[i][j])<=0) {cout<<"File Format Error"<<endl;exit(1);}
		}
	}
	fclose(ifp);
	while(chkend()==-1) {
	current=(pnode)malloc(sizeof(struct movenode));
	current->fchild=NULL;
	current->nsibl=NULL;
	current->m[0]=-1;
	current->m[1]=-1;
	cout<<"Current Board:"<<endl;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++) cout<<board.p[i][j];
		cout<<endl;
	}
	cout<<endl;
	k=dfsmax(current,-999,999);
	current->u=k;
	cout<<"MiniMax Tree:"<<endl;
	outputtree(current,1,1);
	cout<<endl;
	cout<<"Computer Choose To Move: ("<<nextmove[0]+1<<","<<nextmove[1]+1<<")"<<endl;
	cout<<"After Computer Move, the game board becomes:"<<endl;
	board.p[nextmove[0]][nextmove[1]]=role;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++) cout<<board.p[i][j];
		cout<<endl;
	}
	cout<<endl;
	if(chkend()!=-1) break;
	cout<<"Now, it's your turn, input two integers to move"<<endl<<"example: [1 1] to put your next piece into the left top box"<<endl<<"Pay attention you are playing [";
	printf("%c]\n",'O'+'X'-role);
	cin>>i>>j;
	while((i<=0 || i>n) || (j<=0 || j>n) || board.p[i-1][j-1]!='-') {cout<<"Illegal move, try again."<<endl;cin>>i>>j;}
	board.p[i-1][j-1]='O'+'X'-role;
	freemovenode(current);
	}
	if(chkend()==2) cout<<"X win. Program end."<<endl;
	if(chkend()==1) cout<<"O win. Program end."<<endl;
	if(chkend()==0) cout<<"Game end. It's a tie."<<endl;
	return 0;
}
