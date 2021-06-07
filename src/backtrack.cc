/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"
#include <stack>
#include <map>
#define null -1

using namespace std;

Backtrack::Backtrack() {}
Backtrack::~Backtrack() {}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
    start = std::chrono::system_clock::now();
    FindRoot(query, cs);
    Initialize(data, query);
    PrintMatch(data, query, cs, root);
    std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
    printf("%lf [sec]\n", sec.count());
}

void Backtrack::PrintMatch(const Graph& data, const Graph& query,
                           const CandidateSet& cs, const Vertex &qVertex) {
    if (qVertex == -1) {
        count++;
        if (count > 100000) {
            std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
            printf("%lf [sec]\n", sec.count());
            exit(0);
        } else {
            vector<Vertex> ans(query.GetNumVertices(), -1);
            for (size_t i = 0; i < embedded.size(); i++) {
                ans[embedded[i]] = path[i];
            }
            printf("a "); PrintVector(ans);
            return;
        }
    }

    for (size_t i = 0; i < cs.GetCandidateSize(qVertex); i++) {
        const Vertex current_candidate = cs.GetCandidate(qVertex, i);

        if (v[current_candidate]) {
            continue;
        }

        v[current_candidate] = true; path.push_back(current_candidate);
        embedded.push_back(qVertex);
        not_embedded.erase(std::remove(not_embedded.begin(), not_embedded.end(), qVertex), not_embedded.end());
        bool gotoNext = true;

        for (size_t p = 0; p < embedded.size(); p++) {
            if (query.IsNeighbor(embedded[p], qVertex) && !data.IsNeighbor(path[p], current_candidate)) {
                gotoNext = false;
                break;
            }
        }

        if (gotoNext) {
            PrintMatch(data, query, cs, GetExtendableVertex(query, cs));
        }

        v[current_candidate] = false; path.pop_back();
        embedded.erase(std::remove(embedded.begin(), embedded.end(), qVertex), embedded.end());
        not_embedded.push_back(qVertex);
    }
}

void Backtrack::PrintVector(const vector<Vertex>& xs) {
    for (const auto& x : xs) {
        printf("%d ", x);
        // cout << x << " ";
    }
    printf("\n");
    // cout << "\n";
}

Vertex Backtrack::GetExtendableVertex(const Graph &query, const CandidateSet &cs) {
    vector<pair<size_t, Vertex>> qVertices;

    for (Vertex notEmVertex : not_embedded) {
        for (Vertex emVertex : embedded) {
            //bool notEmbedded = std::find(embedded.begin(), embedded.end(), (Vertex) i) == embedded.end();
            bool extendable = query.IsNeighbor(notEmVertex, emVertex);

            if (extendable) {
                // qVertices.emplace_back(std::pair<size_t, Vertex>(cs.GetCandidateSize(notEmVertex), notEmVertex));
                qVertices.emplace_back(make_pair(cs.GetCandidateSize(notEmVertex), notEmVertex));
                break;
            }
        }
    }

    if (qVertices.empty()) return -1;

    std::make_heap(qVertices.begin(), qVertices.end(), greater<pair<size_t, Vertex>>());

    return qVertices.front().second;
}

void Backtrack::FindRoot(const Graph &query, const CandidateSet &cs) {
    for (size_t i = 0; i < query.GetNumVertices(); i++) {
        if (cs.GetCandidateSize(i) < cs.GetCandidateSize(root)) {
            root = i;
        }
    }
}

void Backtrack::Initialize(const Graph &data, const Graph &query) {
    v.resize(data.GetNumVertices(), false);
    for (size_t i = 0; i < query.GetNumVertices(); i++) {
        if (root != (Vertex) i) {
            not_embedded.push_back((Vertex) i);
        }
    }
}

bool Backtrack::CheckEmbedding(const Graph &data, const Graph &query,
                               const CandidateSet &cs, const vector<Vertex>& xs) {
    const size_t len = xs.size();

    for (size_t i = 0; i < len; i++) {
        const Vertex u = i, v = xs[i];
        // cout << "u " << u << " v " << v << "\n";

        if (data.GetLabel(v) != query.GetLabel(u)) {
            return false;
        }

        for (size_t j = query.GetNeighborStartOffset(u); j < query.GetNeighborEndOffset(u); j++) {
            const Vertex jj = query.GetNeighbor(j);
            const Vertex n = static_cast<Vertex>(xs[jj]);

            // cout << "\tj " << jj << " n " << n << "\n";
            if (!data.IsNeighbor(v, n)) {
                return false;
            }
        }
    }
    return true;
}