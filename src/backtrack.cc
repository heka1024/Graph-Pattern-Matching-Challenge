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
  v.resize(data.GetNumVertices(), false);
  
  PrintMatch(data, query, cs, 0);

  // DFS(data, query, cs, 0);

  // BruteForce(data, query, cs);
}

void Backtrack::PrintMatch(const Graph& data, const Graph& query, 
                           const CandidateSet& cs, const size_t it) {
  if (it >= query.GetNumVertices()) {
    for(size_t i = 0; i < path.size() - 1; i++) { // 스택 값 출력 - 경로 출력 
      printf("%d ", path[i]);
    }
    printf("%d\n", path[it - 1]);      
    return;
  }
  for (size_t i = 0; i < cs.GetCandidateSize(it); i++) {
    const Vertex current_candidate = cs.GetCandidate(it, i);

    if (v[current_candidate]) {
      continue;
    }
    v[current_candidate] = true; path.push_back(current_candidate);
    bool gotoNext = true;

    for (size_t p = 0; p < it; p++) {
      if (query.IsNeighbor(p, it) && !data.IsNeighbor(path[p], current_candidate)) {
        gotoNext = false;
        break;
      }
    }

    if (gotoNext) {
      PrintMatch(data, query, cs, it + 1);      
    }
    v[current_candidate] = false; path.pop_back();
  }
}

void Backtrack::DFS(const Graph& data, const Graph& query, 
                           const CandidateSet& cs, const size_t it) {
  if (it >= query.GetNumVertices()) {
    for(size_t i = 0; i < path.size() - 1; i++) { // 스택 값 출력 - 경로 출력 
      printf("%d ", path[i]);
    }
    printf("%d\n", path[it - 1]);      
    return;
  }
  PrintVector(path);

  for (size_t i = 0; i < cs.GetCandidateSize(it); i++) {
    const Vertex current_candidate = cs.GetCandidate(it, i);
    printf("it %d cur %d\n", it, current_candidate);

    if (v[current_candidate]) {
      continue;
    }
    v[current_candidate] = true; path.push_back(current_candidate);
    DFS(data, query, cs, it + 1);      
    v[current_candidate] = false; path.pop_back();
  }

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

bool Backtrack::CheckEmbedding(const Graph &data, const Graph &query,
                               const CandidateSet &cs, const std::vector<Vertex>& xs) {
  const size_t len = xs.size();
  vector<bool> visited(len, false);

  for (size_t i = 0; i < len; i++) {
    const Vertex u = i, v = xs[i];
    // cout << "u " << u << " v " << v << "\n";

    if (visited[v]) {
      return false;
    } else {
      visited[v] = true;
    }

    if (data.GetLabel(v) != query.GetLabel(u)) {
      return false;
    }

    for (size_t j = query.GetNeighborStartOffset(u); j < query.GetNeighborEndOffset(u); j++) {
      const Vertex jj = query.GetNeighbor(j);
      const Vertex n = static_cast<Vertex>(xs[jj]);

      // cout << "j " << jj << " n " << n << "\n";
      if (!data.IsNeighbor(v, n)) {
        return false;
      }
    }
  }
  return true;
}

void Backtrack::BruteForce(const Graph& data, const Graph& query, 
                const CandidateSet& cs) {
  vector<Vertex> xs, ys;
  for (size_t i = 0; i < data.GetNumVertices(); i++) {
    xs.push_back(i);
    ys.push_back(0);
  }

  for (size_t i = 0; i < query.GetNumVertices(); i++) {
    ys[i] = 1;
  }

  do {
    vector<int> cur;
    for (size_t i = 0; i < xs.size(); i++) {
      if (ys[i] == 1) {
        // cout << xs[i] << " ";
        cur.push_back(xs[i]);
      }
    }
    
    if (CheckEmbedding(data, query, cs, cur)) {
      for (const auto& x : cur) {
        cout << x << " ";
      }
      cout << "\n";
    }

  } while (prev_permutation(ys.begin(), ys.end()));
}

void Backtrack::PrintVector(const vector<Vertex>& xs) {
  for (const auto& x : xs) {
    cout << x << " ";
  }
  cout << "\n";
}