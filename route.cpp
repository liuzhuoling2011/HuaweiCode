
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Edge{
    Edge(int i, int e, int w){index = i; end = e; weight = w;}
    int index;
    int end;
    int weight;
};

vector< vector<Edge> > Graph;   //vector临接表

map< int, vector<Edge> > mGraph;    //map临接表
map< int, vector<Edge> >::iterator it;

bool Valid() {

}

//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{

    int index, start, end, weight;

//    unsigned short result[] = {2, 6, 3};//示例中的一个解
//
//    for (int i = 0; i < 3; i++)
//        record_result(result[i]);

//    Graph.resize(edge_num+1);

    for(int i = 0; i < edge_num; i++) {
        sscanf(topo[i], "%d,%d,%d,%d", &index, &start, &end, &weight);

        it = mGraph.find(start);
        if (mGraph.find(start) != mGraph.end()){
            it->second.push_back( Edge(index, end, weight) );
        }else{
            vector<Edge> neighbor;
            neighbor.push_back( Edge(index, end, weight) );
            mGraph.insert(make_pair(start, neighbor));
        }

//        Graph[start].push_back( Edge(index, end, weight) );

    }

    vector<Edge> tempV = mGraph.find(3)->second;
    
}




