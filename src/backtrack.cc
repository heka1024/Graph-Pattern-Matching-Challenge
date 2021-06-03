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

  // for (size_t j = 0; j < cs.GetCandidateSize(0); j++) {
  //   Vertex candidate = cs.GetCandidate(0, j);
  //   path.push_back(candidate);
  //   v[candidate] = true;
  //   PrintMatch(data, query, cs, 0);
  //   v[candidate] = false;
  // }; 
  
  PrintMatch(data, query, cs, 0);

  BruteForce(data, query, cs);
}

void Backtrack::PrintMatch(const Graph& data, const Graph& query, 
                           const CandidateSet& cs, const size_t it) {
  if (it >= query.GetNumVertices()) {
    for(size_t i = 0; i < path.size() - 1; i++) { // 스택 값 출력 - 경로 출력 
      cout << path[i] << " ";
    }      
    cout << path[it - 1] << "\n";
    return;
  }

  for (size_t i = 0; i < cs.GetCandidateSize(it); i++) {
    const Vertex current_candidate = cs.GetCandidate(it, i);
    if (v[current_candidate]) {
      return;
    }
    v[current_candidate] = true; path.push_back(current_candidate);
    bool gotoNext = false;

    for (size_t p = 0; p < it; p++) {
      if (!(query.IsNeighbor(p, current_candidate) && data.IsNeighbor(path[p], current_candidate))) {
        gotoNext = false;
      }
    }

    if (gotoNext) {
      PrintMatch(data, query, cs, it + 1);      
    }
    v[current_candidate] = false; path.pop_back();
  }

}
                             
//   if (it == query.GetNumVertices() - 1) {
//     for(size_t i = 0; i < path.size() - 1; i++) { // 스택 값 출력 - 경로 출력 
//       cout << path[i] << " ";
//     }      
//     cout << path[it - 1] << "\n";
//     path.pop_back();
//     return;
//   }

//   for (size_t j = 0; j < cs.GetCandidateSize(it + 1); j++) {
//     Vertex candidate = cs.GetCandidate(it + 1, j);
//     bool ok = true;
//     if (v[candidate]) {
//       break;
//     }
//     // check embedding
//     for (size_t i = query.GetNeighborStartOffset(it); i < query.GetNeighborEndOffset(it); i++) {
//       const Vertex n = query.GetNeighbor(i);
//       if (!data.IsNeighbor(candidate, n)) {
//         ok = false;
//         break;          
//       }
//     }

//     if (ok) {
//       path.push_back(candidate);
//       v[candidate] = true;
//       PrintMatch(data, query, cs, it + 1);
//       v[candidate] = false;
//     }      
//   }
//   // v[it] = false;
//   path.pop_back();
// }


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
  for (Vertex i = 0; i < data.GetNumVertices(); i++) {
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