
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Edge{
    Edge(int i, int s, int e, int w){index = i; start = s; end = e; weight = w;}
    int index;
    int start;
    int end;
    int weight;
};

vector< vector<Edge> > Graph;   //vector临接表

map< int, vector<Edge> > mGraph;    //map临接表
map< int, bool> isVisited;  //判断是否访问过
map< int, vector<Edge> >::iterator it;


vector<int> V1;
vector<Edge> paths;
vector< vector<Edge> > totalPaths;

int startNode;
int currentNode;
int endNode;

bool Valid(int current) {
    if( isVisited.find(current)->second == false)
        return true;
    else
        return false;
}

void DFS(Edge thisEdge) {

    paths.push_back(thisEdge);
    isVisited.find(thisEdge.end)->second = true;

    if(thisEdge.end == endNode) {
        vector<Edge> path(paths);
        if (paths.size() ==1) paths.pop_back();
        if (isVisited.find(endNode)->second == true) isVisited.find(endNode)->second = false;
        totalPaths.push_back(path);
        return;
    }

    if(mGraph.find(thisEdge.end) == mGraph.end()) return;

    vector<Edge> nextEdge(mGraph.find(thisEdge.end)->second);

    for (int i = 0; i < nextEdge.size(); i++) {
        currentNode = nextEdge[i].end;
        if (Valid(currentNode)) {
//            isVisited.find(currentNode)->second = true;
            DFS(nextEdge[i]);
            paths.pop_back();
            isVisited.find(currentNode)->second = false;
        }
    }
}

//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{

    int index, start, end, weight;

//    unsigned short result[] = {2, 6, 3};//示例中的一个解
//
//    for (int i = 0; i < 3; i++)
//        record_result(result[i]);

    for(int i = 0; i < edge_num; i++) {
        sscanf(topo[i], "%d,%d,%d,%d", &index, &start, &end, &weight);

        it = mGraph.find(start);
        if (mGraph.find(start) != mGraph.end()){
            it->second.push_back( Edge(index, start, end, weight) );
        }else{
            vector<Edge> neighbor;
            neighbor.push_back( Edge(index, start, end, weight) );
            mGraph.insert(make_pair(start, neighbor));

            isVisited.insert(make_pair(start, false));
            isVisited.insert(make_pair(end, false));   //有些点没有指出去的边,也要初始化
        }
    }

    char demandV[500];
    int tempNode = 0;
    sscanf(demand,"%d,%d,%s",&startNode,&endNode,demandV);

    for(int i = 0;i <= strlen(demandV);i++){
        if (demandV[i] == '\0'){
            V1.push_back(tempNode);
            tempNode = 0;
        }
        if (demandV[i] != '|'){
            tempNode = tempNode*10 + demandV[i]-'0';
        }else{
            V1.push_back(tempNode);
            tempNode = 0;
        }

    }

    isVisited.find(startNode)->second = true;
    vector<Edge> startV = mGraph.find(startNode)->second;
    for (int i = 0; i < startV.size(); i++) {
        DFS(startV[i]);
    }

    cout<<"hello";
}




