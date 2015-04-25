#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define oo 10000

// creating a structure whic hhold the key and value and the pointer to the 
//nodes above,  below , previous and next position 
struct node {
	int key ; 
	int value ; 
	struct node * next ;
	struct node * prev ; 
	struct node * above ; 
	struct node * below ; 
	} ; 


struct node * topleft  ; // nodes at the topleft corner and nodes at the topright 
struct node * topright ; 


 int rlevel()
{
    int level = 1;
    while (rand() < RAND_MAX/2 && level < 6)
        level++;
    return level;
}


// function to increase the level of the skiplist by one for the nodes at the 
// topleft and topright 
void inc_level(){
//printf("in\n") ; 
	struct node * p  = (struct node *)malloc(sizeof(struct node )) ; 
	struct node * q = (struct node * )malloc(sizeof(struct node )) ; 
	p->key = -oo ; //  setting the value of the left most node to negative infinity
	p->value = -oo ; 
	q->key = oo ;  //setting the value of the right most node to negative infinity
	p->value  = oo ; 
	topleft->above = p ;  // increasing the level of the node 
	p->below = topleft ; // linking the pointers in the appropriate way 
	topright->above = q ; 
	q->below - topright ; 
	topright = q ; 
	topleft = p ;  
	topleft->next = topright ; 
	topright->prev = topleft ; 
	
}

struct node * search(int k ){
	struct node * p = topleft  ; // search begins at the topleft 
	while(p->below!=NULL){    // going down the level one by one through this loop 
		p = p->below   ; 
		while(k>=p->next->key ) // searches for the maximum element grater than k in that level 
		p = p->next ; 
	}
	
	//if(p->key==k)
	//printf("found\n");  
	//else
	//printf("not found \n ") ; 
	
	return p ; // returning the pointer to that level
	
}


void print(){ // prints the value key and livel of the list 
	struct node * new = topleft ; 
	while(new->below!=NULL){
		new = new->below ; 
	}
	new = new->next ; 
	int count ; 
    printf("\tKey\tValue\tLevel\n") ; 
	while(new->next!=NULL){
		count = 0 ; 
		int key = new->key ;
		struct node * temp = new ; 
		while(temp->above!=NULL){
			count++ ; 
			temp= temp->above ; 
		}
		new = new->next ; 
		printf("\t%d\t%d\t%d\n",key, key , count) ; 
	}
	
	
	
}

void insert(int k ){
	struct node * p = search(k) ; // returns the pointer of the node just less than k in lowest level 
	struct node * q = (struct node *)malloc(sizeof(struct node )) ; 
	q->key = k ; 
	q->value  =  k ; 
	q->next = p->next ; // linking the pointers between p and the new node ; 
	p->next->prev = q ; 
	p->next = q ; 
	q->prev =  p  ;
	int lev = rand()%6 ;   // creating random level for the list 
	int i ; 
    printf("List added with level %d\n",lev) ; 
	for(i = 0 ; i < lev ; i++){  // code block to link all the list before the one inserted with the one inserted 
		while(p->above==NULL){ 
 
			 
            //printf("val %d\n",p->key) ;
			if(p==topleft)
			inc_level() ; 
            else
            p = p->prev ;
			//printf("gg1\n") ;
		}
        //printf("gg\n") ;
		p = p->above ; 
		struct node * new  = (struct node *)malloc(sizeof(struct node ) ) ;
		new->key = k ; 
		new->value =  k  ; 
		new->next = p->next ; 
		p->next->prev = new ; 
		new->prev = p ; 
		p->next = new ; 
		new->below = q ; 
		q->above = new ; 
		q= new ; 
		
	}
	
}


void delete(int x ){
	struct node * new = search(x) ; // searching for the node pointer which kas key value k  
	if(new->key!=x){
		printf("%d doesn'nt exist in skip list\n",x) ; 
		return  ; 
	}
	
	// linking all the nodes in the list with the nodes previous to the one with the node next to this 
	while(new->above != NULL){ 
		new->prev->next = new->next ; 
		new->next->prev  = new->prev ; 
		struct node * tmp = new ; 
		new = new->above ; 
		free(tmp) ; 
	}
	printf("Deleted Successfully\n") ; 
	print() ; 
}


int main(void) {
	// your code goes here
	topleft = (struct node *)malloc(sizeof(struct node ))  ;
	topright = (struct node *)malloc(sizeof(struct node ))  ;
	topleft->key = -oo ; 
	topleft->value = oo ; 
	topright->key = oo  ; 
	topright->value =  oo ; 
	topright->prev = topleft ; 
	topleft->next = topright ; 
	
	while(1){
		printf("Enter 1 for insert \nEnter 2 for search \nEnter 3 for print \nEnter 4 for Delete\n") ;  
		int d ,a,b; 
		scanf("%d",&d) ; 
		switch(d){
			case 1 : 
			 //int a ; 
			 scanf("%d",&a) ; 
			 insert(a) ; 
			 break ; 
			 case 2 : 
			 //int b ; 
			 scanf("%d",&b) ; 
			 struct node * ret  = search(b) ;
             if(ret->key==b)
             printf("found\n") ; 
             else
             printf("Not found\n") ; 
			 case 3 : 
			 print() ; 
             break ; 
			 case 4 : 
			 scanf("%d",&b) ;
			 delete(b) ; 

			
		}
 
		
	}
	
	
	return 0;  
}
