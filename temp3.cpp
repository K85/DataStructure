#include<iostream>
#include<queue>
#include<deque>

using namespace std;
struct Position{
	int i;
	int j;
	int health;
	bool operator<(const Position &another)const{
	return this->health<another.health;}
};

int main(){
	
	int rows,cols;
	cin>>cols>>rows;

	priority_queue<Position> Q;
	int G[rows][cols];
	int visited[rows][cols];//只有0和1 

	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			cin>>G[i][j];
			visited[i][j]=0;
		} 
	}

	int start_i,start_j;
	cin>>start_j>>start_i;
	int start_health;
	cin>>start_health;

	visited[start_i][start_j]=1;
	Q.push({start_i,start_j,start_health});

	while(!Q.empty()){
		int cur_i=Q.top().i;
		int cur_j=Q.top().j;
		int cur_health=Q.top().health;
		Q.pop();

		if(cur_j!=rows-1&&visited[cur_i][cur_j+1]==0&&cur_health>=G[cur_i][cur_j+1]){
			int nowvalue1;
			nowvalue1=cur_health-G[cur_i][cur_j+1];
			Q.push({cur_i,cur_j+1,nowvalue1});
			visited[cur_i][cur_j+1]=1;
		}
		if(cur_j!=0&&visited[cur_i][cur_j-1]==0&&cur_health>=G[cur_i][cur_j-1]){
			int nowvalue2;
			nowvalue2=cur_health-G[cur_i][cur_j-1];
			Q.push({cur_i,cur_j-1,nowvalue2});
			visited[cur_i][cur_j-1]=1;
		}
		if(cur_i!=cols-1&&visited[cur_i+1][cur_j]==0&&cur_health>=G[cur_i+1][cur_j]){
			int nowvalue3;
			nowvalue3=cur_health-G[cur_i+1][cur_j];
			Q.push({cur_i+1,cur_j,nowvalue3});
			visited[cur_i+1][cur_j]=1;
		}
		if(cur_i!=0&&visited[cur_i-1][cur_j]==0&&cur_health>=G[cur_i-1][cur_j]){
			int nowvalue4;
			nowvalue4=cur_health-G[cur_i-1][cur_j];
			Q.push({cur_i-1,cur_j,nowvalue4});
			visited[cur_i-1][cur_j]=1;
		}
	}

  //
	for(int y5=0;y5<rows;y5++){
		for(int x5=0;x5<cols;x5++){
      cout << visited[y5][x5];
		}
		cout<<endl;
	}
	
	return 0;
}
