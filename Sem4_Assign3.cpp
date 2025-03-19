#include <iostream>
#define MAX 10
using namespace std;

struct Point {
    int x, y;
};

int ROW[] = {-1, 1, 0, 0};
int COL[] = {0, 0, -1, 1};
bool visited[MAX][MAX];
Point parent[MAX][MAX];

bool isValid(int x, int y, int rows, int cols, int maze[MAX][MAX]) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0 && !visited[x][y]);
}

bool dfs(int maze[MAX][MAX], int x, int y, int goalX, int goalY, Point path[MAX * MAX], int &pathIndex, int rows, int cols) {
    if (x == goalX && y == goalY) {
        path[pathIndex++] = {x, y};
        return true;
    }
    visited[x][y] = true;
    path[pathIndex++] = {x, y};
    
    for (int i = 0; i < 4; i++) {
        int newX = x + ROW[i], newY = y + COL[i];
        if (isValid(newX, newY, rows, cols, maze)) {
            if (dfs(maze, newX, newY, goalX, goalY, path, pathIndex, rows, cols))
                return true;
        }
    }
    
    pathIndex--;
    return false;
}

void bfs(int maze[MAX][MAX], int startX, int startY, int goalX, int goalY, Point path[MAX * MAX], int &pathIndex, int rows, int cols) {
    int queueX[MAX * MAX], queueY[MAX * MAX];
    int front = 0, rear = 0;
    
    queueX[rear] = startX;
    queueY[rear++] = startY;
    visited[startX][startY] = true;
    parent[startX][startY] = {-1, -1};
    
    while (front < rear) {
        int x = queueX[front], y = queueY[front++];
        
        if (x == goalX && y == goalY) {
            pathIndex = 0;
            while (x != -1 && y != -1) {
                path[pathIndex++] = {x, y};
                Point temp = parent[x][y];
                x = temp.x;
                y = temp.y;
            }
            return;
        }
        
        for (int i = 0; i < 4; i++) {
            int newX = x + ROW[i], newY = y + COL[i];
            if (isValid(newX, newY, rows, cols, maze)) {
                visited[newX][newY] = true;
                parent[newX][newY] = {x, y};
                queueX[rear] = newX;
                queueY[rear++] = newY;
            }
        }
    }
}

void printPath(Point path[MAX * MAX], int pathIndex) {
    if (pathIndex == 0) {
        cout << "No path found." << endl;
        return;
    }
    for (int i = pathIndex - 1; i >= 0; i--) {
        cout << "(" << path[i].x << ", " << path[i].y << ") -> ";
    }
    cout << "Goal\n";
}

int main() {
    int maze[MAX][MAX] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    
    int startX = 0, startY = 0, goalX = 4, goalY = 4;
    Point path[MAX * MAX];
    int pathIndex = 0;
    
    cout << "DFS Path: " << endl;
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            visited[i][j] = false;
    
    if (dfs(maze, startX, startY, goalX, goalY, path, pathIndex, 5, 5)) {
        printPath(path, pathIndex);
    } else {
        cout << "No path found." << endl;
    }
    
    cout << "\nBFS Path: " << endl;
    pathIndex = 0;
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            visited[i][j] = false;
    
    bfs(maze, startX, startY, goalX, goalY, path, pathIndex, 5, 5);
    printPath(path, pathIndex);
    
    return 0;
}
