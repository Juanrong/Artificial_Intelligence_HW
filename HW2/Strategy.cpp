#include <iostream>
#include "Point.h"
#include "Strategy.h"

using namespace std;

/*
	策略函数接口,该函数被对抗平台调用,每次传入当前状态,要求输出你的落子点,该落子点必须是一个符合游戏规则的落子点,不然对抗平台会直接认为你的程序有误
	
	input:
		为了防止对对抗平台维护的数据造成更改，所有传入的参数均为const属性
		M, N : 棋盘大小 M - 行数 N - 列数 均从0开始计， 左上角为坐标原点，行用x标记，列用y标记
		top : 当前棋盘每一列列顶的实际位置. e.g. 第i列为空,则_top[i] == M, 第i列已满,则_top[i] == 0
		_board : 棋盘的一维数组表示, 为了方便使用，在该函数刚开始处，我们已经将其转化为了二维数组board
				你只需直接使用board即可，左上角为坐标原点，数组从[0][0]开始计(不是[1][1])
				board[x][y]表示第x行、第y列的点(从0开始计)
				board[x][y] == 0/1/2 分别对应(x,y)处 无落子/有用户的子/有程序的子,不可落子点处的值也为0
		lastX, lastY : 对方上一次落子的位置, 你可能不需要该参数，也可能需要的不仅仅是对方一步的
				落子位置，这时你可以在自己的程序中记录对方连续多步的落子位置，这完全取决于你自己的策略
		noX, noY : 棋盘上的不可落子点(注:其实这里给出的top已经替你处理了不可落子点，也就是说如果某一步
				所落的子的上面恰是不可落子点，那么UI工程中的代码就已经将该列的top值又进行了一次减一操作，
				所以在你的代码中也可以根本不使用noX和noY这两个参数，完全认为top数组就是当前每列的顶部即可,
				当然如果你想使用lastX,lastY参数，有可能就要同时考虑noX和noY了)
		以上参数实际上包含了当前状态(M N _top _board)以及历史信息(lastX lastY),你要做的就是在这些信息下给出尽可能明智的落子点
	output:
		你的落子点Point
*/
extern "C" __declspec(dllexport) Point* getPoint(const int M, const int N, const int* top, const int* _board, 
	const int lastX, const int lastY, const int noX, const int noY){
	/*
		不要更改这段代码
	*/
	int x = -1, y = -1;//最终将你的落子点存到x,y中
	int** board = new int*[M];
	for(int i = 0; i < M; i++){
		board[i] = new int[N];
		for(int j = 0; j < N; j++){
			board[i][j] = _board[i * N + j];
		}
	}





	
	/*
		根据你自己的策略来返回落子点,也就是根据你的策略完成对x,y的赋值
		该部分对参数使用没有限制，为了方便实现，你可以定义自己新的类、.h文件、.cpp文件
	*/
	//Add your own code below
	//my code

	int *top_c=new int[N];
	for (int j=0;j<N;j++){
		top_c[j]=top[j];
	}
	 
	int maxDepth=4;
	Move *move=new Move;
	Move *final=SearchMaxMin(board,0,-1000,1000,top_c,M,N,maxDepth,true,move);
	x=final->x;
	y=final->y;
	
	//my code






	/*
     //a naive example
	for (int i = N-1; i >= 0; i--) {
		if (top[i] > 0) {
			x = top[i] - 1;
			y = i;
			break;
		}
	}
    */
	
	
	/*
		不要更改这段代码
	*/
	clearArray(M, N, board);
	return new Point(x, y);
}


/*
	getPoint函数返回的Point指针是在本dll模块中声明的，为避免产生堆错误，应在外部调用本dll中的
	函数来释放空间，而不应该在外部直接delete
*/
extern "C" __declspec(dllexport) void clearPoint(Point* p){
	delete p;
	return;
}

/*
	清除top和board数组
*/
void clearArray(int M, int N, int** board){
	for(int i = 0; i < M; i++){
		delete[] board[i];
	}
	delete[] board;
}


/*
	添加你自己的辅助函数，你可以声明自己的类、函数，添加新的.h .cpp文件来辅助实现你的想法


*/

//my code

#include "Judge.h"
//评价棋盘函数
int calvalue(int M,int N,int **board,int label){
	int num_2=0;
	int num_3=0;
    
	for (int i=0;i<M;i++){
		for (int j=0;j<N;j++){
            
			//row num_3
			if (j+2<N){
				if (board[i][j]==label && 
					board[i][j+1]==label && 
					board[i][j+2]==label)
				{
					num_3+=1;
					//cout<<"row_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}
            //row num_2
		
		    if (j+1<N){
				if ((board[i][j-1]!=label || j-1==-1) && 
					board[i][j]==label && 
					board[i][j+1]==label && 
					(i+2==N || board[i][j+2]!=label))
				{
					num_2+=1;
					//cout<<"row_2"<<endl;
					//cout<<i<<j<<endl;

				}
			}
            
            
			//col num_3
			if (i+2<M){
				if (board[i][j]==label && 
					board[i+1][j]==label && 
					board[i+2][j]==label)
				{
					num_3+=1;
					//cout<<"col_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}

			//col num_2
			if (i+1<M){
				if ((i-1==-1 || board[i-1][j]!=label) &&
					board[i][j]==label &&
				    board[i+1][j]==label &&
				    (i+2==M || board[i+2][j]!=label))
				    {
				    	num_2+=1;
				    	//cout<<"col_2"<<endl;
				    	//cout<<i<<j<<endl;

				    }
			}

			//down to right num_3
			if (i-1!=-1 && j-1!=-1 && i+1!=M && j+1!=N){
				if (board[i][j]==label &&
					board[i-1][j-1]==label &&
					board[i+1][j+1]==label)
				{
					num_3+=1;
					//out<<"down_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}

			//down to right num_2
			if (i+1!=M && j+1!=N){
				if (board[i][j]==label && board[i+1][j+1]==label){
					if ((j-1==-1 || i-1==-1 || board[i-1][j-1]!=label)&&
						(j+2==N || i+2==M || board[i+2][j+2]!=label))
					{
						num_2+=1;
						//cout<<"down_2"<<endl;
						//cout<<i<<j<<endl;
					}

				}
			}

 
			//up to right num_3
			if (i+1!=M && j-1!=-1 && i-1!=-1 && j+1!=N){
				if (board[i][j]==label && 
					board[i+1][j-1]==label && 
					board[i-1][j+1]==label)
				{
					num_3+=1;
					//cout<<"up_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}

			//up to right num_2
			if (i-1!=-1 && j+1!=N){
				if (board[i][j]==label && board[i-1][j+1]==label){
					if ((i+1==M || j-1==-1 || board[i+1][j-1]!=label) &&
						(i-2==-1 || j+2==N || board[i-2][j+2]!=label))
					{
						num_2+=1;
						//cout<<"up_2"<<endl;
						//cout<<i<<j<<endl;
					}
				}
			}
		}
	}
	
    return  100*num_3+10*num_2;
}

int calvalue_2(int M,int N,int **board,int label,int label_2){
	int num_2=0;
	int num_3=0;
    int break_3=0;


	for (int i=0;i<M;i++){
		for (int j=0;j<N;j++){
            
			//row num_3
			if (j+3<N){
				if (board[i][j]==label && 
					board[i][j+1]==label && 
					board[i][j+2]==label &&
					board[i][j+3]==0 &&
					(i+1>=M || board[i+1][j+3]!=0))
				{
					num_3+=1;
					//cout<<"row_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}

			if (j+3<N){
				if (board[i][j]==label_2 && 
					board[i][j+1]==label_2 && 
					board[i][j+2]==label_2 &&
					board[i][j+3]==label&&
					(i+1>=M || board[i+1][j+3]==label))
				{
					break_3+=1;
					//cout<<"row_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}

			if (j-3>=0){
				if (board[i][j]==label &&
					board[i][j-1]==label &&
					board[i][j-2]==label &&
					board[i][j-3]==0 &&
					(i+1>=M || board[i+1][j-3]!=0))
				{
					num_3+=1;
				}
			}

		if (j-3>=0){
				if (board[i][j]==label_2 &&
					board[i][j-1]==label_2 &&
					board[i][j-2]==label_2 &&
					board[i][j-3]==label &&
					(i+1>=M || board[i+1][j-3]==label))
				{
					break_3+=1;
				}
			}



            //row num_2
		
		    if (j+2<N){
				if ((j-1==-1 || board[i][j-1]!=label ) && 
					board[i][j]==label && 
					board[i][j+1]==label && 
					board[i][j+2]==0 && 
					(i+1>=M || board[i+1][j+2]!=0))
				{
					num_2+=1;
					//cout<<"row_2"<<endl;
					//cout<<i<<j<<endl;

				}
			}

			if (j-2>=0){
				if ((board[i][j+1]!=label || j+1==N) &&
					board[i][j]==label &&
					board[i][j-1]==label &&
					board[i][j-2]==0 &&
					(i+1>=M || board[i+1][j-2]!=0))
				{
					num_2+=1;
				}
			}


            
            
			//col num_3
			if (i-3>=0){
				if (board[i][j]==label && 
					board[i-1][j]==label && 
					board[i-2][j]==label &&
					board[i-3][j]==0)
				{
					num_3+=1;
					//cout<<"col_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}
			
			if (i-3>=0){
				if (board[i][j]==label_2 && 
					board[i-1][j]==label_2 && 
					board[i-2][j]==label_2 &&
					board[i-3][j]==label)
				{
					break_3+=1;
					//cout<<"col_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}

			//col num_2
			if (i-2>=0){
				if (board[i][j]==label &&
					board[i-1][j]==label &&
					board[i-2][j]==0 &&
					(i+1>=M || board[i+1][j]!=label))
				    {
				    	num_2+=1;
				    	//cout<<"col_2"<<endl;
				    	//cout<<i<<j<<endl;

				    }
			}

			//down to right num_3
			if (i-2>=0 && j-2>=0 && i+1<M && j+1<N){
				if (board[i][j]==label &&
					board[i-1][j-1]==label &&
					board[i-2][j-2]==0 &&
					board[i-1][j-2]!=0 &&
					board[i+1][j+1]==label)
				{
					num_3+=1;
					//out<<"down_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}

			if (i-2>=0 && j-2>=0 && i+1<M && j+1<N){
				if (board[i][j]==label_2 &&
					board[i-1][j-1]==label_2 &&
					board[i-2][j-2]==label &&
					board[i-1][j-2]==label &&
					board[i+1][j+1]==label_2)
				{
					break_3+=1;
					//out<<"down_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}
			if (i-1>=0 && j-1>=0 && i+2<M && j+2<N){
				if (board[i-1][j-1]==label &&
					board[i][j]==label &&
					board[i+1][j+1]==label &&
					board[i+2][j+2]==0 &&
					(i+3>=M || board[i+3][j+2]!=0))
				    {
				    	num_3+=1;
				    }
			}
			if (i-1>=0 && j-1>=0 && i+2<M && j+2<N){
				if (board[i-1][j-1]==label_2 &&
					board[i][j]==label_2 &&
					board[i+1][j+1]==label_2 &&
					board[i+2][j+2]==label &&
					(i+3>=M || board[i+3][j+2]==label))
				    {
				    	break_3+=1;
				    }
			}




			//down to right num_2
			if (i+1<M && j+1<N){
				if (board[i][j]==label && board[i+1][j+1]==label){
					if ((j-1>=0 && i-1>=0 && board[i-1][j-1]==0 && board[i][j-1]!=0)&&
						(j+2>=N || i+2>=M || board[i+2][j+2]!=label))
					{
						num_2+=1;
						//cout<<"down_2"<<endl;
						//cout<<i<<j<<endl;
					}

				}
			}

			if (i+1<M && j+1<N){
				if (board[i][j]==label && board[i+1][j+1]==label){
					if ((i+2<M && j+2<N && board[i+2][j+2]==0) &&
						(i-1<=-1 || j-1<=-1 || board[i-1][j-1]!=label))
					{
						num_2+=1;
					}
				}
			}




 
			//up to right num_3
			if (i+1<M && j-1>=0 && i-2>=0 && j+2<N){
				if (board[i][j]==label && 
					board[i+1][j-1]==label && 
					board[i-1][j+1]==label &&
					board[i-2][j-2]==0 &&
					board[i-1][j+2]!=0)
				{
					num_3+=1;
					//cout<<"up_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}

			if (i+1<M && j-1>=0 && i-2>=0 && j+2<N){
				if (board[i][j]==label_2 && 
					board[i+1][j-1]==label_2 && 
					board[i-1][j+1]==label_2 &&
					board[i-2][j-2]==label &&
					board[i-1][j+2]==label)
				{
					break_3+=1;
					//cout<<"up_3"<<endl;
					//cout<<i<<j<<endl;
				}
			}

			if (i+2<M && j-2>=0 && i-1>=0 && j+1<N){
				if (board[i][j]==label &&
					board[i-1][j+1]==label &&
					board[i+1][j-1]==label &&
					board[i+2][j-2]==0 &&
					(i+3>=M || board[i+3][j-2]!=0))
				{
					num_3+=1;
				}
			}

           if (i+2<M && j-2>=0 && i-1>=0 && j+1<N){
				if (board[i][j]==label_2 &&
					board[i-1][j+1]==label_2 &&
					board[i+1][j-1]==label_2 &&
					board[i+2][j-2]==label &&
					(i+3>=M || board[i+3][j-2]==label))
				{
					break_3+=1;
				}
			}




			//up to right num_2
			if (i-1>=0 && j+1<N){
				if (board[i][j]==label && board[i-1][j+1]==label){
					if ((i+1>=M || j-1<0 || board[i+1][j-1]!=label) &&
						(i-2>=0 && j+2<N && board[i-2][j+2]==0 && board[i-1][j+2]!=0 ))
					{
						num_2+=1;
						//cout<<"up_2"<<endl;
						//cout<<i<<j<<endl;
					}
				}
			}

			if (i-1>=0 && j+1<N){
				if (board[i][j]==label && board[i-1][j+1]==label){
					if ((i-2<0 || j+2>=N || board[i-2][j+2]!=label) &&
						(i+1<M && j-1>=0 && board[i+1][j-1]==0) && 
						(i+2>=M || j-1<0 || board[i+2][j-1]!=0))
					{
						num_2+=1;
					}
				}
			}
		}
	}
	return 75*num_3+100*break_3+5*num_2;
}



Move *getvalue(int M, int N, int **board, Move *move){
    
	move->value=calvalue_2(M,N,board,2,1)-calvalue_2(M,N,board,1,2);
	return move;
}


Move *SearchMaxMin(int **myboard,int depth,int alpha,int beta,int top[],int M, int N,int maxDepth,bool maxPlayer, Move *move){

    if (depth==maxDepth){
			return getvalue(M,N,myboard,move);

	}

	if (maxPlayer){
	Move *temp=new Move;
	int best=-1000000;
	for (int y=0;y<N;y++){
		int x=top[y]-1;
		if (x==-1) continue;
		
		myboard[x][y]=2;
		top[y]=top[y]-1;
		//cout<<top[0]<<top[1]<<top[2]<<endl;
		//
		
		
		if (machineWin(x,y,M,N,myboard)){
			temp->value=10000*(1+maxDepth-depth);
			temp->x=x;
			temp->y=y;
		    myboard[x][y]=0;
		    top[y]=top[y]+1;
			//alpha=temp->value;
			break;

		}
		
		
		
		//
		move=SearchMaxMin(myboard,depth+1,alpha, beta, top, M, N, maxDepth, false, move);

		//cout<<x<<y<<move->value<<endl;
		myboard[x][y]=0;
        top[y]=top[y]+1;

        if (move->value>best){
            temp->x=x;
            temp->y=y;
        }
        best=max(best,move->value);
        //cout<<best<<endl;
        temp->value=best;
		alpha=max(alpha,best);

        
		if (beta<=alpha){
			//cout<<"pruning"<<endl;
			break;
		}

	}
	//cout<<temp->x<<temp->y<<temp->value<<endl;
	return temp;
}
    else{
    Move *temp=new Move;
	int best=1000000;
	for (int y=0;y<N;y++){
		int x=top[y]-1;
		if (x==-1) continue;
		
		myboard[x][y]=1;
		top[y]=top[y]-1;
		//cout<<top[0]<<top[1]<<top[2]<<endl;
		//
		
		
		if (userWin(x,y,M,N,myboard)){
			temp->value=-10000*(1+maxDepth-depth);
			temp->x=x;
			temp->y=y;
		    myboard[x][y]=0;
		    top[y]=top[y]+1;
			//beta=temp->value;
			break;

		}
		
		

		
		//
		move=SearchMaxMin(myboard,depth+1,alpha,beta,top,M,N,maxDepth,true,move);
		//cout<<x<<y<<move->value<<endl;
		//cout<<move->x<<move->y<<endl;
		myboard[x][y]=0;
		top[y]=top[y]+1;

        if (move->value<best){
		    temp->x=x;
		    temp->y=y;
		}
		best=min(best,move->value);
		temp->value=best;
		beta=min(beta,best);
		
		
		if (beta<=alpha){
			//cout<<"pruning"<<endl;
			break;
		}

	}
	//cout<<temp->x<<temp->y<<temp->value<<endl;
	return temp;
}
}

//my code
