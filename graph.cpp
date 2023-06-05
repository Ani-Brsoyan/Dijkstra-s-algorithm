#include <iostream>
#include <vector>
#include <limits.h>
//complexity O(v_count^2)

int select_vertex(int*& dist, bool*& visited, int v_count);
void dijkstra(const std::vector<std::vector<std::pair<char, int>>>&, int);
void print(int*& dist, int len, int start);

int main()
{
	int n;
	std::cout << "How many vertices does your graph have?\n";
	do{
		std::cin >> n;
	}while(n <= 0);
	std::cout << "Your vertices are ";
	for(int i = 0; i < n; i++){
		std::cout << static_cast<char>(i + 'A') << " ";
	}
	std::vector<std::vector<std::pair<char, int>>> mat(n);
	for(int i = 0; i < n; i++){
		char ver = 'A';
		std::cout << "\n*****\nEnter the adjecents of vertex " << static_cast<char>(ver + i) << std::endl;
		std::cout << "press 0 for the end\n";
		int count = n - 1;
		while(count){
			std::pair<char, int> tmp;
			std::cout << "\nVertice name " << std::endl;
			std::cin >> tmp.first;
			if(tmp.first == '0'){
				break;
			}
			else if(tmp.first < 'A' || tmp.first >= (n + 'A') || tmp.first == static_cast<char>(i + 'A')){
				std::cout << "!!Invalid name\n";
			}else{

				std::cout << "Enter the distance(positive) between " << static_cast<char>(ver + i) << " and " << tmp.first << " ";
				do{
					std::cin >> tmp.second;
				}while(tmp.second <= 0);
				mat[i].push_back(tmp);
				count--;
			}

		}
	}
	dijkstra(mat, 0);
	return 0;
}

void dijkstra(const std::vector<std::vector<std::pair<char, int>>>& my_graph, int start)
{
	int v_count = my_graph.size();
	bool* visited = new bool[v_count]{};
	int* dist = new int[v_count];
	for(int i = 0; i < v_count; i++){
		dist[i] = INT_MAX;
	}
	dist[start] = 0;

	for(int i = 0; i < v_count - 1; i++){
		int tmp_index = select_vertex(dist, visited, v_count);
		visited[tmp_index] = true;
		int len = my_graph[tmp_index].size();
		for(int j = 0; j < len; j++){
			int cur_dist = static_cast<int>(my_graph[tmp_index][j].first - 'A');
			if(visited[cur_dist] == false && dist[tmp_index] != INT_MAX 
			   && dist[tmp_index] + my_graph[tmp_index][j].second < dist[cur_dist]){
				dist[cur_dist] = dist[tmp_index] + my_graph[tmp_index][j].second; 
			}
		}	
	}
	print(dist, v_count, start);
	delete[] visited;
	delete[] dist;
}

int select_vertex(int*& dist, bool*& visited, int v_count)
{
	int min = INT_MAX;
	int index = 0;
	for(int i= 0; i < v_count; i++){
		if(visited[i] == false && dist[i] < min){
			min = dist[i];
			index = i;
		}
	}
	return index;
}

void print(int*& dist,int len, int start)
{
	std::cout << "\n\nHere are the shortest distances from " << static_cast<char>(start + 'A') << std::endl;
	for(int i = 0; i < len; i++){
		if(i != start){
			std::cout << static_cast<char>(i + 'A') << "  ->  " << dist[i];
			std::cout << std::endl;
		}
	}

}
