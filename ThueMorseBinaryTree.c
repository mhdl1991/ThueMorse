#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node {
	int data;
	struct node *left;
	struct node *right;
};
struct node* create(int value) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->data = value;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}
// Insert on the left of the node.
struct node* insertLeft(struct node* root, int value) {
  root->left = create(value);
  return root->left;
}
// Insert on the right of the node.
struct node* insertRight(struct node* root, int value) {
  root->right = create(value);
  return root->right;
}

int getLevelCount(struct node* n) {
	if (n == NULL) {
		return 0;
	}
	int leftMaxLevel = 1 + getLevelCount(n->left);
	int rightMaxLevel = 1 + getLevelCount(n->right);
	
	if (leftMaxLevel > rightMaxLevel) { 
		return leftMaxLevel; 
	}
    return rightMaxLevel;
}

void printLevel(struct node* n, int level) {
    if (n != NULL && level == 0)
    {
        printf("%d", n->data);
    }   
    else if (n != NULL )
    {
        printLevel(n->left, level - 1);
        printLevel(n->right, level - 1);
    }
}

void printElements(struct node* n) {
    int i;
    int levelCount = getLevelCount(n);
    for (i = 0; i < levelCount; i++)
    {
        printLevel(n, i);
		printf("\n");
    }
	printf("\n");
}

void generateThueMorseTree(struct node* n, int generation) {
	struct node* n_left = NULL;
	struct node* n_right = NULL;
	
	if (generation <= 0) {return;}
	
	if (n == NULL) {return;}
	// if the current node is 0, the left branch is 0 and the right branch is 1
	// if the current node is 1, the left branch is 1 and the right branch is 0
	int L = n->data;
	int R = (L==0)?1:0;
	
	
	if (n->left == NULL) {
		n_left = insertLeft(n, L);
	} else {
		n_left = n->left;
		n_left->data = L;
	}
	
	if (n->right == NULL) {
		n_right = insertRight(n, R);
	} else {
		n_right = n->right;
		n_right->data = R;
	}

	generateThueMorseTree(n_left, generation - 1);
	generateThueMorseTree(n_right, generation - 1);
}

int freeTree(struct node* n) {
	if (n == NULL) {
		return 0;
	}
	if (n->left != NULL) {
		freeTree(n->left);
	}
	if (n->right != NULL){
		freeTree(n->right);
	}
	free(n);
	return 0;
}

int main(int argc, char** argv) {
	struct node* root = create(0);
	int generation = atoi(argv[1]);
	generateThueMorseTree(root, generation);
	printElements(root);
	//printLevel(root, generation);
	freeTree(root);
	
	return 0;
}
