# 15-Puzzle
Comparison of BFS, DFID, A* and IDA* algorithms on the 15-Puzzle Problem.

## 1. Puzzle Statement
The 15 puzzle is a sliding puzzle having 15 square tiles numbered 1–15 in a 4x4 frame, leaving one unoccupied tile. <br>
Tiles in the same row or column of the open position can be moved by sliding them horizontally or vertically. <br>
Given state of the puzzle is known as the **initial state**. And the ordering of tiles required to achieve is called the **final state/goal state**.

**Example:** <br>
![image](https://user-images.githubusercontent.com/58243776/170693786-20416c17-1d13-4c6a-9685-528eeb893809.png)

## 2. Algorithms
### 2.1 Breadth First Search (BFS):
BFS is a method used for traversing a graph. It starts at any item we want to use as a starting position in a graph, and explores all of the neighbour items at the present depth before moving on to the items at the next depth level.
### Pseudocode: 
Let G be a graph with starting node S and Final node F. Let Q be a queue.<br><br>
![image](https://user-images.githubusercontent.com/58243776/170695255-11d716e9-9a73-4df7-b1c6-508973b89021.png)
### 2.2 Defth First Iterative Deepening (DFID):
DFID is a state space or graph search strategy in which a depth-limited version of Depth First Search (DFS) is run repeatedly with increasing depth limits until the goal is found.
### Pseudocode:
Let G be a graph with starting node S and Final node F. Let Q be a priority queue of nodes. Let depth allowed be D. <br><br>
![image](https://user-images.githubusercontent.com/58243776/170696402-0812e262-5c66-4234-9634-6535d7c3a060.png)
### 2.3 A*:
A* is a graph traversal and path search algorithm. Peter Hart, Nils Nilsson and Bertram Raphael of Stanford Research Institute (now SRI International) first published the algorithm in 1968. It can be seen as an extension of Dijkstra's algorithm. A* achieves better performance by using heuristics to guide its search.
### Pseudocode:
Let G be a graph with starting node S and Final node F. Let Q be a priority queue of nodes. Let h(S) be the heuristic value (f(n) = g(n) + h(n)) of S, g(S) = 0.<br><br>
![image](https://user-images.githubusercontent.com/58243776/170696783-a1565717-4615-4edb-81e0-721a25e09040.png)
### 2.4 Iterative Deepening A* (IDA*):
IDA* is a graph traversal and path search algorithm that can find the shortest path between a designated start node and any member of a set of goal nodes in a weighted graph. It is a variant of DFID search that borrows the idea to use a heuristic function to evaluate the remaining cost to get to the goal from the A* search algorithm
### Pseudocode:
Let G be a graph with starting node S and Final node F. Let Q be a priority queue of nodes. Let h(S) be the heuristic value (f(n) = g(n) + h(n)) of S, g(S) = 0. Suppose B be the initial bound on heuristic. <br><br>
![image](https://user-images.githubusercontent.com/58243776/170696979-ec5613e6-b7f1-49aa-9f46-b7cf6e43b3a4.png)

## 3. Properties of Algorithms
Let G be a graph having starting node S and goal node G. Let the average branching factor be ‘b’ and the depth of G from S be ‘d’.
### 3.1 Breadth First Search (BFS):
_Time Complexity, T(n) = O(b<sup>d</sup>) <br>
Space Complexity, S(n) = O(b<sup>d</sup>) <br>
Completeness : Yes <br>
Optimality : Yes <br>_
### 3.2 Defth First Iterative Deepening (DFID):
_Time Complexity, T(n) = O(b<sup>d</sup>) <br>
Space Complexity, S(n) = O(bd) <br>
Completeness : Yes <br>
Optimality : Yes <br>_
### 3.3 A*:
_Time Complexity, T(n) = O(b<sup>d</sup>) <br>
Space Complexity, S(n) = O(b<sup>d</sup>) <br>
Completeness : Yes <br>
Optimality : Yes <br>_
### 3.4 Iterative Deepening A* (IDA*):
_Time Complexity, T(n) = O(b<sup>d</sup>) <br>
Space Complexity, S(n) = O(bd) <br>
Completeness : Yes <br>
Optimality : Yes <br>_
