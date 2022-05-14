/* 
Huy Dinh Tran 
ID: 862325308
Email: htran197@ucr.edu

CS205 AI Spring 2022
Project 1 
Dr. Eamonn Keogh
*/
#include <stdio.h> 
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <chrono>  

using namespace std;

struct Node { //struct of a Node which has pointers to childs and parent with attribute of heuristic, movement cost and location of the blank within matrix. 
    int matrix[3][3];
    Node* child1;
    Node* child2;
    Node* child3;
    Node* child4;
    Node* parent;
    int blankX, blankY;
    int hMan;
    int hTile;
    int moveCost;
};

struct compareHTile { //used for priority_queue, place lowest MisTile heuristic at the top
    bool operator()(Node* &a,  Node* &b) 
    {
        return a->hTile > b->hTile;
    }
};

struct compareUni { //used for priority_queue, place lowest movement cost at the top
    bool operator()(Node*& a, Node*& b)
    {
        return a->moveCost > b->moveCost;
    }
};

struct compareHMan { //used for priority_queue, place lowest Manhattan heuristic at the top
    bool operator()(const Node* a, const Node* b) const
    {
        return a->hMan > b->hMan;
    }
};

bool checkGoal(int input[3][3], int goal[3][3]) { //return true if input matrix the same as goal matrix, else, return false
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (input[i][j] != goal[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int hMisTile(int input[3][3], int goal[3][3]) { //return the heuristic value for misplace tiles 
    int h=0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (input[i][j] != goal[i][j] && goal[i][j] != 0)
                h++;
        }
    }
    return h;
}

int hManhattan(int input[3][3], int goal[3][3]) { //return the heuristic value for Manhattan
    int h = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (input[i][j] != goal[i][j]) {
                switch (input[i][j]) {
                    case 1:
                        h += abs(i - 0) + abs(j - 0);
                        break;
                    case 2:
                        h += abs(i - 0) + abs(j - 1);
                        break;
                    case 3:
                        h += abs(i - 0) + abs(j - 2);
                        break;
                    case 4:
                        h += abs(i - 1) + abs(j - 0);
                        break;
                    case 5:
                        h += abs(i - 1) + abs(j - 1);
                        break;
                    case 6:
                        h += abs(i - 1) + abs(j - 2);
                        break;
                    case 7:
                        h += abs(i - 2) + abs(j - 0);
                        break;
                    case 8:
                        h += abs(i - 2) + abs(j - 1);
                        break;
                }
            }
        }
    }
    return h;
}

void printBoard(int input[3][3]) { //print the current board 
    for (int i = 0; i < 3; i++) {
        cout << "[ ";
        for (int j = 0; j < 3; j++) {
            cout << input[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

void copyBoard(int (&target)[3][3], int (&matrix)[3][3]) { //copying matrix from input to target
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            target[i][j] = matrix[i][j];
        }
    }
}

bool isDup(vector<Node*>vec, Node* input) { //searching through vector to see if there is any duplication
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i]->matrix == input->matrix) {
            return true;
        }
    }
    return false;
}

void assignChild1(Node* &curr, int (&childMatrix)[3][3], int blankX, int blankY, int &nodeExpand) { //making child1
    Node* temp = new Node;
    int goal[3][3] = { {1,2,3},{4,5,6},{7,8,0} };
    temp->moveCost = curr->moveCost + 1;
    copyBoard(temp->matrix, childMatrix);
    temp->parent = curr;
    temp->blankX = blankX;
    temp->blankY = blankY;
    temp->hMan = hManhattan(childMatrix,goal) + temp->moveCost;
    temp->hTile = hMisTile(childMatrix, goal) + temp->moveCost;
    nodeExpand++;
    curr->child1 = temp;
}

void assignChild2(Node* &curr, int (&childMatrix)[3][3], int blankX, int blankY, int& nodeExpand) { //making child2
    Node* temp = new Node;
    int goal[3][3] = { {1,2,3},{4,5,6},{7,8,0} };
    temp->moveCost = curr->moveCost + 1;
    copyBoard(temp->matrix, childMatrix);
    temp->parent = curr;
    temp->blankX = blankX;
    temp->blankY = blankY;
    temp->hMan = hManhattan(childMatrix, goal) + temp->moveCost;
    temp->hTile = hMisTile(childMatrix, goal) + temp->moveCost;
    nodeExpand++;
    curr->child2 = temp;
}

void assignChild3(Node* &curr, int (&childMatrix)[3][3], int blankX, int blankY, int& nodeExpand) { //making child3
    Node* temp = new Node;
    int goal[3][3] = { {1,2,3},{4,5,6},{7,8,0} };
    temp->moveCost = curr->moveCost + 1;
    copyBoard(temp->matrix, childMatrix);
    temp->parent = curr;
    temp->blankX = blankX;
    temp->blankY = blankY;
    temp->hMan = hManhattan(childMatrix, goal) + temp->moveCost;
    temp->hTile = hMisTile(childMatrix, goal) + temp->moveCost;
    nodeExpand++;
    curr->child3 = temp;
}

void assignChild4(Node* &curr, int (&childMatrix)[3][3], int blankX, int blankY, int& nodeExpand) { //making child4
    Node* temp = new Node;
    int goal[3][3] = { {1,2,3},{4,5,6},{7,8,0} };
    temp->moveCost = curr->moveCost + 1;
    copyBoard(temp->matrix, childMatrix);
    temp->parent = curr;
    temp->blankX = blankX;
    temp->blankY = blankY;
    temp->hMan = hManhattan(childMatrix, goal) + temp->moveCost;
    temp->hTile = hMisTile(childMatrix, goal) + temp->moveCost;
    nodeExpand++;
    curr->child4 = temp;
}

void moveBlankHTile(Node* &node, priority_queue <Node*, vector<Node*>, compareHTile> &q, int &nodeExpand, int &queueSize)  {//moving empty tile, creating childs and also pushing into queue for A*MisTile
    int temp[3][3];
    switch (node->blankX) {
    case 0:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[0][0], temp[0][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][0], temp[1][0]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 0, nodeExpand);
                q.push(node->child2);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[0][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[0][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 0, 2, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 1, 1, nodeExpand);
                q.push(node->child3);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[0][2], temp[0][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][2], temp[1][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 2, nodeExpand);
                q.push(node->child2);
            }
            break;
        }
    case 1:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[0][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 1, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[2][0]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 2, 0, nodeExpand);
                q.push(node->child3);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[1][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 1, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[0][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 0, 1, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[1][2]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 1, 2, nodeExpand);
                q.push(node->child3);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[2][1]);
            if (node->parent->matrix != temp) {
                assignChild4(node, temp, 2, 1, nodeExpand);
                q.push(node->child4);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 1, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[0][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 0, 2, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[2][2]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 2, 2, nodeExpand);
                q.push(node->child3);
            }
            break;
        }
    case 2:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[2][0], temp[1][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 1, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][0], temp[2][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 2, 1, nodeExpand);
                q.push(node->child2);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[2][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 2, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 1, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[2][2]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 2, 2, nodeExpand);
                q.push(node->child3);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[2][2], temp[2][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 2, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][2], temp[1][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 2, nodeExpand);
                q.push(node->child2);
            }
            break;
        }
    }
}

void moveBlankHMan(Node*& node, priority_queue <Node*, vector<Node*>, compareHMan> &q, int& nodeExpand, int& queueSize) { //moving empty tile, creating childs and also pushing into queue for A*Manhattan
    int temp[3][3];
    switch (node->blankX) {
    case 0:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[0][0], temp[0][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][0], temp[1][0]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 0, nodeExpand);
                q.push(node->child2);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[0][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[0][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 0, 2, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 1, 1, nodeExpand);
                q.push(node->child3);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[0][2], temp[0][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][2], temp[1][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 2, nodeExpand);
                q.push(node->child2);
            }
            break;
        }
    case 1:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[0][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 1, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[2][0]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 2, 0, nodeExpand);
                q.push(node->child3);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[1][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 1, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[0][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 0, 1, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[1][2]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 1, 2, nodeExpand);
                q.push(node->child3);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[2][1]);
            if (node->parent->matrix != temp) {
                assignChild4(node, temp, 2, 1, nodeExpand);
                q.push(node->child4);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 1, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[0][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 0, 2, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[2][2]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 2, 2, nodeExpand);
                q.push(node->child3);
            }
            break;
        }
    case 2:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[2][0], temp[1][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 1, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][0], temp[2][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 2, 1, nodeExpand);
                q.push(node->child2);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[2][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 2, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 1, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[2][2]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 2, 2, nodeExpand);
                q.push(node->child3);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[2][2], temp[2][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 2, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][2], temp[1][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 2, nodeExpand);
                q.push(node->child2);
            }
            break;
        }
    }
}

void moveBlankUni(Node*& node, priority_queue <Node*, vector<Node*>, compareUni> &q, int& nodeExpand, int& queueSize) { //moving empty tile, creating childs and also pushing into queue for UniCostSearch
    int temp[3][3];
    switch (node->blankX) {
    case 0:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[0][0], temp[0][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][0], temp[1][0]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 0, nodeExpand);
                q.push(node->child2);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[0][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[0][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 0, 2, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 1, 1, nodeExpand);
                q.push(node->child3);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[0][2], temp[0][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][2], temp[1][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 2, nodeExpand);
                q.push(node->child2);
            }
            break;
        }
    case 1:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[0][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 0, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 1, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[2][0]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 2, 0, nodeExpand);
                q.push(node->child3);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[1][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 1, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[0][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 0, 1, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[1][2]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 1, 2, nodeExpand);
                q.push(node->child3);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[2][1]);
            if (node->parent->matrix != temp) {
                assignChild4(node, temp, 2, 1, nodeExpand);
                q.push(node->child4);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 1, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[0][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 0, 2, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[2][2]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 2, 2, nodeExpand);
                q.push(node->child3);
            }
            break;
        }
    case 2:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[2][0], temp[1][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 1, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][0], temp[2][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 2, 1, nodeExpand);
                q.push(node->child2);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[2][0]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 2, 0, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[1][1]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 1, nodeExpand);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[2][2]);
            if (node->parent->matrix != temp) {
                assignChild3(node, temp, 2, 2, nodeExpand);
                q.push(node->child3);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[2][2], temp[2][1]);
            if (node->parent->matrix != temp) {
                assignChild1(node, temp, 2, 1, nodeExpand);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][2], temp[1][2]);
            if (node->parent->matrix != temp) {
                assignChild2(node, temp, 1, 2, nodeExpand);
                q.push(node->child2);
            }
            break;
        }
    }
}

void UniCostSearch(int input[3][3], int goal[3][3], Node* root, int &depth, int &nodeExpand, int &queueSize) { //search algorithm for Uniform Cost Search
    priority_queue <Node*, vector<Node*>, compareUni> q;
    priority_queue <Node*, vector<Node*>, compareUni> q2;
    Node* temp = new Node;
    vector<Node*> duplicate;
    q.push(root);
    while (q.size() > 0) {
        if (q.empty() == true) {
            cout << "Failure";
            return;
        }
        q2 = q;
        while (q.size() > 0) {
            if (queueSize < q.size()) {
                queueSize = q.size();
            }
            temp = q.top();
            q.pop();

            cout << "g(n) = " << temp->moveCost << " and h(n) = 0" << endl;
            printBoard(temp->matrix);

            if (checkGoal(temp->matrix, goal) == true) {
                cout << "Solution found!" << endl;
                cout << "Solution depth: " << temp->moveCost << endl;
                cout << "Number of nodes expanded: " << nodeExpand << endl;
                cout << "Max queue size: " << queueSize << endl;
                return;
            }
        }
        while (q2.size() > 0) {
            temp = q2.top();
            q2.pop();
            if (isDup(duplicate, temp) == false) {
                moveBlankUni(temp, q, nodeExpand, queueSize);
                duplicate.insert(duplicate.begin(), temp);
            }
        }
    }
}

void AMisTile(int input[3][3], int goal[3][3], Node* root, int &depth, int &nodeExpand, int &queueSize) { //search algorithm for A star Misplaced Tile Heuristic
    priority_queue <Node*, vector<Node*>, compareHTile> q;
    Node* temp = new Node;
    vector<Node*> duplicate;
    q.push(root);
    while (q.size() > 0) {
        if (q.empty() == true) {
            cout << "Failure";
            return;
        }
        if (queueSize < q.size()) {
            queueSize = q.size();
        }

        temp = q.top();
        q.pop();

        cout << "g(n) = " << temp->moveCost << " and h(n) = " << temp->hTile - temp->moveCost << endl;
        printBoard(temp->matrix);

        if (checkGoal(temp->matrix, goal) == true) {
            cout << "Solution found!" << endl;
            cout << "Solution depth: " << temp->moveCost << endl;
            cout << "Number of nodes expanded: " << nodeExpand << endl;
            cout << "Max queue size: " << queueSize << endl;
            return;
        }
        else {
            moveBlankHTile(temp, q, nodeExpand, queueSize);
            duplicate.insert(duplicate.begin(), temp);
        }
    }
}

void AManhattan(int input[3][3], int goal[3][3], Node* root, int &depth, int &nodeExpand, int &queueSize) { //search algorithm for A star Manhattan Distance Heuristic
    priority_queue <Node*, vector<Node*>, compareHMan> q;
    Node* temp = new Node;
    vector<Node*> duplicate;
    q.push(root);
    while (q.size() > 0) {
        if (q.empty() == true) {
            cout << "Failure";
            return;
        }
        if (queueSize < q.size()) {
            queueSize = q.size();
        }
        temp = q.top();
        q.pop();

        cout << "g(n) = " << temp->moveCost << " and h(n) = " << temp->hMan - temp->moveCost << endl;
        printBoard(temp->matrix);

        if (checkGoal(temp->matrix, goal) == true) {
            cout << "Solution found!" << endl;
            cout << "Solution depth: " << temp->moveCost << endl;
            cout << "Number of nodes expanded: " << nodeExpand << endl;
            cout << "Max queue size: " << queueSize << endl;
            return;
        }
        else {
            moveBlankHMan(temp, q, nodeExpand, queueSize);
            duplicate.insert(duplicate.begin(), temp);
        }
    }
}

int main() //Choosing and user inputing current state into searching algorithm
{
    int initChoose;
    int blankX=1, blankY=1;
    int depth, nodeExpand, queueSize;
    int matrix[3][3] = { {1,2,3},{5,0,6},{4,7,8} };
    int goal[3][3] = { {1,2,3},{4,5,6},{7,8,0} };
    
    cout << "Welcome to Huy Dinh Tran (862325308, htran197) 8-Puzzle Solver.\nType '1' to to use a default puzzle, or '2' to create your own.\n";
    cout << "Default puzzle: [ 1 2 3 ]" << endl;
    cout << "                [ 5 0 6 ]\n";
    cout << "                [ 4 7 8 ]\n";
    cin >> initChoose;

    if (initChoose == 2) {
        cout << "Enter your puzzle, using a zero to represent the blank. Please only enter valid 8-puzzles. \nEnter the puzzle demilimiting the numbers with a space. Press ENTER only when finished.\n";
        cout << "Enter the first row: ";
        for (int i = 0; i < 3; i++) {
            cin >> matrix[0][i];
            if (matrix[0][i] == 0) {
                blankX = 0;
                blankY = i;
            }
        }
        cout << "Enter the second row: ";
        for (int i = 0; i < 3; i++) {
            cin >> matrix[1][i];
            if (matrix[1][i] == 0) {
                blankX = 1;
                blankY = i;
            }
        }
        cout << "Enter the third row: ";
        for (int i = 0; i < 3; i++) {
            cin >> matrix[2][i];
            if (matrix[2][i] == 0) {
                blankX = 2;
                blankY = i;
            }
        }
    }

    Node* node = new Node;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++) {
            node->matrix[i][j]=matrix[i][j];
        }
    }

    //initializing root node
    node->parent = NULL;
    node->hMan = 0;
    node->hTile = 0;
    node->moveCost = 0;
    node->blankX = blankX;
    node->blankY = blankY;
    depth = 0;
    nodeExpand = 0;
    queueSize = 0;

    int algoChoose;
    cout << "Select algorithm: \n(1) for Uniform Cost Search \n(2) for the Misplaced Tile Heuristic \n(3) the Manhattan Distance Heuristic" << endl;
    cin >> algoChoose;

    auto start = chrono::steady_clock::now();
    
    switch (algoChoose) {
    case 1:
        UniCostSearch(matrix, goal, node, depth, nodeExpand, queueSize);
        break;
    case 2:
        AMisTile(matrix, goal, node, depth, nodeExpand, queueSize);
        break;
    case 3:
        AManhattan(matrix, goal, node, depth, nodeExpand, queueSize);
        break;
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Execution time (seconds): " << chrono::duration <double, milli>(diff).count() << " ms" << endl;

    return 0;
}