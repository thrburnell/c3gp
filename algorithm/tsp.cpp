#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cmath>
#include <bitset>
#include <list>

using namespace std;

#define e '\n'
#define INF 1023456789
#define ll long long

//#define FILE "data"

#ifdef FILE
ifstream f(string (string(FILE) + ".in").c_str());
ofstream g(string (string(FILE) + ".out").c_str());
#endif
#ifndef FILE
#define f cin
#define g cout
#endif

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
 * At the moment the algorithm is returning
 */

struct Edge {
	int cost;
	int node;
};

const int NMAX = 1000;
int n, m, x, y, c;
vector<Edge> distances[NMAX];

int main() {

	f >> n >> m;

	for (int i = 0; i <= n; ++i) {
		f >> x >> y >> c;
		Edge * edge = new Edge();
		edge -> cost = c;
		edge -> node = y;
		distances[x].push_back(*edge);
	}

	for (int i = 0; i <= n; ++i) {
		g << i << " ";
	}

	g << 0 << e;

}
