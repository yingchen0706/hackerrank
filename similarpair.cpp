#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <stack>
#include <set>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* pLeft;
    TreeNode* pRight;
};

int T = 0;
int TOTAL = 0;

void insertToTree(TreeNode** root, int parent, int child) {
    TreeNode* pNode = new TreeNode;
    *pNode = {child, NULL, NULL};
    if (*root == NULL) {
        *root = new TreeNode;
        **root = {parent, pNode, NULL};
        if (abs(parent-child) <= T) {
            TOTAL++;
        }
    } else {
        // post order traversal the tree
        stack<TreeNode*> s;
        set<int> set;
        TreeNode* pCur = *root;
        TreeNode* pLastVisit = NULL;
        while (pCur) {
            s.push(pCur);
            set.insert(pCur->data);
            pCur = pCur->pLeft;
        }
        while (!s.empty()) {
            pCur = s.top();
            s.pop();
            
            if (!pCur->pRight || pCur->pRight == pLastVisit) {
                //insert
                if (pCur->data == parent) {
                    if (!pCur->pLeft) {
                        pCur->pLeft = pNode;
                    } else {
                        pCur->pRight = pNode;
                    }
                    auto lower = set.lower_bound(child - T);
                    auto upper = set.upper_bound(child + T);
                    for (; lower != upper; lower++) {
                        TOTAL++;
                    }
                    /*if (abs(parent-child) <=T) {
                        TOTAL++;
                    }*/
                    return;
                }
                
                pLastVisit = pCur;
                set.erase(pCur->data);
            }
            else {
                s.push(pCur);
                pCur = pCur->pRight;
                while (pCur) {
                    s.push(pCur);
                    set.insert(pCur->data);
                    pCur = pCur->pLeft;                    
                }
            }
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int cnt = 0;
    cin >> cnt;
    cin >> T;
    int parent = 0;
    int child = 0;
    TreeNode* root = NULL;
    for (int i = 1; i < cnt; i++) {
        cin >> parent >> child;
        insertToTree(&root, parent, child);
    }
    cout << TOTAL;
    return 0;
}
