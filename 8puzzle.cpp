/* 
Huy Dinh Tran 
ID: 862325308
Email: htran197@ucr.edu

CS205 AI Project 1
*/
#include <stdio.h> 
#include <iostream>
#include <algorithm>
#include <queue>
#include <list>
#include <string>
#include <cstdlib>
#include "8puzzle.h"
//Move blank is not working, queue doesn't have changing matrix
using namespace std;

struct Node {
    int matrix[3][3];
    Node* child1;
    Node* child2;
    Node* child3;
    Node* child4;
    Node* parent;
    int blankX, blankY;
    int heuristic;
    int moveCost;
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

void copyBoard(int (&target)[3][3], int (&matrix)[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            target[i][j] = matrix[i][j];
        }
    }
}

void assignChild1(Node* &curr, int (&matrix)[3][3], int blankX, int blankY) {
    Node* temp = new Node;
    temp->moveCost = curr->moveCost + 1;
    copyBoard(temp->matrix, matrix);
    temp->parent = curr;
    temp->blankX = blankX;
    temp->blankY = blankY;
    curr->child1 = temp;
}

void assignChild2(Node* &curr, int(&matrix)[3][3], int blankX, int blankY) {
    Node* temp = new Node;
    temp->moveCost = curr->moveCost + 1;
    copyBoard(temp->matrix, matrix);
    temp->parent = curr;
    temp->blankX = blankX;
    temp->blankY = blankY;
    curr->child2 = temp;
}

void assignChild3(Node* &curr, int(&matrix)[3][3], int blankX, int blankY) {
    Node* temp = new Node;
    temp->moveCost = curr->moveCost + 1;
    copyBoard(temp->matrix, matrix);
    temp->parent = curr;
    temp->blankX = blankX;
    temp->blankY = blankY;
    curr->child3 = temp;
}

void assignChild4(Node* &curr, int(&matrix)[3][3], int blankX, int blankY) {
    Node* temp = new Node;
    temp->moveCost = curr->moveCost + 1;
    copyBoard(temp->matrix, matrix);
    temp->parent = curr;
    temp->blankX = blankX;
    temp->blankY = blankY;
    curr->child4 = temp;
}

void moveBlank(Node* &node, queue <Node*> &q) {
    int temp[3][3];
    switch (node->blankX) {
    case 0:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[0][0], temp[0][1]);
            if (node->parent->matrix != node->matrix) {
                assignChild1(node, temp, 0, 1);
                //printBoard(temp);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][0], temp[1][0]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 1, 0);
                //printBoard(temp);
                q.push(node->child2);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[0][0]);
            if (node->parent->matrix != node->matrix) {
                assignChild1(node, temp, 0, 0);
                //printBoard(temp);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[0][2]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 0, 2);
                //printBoard(temp);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][1], temp[1][1]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 1, 1);
                //printBoard(temp);
                q.push(node->child3);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[0][2], temp[0][1]);
            if (node->parent->matrix != node->matrix) {
                assignChild1(node, temp, 0, 1);
                printBoard(temp);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[0][2], temp[1][2]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 1, 2);
                printBoard(temp);
                q.push(node->child2);
            }
            break;
        }
    case 1:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[0][0]);
            if (node->parent->matrix != node->matrix) {
                assignChild1(node, temp, 0, 0);
                //printBoard(temp);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[1][1]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 1, 1);
                //printBoard(temp);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][0], temp[2][0]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 2, 0);
                //printBoard(temp);
                q.push(node->child3);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[1][0]);
            if (node->parent->matrix != node->matrix) {
                assignChild1(node, temp, 1, 0);
                //printBoard(temp);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[0][1]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 0, 1);
                //printBoard(temp);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[1][2]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 1, 2);
                //printBoard(temp);
                q.push(node->child3);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][1], temp[2][1]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 2, 1);
                //printBoard(temp);
                q.push(node->child4);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[1][1]);
            if (node->parent->matrix != node->matrix) {
                assignChild1(node, temp, 1, 1);
                printBoard(temp);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[0][2]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 0, 2);
                printBoard(temp);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[1][2], temp[2][2]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 2, 2);
                printBoard(temp);
                q.push(node->child3);
            }
            break;
        }
    case 2:
        switch (node->blankY) {
        case 0:
            copyBoard(temp, node->matrix);
            swap(temp[2][0], temp[1][0]);
            if (node->parent->matrix != node->matrix) {
                assignChild1(node, temp, 1, 0);
                //printBoard(temp);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][0], temp[2][1]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 2, 1);
                //printBoard(temp);
                q.push(node->child2);
            }
            break;
        case 1:
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[2][0]);
            if (node->parent->matrix != node->matrix) {
                assignChild1(node, temp, 2, 0);
                //printBoard(temp);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[1][1]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 1, 1);
                //printBoard(temp);
                q.push(node->child2);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][1], temp[2][2]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 2, 2);
                //printBoard(temp);
                q.push(node->child3);
            }
            break;
        case 2:
            copyBoard(temp, node->matrix);
            swap(temp[2][2], temp[2][1]);
            if (node->parent->matrix != node->matrix) {
                assignChild1(node, temp, 2, 1);
                printBoard(temp);
                q.push(node->child1);
            }
            copyBoard(temp, node->matrix);
            swap(temp[2][2], temp[1][2]);
            if (node->parent->matrix != node->matrix) {
                assignChild2(node, temp, 1, 2);
                printBoard(temp);
                q.push(node->child2);
            }
            break;
        }
    }
}

void UniCostSearch(int input[3][3], int goal[3][3], Node* root, int &depth, int &nodeExpand, int &queueSize) { //search algorithm for Uniform Cost Search

}

void AMisTile(int input[3][3], int goal[3][3], Node* root, int &depth, int &nodeExpand, int &queueSize) { //search algorithm for A star Misplaced Tile Heuristic
    queue <Node*> q;
    int check[3][3];
    Node* temp = new Node;
    bool isSolved = false;

    q.push(root);
    while (isSolved == false) {
        if (q.empty() == true) {
            cout << "empty";
        }
        for (int i = 0; i < q.size(); i++) {
            temp = q.front();
            //printBoard(temp->matrix);
            q.pop();
            copyBoard(check, temp->matrix);
            //cout << q.size() << endl;
            if (checkGoal(check, goal) == true) {
                isSolved = true;
                cout << "success";
            }
        }
        moveBlank(root, q);
    }
}

void AManhattan(int input[3][3], int goal[3][3], Node* root, int depth, int nodeExpand, int queueSize) { //search algorithm for A star Manhattan Distance Heuristic

}

int main()
{
    int initChoose;
    int blankX=0, blankY=0;
    int depth, nodeExpand, queueSize;
    int matrix[3][3] = { {1,2,3}, {5,0,6}, {4,7,8} };
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
    node->child1 = NULL;
    node->child2 = NULL;
    node->child3 = NULL;
    node->child4 = NULL;
    node->parent = NULL;
    node->heuristic = 0;
    node->moveCost = 0;
    node->blankX = blankX;
    node->blankY = blankY;
    depth = 0;
    nodeExpand = 0;
    queueSize = 0;

    int algoChoose;
    cout << "Select algorithm: \n(1) for Uniform Cost Search \n(2) for the Misplaced Tile Heuristic \n(3) the Manhattan Distance Heuristic" << endl;
    cin >> algoChoose;

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

    return 0;
}