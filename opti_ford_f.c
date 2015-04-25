 
	if (a>b)
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
	

void dfs(int s ){                       //  function for DFS for finding min cut 
        //printf("gg\n") ; 
	visited[s] = 1 ; 
	int i ; 
	for(i= 0 ; i< nodes ; i++){
		if(capacity[s][i]-flow[s][i]!=0 && !visited[i] ){
                //printf("%d\n",i) ; 
		dfs(i) ; 
}
	}
	
	
}


int search(int source ,int sink, int delta ){
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
		// greater than delta and hasnt been selected 
		for(i=0 ; i<nodes ; i++){ 
			if(status[i]==0 && capacity[j][i] - flow[j][i]>delta ){
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
	int e1,e2,cap, maximum= 0  , delta =1 ;  
	for(i=0 ; i<edges ; i++){
		fscanf(fp,"%d %d %d",&e1,&e2,&cap) ; 
		capacity[e1][e2] = cap ; // update the capacities of the edges there in the graph 
		maximum = maxi(maximum,cap) ; 
	}
	fclose(fp) ; 
	
	while(maximum>=1){
		maximum = maximum/2 ; 
		delta = delta * 2 ; 
	}
	
	while(delta>=1){
	while(search(0,nodes-1, delta)){                               //  run the for fulkersons algo till there is st path .
		int bottleneck = 100000 ; 
		for(i= nodes -1 ; pred[i]>=0 ; i = pred[i]){           //finding the bottleneck 
			bottleneck = min(bottleneck , capacity[pred[i]][i] - flow[pred[i]][i]  ) ; 
		}
		
		for(i= nodes-1 ; pred[i]>=0 ; i = pred[i] ){       //  updating the acuual flow and residual flow ; 
			 flow[pred[i]][i] += bottleneck;
	         flow[i][pred[i]] -= bottleneck;
		}
		
		maxflow += bottleneck ;    // updating the maximum flow throug the graph
	}
	delta = delta/2 ; 
	}
	
	for(i=0 ; i< nodes ; i++){
		visited[i] = 0 ; 
	}
	printf("Maximum flow through the network is : %d\n",maxflow) ;
	dfs(0) ;                // running depth first search for find the min cut . ..
	printf("Following are the min cut edges cut by the arc\n");
	for(i=0 ; i<nodes;i++){
		for(j=0 ; j<nodes ;j++){
                        //printf("%d %d %d\n",i,j,flow[i][j]) ; 
			if(visited[i]&& !visited[j] && capacity[i][j]!=0 )
			printf("%d---%d\n",i,j) ; 

		}
	}
	
	 
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
