
#include<iostream>
#include<queue>
#include<deque>

using namespace std;
struct Qitem{
	int i;
	int j;
	int curvalue;
	//Qitem(int _i,int _j,int _curvalue):i(_i),j(_j),curvalue(_curvalue){}
	bool operator<(const Qitem &another)const{
	return this->curvalue<another.curvalue;}
};

int main(){
	
	int x,y;
	priority_queue<Qitem> que;
	int x1,y1;
	cin>>x>>y;
	int qur[y][x];
	int qur1[y][x];//只有0和1 
	for(int y2=0;y2<y;y2++){
		for(int x2=0;x2<x;x2++){
			cin>>qur[y2][x2];
			qur1[y2][x2]=0;
		} 
	}
	cin>>x1>>y1;
	int value;
	cin>>value;

	qur1[y1][x1]=1;
	que.push({y1,x1,value});
	while(!que.empty()){
		int y3=que.top().i;
		int x3=que.top().j;
		int nowvalue=que.top().curvalue;
		que.pop();
		if(x3!=x-1&&qur1[y3][x3+1]==0&&nowvalue>=qur[y3][x3+1]){
			int nowvalue1;
			nowvalue1=nowvalue-qur[y3][x3+1];
			que.push({y3,x3+1,nowvalue1});
			qur1[y3][x3+1]=1;
		}
		if(x3!=0&&qur1[y3][x3-1]==0&&nowvalue>=qur[y3][x3-1]){
			int nowvalue2;
			nowvalue2=nowvalue-qur[y3][x3-1];
			que.push({y3,x3-1,nowvalue2});
			qur1[y3][x3-1]=1;
		}
		if(y3!=y-1&&qur1[y3+1][x3]==0&&nowvalue>=qur[y3+1][x3]){
			int nowvalue3;
			nowvalue3=nowvalue-qur[y3+1][x3];
			que.push({y3+1,x3,nowvalue3});
			qur1[y3+1][x3]=1;
		}
		if(y3!=0&&qur1[y3-1][x3]==0&&nowvalue>=qur[y3-1][x3]){
			int nowvalue4;
			nowvalue4=nowvalue-qur[y3-1][x3];
			que.push({y3-1,x3,nowvalue4});
			qur1[y3-1][x3]=1;
		}
	}
	for(int y5=0;y5<y;y5++){
		for(int x5=0;x5<x;x5++){
			if(qur1[y5][x5]==1){
				cout<<1;
			}else{
				cout<<0;
			} 
		}
		cout<<endl;
	}
	
	return 0;
}
