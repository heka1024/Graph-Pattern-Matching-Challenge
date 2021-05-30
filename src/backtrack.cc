/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"
#include <stack>

using namespace std;

Backtrack::Backtrack() {}
Backtrack::~Backtrack() {}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
  vector<Vertex> candidates;
  v.resize(data.GetNumVertices(), false);

  for (size_t j = 0; j < cs.GetCandidateSize(0); j++) {
    Vertex candidate = cs.GetCandidate(0, j);
    path.push_back(candidate);
    v[candidate] = true;
    PrintMatch(data, query, cs, 0);
    v[candidate] = false;
  }
}


void Backtrack::PrintMatch(const Graph& data, const Graph& query, 
                           const CandidateSet& cs, const size_t it) {
    if (it == query.GetNumVertices() - 1) {
      for(size_t i = 0; i < path.size(); i++) { // 스택 값 출력 - 경로 출력 
			  cout << path[i] << " ";
		  }
      cout << "\n";
      path.pop_back();
      return;
    }

    for (size_t j = 0; j < cs.GetCandidateSize(it + 1); j++) {
      Vertex candidate = cs.GetCandidate(it + 1, j);
      if (!v[candidate]) {
        path.push_back(candidate);
        v[candidate] = true;
        PrintMatch(data, query, cs, it + 1);
        v[candidate] = false;
      }
    }
    // v[it] = false;
    path.pop_back();
  }


void Backtrack::PrintCandidate(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
  std::cout << "t " << query.GetNumVertices() << "\n";

  std::cout << "g " << data.GetNumVertices() << "\n";

  for (size_t i = 0; i < query.GetNumVertices(); i++) {
    cout << "v " << i << " [";
    for (size_t j = 0; j < cs.GetCandidateSize(i); j++) {
      cout << cs.GetCandidate(i, j) << " ";
    }
    cout << "]\n";
  }
}