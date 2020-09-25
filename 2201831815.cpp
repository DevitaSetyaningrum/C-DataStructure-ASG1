#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	int key;
	char name[110];
	long int bal;
	int height;
	Node *left;
	Node *right;
};

Node *ROOT = NULL, *temp = NULL;

int get_maximum(int heightLeft, int heightRight){
	return (heightLeft > heightRight) ? heightLeft : heightRight;
}

int get_height(Node *node){
	if( !node ){
		return 0;
	}
	else{
		return node->height;
	}
}

int get_balance(Node *node){
	if( !node ){
		return 0;
	}
	else{
		return (get_height(node->left) - get_height(node->right));
	}
}

int calculate_height(Node *node){
	return 1 + get_maximum(get_height(node->left), get_height(node->right));
}

Node* get_right_most_of_left_child(Node *node){
	Node *curr = node->left;
	while(curr->right){
		curr = curr->right;
	}
	return curr;
	
}

Node* create_node(int key, char name[], long int bal){
	Node *node = (Node*)malloc(sizeof(Node));
	node->key = key;
	strcpy(node->name, name);
	node->bal = bal;
	node->height = 1;
	node->left = node->right = NULL;
	printf("\n");
	printf("Account [%.8d (%s)] was registered successfully.\n\n", key, name);
	printf("Press ENTER to continue...\n");
	getchar();
	return node;
}

Node* right_rotate(Node *curr){
	Node *pivot = curr->left;
	Node *cut = pivot->right;
	
	pivot->right = curr;
	curr->left = cut;
	
	curr->height = calculate_height(curr);
	pivot->height = calculate_height(pivot);
	
	return pivot;
}

Node* left_rotate(Node *curr){
	Node *pivot = curr->right;
	Node *cut = pivot->left;
	
	pivot->left = curr;
	curr->right = cut;
	
	curr->height = calculate_height(curr);
	pivot->height = calculate_height(pivot);
	
	return pivot;	
}

Node* insert_node(Node* node, int key, char name[], long int bal){
	if( !node ){
		return create_node(key, name, bal);
	}	
	
	if( key < node->key ){
		node->left = insert_node(node->left, key, name, bal);
	}
	else if( key > node->key ){
		node->right = insert_node(node->right, key, name, bal);
	}
	else if( key == node->key ){
		printf("\n");
		printf("Another account with number [%.8d] was already registered.\n\n", key);
		printf("Press ENTER to continue...\n");
		getchar();
		return node;
	}
	
	node->height = calculate_height(node);	
	
	int balance = get_balance(node);	
	
	//LL
	if( balance > 1 && key < node->left->key ){
		return right_rotate(node);
	}
	
	//RR
	if( balance < -1 && key > node->right->key ){
		return left_rotate(node);
	}
	
	//LR
	if( balance > 1 && key > node->left->key ){
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	
	//RL
	if( balance < -1 && key < node->left->key ){
		node->right = right_rotate(node->right);
		return left_rotate(node->right);
	}

	return node;
}

Node* delete_node(Node *node, int key){
	if( !node ){
		printf("\n");
		printf("Account with number [%.8d] was not found.\n\n", key);
		printf("Press ENTER to continue...\n");
		getchar();
		return node;
	}
	
	if( key < node->key ){
		node->left = delete_node(node->left, key);
	}
	else if( key > node->key ){
		node->right = delete_node(node->right, key);
	}
	else{
		if( !node->left && !node->right ){
			printf("\n");
			printf("Account with number [%.8d (%s)] was removed successfully!\n\n", node->key, node->name);
			printf("Press ENTER to continue...\n");
			getchar();
			
			free(node);
			node = NULL;
		}
		else if( !node->left || !node->right ){
			Node *replacement = node->left ? node->left : node->right;
			printf("\n");
			printf("Account with number [%.8d (%s)] was removed successfully!\n\n", node->key, node->name);
			printf("Press ENTER to continue...\n");
			getchar();
			free(node);
			node = replacement;
		}
		else{
			Node *replacement = get_right_most_of_left_child(node);
			printf("\n");
			printf("Account with number [%.8d (%s)] was removed successfully!\n\n", node->key, node->name);
			printf("Press ENTER to continue...\n");
			getchar();
			node->key = replacement->key;
			node->bal = replacement->bal;
			strcpy(node->name, replacement->name);
			node->left = delete_node(node->left, replacement->key);
		}
	}
	
	if( !node ){
		return node;
	}
	
	node->height = calculate_height(node);
	int balance = get_balance(node);
	
	//LL
	if( balance > 1 && get_balance(node->left) >= 0 ){
		return right_rotate(node);
	}
	
	//LR
	else if( balance > 1 && get_balance(node->left) < 0 ){
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	
	//RR
	else if( balance < -1 && get_balance(node->right) <=0 ){
		return left_rotate(node);
	}
	
	else if( balance < -1 && get_balance(node->right) > 0 ){
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}
	
	return node;
}

Node* search_node(Node *node, int key, int updateBal){
	if( !node ){
		printf("\n");
		printf("Account with number [%.8d] was not found.\n\n", key);
		printf("Press ENTER to continue...\n");
		getchar();
		return node;
	}	
	
	if( key < node->key ){
		node->left = search_node(node->left, key, updateBal);
	}
	else if( key > node->key ){
		node->right = search_node(node->right, key, updateBal);
	}
	else{		
		if(key == node->key){
			printf("\n");
			printf("Account with number [%.8d (%s)] was found.\n", node->key, node->name);
			printf("Previous balance: %ld\n", node->bal);
			if(node->bal + updateBal < 0){
				printf("\n");
				printf("Fail to withdraw, not enough balance.\n\n");
				printf("Press ENTER to continue...\n");
				getchar();
			}else{
				node->bal = node->bal + updateBal;
				printf("New balance: %ld\n\n", node->bal);
				printf("Press ENTER to continue...\n");
				getchar();
			}
		}
		return node;
	}
}

void in_order(Node *node){
	if( node ){
		in_order(node->left);
		printf("\n");
		printf("Account Number: %.8d\n", node->key);
		printf("Customer Name : %s\n", node->name);
		printf("Balance       : %ld\n", node->bal);
		in_order(node->right);
	}
}

void pop_all(Node *node){
	if( node ){
		pop_all(node->left);
		pop_all(node->right);
		free(node);
		node = NULL;
	}
}

void show(){
	in_order(ROOT);
	printf("\n\n");
	printf("Press ENTER to Continue...\n");
	getchar();
}

void search(int key, int updateBal){
	
	ROOT = search_node(ROOT, key, updateBal);
	
	return;
}

void del(){
	int key;
	printf("Input account number [8 digits]        : ");
	scanf("%d", &key);
	getchar();
	
	ROOT = delete_node(ROOT, key);
	
	return;
}

void insert(){
	int key=0;
	char name[110]={};
	long int bal=0;
	
	do{
		printf("Input account number [8 digits]        : ");
		scanf("%d", &key);
		getchar();
	}while(key<1 || key>=100000000);
	
	do{
		printf("Input account name [1 - 100 characters]: ");
		scanf("%[^\n]", &name);
		getchar();
	}while(strlen(name) < 1 || strlen(name) > 100 );
	
	do{
		printf("Input account initial balance          : ");
		scanf("%ld", &bal);
		getchar();
	}while(bal<=0);
	
	ROOT = insert_node(ROOT, key, name, bal);
	
	return;
}

void addBal(){
	int key=0;
	long int bal=0;
	
	do{
		printf("Input account number [8 digits]        : ");
		scanf("%d", &key);
		getchar();
	}while(key<1 || key>=100000000);
	
	printf("Input nominal to deposit               : ");
	scanf("%ld", &bal);
	getchar();
	
	search(key, bal);
	
	return;
}

void delBal(){
	int key=0;
	long int bal=0;
	
	do{
		printf("Input account number [8 digits]        : ");
		scanf("%d", &key);
		getchar();
	}while(key<1 || key>=100000000);
	
	printf("Input nominal to withdraw              : ");
	scanf("%ld", &bal);
	getchar();
	
	search(key, bal*-1);
	
	return;
}

int main(){
	int i=0;
	while(i!=6){
		printf("HOVBank Database Prototype\n");
		printf("================================\n");
		printf("[1] Show All Account\n");
		printf("[2] Register a New Account\n");
		printf("[3] Remove an Existing Account\n");
		printf("[4] Deposit to an Account\n");
		printf("[5] Withdraw from an Account\n");
		printf("[6] Exit and Purge All Data\n");
		printf(">> ");
		scanf("%d", &i);
		getchar();
		switch(i){
			case(1): show(); break;
			case(2): insert(); break;
			case(3): del(); break;
			case(4): addBal(); break;
			case(5): delBal(); break;
		}
	}
	
	pop_all(ROOT);
	ROOT = NULL;
	printf("All data was removed succesfully.\n\n");
	printf("Press ENTER to Continue...\n");
	getchar();
	
	return 0;
}
