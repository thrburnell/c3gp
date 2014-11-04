#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/**
 * Input structure:
 *
 * First line, 2 space separated integers, n, m
 * n - the number of nodes
 * m - the number of known distances
 *
 * Starting node is indexed 0, all other nodes are contiguous integers greater
 * than 0.
 *
 * m lines follow having 3 integers per line x, y, c
 * x - start node
 * y - destination node
 * c - cost associated to travelling from x to y
 *
 * !! It cannot be assumed that if x->y has cost c than y->x also has cost c
 * The graph is directed.
 *
 */


/**
 * At the moment the algorithm is returning the identity permutation
 */

struct Edge {
	int cost;
	int node;
};

const int NMAX = 1000;
int n, m, x, y, c;
vector<unique_ptr<Edge>> distances[NMAX];

int main() {

	cin >> n >> m;

	for (int i = 0; i < n + 1; ++i) {
		cin >> x >> y >> c;
		unique_ptr<Edge> edge(new Edge);
		edge->cost = c;
		edge->node = y;
		distances[x].push_back(move(edge));
	}

	for (int i = 0; i <= n; ++i) {
		cout << i << " ";
	}

	cout << 0 << "\n";

	return 0;

}
