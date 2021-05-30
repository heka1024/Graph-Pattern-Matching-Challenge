/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"

using namespace std;

Backtrack::Backtrack() {}
Backtrack::~Backtrack() {}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
  PrintCandidate(data, query, cs);
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

void Backtrack::PrintMatch(const Graph& data, const Graph& query, 
                           const CandidateSet& cs, std::vector<bool>& v, 
                           const size_t it, vector<size_t> order) {
    if (it == query.GetNumVertices() - 1) {
      cout << "find!" << "\n";
      for (const auto& it : order) {
        cout << it << " ";
      }
      cout << "\n";

      return;
    }
    v[it] = true;
    for (size_t j = 0; j < cs.GetCandidateSize(it + 1); j++) {
      const Vertex next = cs.GetCandidate(it + 1, j);
      // cout << next << " ";
      order.push_back(next);
      if (!v[next]) {
        PrintMatch(data, query, cs, v, it + 1, order);
      }
    }
    v[it] = false;
  }
