#ifndef PRELUDE_H
#define PRELUDE_H

#define M_PI 3.14159265358979323846
#define EPS 1e-9

#include <algorithm>
#include <cmath>
#include <numeric>

#include <vector>
#include <set>
#include <map>
#include <queue>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

typedef std::pair<int, int> ii;
typedef std::pair<ll, ll> llll;
typedef std::pair<int, ll> ill;
typedef std::pair<double, double> dd;

typedef std::vector<int> vi;
typedef std::vector<ii> vii;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
typedef std::vector<vii> vvii;
typedef std::vector<ill> vill;
typedef std::vector<vill> vvill;

typedef std::vector<bool> vb;

typedef std::vector<char> vc;
typedef std::vector<std::vector<char>> vvc;

typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;
typedef std::vector<llll> vllll;
typedef std::vector<double> vd;
typedef std::vector<dd> vdd;

typedef std::string ss;
typedef std::vector<ss> vss;
typedef std::vector<vss> vvss;

typedef std::set<int> si;
typedef std::set<ii> sii;
typedef std::set<ll> sll;

typedef std::map<int, int> mii;
typedef std::map<char, int> mci;

typedef std::queue<int> qi;

typedef std::vector<std::pair<int, ii>> EdgeList;

#define REP(i,n) for(int i=0;i<n;++i)
#define DEBUG(a) #a << ": " << (a) << " " <<
#define ENDL "\n"
#define REPLL(l,n) for(ll l=0;l<n;++l)
#define FOR(i,s,n) for(int i=s;i<=n;++i)
#define FOREACH(it,a) for(auto it=a.begin(); it != a.end(); ++it)

#endif //PRELUDE_H
