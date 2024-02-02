#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------*/
// STRUCTURES USED IN THE PROGRAM
// Structure representing a step in a route
typedef struct Step {
    char town[50];
    int isDeparture;
} Step;

// Structure representing a route 
typedef struct Route {
    Step* step;
    int stepNumber;
} Route;

// Structure representing a town with the total of number route and departures
typedef struct Town {
    char name[50];
    int totalRoute;
    int departures;
} Town;

// Structure representing an AVL node
typedef struct Node {
    Town town;
    struct Node* left;
    struct Node* right;
    int height;
} Node;


/*-----------------------------------------------*/
// FUNCTIONS FOR THE PROGRAM
// Utility function to create a new AVL tree node
Node* newNode(char* name, int totalRoute, int departures){
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->town.name, name);

    node->town.totalRoute = totalRoute;
    node->town.departures = departures;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}


// Utility function to get the height of a node
int height(Node* node){
    if(node != NULL){
      return node->height;
    }
    else {
      return 0;
    }
}


// Utility function to get the maximum of two integers
int max(int a, int b){
   if(a > b){
     return a;
   }
   else {
     return b;
   } 
}


// Rotation functions to move nodes in the AVL :
// Utility function to do a simple left rotation
Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;

    // Do the rotations :
    x->left = y;
    y->right = T2;

    // Updating the heights : 
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}


// Utility function to do a simple right rotation
Node* rotateRight(Node* x) {
    Node* y = x->left;
    Node* T2 = y->right;

    // Do the rotation : 
    y->right = x;
    x->left = T2;

    // Updating the heights : 
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


// Utility function to get the balance of a node 
int getBalance(Node* node) {
    if(node != NULL){
      return height(node->left) - height(node->right);
    }
    else {
      return 0;
    }
}


// Function to insert a node in the AVL 
Node* insert(Node* root, char* name, int totalRoute, int departures){

    // Normal insertion for an ABR :
    if(root == NULL){
        return newNode(name, totalRoute, departures);
    }
    int compareResult = strcmp(name, root->town.name);

    if(compareResult < 0){
        root->left = insert(root->left, name, totalRoute, departures);
    }
    else if (compareResult > 0){
        root->right = insert(root->right, name, totalRoute, departures);
    }

    // Updating the node's heights :
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this node to check balance :
    int balance = getBalance(root);

    // Case of imbalance on the left :
    if(balance > 1){
        if(compareResult < 0){
            return rotateRight(root);
        }
        else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }


    // Case of imbalance on the right :
    if(balance < -1){
        if(compareResult > 0){
            return rotateLeft(root);
        }
        else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    // The AVL Tree is balanced
    return root;
}


// Utility function to free the AVL's memory 
void freeTree(Node* root) {
    if(root != NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void getTopCities(Node* root, Town topCities[], int* count) {
    if (root != NULL) {

        // Call recursively for left and right subtrees
        getTopCities(root->left, topCities, count);
        getTopCities(root->right, topCities, count);

        // Add the current city to the data if it has more trips than some of the current cities
        if (root->town.totalRoute > topCities[9].totalRoute) {
            // Add departure Town
            if (root->town.departures > 0) {
                for (int i = 0; i < 10; ++i) {
                    if (root->town.totalRoute > topCities[i].totalRoute) {
                        for (int j = 9; j > i; --j) {
                            topCities[j] = topCities[j - 1];
                        }
                        strcpy(topCities[i].name, root->town.name);
                        topCities[i].totalRoute = root->town.totalRoute;
                        topCities[i].departures = root->town.departures;
                        break;
                    }
                }
            }
        }
    }
}


// MAIN PROGRAM, EXECUTE THE SORT AND HOLD THE DATA
int main(){
    // initialisation of the AVL
    struct Node* root = NULL;

    // Opening CSV file
    FILE *csvFILE;
    csvFILE = fopen("data/data.csv", "r");
    if (csvFILE == NULL) {
        printf("Error opening file !");
        exit(1);
    }

    // Reading CSV file lines 
    char line[256];
    while (fgets(line, sizeof(line), csvFILE)) {
        char *token = strtok(line, ";");

        // Getting data
        char townA[50], townB[50];
        strcpy(townA, token);
        token = strtok(NULL, ";");
        strcpy(townB, token);

        // Processing datas for the towns
        root = insert(root, townA, 1, 0);
        root = insert(root, townB, 1, 1);
    }

    // Closing CSV file
    fclose(csvFILE);

    // Tab to hold the town informations
    struct Town topCities[10];
    int count = 0;

    // Getting 10 first cities
    getTopCities(root, topCities, &count);

    // Display top 10 cities
    printf("Les 10 premières villes avec le plus de trajets :\n");
    for (int i = 0; i < 10; i++) {
        printf("%s - Nombre total de trajets : %d, Départs de trajets : %d\n", topCities[i].name, topCities[i].totalRoute, topCities[i].departures);
    }

    // Free the memory
    freeTree(root);

    return 0;
  
}

// END OF THE MAIN FUNCTON
// END OF THE PROCESSING OF THE DATAS
