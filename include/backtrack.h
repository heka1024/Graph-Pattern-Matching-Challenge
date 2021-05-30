/**
 * @file backtrack.h
 *
 */

#ifndef BACKTRACK_H_
#define BACKTRACK_H_

#include "candidate_set.h"
#include "common.h"
#include "graph.h"

class Backtrack {
 public:
  Backtrack();
  ~Backtrack();

  void PrintAllMatches(const Graph &data, const Graph &query,
                       const CandidateSet &cs);
  void PrintMatch(const Graph& data, const Graph& query, 
                  const CandidateSet& cs, std::vector<bool>& v, 
                  const size_t it, std::vector<size_t> order);
  void PrintCandidate(const Graph &data, const Graph &query,
                      const CandidateSet &cs);
 private:
  
};

#endif  // BACKTRACK_H_
