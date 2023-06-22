#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#define MAX 10
// SEARCH COMPLEXITY: O(L) -> as long as the word
typedef struct trieNode{
	struct trieNode* arr[MAX];
	char word[MAX];
	int key;
	bool isWord;
}TrieNode;

TrieNode* getTrie(){
	int i;
	TrieNode* newTrie=(TrieNode*)malloc(sizeof(TrieNode));
	newTrie->isWord=false;
	strcpy(newTrie->word, "-1");
	for(i=0;i<MAX;i++)
		newTrie->arr[i]=NULL;
	return newTrie;
}

TrieNode* insert(TrieNode* root, int* pattern, int lenght, char* word){
	int i, j, k;
	if(root==NULL)
		root=getTrie();
	TrieNode* temp=root;
	for(i=0;i<lenght;i++){
			if(temp->arr[pattern[i]]==NULL){
				temp->arr[pattern[i]]=getTrie();
				temp->arr[pattern[i]]->key=pattern[i];
			}
			temp=temp->arr[pattern[i]];
	}
	if(strcmp(temp->word, "-1")==0){
		strcpy(temp->word, word);
		temp->isWord=true;
	}
	else{
		while(temp->arr[0]!=NULL)
			temp=temp->arr[0];
		temp->arr[0]=getTrie();
		strcpy(temp->arr[0]->word, word);
		temp->arr[0]->isWord=true;
	}
	return root;
}

int* findPath(char* word, char** keypad, int* pattern, int* lenght){
	int i, j, k, flag;
	for(i=0;word[i]!='\0';i++){
		flag=0, j=0;
		while(flag==0 && j<MAX){
			for(k=0;keypad[j][k]!='\0';k++)
				if(word[i]==keypad[j][k])
					flag=1;
			j++;
		}
		if(flag==1)
			pattern[i]=j-1;
		else
			printf("a letter that is not in the alphabet!\n");
	}
	*lenght=i;
	return pattern;
}

TrieNode* readAndCreate(TrieNode* root, char** keypad, char* fileName, int* pattern){
	int i, j, k, lenght;
	char temp[MAX];
	FILE* fp=fopen(fileName, "r");
	if(fp==NULL)
		printf("file error!");
	else{
		while(!feof(fp)){
			fscanf(fp, "%s\n", temp);
			pattern=findPath(temp, keypad, pattern, &lenght);
			printf("word->%s pattern->", temp);
			for(i=0;i<lenght;i++)
				printf("%d ", pattern[i]);
			printf("\n");
			root=insert(root, pattern, lenght, temp);
		}
		fclose(fp);
	}
	return root;
}

bool search(TrieNode* root, int* array, int lenght){
	if(root==NULL)
		return false;
	TrieNode* temp=root;
	int i;
	for(i=0;i<lenght;i++){
		temp=temp->arr[array[i]];
		if(temp==NULL)
			return false;
	}
	if(temp->isWord){
		printf("'%s' ", temp->word);
		while(temp->arr[0]!=NULL){
			temp=temp->arr[0];
			printf("'%s' ", temp->word);
		}
	}
	return temp->isWord;
}

int* extractDigits(int num, int* lenght){
	int i=0, digit, temp;
	int* arr=(int*)malloc(sizeof(int)*MAX);
	while(num>0){
		digit=num%10;
		arr[i]=digit;
		num=num/10;
		i++;
	}
	*lenght=i;
	for(i=0;i<*lenght/2;i++){
		temp=arr[i];
		arr[i]=arr[*lenght-i-1];
		arr[*lenght-i-1] = temp;
	}
	return arr;
}

void freeTrie(TrieNode* root){
	int i;
	for(i=0; i<MAX; i++) 
        if (root->arr[i] != NULL) 
            freeTrie(root->arr[i]);
    free(root);
}

int main(){
	setlocale(LC_ALL, "Turkish");
	char *keypad[MAX]= {'\0'};
	keypad[0]="#";
	keypad[1]="зрью";
	keypad[2]="abc";
	keypad[3]="def";
	keypad[4]="ghi";
	keypad[5]="jkl";
	keypad[6]="mno";
	keypad[7]="pqrs";
	keypad[8]="tuv";
	keypad[9]="wxyz";
	char* fileName="words.txt", input[MAX];
	bool check;
	TrieNode* root=NULL;
	int *array, num, lenght;
	int *pattern=(int*)malloc(sizeof(int)*MAX);
	printf("Words in the dictionary:\n");
	root=readAndCreate(root, keypad, fileName, pattern);
	printf("Press 'q' to exit\n");
	while(strcmp(input, "q")!=0){
		printf("input: ");
		scanf("%s", &input);
		if(strcmp(input, "q")!=0){
			num=atoi(input);
			array=extractDigits(num, &lenght);
			check=search(root, array, lenght);
			if(check)
				printf("Found\n");
			else
				printf("No equivalent in the dictionary\n");
		}
	}
	freeTrie(root);
	return 0;
}
