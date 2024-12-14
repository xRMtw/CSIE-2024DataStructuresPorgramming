#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#define MAX_ENTRIES 16  // maxinum number of data item each node can hold. Sample Output shows the result when MAX_ENTRIES is 2
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

// insert data
void insert(RTreeNode** root, DataItem item) {
    RTreeNode* node = *root;
    
    // 找到適合的葉節點
    while (!node->isLeaf) {
        double minExpansion = DBL_MAX;
        int bestIndex = -1;
        for (int i = 0; i < node->count; i++) {
            BoundingBox* mbr = &node->children[i]->mbr;
            double currentArea = (mbr->maxX - mbr->minX) * (mbr->maxY - mbr->minY);
            double newMinX = fmin(mbr->minX, item.longitude);
            double newMinY = fmin(mbr->minY, item.latitude);
            double newMaxX = fmax(mbr->maxX, item.longitude);
            double newMaxY = fmax(mbr->maxY, item.latitude);
            double newArea = (newMaxX - newMinX) * (newMaxY - newMinY);
            double expansion = newArea - currentArea;

            if (expansion < minExpansion) {
                minExpansion = expansion;
                bestIndex = i;
            }
        }
        node = node->children[bestIndex];
    }

    // 插入資料到葉節點
    if (node->count < MAX_ENTRIES) {
        node->data[node->count] = item;
        node->count++;
        // 更新 MBR
        node->mbr.minX = fmin(node->mbr.minX, item.longitude);
        node->mbr.minY = fmin(node->mbr.minY, item.latitude);
        node->mbr.maxX = fmax(node->mbr.maxX, item.longitude);
        node->mbr.maxY = fmax(node->mbr.maxY, item.latitude);
    } else {
        // 分裂節點邏輯
        printf("Node splitting is not implemented yet.\n");
    }
}


// search data
SearchResult* search(RTreeNode* root, double latitude, double longitude, int n) {
    if (!root) return NULL;

    SearchResult* results = malloc(n * sizeof(SearchResult));
    int resultCount = 0;

    if (root->isLeaf) {
        for (int i = 0; i < root->count; i++) {
            double distance = sqrt(pow(root->data[i].latitude - latitude, 2) +
                                   pow(root->data[i].longitude - longitude, 2));
            if (resultCount < n) {
                results[resultCount].item = root->data[i];
                results[resultCount].distance = distance;
                resultCount++;
            } else {
                // 排序並保持最近的 n 個
                for (int j = 0; j < n; j++) {
                    if (distance < results[j].distance) {
                        results[j].item = root->data[i];
                        results[j].distance = distance;
                        break;
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < root->count; i++) {
            BoundingBox* mbr = &root->children[i]->mbr;
            if (latitude >= mbr->minY && latitude <= mbr->maxY &&
                longitude >= mbr->minX && longitude <= mbr->maxX) {
                SearchResult* childResults = search(root->children[i], latitude, longitude, n);
                for (int j = 0; j < n && childResults[j].distance != DBL_MAX; j++) {
                    // 合併結果
                    if (resultCount < n) {
                        results[resultCount++] = childResults[j];
                    } else {
                        // 排序並保持最近的 n 個
                        for (int k = 0; k < n; k++) {
                            if (childResults[j].distance < results[k].distance) {
                                results[k] = childResults[j];
                                break;
                            }
                        }
                    }
                }
                free(childResults);
            }
        }
    }
    return results;
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

RTreeNode* createNode ( int leaf ) {

    RTreeNode *t = (RTreeNode*)malloc(sizeof(RTreeNode));

    if (!t) return NULL;
    
    t->isLeaf = leaf;
    t->count = 0;

    t->mbr.maxX = -DBL_MAX;
    t->mbr.maxY = -DBL_MAX;
    t->mbr.minX = DBL_MAX;
    t->mbr.minY = DBL_MAX;

    for( int i = 0 ; i < MAX_ENTRIES + 1 ; i++ ) {
        t->children[i] = NULL;
    }

    return t;

}

int main() {
    RTreeNode* root = createNode(1); //1 means it's a leaf node
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
