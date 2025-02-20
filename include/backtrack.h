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
#include <chrono>

class Backtrack {
public:
    Backtrack();
    ~Backtrack();

    void PrintAllMatches(const Graph &data, const Graph &query,
                         const CandidateSet &cs);
    void PrintMatch(const Graph& data, const Graph& query,
                    const CandidateSet& cs, const Vertex &qVertex);
    void PrintVector(const std::vector<Vertex>& xs);
    Vertex GetExtendableVertex(const Graph &query, const CandidateSet &cs);
    void FindRoot(const Graph &query, const CandidateSet &cs);
    void Initialize(const Graph &data, const Graph &query);
    bool CheckEmbedding(const Graph &data, const Graph &query,
                        const CandidateSet &cs, const std::vector<Vertex>& xs);

private:
    std::vector<bool> v;
    std::vector<Vertex> embedded;
    std::vector<Vertex> not_embedded;
    std::vector<Vertex> path;
    size_t count = 0;
    std::chrono::system_clock::time_point start;
    Vertex root = 0;

};

#endif  // BACKTRACK_H_
