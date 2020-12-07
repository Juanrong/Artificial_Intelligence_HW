#include <iostream>
#include "Point.h"
#include "Strategy.h"

using namespace std;

/*
	���Ժ����ӿ�,�ú������Կ�ƽ̨����,ÿ�δ��뵱ǰ״̬,Ҫ�����������ӵ�,�����ӵ������һ��������Ϸ��������ӵ�,��Ȼ�Կ�ƽ̨��ֱ����Ϊ��ĳ�������
	
	input:
		Ϊ�˷�ֹ�ԶԿ�ƽ̨ά����������ɸ��ģ����д���Ĳ�����Ϊconst����
		M, N : ���̴�С M - ���� N - ���� ����0��ʼ�ƣ� ���Ͻ�Ϊ����ԭ�㣬����x��ǣ�����y���
		top : ��ǰ����ÿһ���ж���ʵ��λ��. e.g. ��i��Ϊ��,��_top[i] == M, ��i������,��_top[i] == 0
		_board : ���̵�һά�����ʾ, Ϊ�˷���ʹ�ã��ڸú����տ�ʼ���������Ѿ�����ת��Ϊ�˶�ά����board
				��ֻ��ֱ��ʹ��board���ɣ����Ͻ�Ϊ����ԭ�㣬�����[0][0]��ʼ��(����[1][1])
				board[x][y]��ʾ��x�С���y�еĵ�(��0��ʼ��)
				board[x][y] == 0/1/2 �ֱ��Ӧ(x,y)�� ������/���û�����/�г������,�������ӵ㴦��ֵҲΪ0
		lastX, lastY : �Է���һ�����ӵ�λ��, ����ܲ���Ҫ�ò�����Ҳ������Ҫ�Ĳ������ǶԷ�һ����
				����λ�ã���ʱ��������Լ��ĳ����м�¼�Է������ಽ������λ�ã�����ȫȡ�������Լ��Ĳ���
		noX, noY : �����ϵĲ������ӵ�(ע:��ʵ���������top�Ѿ����㴦���˲������ӵ㣬Ҳ����˵���ĳһ��
				������ӵ�����ǡ�ǲ������ӵ㣬��ôUI�����еĴ�����Ѿ������е�topֵ�ֽ�����һ�μ�һ������
				��������Ĵ�����Ҳ���Ը�����ʹ��noX��noY��������������ȫ��Ϊtop������ǵ�ǰÿ�еĶ�������,
				��Ȼ�������ʹ��lastX,lastY�������п��ܾ�Ҫͬʱ����noX��noY��)
		���ϲ���ʵ���ϰ����˵�ǰ״̬(M N _top _board)�Լ���ʷ��Ϣ(lastX lastY),��Ҫ���ľ�������Щ��Ϣ�¸������������ǵ����ӵ�
	output:
		������ӵ�Point
*/
extern "C" __declspec(dllexport) Point* getPoint(const int M, const int N, const int* top, const int* _board, 
	const int lastX, const int lastY, const int noX, const int noY){
	/*
		��Ҫ������δ���
	*/
	int x = -1, y = -1;//���ս�������ӵ�浽x,y��
	int** board = new int*[M];
	for(int i = 0; i < M; i++){
		board[i] = new int[N];
		for(int j = 0; j < N; j++){
			board[i][j] = _board[i * N + j];
		}
	}





	
	/*
		�������Լ��Ĳ������������ӵ�,Ҳ���Ǹ�����Ĳ�����ɶ�x,y�ĸ�ֵ
		�ò��ֶԲ���ʹ��û�����ƣ�Ϊ�˷���ʵ�֣�����Զ����Լ��µ��ࡢ.h�ļ���.cpp�ļ�
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
		��Ҫ������δ���
	*/
	clearArray(M, N, board);
	return new Point(x, y);
}


/*
	getPoint�������ص�Pointָ�����ڱ�dllģ���������ģ�Ϊ��������Ѵ���Ӧ���ⲿ���ñ�dll�е�
	�������ͷſռ䣬����Ӧ�����ⲿֱ��delete
*/
extern "C" __declspec(dllexport) void clearPoint(Point* p){
	delete p;
	return;
}

/*
	���top��board����
*/
void clearArray(int M, int N, int** board){
	for(int i = 0; i < M; i++){
		delete[] board[i];
	}
	delete[] board;
}


/*
	������Լ��ĸ�������������������Լ����ࡢ����������µ�.h .cpp�ļ�������ʵ������뷨


*/

//my code

#include "Judge.h"
//�������̺���
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
