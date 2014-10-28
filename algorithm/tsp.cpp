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


int main() {
	g << "Hello World" << e;
}