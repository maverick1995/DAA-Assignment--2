/*
Author : Shashanth R V , Anvesh Reddy Patlolla  , Akarshan Sajja 
DAA Assignment 2 - Question 1 
*/

#include <stdio.h>
#define max 100

int capacity[max][max] ; // capacity of the edges
int flow[max][max] ;   // flow through 
int status[max] ;    // status of every node durinf breadth first search
int pred[max] ;   // predecessor for every node in the augmented pat foung in BFS 
int q[max] ;   //  used in implementing queues in BFS 

int push , pop ;    
int nodes , edges ; // number of nodes and edges 
int maxflow = 0 ;  // flow through the edges 

int min(int a , int b){
	if(a<b)
	return a ; 
	else
	return b ; 
	}

void enqueue(int x ){
	q[pop] = x ; 
	pop++ ; 
	status[x] = 1 ; 
	}

int dequeue(){
	int x = q[push] ; 
	push++ ; 
	status[x] = 2 ; 
	return x ; 
	
}	
	

int search(int source ,int sink ){
	int i,j  ; 
	for(i=0; i<nodes; i++){
		status[i] = 0 ;  
	}
	push =0 ; pop = 0 ; 
	enqueue(source) ; 
	pred[source] = -1 ; 
	while(push!=pop){
		j = dequeue() ; 
		// searching for all the adjacent nodes in the graph which has been dequeued whose residual is 
		// greater than zero and hasnt been selected 
		for(i=0 ; i<nodes ; i++){
			if(status[i]==0 && capacity[j][i] - flow[j][i]>0 ){
				enqueue(i) ; 
				pred[i] = j ; 
			}
			
		}
		
		
	}
	
	if(status[sink]==2)   // return path found if the sink has been dequeued 
	return 1 ; 
	else
	return 0 ; 
	
	}



ford_f(char * s){
	FILE *fp  = fopen(s , "r") ; // opens the input file 
	fscanf(fp,"%d %d",&nodes , &edges) ;    
	int i , j  ; 
	for(i=0; i < nodes; i++){
		for(j=0; j<nodes ; j++){
			capacity[i][j] =0 ;     // intitiale the capacity and flow to zero for all the edges even which are not there int he graph 
			flow[i][j] = 0 ; 
		}
	}
	int e1,e2,cap ; 
	for(i=0 ; i<edges ; i++){
		fscanf(fp,"%d %d %d",&e1,&e2,&cap) ; 
		capacity[e1][e2] = cap ; // update the capacities of the edges there in the graph 
	}
	fclose(fp) ; 
	
	while(search(0,nodes-1)){                               //  run the for fulkersons algo till there is st path .
		int bottleneck = 100000 ; 
		for(i= nodes -1 ; pred[i]>=0 ; i = pred[i]){          //finding the bottleneck 
			bottleneck = min(bottleneck , capacity[pred[i]][i] - flow[pred[i]][i]  ) ; 
		}
		
		for(i= nodes-1 ; pred[i]>=0 ; i = pred[i] ){       //  updating the acuual flow and residual flow ; 
			 flow[pred[i]][i] += bottleneck;
	         flow[i][pred[i]] -= bottleneck;
		}
		
		maxflow += bottleneck ;    // updating the maximum flow throug the graph
	}
	
	printf("%d\n",maxflow) ; 
	}



int main(int argv , char *args[]) {
	// your code goes here
	if(argv!=2){                                //  alerting if wrong input given 
		printf("Wrong Input format\n") ; 
		return 0  ;  
	}
	
	ford_f(args[1]) ; 
	return 0;
}
