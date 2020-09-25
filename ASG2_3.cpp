//
// Created by Hanry Ham on 2020-05-25.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct storage{
    int qty;
    char name[25];
    char category[20];
    struct storage *left;
    struct storage *right;
};

int flag=0;

struct storage *newNode(const char *name, const char *category){
    struct storage *curr = (struct storage *) malloc(sizeof(struct storage));
    curr->qty = 1;
    strcpy(curr->name, name);
    strcpy(curr->category, category);
    curr->left = NULL;
    curr->right = NULL;
    return curr;
}

struct storage *insert(struct storage *root, const char *name, const char *category){
    // [10%] (1) INSERT YOUR CODE HERE
    if(root == NULL){
    	root = newNode(name, category);
	}else if(strcmp(root->name, name)==0){
		root->qty+=1;
	}else if(strcmp(root->name, name)<0){
		root->right = insert(root->right, name, category);
	}else if(strcmp(root->name, name)>0){
		root->left = insert(root->left, name, category);
	}
	
    return root;
}

struct storage *predecessor(struct storage *root){
    // [5%] (2) INSERT YOUR CODE HERE
    root = root->left;
    while(root->right != NULL){
    	root = root->right;
	}
	
	return root;
}

struct storage *successor(struct storage *root){
    // [5%] (3) INSERT YOUR CODE HERE
    root = root->right;
    while(root->left != NULL){
    	root = root->left;
	}
	
	return root;
}

struct storage *deleteKey(struct storage *root, const char *name){
    // [15%] (4) INSERT YOUR CODE HERE
    if(strcmp(root->name, name)<0){
		root->right = deleteKey(root->right, name);
	}else if(strcmp(root->name, name)>0){
		root->left = deleteKey(root->left, name);
	}else if(strcmp(root->name, name)==0){
		if(root->qty > 1 && flag == 0){
			root->qty-=1;
			return root;
		}else if(root->left == NULL && root->right == NULL){
			root = NULL;
			free(root);
		}
		else if (root->left == NULL){
			struct storage *inherit = root->right;
			free(root);
			return inherit;
		}else if (root->right == NULL){
			struct storage *inherit = root->left;
			free(root);
			return inherit;
		}else{
			struct storage *inherit = root->left;
				
		    while(inherit->right != NULL){
		    	inherit = inherit->right;
			}if(inherit->qty > 1){
				flag=1;
			}
			root->qty = inherit->qty;
			strcpy(root->name, inherit->name);
			strcpy(root->category, inherit->category);
			root->left = deleteKey(root->left, inherit->name);
		}
	}
	flag=0;
    return root;
}

void inOrder(struct storage *root){
    if(root){
    // [5%] (5) INSERT YOUR CODE HERE
		inOrder(root->left);
		printf("%-10s (%-3d)\n", root->name, root->qty);
		inOrder(root->right);
    }
}

struct storage *freeAll(struct storage *root){
    if(root){
        freeAll(root->left);
        freeAll(root->right);
        free(root);
        root = NULL;
    }
    return root;
}

int main(){
    struct storage *root = NULL;

    root = insert(root, "Sate Ayam", "Daging");
    root = insert(root, "Gulai Kambing", "Daging");
    root = insert(root, "Kangkung", "Sayuran");
    root = insert(root, "Coca Cola", "Minuman");
    root = insert(root, "Sate Kambing", "Daging");
    root = insert(root, "Opor Ayam", "Daging");
    root = insert(root, "Sprite", "Minuman");
    root = insert(root, "Fanta", "Minuman");
    root = insert(root, "Ayam Kalasan", "Daging");
    root = insert(root, "Kangkung", "Sayuran");
    root = insert(root, "Fanta", "Minuman");
    root = insert(root, "Coca Cola", "Minuman");
    root = insert(root, "Opor Ayam", "Daging");

    printf("Predecessor : %s\n", predecessor(root)->name);
    printf("Successor : %s\n", successor(root)->name);

    printf("\nInorder : \n");
    inOrder(root);

    root = deleteKey(root, "Sate Ayam"); // 50
	root = deleteKey(root, "Gulai Kambing"); // 25
	root = deleteKey(root, "Coca Cola"); // 15
    root = deleteKey(root, "Opor Ayam"); // 40
    root = deleteKey(root, "Sate Kambing"); // 60
    root = deleteKey(root, "Ayam Kalasan"); // 10
    printf("\nAfter Del Inorder : \n");
    inOrder(root);
    
    freeAll(root);
    return 0;
}

