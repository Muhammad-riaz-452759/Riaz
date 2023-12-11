#include <bits/stdc++.h>
using namespace std;

#define N 3

struct Node
{
    Node* parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};

int printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    return 0;
}

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;
    for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        node->mat[i][j] = mat[i][j];
    }
    }
//    memcpy(node->mat, mat, sizeof node->mat);
//    swap(node->mat[x][y], node->mat[newX][newY]);
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;
    return node;
}

int calculateManhattanDistance(int mat[N][N], int final[N][N]) {
    int distance = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int value = mat[i][j];

            // Find the position of the current value in the goal state
            for (int x = 0; x < 3; ++x) {
                for (int y = 0; y < 3; ++y) {
                    if (final[x][y] == value) {
                        // Calculate the Manhattan distance and add to the total
                        distance += std::abs(i - x) + std::abs(j - y);
                    }
                }
            }
        }
    }

    return distance;
}

int calculateCost(int current[N][N], int goal[N][N])
{
    int man = calculateManhattanDistance(current, goal);
    return man;
}

int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printPath(Node* root)
{
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);
    printf("\n");
}

struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return (lhs->cost ) > (rhs->cost );
    }
};

int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

void solve(int initial[N][N], int x, int y, int final[N][N])
{
    priority_queue<Node*, std::vector<Node*>, comp> pq;

    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);
    pq.push(root);

    while (!pq.empty())
    {
        Node* min = pq.top();
        pq.pop();

        if (min->cost == 0)
        {
            printPath(min);
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            if (isSafe(min->x + row[i], min->y + col[i]))
            {
                Node* child = newNode(min->mat, min->x, min->y, min->x + row[i], min->y + col[i], min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
                pq.push(child);
            }
        }
    }
}

int main()
{
    int initial[N][N] = {{1, 2, 3}, {5, 6, 0}, {7, 8, 4}};
    int final[N][N] = {{1, 2, 3}, {5, 8, 6}, {0, 7, 4}};

    int x = 1, y = 2;

    solve(initial, x, y, final);

    return 0;
}