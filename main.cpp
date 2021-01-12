#include "Graph.h"
#include <iostream>
/*You can add additional libraries here to read and process the dataset*/
#include <fstream> // file read/write

using namespace std;

// tester
int main() {

    // read input file
    ifstream inputF;

    // Metal trade Graph
    Graph graph;

    fstream file("world_trade.txt");

    string vertices;
    getline(file, vertices, '\t'); // skip header
    getline(file, vertices, '\n'); // number of vertices

    int numvertices = atoi( vertices.c_str() );
    HashTable<int, Node> nodeTable;

    // Build the graph from the txt input file
    for (int i = 0; i < numvertices; i++) {

        string vid, country, continent, gdp;
        getline(file, vid, '\t');
        getline(file, country, '\t');
        getline(file, continent, '\t');
        getline(file, gdp, '\n');

        Node node(atoi(vid.c_str()), country, continent, atol(gdp.c_str()));
        nodeTable.Insert(node.getVid(), node);

        graph.addNode(node);
    }
    getline(file, vertices, '\n'); // skip header

    // create connections
    string line;
    while (getline(file, line)) {
        int pos = line.find("\t");
        int vid1 = atoi(line.substr(0, pos).c_str());

        line = line.substr(pos+1);
        pos = line.find("\t");
        int vid2 = atoi(line.substr(0, pos).c_str());

        line = line.substr(pos+1);
        long import = atol(line.c_str());

        graph.addConnection(nodeTable.Get(vid1), nodeTable.Get(vid2), import);
    }

    file.close();
    HashTable<int, float> table2;
    Node n;
    n.setVid(80);
    n.setCountry("turkey");
    n.setContinent("asia");
    n.setGdp(900);
    Node germany(100, "germany", "europe", 2000);
    Node china(120, "china", "asia", 4000);
    Node usa(90, "usa", "america", 5000);
    Node bangladesh(70, "bangladesh", "asia", 100);
    Graph trades;
    trades.addNode(germany);
    trades.addNode(n);
    trades.addNode(china);
    trades.addNode(usa);
    trades.addNode(bangladesh);
    trades.addConnection(usa, china, 200);
    trades.addConnection(n, bangladesh, 700);
    trades.addConnection(usa, n, 1000);
    trades.addConnection(usa, germany, 200);
    trades.addConnection(germany, usa, 100);
    trades.addConnection(germany, bangladesh, 1900);
    trades.addConnection(china, n, 200);
    list<Node> tradeofusa = trades.getAdjacentNodes(usa);
    //cout << "reached" << endl;
    for (list<Node>::iterator it = tradeofusa.begin(); it != tradeofusa.end(); ++it) {
        //cout << "reached" << endl;
        cout << (*it).getCountry() << endl;

    }
    cout << trades.getTotalImports(usa) << endl;
    list<string> li = trades.findLeastCostPath(germany, bangladesh);
    list<string>::const_iterator it = li.begin();
    for (; it != li.end(); ++it) {
        cout << (*it) << endl;
    }

		
	// YOU CAN WRITE YOUR TEST CASES BELOW
	


    return 0;
}
