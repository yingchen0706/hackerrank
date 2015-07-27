//https://www.hackerrank.com/challenges/similarpair
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <stack>
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
        list<int> list;
        TreeNode* pCur = *root;
        TreeNode* pLastVisit = NULL;
        while (pCur) {
            s.push(pCur);
            list.push_back(pCur->data);
            pCur = pCur->pLeft;
        }
        while (!s.empty()) {
            pCur = s.top();
            s.pop();
            list.pop_back();
            
            if (!pCur->pRight || pCur->pRight == pLastVisit) {
                //insert
                if (pCur->data == parent) {
                    if (!pCur->pLeft) {
                        pCur->pLeft = pNode;
                    } else {
                        pCur->pRight = pNode;
                    }
                    for (auto it = list.begin(), end = list.end(); it != end; it++) {
                        if (abs((*it) - child) <= T) {
                            TOTAL++;
                        }
                    }
                    if (abs(parent-child) <=T) {
                        TOTAL++;
                    }
                    return;
                }
                
                pLastVisit = pCur;
                
            }
            else {
                s.push(pCur);
                list.push_back(pCur->data);
                pCur = pCur->pRight;
                while (pCur) {
                    s.push(pCur);
                    list.push_back(pCur->data);
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
