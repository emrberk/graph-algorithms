#include <list>
#include <stack>
#include <queue>
#include <vector>

#include "HashTable.h"
#include "Edge.h"
/* Do not add new libraries or files */

using namespace std;

/** An adjacency list representation of a directed weighted graph. */
class Graph {

public:

    // TODO: IMPLEMENT THESE FUNCTIONS.
    /** CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR */
    Graph();
    Graph(const Graph& rhs);
    Graph& operator=(const Graph& rhs);
    ~Graph();

    // TODO: IMPLEMENT THIS FUNCTION.
    /** Adds the given node to the graph with vid or country as key,
     * and an empty edge list as value */
    void addNode(const Node& node);

    // TODO: IMPLEMENT THIS FUNCTION.
    /** Adds a new edge to the edge list of headNode using tailNode and import data */
    void addConnection(const Node& headNode, const Node& tailNode, int import);

    // TODO: IMPLEMENT THIS FUNCTION.
    /** Given a country, returns all adjacent
     * countries of the given country as a list of Node
     * Throw ItemNotFoundException, if the given node does not exist */
    list<Node> getAdjacentNodes(const Node& node);

    // TODO: IMPLEMENT THIS FUNCTION.
    /** For the given node, returns the sum of imports */
    long getTotalImports(const Node& node);

    // TODO: IMPLEMENT THIS FUNCTION.
    /** Deletes the given country from the graph
     * together with its incident connections(edges) */
    void deleteNode(const Node& node);

    // TODO: IMPLEMENT THIS FUNCTION.
    /** Given two countries , returns the least cost path/route between
     * them using import values as the edge weight */
    list<string> findLeastCostPath(const Node& srcNode, const Node& destNode);

    // TODO: IMPLEMENT THIS FUNCTION.
    /** Detect whether the graph contains any cycle */
    bool isCyclic();

    // TODO: IMPLEMENT THIS FUNCTION.
    /** returns the BFS path from srcNode to destNode as a list of country names */
    list<string> getBFSPath(const Node& srcNode, const Node& destNode);

private:
    /** Adjacency list representation of the graph;
    You can change the signature of this variable*/
    typedef struct dv {
        long distance;
        string prevkey;
        dv() : distance(LONG_MAX), prevkey("") {}
    }dv;
    struct pair {
        long distance;
        string key;
        pair() : distance(LONG_MAX), key("") {}
    };
    struct cycleHelper {
        bool visited;
        bool completed;
        cycleHelper() : visited(false), completed(false) {}
    };
    struct bfstruct {
        bool visited;
        string prev;
        bfstruct() : visited(false), prev("") {}
    };

    class minList {
        struct listNode {
            pair p;
            listNode* prev;
            listNode* next;
            listNode() {
                next = prev = nullptr;
            }
            listNode(pair _p) {
                p = _p;
                next = nullptr;
                prev = nullptr;
            }
            listNode(pair _p, listNode* _prev, listNode* _next) {
                p = _p;
                prev = _prev;
                next = _next;
            }

        };
        listNode* head;
        listNode* tail;
        int elements;

    public:

        minList() {
            head = nullptr;
            tail = nullptr;
            elements = 0;
        }
        ~minList() {
            listNode* current = head;
            while (current != nullptr) {
                listNode* temp = current->next;
                delete current;
                current = temp;
            }
        }

        void insertList(pair& p) {
            listNode* inserted = new listNode(p);
            if (elements == 0) {
                head = inserted;
                tail = inserted;
            }
            else if (p.distance <= head->p.distance) {
                inserted->next = head;
                inserted->prev = nullptr;
                head->prev = inserted;
                head = inserted;
            }
            else if (p.distance >= tail->p.distance) {
                inserted->next = nullptr;
                inserted->prev = tail;
                tail->next = inserted;
                tail = inserted;
            }
            else {
                for (listNode* current = head; current != nullptr; current = current->next) {
                    if (current->p.distance >= p.distance) {
                        inserted->prev = current->prev;
                        inserted->next = current;
                        current->prev->next = inserted;
                        current->prev = inserted;
                        break;
                    }
                }
            }
            elements++;
        }
        void changeDistance(string key, long newdistance) {
            for (listNode* current = head; current != nullptr; current = current->next) {
                if (current->p.key != key) {
                    continue;
                }
                current->p.distance = newdistance;
                listNode updated = *current;
                if (isEmpty()) {
                    return;
                }
                if (head == current) {
                    if (tail == current) {
                        head = nullptr;
                        tail = nullptr;
                    }
                    else {
                        head = head->next;
                        head->prev = nullptr;
                    }
                }
                else if (tail == current) {
                    tail = tail->prev;
                    tail->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;

                }
                elements--;
                delete current;
                insertList(updated.p);
                break;
            }
        }
        pair pop() {
            pair ret = head->p;
            listNode* newhead = head->next;
            delete head;
            head = newhead;
            elements--;
            return ret;
        }
        bool isEmpty() {
            return elements == 0;
        }
    };
    minList ml;
    HashTable<string, dv> dvgraph;
    HashTable<string, cycleHelper> cycleGraph;
    HashTable<string, bfstruct> bfsGraph;
    HashTable<string, list<Edge>> adjList;
    bool searchCycle(string key);
    bool isConnected(string start, string dest);


};
// End of header file
