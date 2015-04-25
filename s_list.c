#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define oo 10000


struct node {
	int key ; 
	int value ; 
	struct node * next ;
	struct node * prev ; 
	struct node * above ; 
	struct node * below ; 
	} ; 


struct node * topleft  ; 
struct node * topright ; 


 int rlevel()
{
    int level = 1;
    while (rand() < RAND_MAX/2 && level < 6)
        level++;
    return level;
}

void inc_level(){
//printf("in\n") ; 
	struct node * p  = (struct node *)malloc(sizeof(struct node )) ; 
	struct node * q = (struct node * )malloc(sizeof(struct node )) ; 
	p->key = -oo ; 
	p->value = -oo ; 
	q->key = oo ;  
	p->value  = oo ; 
	topleft->above = p ;  
	p->below = topleft ; 
	topright->above = q ; 
	q->below - topright ; 
	topright = q ; 
	topleft = p ;  
	topleft->next = topright ; 
	topright->prev = topleft ; 
	
}

struct node * search(int k ){
	struct node * p = topleft  ;
	while(p->below!=NULL){
		p = p->below   ; 
		while(k>=p->next->key )
		p = p->next ; 
	}
	
	//if(p->key==k)
	//printf("found\n");  
	//else
	//printf("not found \n ") ; 
	
	return p ;
	
}


void print(){
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
	struct node * p = search(k) ; 
	struct node * q = (struct node *)malloc(sizeof(struct node )) ; 
	q->key = k ; 
	q->value  =  k ; 
	q->next = p->next ; 
	p->next->prev = q ; 
	p->next = q ; 
	q->prev =  p  ;
	int lev = rand()%6 ; 
	int i ; 
        printf("List added with level %d\n",lev) ; 
	for(i = 0 ; i < lev ; i++){
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
	struct node * new = search(x) ; 
	if(new->key!=x){
		printf("%d doesn'nt exist in skip list\n",x) ; 
		return  ; 
	}
	
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
