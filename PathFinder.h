#pragma once
#include <vector>
#include <queue>
#include <unordered_set>
#include "Collider.h"
#include <cmath>
#include <iostream>
//#include <algorithm>
class PathFinder
{
public:
	PathFinder(std::vector<std::vector<int>> map, Collider* monster) : m_Map(map) {
		tile_size_row = monster->Get().h / 32;
		tile_size_col = monster->Get().w / 32;
		
		int rows = m_Map.size();
		int cols = m_Map[0].size();
		if (tile_size_row != 1 || tile_size_col != 1) {
			for (int i = 0; i < m_Map.size(); i++) {
				for (int j = 0; j < m_Map[0].size(); j++) {
					if (m_Map[i][j] != 10 && m_Map[i][j] != -1) {
						for (int dx = -(tile_size_row - 2 ); dx <= (tile_size_row - 1 ); dx++) {
							for (int dy = -(tile_size_col - 1 ); dy <= (tile_size_col - 1); dy++) {
								if (i + dx >= 0 && i + dx < rows && j + dy >= 0 && j + dy < cols && m_Map[i + dx][j + dy] == 10) {
									m_Map[i + dx][j + dy] = -1;
								}
							}
						}
					}
				}
			}
		}
		if (tile_size_row == 1 || tile_size_col == 1) {

			for (int i = 0; i < m_Map.size(); i++) {
				for (int j = 0; j < m_Map[0].size(); j++) {
					if (m_Map[i][j] != 10 && m_Map[i][j] != -1) {
						for (int dx = -(tile_size_row); dx <= (tile_size_row); dx++) {
							for (int dy = -(tile_size_col); dy <= (tile_size_col); dy++) {
								if (i + dx >= 0 && i + dx < rows && j + dy >= 0 && j + dy < cols && m_Map[i + dx][j + dy] == 10) {
									m_Map[i + dx][j + dy] = -1;
								}
							}
						}
					}
				}
			}
		}
		/*for (int i = 0; i < m_Map.size(); i++) {
			for (int j = 0; j < m_Map[0].size(); j++) {
				std::cout << m_Map[i][j] << " ";
			}
			std::cout << std::endl;
		}*/
	};
	struct Cell {
		int x, y;
		float distance;
		Cell() : x(0), y(0), distance(1e9){}
		Cell(int x,int y,int distance = 1e9) : x(x), y(y), distance(distance){}
		bool operator!=(const Cell& b) const {
			return x != b.x || y != b.y;
		}
		bool operator>(const Cell& other) const {
			return distance > other.distance;
		}
		friend std::ostream& operator<< (std::ostream& out, const Cell& c) {
			out << c.x << " " << c.y << "\n";
			return out;
		}
	};

	struct CompareDistance {
		bool operator()(Cell const& a, Cell const& b) {
			return a.distance > b.distance;
		}
	};

	bool isValid(int x, int y, int rows, int cols, Collider* collider, int dx, int dy) {
		if (x < 0 || x >= rows || y < 0 || y >= cols) {
			return false;
		}

		// Check if the cell is not a wall
		if (m_Map[x][y] != 10) {
			return false;
		}

		// Check if moving diagonally and one of the adjacent cells is a wall
		if (abs(dx) == 1 && abs(dy) == 1) {
			if (m_Map[x - dx][y] != 10 || m_Map[x][y - dy] != 10) {
				return false;
			}
		}
		//int left = collider->Get().x;
		//int right = collider->Get().x + collider->Get().w;
		//int top = collider->Get().y;
		//int bot = collider->Get().y + collider->Get().h;
		//int leftCell = left / 32;   // Assuming each cell is 32x32 pixels
		//int rightCell = right / 32; // Assuming each cell is 32x32 pixels
		//int topCell = top / 32;     // Assuming each cell is 32x32 pixels
		//int botCell = bot / 32;     // Assuming each cell is 32x32 pixels

		//// Check if the cells occupied by the collider are not walls
		//for (int i = topCell; i <= botCell; ++i) {
		//	for (int j = leftCell; j <= rightCell; ++j) {
		//		if (i < 0 || i >= rows || j < 0 || j >= cols) {
		//			return false;
		//		}
		//		if (m_Map[i][j] != 10) {
		//			return false;
		//		}
		//	}
		//}
		

		return true;

	}


	std::vector<Cell> Dijkstra(Collider* monster, Vector2D player_position)
	{
		int rows = m_Map.size();
		int cols = m_Map[0].size();
		Cell begin = { int(monster->GetPosition().Y / 32),(int)monster->GetPosition().X / 32 ,0 };
		Cell end = { (int)player_position.Y / 32,(int)player_position.X / 32 };
		std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
		std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> pq;
		std::vector<std::vector<float>> distances(rows, std::vector<float>(cols, 1e9));
		std::vector<std::vector<Cell>> parent(rows, std::vector<Cell>(cols));
		pq.push(begin);
		distances[begin.x][begin.y] = 0;

		//std::cout << "-------------------------------\n";
		//std::cout << "begin" << begin.x << " " << begin.y << "\n";
		//std::cout << "endl" << end.x << " " << end.y << "\n";
		//std::cout << monster->Get().w << " " << monster->Get().h << std::endl;


		std::vector<std::pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

		bool is_finded = false;
		//std::cout << end << "\n";
		while (!pq.empty()) {
			Cell current = pq.top();
			pq.pop();
			//std::cout << current.x << " " << current.y <<" "<<current.distance<<  std::endl;
			if (tile_size_col!=1 || tile_size_row!=1) {
				if (m_Map[end.x][end.y] != 10) {
					for (int dx = -(tile_size_row-1); dx <= (tile_size_row-1); dx++) {
						for (int dy = -(tile_size_col-1); dy <= (tile_size_col-1); dy++) {
							int newX = end.x + dx;
							int newY = end.y + dy;
							if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && current.x == newX && current.y == newY) {
								end.x = newX;
								end.y = newY;
								is_finded = true;
								break;
							}
						}
						if (is_finded) {
							//std::cout << end << "\n";
							break;
						}
					}
				}
				else {
					if (current.x == end.x && current.y == end.y) break;
				}
			}
			else if (tile_size_col == 1 || tile_size_row == 1) {
				if (m_Map[end.x][end.y] != 10) {
					for (int dx = -(tile_size_row); dx <= (tile_size_row); dx++) {
						for (int dy = -(tile_size_col); dy <= (tile_size_col); dy++) {
							int newX = end.x + dx;
							int newY = end.y + dy;
							if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && current.x == newX && current.y == newY) {
								end.x = newX;
								end.y = newY;
								is_finded = true;
								break;
							}
						}
						if (is_finded) {
							//std::cout << end << "\n";
							break;
						}
					}
				}
				else {
					if (current.x == end.x && current.y == end.y) break;
				}
			}
			//if (current.x == end.x && current.y == end.y) { break; }
			if (is_finded)
			{	
				//std::cout << "endl" << end.x << " " << end.y << "\n";
				break;
			}
			if (visited[current.x][current.y]) continue;
			visited[current.x][current.y] = true;
			for (std::pair<int, int>& dir : directions) {
				int newX = current.x + dir.first;
				int newY = current.y + dir.second;

				if (isValid(newX, newY, rows, cols,monster, dir.first, dir.second)) {
					float d_dis = 1;
					if (abs(dir.first) == 1 && abs(dir.second) == 1) {
						d_dis = sqrt(2);
					}
					if (distances[current.x][current.y] + d_dis < distances[newX][newY]) {
						distances[newX][newY] = distances[current.x][current.y] + d_dis;
						//std::cout << newX << " " << newY << " " << distances[newX][newY] << "\n";
						parent[newX][newY] = current;
						//std::cout << parent[newX][newY].x <<" " << parent[newX][newY].y << "\n";
						pq.push(Cell(newX, newY, distances[newX][newY]));
					}
				}
			}
		}


		std::vector<Cell> path;
		
		for (Cell curr = end; curr.x != begin.x || curr.y != begin.y; curr = parent[curr.x][curr.y]) {
			path.push_back(curr);
		}

		std::reverse(path.begin(), path.end());
		/*for (int i = 0; i < path.size(); i++) {
			std::cout << path[i];
		}*/
		
		return path;
	}

	Vector2D getDirection(Collider* monster, Vector2D player_position) {
		std::vector<Cell> path = Dijkstra(monster, player_position);
		if (path.empty()) {
			// No path found, return a zero vector
			return Vector2D(0, 0);
		}
		//std::cout << path[0].x << " " << path[0].y << "\n";
		
		Vector2D dest;
		if (path.size() != 0) {

			dest.X = path[0].y * 32 + 16;
			dest.Y = path[0].x * 32 + 16;
		}
		Cell begin = { int(monster->GetPosition().Y / 32) ,(int)monster->GetPosition().X / 32 ,0 };
		//std::cout << begin.y * 32 + 16 << " " << begin.x * 32 + 16 << "\n";
		//std::cout << path[0].y * 32 + 16 << " " << path[0].x * 32 + 16 << "\n";
		Vector2D dir;
		dir.X = path[0].y * 32 + 16 - (begin.y * 32 + 16);
		dir.Y = path[0].x * 32 + 16 - (begin.x * 32 + 16);
		//std::cout << dir.X << " " << dir.Y << std::endl;
		dir.Normalize();
		return dir;
	}



private:
	std::vector<std::vector<int>> m_Map;
	int tile_size_row;
	int tile_size_col;
	
};

