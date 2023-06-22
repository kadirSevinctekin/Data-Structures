#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct cark{
	int data;
	struct cark *prev;
	struct cark *next;
}CARK;

int kontrol(CARK* head, int k){
	CARK* temp=head;
	do{
		if(temp->data==k){
			return 1;
		}
		temp=temp->next;
	}while(temp!=head);
	return 2;
}

void sayilariatama1(CARK** head1, int n, int m){
	int i=0, k;
	while(i<m){
		k=rand()%n+1;
		if(*head1==NULL){
			CARK* newNode=(CARK*)malloc(sizeof(CARK));
			newNode->data=k;
			*head1=newNode; (*head1)->prev=*head1; (*head1)->next=*head1;
		}
		else{
			int flag;
			flag=kontrol(*head1, k);
			while(flag==1){
				k=rand()%n+1;
				flag=kontrol(*head1, k);
			}
			CARK* newNode=(CARK*)malloc(sizeof(CARK));
			newNode->data=k;
			CARK* lastNode=(*head1)->prev; newNode->next=*head1;
			newNode->prev=lastNode; (*head1)->prev=newNode;
			lastNode->next=newNode; *head1=newNode;
		}
		i++;
	}
}

void sayilariatama2(CARK** head1, CARK** head2, int n, int m, int* ortak){
	int i=0, k, count=0, q, w;
	while(count!=1){
		count=0; i=0; *head2=NULL;
		while(i<m){
			k=rand()%n+1;
			if(*head2==NULL){
				CARK* newNode=(CARK*)malloc(sizeof(CARK));
				newNode->data=k;
				*head2=newNode; (*head2)->prev=*head2; (*head2)->next=*head2;
			}
			else{
				int flag;
				flag=kontrol(*head2, k);
				while(flag==1){
					k=rand()%n+1;
					flag=kontrol(*head2, k);
				}
				CARK* newNode=(CARK*)malloc(sizeof(CARK));
				newNode->data=k;
				CARK* lastNode=(*head2)->prev; newNode->next=*head2;
				newNode->prev=lastNode; (*head2)->prev=newNode;
				lastNode->next=newNode; *head2=newNode;
			}
			i++;
		}
		CARK* temp1; CARK* temp2=*head2;
		for(q=0;q<m;q++){
			temp1=*head1;
			for(w=0;w<m;w++){
				if(temp1->data==temp2->data){
					count++;
				}
				temp1=temp1->next;
			}
			temp2=temp2->next;
		}
	}
	CARK* temp1; CARK* temp2=*head2;
	for(q=0;q<m;q++){
		temp1=*head1;
		for(w=0;w<m;w++){
			if(temp1->data==temp2->data){
				*ortak=temp1->data;
			}
			temp1=temp1->next;
		}
		temp2=temp2->next;
	}
}

void sayilariatama3(CARK** head3 ,int n, int m, int ortak){
	int i=0, k, flag=0, j;
	CARK* temptemp;
	while(flag==0){
		i=0; *head3=NULL;
		while(i<m){
			k=rand()%n+1;
			if(*head3==NULL){
				CARK* newNode=(CARK*)malloc(sizeof(CARK));
				newNode->data=k;
				*head3=newNode; (*head3)->prev=*head3; (*head3)->next=*head3;
			}
			else{
				int flag;
				flag=kontrol(*head3, k);
				while(flag==1){
					k=rand()%n+1;
					flag=kontrol(*head3, k);
				}
				CARK* newNode=(CARK*)malloc(sizeof(CARK));
				newNode->data=k;
				CARK* lastNode=(*head3)->prev; newNode->next=*head3;
				newNode->prev=lastNode; (*head3)->prev=newNode;
				lastNode->next=newNode; *head3=newNode;
			}
			i++;
		}
		temptemp=*head3;
		for(j=0;j<m;j++){
			if(temptemp->data==ortak){
				flag=1;
			}
		}
	}
}

void yazdir(CARK* head){
	if(head==NULL){
		printf("liste bos\n");
	}
	else{
		CARK* cur=head;
		do{
			printf("%d\t", cur->data);
			cur=cur->next;
		}while(cur!=head);
	}
	printf("\n\n");
}

void degerlerial(int* n, int* m){
	int flag=0;
	while(flag==0){
		printf("N ve M degerlerini giriniz: ");
		scanf("%d%d", n, m);
		flag=1;
		if(*n<(2*(*m))-1){
			printf("N > 2*M-1 olmalidir.\n");
			flag=0;
		}
	}
}

void yerBulma(CARK *head, int ortak, int *poz, int cark){
	int i=1;
	CARK *temp=head;
	do{
		if(temp->data==ortak){
			printf("%d. carktaki konumu: %d\n", cark, i);
			*poz=i;
		}
		temp=temp->next;
		i++;
	}while(temp!=head); 
}

void hamleler(int poz1, int poz, int m, int* h, int cark){
	if(poz1>poz){
		if(poz1-poz>m-(poz1-poz)){
			if(poz1-poz==m/2 && m%2==0){
				printf("%d. cark sola dogru %d adim cevrilmeli (Saga dogru da %d adim cevrilebilir.)\n", cark, m-(poz1-poz), m-(poz1-poz));
				*h=-(m-(poz1-poz));
			}
			else{
				printf("%d. cark sola dogru %d adim cevrilmeli\n", cark, m-(poz1-poz));
				*h=-(m-(poz1-poz));	
			}
		}
		else{
			if(poz1-poz==m/2 && m%2==0){
				printf("%d. cark saga dogru %d adim cevrilmeli (Sola dogru da %d adim cevrilebilir.)\n", cark, poz1-poz, poz1-poz);
				*h=poz1-poz;
			}
			else{
				printf("%d. cark saga dogru %d adim cevrilmeli\n", cark, poz1-poz);
				*h=poz1-poz;
			}
		}
	}
	else if(poz1==poz){
		printf("%d. cark dogru yerde\n", cark);
		*h=poz1;
	}
	else if(poz1<poz){
		if(poz-poz1>m-(poz-poz1)){
			if(poz-poz1==m/2 && m%2==0){
				printf("%d. cark saga dogru %d adim cevrilmeli (Sola dogru da %d adim cevrilebilir.)\n", cark, m-(poz-poz1), m-(poz-poz1));
				*h=m-(poz-poz1);
			}
			else{
				printf("%d. cark saga dogru %d adim cevrilmeli\n", cark, m-(poz-poz1));
				*h=m-(poz-poz1);
			}
		}
		else{
			if(poz-poz1==m/2 && m%2==0){
				printf("%d. cark sola dogru %d adim cevrilmeli (Saga dogru da %d adim cevrilebilir.)\n", cark, poz-poz1, poz-poz1);
				*h=-(poz-poz1);
			}
			else{
				printf("%d. cark sola dogru %d adim cevrilmeli\n", cark, poz-poz1);
				*h=-(poz-poz1);
			}
		}
	}	
}

void dondurme(CARK** head, int poz1, int h){
	CARK* cur=*head; int i;
	if(h!=poz1){
		if(h<0){
			for(i=0;i<-h;i++){
				cur=cur->next;
			}
		}
		else{
			for(i=0;i<h;i++){
				cur=cur->prev;
			}
		}
		*head=cur;
	}
}

void freeLL(CARK **head){
	if(*head!=NULL){
		CARK *cur=*head, *temp;
		do{
			temp=cur;
			cur=cur->next;
			free(temp);
		}while(cur!=*head);
	}
}

int main(){
	srand(time(NULL));
	CARK *head1=NULL, *head2=NULL, *head3=NULL;
	int n, m, ortak, poz1, poz2, poz3, h2, h3;
	degerlerial(&n, &m);
	sayilariatama1(&head1, n, m);
	sayilariatama2(&head1, &head2, n, m, &ortak);
	sayilariatama3(&head3 , n, m, ortak);
	yazdir(head1); 
	yazdir(head2); 
	yazdir(head3);
	printf("\nortak sayi: %d\n\n", ortak);
	yerBulma(head1, ortak, &poz1, 1);
	yerBulma(head2, ortak, &poz2, 2);
	yerBulma(head3, ortak, &poz3, 3); 
	printf("\n");
	hamleler(poz1, poz2, m, &h2, 2);
	hamleler(poz1, poz3, m, &h3, 3);
	dondurme(&head2, poz1, h2);
	dondurme(&head3, poz1 ,h3); printf("\n\n");
	yazdir(head1); yazdir(head2); yazdir(head3);
	freeLL(&head1); freeLL(&head2); freeLL(&head3);
	return 0;
}
