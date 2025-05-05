#include "maze_solver.h"
#include <stack>
using namespace std;

bool MazeSolver::dfs(Maze& maze, int r, int c, vector<vector<bool>>& visited) {
    // 1. Guard – out of bounds, wall, or already visited ➔ return false
    if ((!maze.inBounds(r, c)) || (maze.isWall(r, c)) || (visited[r][c] == true)) {
        return false;
    }

    // 2. Goal – if (r,c) == finish, return true
    if ((maze.finish.row == r) && (maze.finish.col == c)) {
        return true;
    }

    // 3. Mark – visited[r][c] = true
    visited[r][c] = true;

    // 4. Explore – recursively call dfs on N,E,S,W
    stack<Cell> toBeVisited;
    toBeVisited.push({r + 1, c});
    toBeVisited.push({r - 1, c});
    toBeVisited.push({r, c + 1});
    toBeVisited.push({r, c - 1});

    while (!toBeVisited.empty()) {
        Cell next = toBeVisited.top();
        toBeVisited.pop();

        if (dfs(maze, next.row, next.col, visited)) {
            maze.path.push_back(next);
            return true;
        }
    }

    // 6. Fail – otherwise return false
    return false;
}

bool MazeSolver::solveDFS(Maze& maze) {
    maze.path.clear();
    vector<vector<bool>> visited(maze.grid.size(),
                                 vector<bool>(maze.grid[0].size(), false));
    bool found = dfs(maze, maze.start.row, maze.start.col, visited);
    if (found) {
        maze.path.push_back(maze.start);
    }
    return found;
}
