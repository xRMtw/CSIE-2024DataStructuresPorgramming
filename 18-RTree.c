#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#define MAX_ENTRIES 16 // maxinum number of data item each node can hold. Sample Output shows the result when MAX_ENTRIES is 2
#define MAX_NAME_LEN 50 // maxinum number of character for item name

typedef struct {
    double minX, minY;
    double maxX, maxY;
} BoundingBox;

typedef struct {
    double latitude, longitude;
    char name[MAX_NAME_LEN];
} DataItem;

typedef struct RTreeNode {
    int isLeaf;                     // 是否為葉節點is leaf or not
    int count;                      // number of node
    BoundingBox mbr;                // minimum bounding rectangle
    struct RTreeNode* children[MAX_ENTRIES + 1];
    DataItem data[MAX_ENTRIES];     //
} RTreeNode;

typedef struct {
    DataItem item;
    double distance;
} SearchResult;

RTreeNode* createNode ( int leaf ) {

    RTreeNode *t = (RTreeNode*)malloc(sizeof(RTreeNode));

    if (!t) return NULL;
    
    t->isLeaf = leaf;
    t->count = 0;
    t->data->latitude = 0;
    t->data->longitude = 0;
    memset(t->data->name,'\0', MAX_NAME_LEN);

    t->mbr.maxX = -DBL_MAX;
    t->mbr.maxY = -DBL_MAX;
    t->mbr.minX = DBL_MAX;
    t->mbr.minY = DBL_MAX;

    for( int i = 0 ; i < MAX_ENTRIES + 1 ; i++ ) {
        t->children[i] = NULL;
    }

    return t;

}

BoundingBox findMBR ( RTreeNode *node ) {

    BoundingBox temp;
    temp.maxX = -DBL_MAX;
    temp.maxY = -DBL_MAX;
    temp.minX = DBL_MAX;
    temp.minY = DBL_MAX;

    if( node->isLeaf ) {
        for ( int i = 0 ; i < node->count ; i++ ) {
            temp.maxX = ( temp.maxX > node->data[i].longitude )? temp.maxX : node->data[i].longitude; 
            temp.maxY = ( temp.maxY > node->data[i].latitude )? temp.maxY : node->data[i].latitude;
            temp.minX = ( temp.minX < node->data[i].longitude )? temp.minX : node->data[i].longitude;
            temp.minY = ( temp.minY < node->data[i].latitude )? temp.minY : node->data[i].latitude;
        }
    }
    else {

        for ( int i = 0 ; i < node->count ; i++ ) {
            BoundingBox ctemp = node->children[i]->mbr;
            temp.maxX = ( temp.maxX > ctemp.maxX )? temp.maxX : ctemp.maxX; 
            temp.maxY = ( temp.maxY > ctemp.maxY )? temp.maxY : ctemp.maxY;
            temp.minX = ( temp.minX < ctemp.minX )? temp.minX : ctemp.minX;
            temp.minY = ( temp.minY < ctemp.minY )? temp.minY : ctemp.minY;
        }

    }

    return temp;

}

void updateMBR ( RTreeNode *n ) {
    if ( !n ) return;
    n->mbr = findMBR(n);
}

double calculateExpansion(BoundingBox mbr, DataItem item) {
    // 計算插入資料後的 MBR
    double newMinX = ( item.longitude < mbr.minX )? item.longitude : mbr.minX;
    double newMinY = ( item.latitude < mbr.minY )? item.latitude : mbr.minY;
    double newMaxX = ( item.longitude > mbr.maxX )? item.longitude : mbr.maxX;
    double newMaxY = ( item.latitude > mbr.maxY )? item.longitude : mbr.maxY;

    // 計算原始 MBR 面積
    double originalArea = (mbr.maxX - mbr.minX) * (mbr.maxY - mbr.minY);

    // 計算擴展後 MBR 面積
    double newArea = (newMaxX - newMinX) * (newMaxY - newMinY);

    // 返回面積增加量
    return newArea - originalArea;
}

// insert data
void insert(RTreeNode** root, DataItem item) {

    if ( !root || !*root ) return;

    if ( (*root)->isLeaf ) {
        if ( (*root)->count < MAX_ENTRIES && (*root)->count >= 0 ) {
            (*root)->data[(*root)->count] = item;
            (*root)->count++;
            updateMBR( *root );
            
        }
        else {

            RTreeNode *newN = createNode(0);

            if (!newN) return;

            newN->children[0] = createNode(1);
            newN->children[1] = createNode(1);

            if ( !newN->children[0] || !newN->children[1] ) {
                if (newN->children[0]) free (newN->children[0]);
                if (newN->children[1]) free(newN->children[1]);
                free (newN);
                return;
            }

            newN->count = 2;
            int split = MAX_ENTRIES/2;
            for( int i = 0 ; i < MAX_ENTRIES ; i++ ) {
                if ( i >= MAX_ENTRIES/2 ) {
                    newN->children[1]->data[i-split] = (*root)->data[i];
                    newN->children[1]->count++;
                }
                else {
                    newN->children[0]->data[i] = (*root)->data[i];
                    newN->children[0]->count++;
                }
            }
            
            updateMBR(newN->children[0]);
            updateMBR(newN->children[1]);
            
            double expansion0 = calculateExpansion(newN->children[0]->mbr, item);
            double expansion1 = calculateExpansion(newN->children[1]->mbr, item);
            
            if (expansion0 <= expansion1) {
                newN->children[0]->data[newN->children[0]->count] = item;
                newN->children[0]->count++;
            } else {
                newN->children[1]->data[newN->children[1]->count] = item;
                newN->children[1]->count++;
            }
            
            updateMBR(newN->children[0]);
            updateMBR(newN->children[1]);
            updateMBR(newN);
          
            free(*root);
            *root = newN;  
            
        }
    }
    else {

        int bestChild = 0;
        double minExpansion = DBL_MAX;
        for (int i = 0; i < (*root)->count; i++) {
            double expansion = calculateExpansion((*root)->children[i]->mbr, item);
            if (expansion < minExpansion) {
                minExpansion = expansion;
                bestChild = i;
            }
        }
        // 插入到選定的子節點
        insert(&((*root)->children[bestChild]), item);

        // 更新當前節點的 MBR
        updateMBR(*root);

    }
}

double countDistance ( DataItem *r ,double latitude, double longitude ) {
    if (!r) return DBL_MAX; ///
    double dx, dy;
    dx = (r->longitude - longitude);
    dy = (r->latitude - latitude);

    return sqrt( (dx*dx) + (dy*dy) );
}

// search data
SearchResult* search(RTreeNode* root, double latitude, double longitude, int n) {

    if ( !root || n <= 0 ) return NULL;

    SearchResult* Save = (SearchResult*)malloc( n*sizeof(SearchResult));

    if (!Save) return NULL;

    for ( int t = 0 ; t < n ; t++ ) {
        Save[t].distance = DBL_MAX;
        Save[t].item.latitude = 0.0;
        Save[t].item.longitude = 0.0;
        memset(Save[t].item.name, '\0', MAX_NAME_LEN);///
    }

    if ( root->isLeaf ) {

        for ( int i = 0 ; i < root->count ; i++ ) {
    
            double distance = countDistance( &root->data[i], latitude, longitude );
            
            for ( int k = 0 ; k < n ; k++ ) {

                if ( distance < Save[k].distance ) {

                    for ( int m = n-1 ; m > k ; m-- ) {
                        Save[m] = Save[m-1];
                    }

                    Save[k].distance = distance;
                    Save[k].item = root->data[i];
                    break;
                }
            }
        }

    }
    else {
        
        for ( int i = 0 ; i < root->count ; i++ ) {
            SearchResult *temp = search( root->children[i], latitude , longitude, n );
            if (temp) {
                for ( int j = 0; j < n; j++ ) {
                    for ( int k = 0; k < n; k++ ) {
                        if ( temp[j].distance < Save[k].distance ) {
                            
                            for ( int m = n - 1; m > k; m-- ) {
                                Save[m] = Save[m - 1];
                            }
                            Save[k] = temp[j];
                            break;
                        }
                    }
                }
                free(temp);
            }
        
        }

    }

    return Save;
}

// print tree
void printTree(RTreeNode* root, int depth) {
    for (int i = 0; i < depth; i++) printf("  ");
    printf("Node (count=%d, isLeaf=%d):\n", root->count, root->isLeaf);
    for (int i = 0; i < root->count; i++) {
        if (root->isLeaf) {
            for (int j = 0; j < depth + 1; j++) printf("  ");
            printf("Data: %s (%.2f, %.2f)\n", root->data[i].name, root->data[i].latitude, root->data[i].longitude);
        } else {
            printTree(root->children[i], depth + 1);
        }
    }
}

int main() {
    RTreeNode* root = createNode(1);
    DataItem item;
    double latitude, longitude;
    SearchResult* results;
    
    char command[50];
    
    while(1) {
        scanf("%s", command);
        if(strcmp("insert", command) == 0) {
            scanf("%lf%lf%s", &item.latitude, &item.longitude, item.name);
            insert(&root, item);
        }
        else if(strcmp("print", command) == 0) {
            printTree(root, 0);
        }
        else if(strcmp("exit", command) == 0) {
            break;
        }
        else if(strcmp("search", command) == 0) {
            scanf("%lf%lf", &latitude, &longitude);
            results = search(root, latitude, longitude, 2);
            for (int i = 0; i < 2; i++) {
                printf("%s (%.2f, %.2f) - Distance: %.2f\n", results[i].item.name, results[i].item.latitude, results[i].item.longitude, results[i].distance);
            }
        }
        else {
            printf("Unknow command.\n");
        }
    }
    return 0;
}