#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
	int data, firstValue;
	struct node *next;
}NODE;

typedef struct tree{
	int data, firstValue;
	struct tree *left;
	struct tree *right;
}TREE;

void getInitValues(int *n, int *m){
	printf("enter the N (max weight) and M (number of nodes): ");
	scanf("%d%d", n, m);
	if(*n<*m || *m<1)
		getInitValues(n,m);
}

int control(NODE* head, int k){
	NODE* temp=head;
	while(temp!=NULL){
		if(temp->data==k)
			return 1;
		temp=temp->next;
	}
	return 2;
}

void randomNumbers(NODE** head, int n, int m){
	int i=0, k;
	while(i<m){
		k=rand()%n+1;
		if(*head==NULL){
			NODE* newNode=(NODE*)malloc(sizeof(NODE));
			newNode->data=newNode->firstValue=k;
			*head=newNode; (*head)->next=NULL;
		}
		else{
			int flag;
			flag=control(*head, k);
			while(flag==1){
				k=rand()%n+1;
				flag=control(*head, k);
			}
			NODE* newNode=(NODE*)malloc(sizeof(NODE));
			newNode->data=newNode->firstValue=k;
			newNode->next=*head;
			*head=newNode;
		}
		i++;
	}
}

void traverseList(NODE* head){
	NODE* temp=head;
	while(temp!=NULL){
		printf("%d ", temp->data);
		temp=temp->next;
	}
	printf("\n\n\n");
}

TREE* getNode(int firstValue, int data){
	TREE* newNode=(TREE*)malloc(sizeof(TREE));
	newNode->data=data;
	newNode->firstValue=firstValue;
	newNode->left=NULL; newNode->right=NULL;
	return newNode;
}

TREE* constructTree(TREE* root, int firstValue, int data){
	if(root==NULL){
		root=getNode(firstValue, data);
		return root;
	}
	else if(firstValue > root->firstValue)
		root->right=constructTree(root->right, firstValue, data);
	else if(firstValue < root->firstValue)
		root->left=constructTree(root->left, firstValue, data);	
	return root;
}

void printTree(TREE* root, int distance){
	int i;
	if (root == NULL)
        return;
    distance += 10;
    printTree(root->right, distance);
    printf("\n");
    for (i = 10; i < distance; i++)
        printf(" ");
    printf("%d<%d>\n", root->firstValue, root->data);
    printTree(root->left, distance);
}

void print(TREE* root){
	printTree(root, 0);
}

TREE* findNode(TREE* root, int k){
	if(root==NULL) return NULL;
	if(root->firstValue==k) return root;
	if(k<root->firstValue)
		findNode(root->left, k);
	else
		findNode(root->right, k);
}

TREE* minValue(TREE* node){
    TREE* current = node;
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}

TREE* deleteNode(TREE* root, int firstValue){
    if(root==NULL)
    	return root;
    if(firstValue<root->firstValue)
    	root->left=deleteNode(root->left, firstValue);
    else if(firstValue>root->firstValue)
    	root->right=deleteNode(root->right, firstValue);
    else{
    	if(root->left==NULL){
    		TREE* temp=root->right;
    		free(root);
    		return temp;
		}
		else if(root->right==NULL){
			TREE* temp=root->left;
			free(root);
			return temp;
		}
		TREE* temp=minValue(root->right);
		root->firstValue=temp->firstValue;
		root->data=temp->data;
		root->right=deleteNode(root->right, temp->firstValue);
	}
	return root;
}

void push(NODE** myStack, int fallenValue){
	if(*myStack==NULL){
		NODE* newNode=(NODE*)malloc(sizeof(NODE));
		newNode->data=fallenValue;
		*myStack=newNode; (*myStack)->next=NULL;
	}
	else{
		NODE* newNode=(NODE*)malloc(sizeof(NODE));
		newNode->data=fallenValue;
		newNode->next=*myStack; *myStack=newNode;
	}
}

void shoot(TREE** root, int m, NODE** myStack){
	int k, i, p;
	TREE* flag;
	while(m!=0){
		printf("please enter the value of node to shoot: ");
		scanf("%d", &k);
		flag=findNode(*root, k);
		while(flag==NULL){
			printf("please enter the value of an exist node to shoot: ");
			scanf("%d", &k);
			flag=findNode(*root, k);
		}
		printf("please enter the shot power: ");
		scanf("%d", &p);
		while(p<1){
			printf("please enter the shot power as a positive number: ");
			scanf("%d", &p);
		}
		if(p<flag->data){
			flag->data-=p;
		}
		else{
			push(myStack, flag->firstValue);
			*root=deleteNode(*root, flag->firstValue);
			m--;
		}
		printf("\n\n------------------------------------\n\n");
		print(*root);				
	}
}

void printStack(NODE* myStack, NODE** myStack2){
	printf("basket: ");
	while(myStack!=NULL){
		printf("%d ", myStack->data);
		push(myStack2, myStack->data);
		myStack=myStack->next;
	}
	printf("\n");
}

void output(NODE* myStack2){
	while(myStack2!=NULL){
		printf("%d ", myStack2->data);
		myStack2=myStack2->next;
	}	
}

void freeStack(NODE* myStack){
	NODE* temp=myStack, *cur;
	if(temp->next==NULL)
		free(temp);
	else{
		while(temp->next!=NULL){
			cur=temp;
			temp=temp->next;
			free(cur);
		}
		free(temp);
	}
}

int main(){
	srand(time(NULL));
	int n, m, i;
	NODE* head=NULL, *temp, *myStack=NULL, *myStack2=NULL;
	TREE* root=NULL;
	getInitValues(&n, &m);
	randomNumbers(&head, n, m);	
	traverseList(head);
	temp=head;
	for(temp=head;temp!=NULL;temp=temp->next)
		root=constructTree(root, temp->firstValue, temp->data);
	printf("root=%d\n\n", head->firstValue);
	print(root);
	shoot(&root, m, &myStack);
	printStack(myStack, &myStack2);
	printf("output: ");
	output(myStack2);
	freeStack(head);
	freeStack(myStack);
	freeStack(myStack2);
	return 0;
}
