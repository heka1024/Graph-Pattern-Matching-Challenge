/**
 * @file backtrack.h
 *
 */

#ifndef BACKTRACK_H_
#define BACKTRACK_H_

#include "candidate_set.h"
#include "common.h"
#include "graph.h"
#include <stack>

class Backtrack {
 public:
  Backtrack();
  ~Backtrack();

  void PrintAllMatches(const Graph &data, const Graph &query,
                       const CandidateSet &cs);
  void PrintMatch(const Graph& data, const Graph& query, 
                  const CandidateSet& cs, const size_t it);
  void PrintCandidate(const Graph &data, const Graph &query,
                      const CandidateSet &cs);
  bool CheckEmbedding(const Graph &data, const Graph &query,
                      const CandidateSet &cs, const std::vector<Vertex>& xs);
 private:
  std::vector<bool> v;
  std::vector<Vertex> path;
  
};

#endif  // BACKTRACK_H_
