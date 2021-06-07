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
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    Initialize(data, query);
    //Vertex vertex = GetExtendableVertex(query, cs);
    PrintMatch(data, query, cs, 0);
    std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
    printf("%lf [sec]\n", sec.count());

    // DFS(data, query, cs, 0);

    // BruteForce(data, query, cs);
}

void Backtrack::PrintMatch(const Graph& data, const Graph& query,
                           const CandidateSet& cs, const Vertex &qVertex) {
    if (qVertex == -1) {
        count++;
        if (count > 100000) {
            exit(0);
        } else {
            PrintPath();
        }
        return;
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
        cout << x << " ";
    }
    cout << "\n";
}

void Backtrack::PrintPath() {
    printf("a ");
    for (const Vertex& u : embedded) {
        printf("%d ", path[u]);
    }
    printf("\n");
}

Vertex Backtrack::GetExtendableVertex(const Graph &query, const CandidateSet &cs) {
    std::vector<std::pair<size_t, Vertex>> qVertices;

    for (Vertex notEmVertex : not_embedded) {
        for (Vertex emVertex : embedded) {
            //bool notEmbedded = std::find(embedded.begin(), embedded.end(), (Vertex) i) == embedded.end();
            bool extendable = query.IsNeighbor(notEmVertex, emVertex);

            if (extendable) {
                qVertices.emplace_back(std::pair<size_t, Vertex>(cs.GetCandidateSize(notEmVertex), notEmVertex));
                break;
            }
        }
    }

    if (qVertices.empty()) return -1;

    std::make_heap(qVertices.begin(), qVertices.end(), greater<std::pair<size_t, Vertex>>());

    return qVertices.front().second;
}

void Backtrack::Initialize(const Graph &data, const Graph &query) {
    v.resize(data.GetNumVertices(), false);
    for (size_t i = 1; i < query.GetNumVertices(); i++) {
        not_embedded.push_back((Vertex) i);
    }
}