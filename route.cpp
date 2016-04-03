
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Edge{
    Edge(unsigned short i, int s, int e, int w){index = i; start = s; end = e; weight = w;}
    unsigned short index;
    int start;
    int end;
    int weight;
};

map< int, vector<Edge> > mGraph;    //map临接表
map< int, bool> isVisited;  //判断是否访问过
map< int, vector<Edge> >::iterator it;


vector<int> V1;
vector<Edge> paths;
vector< vector<Edge> > totalPaths;

int startNode;
int endNode;
int MIN_WEIGHT = 100000;

bool compare(const Edge &e1, const Edge &e2){   //加入贪心算法的思路,优先访问V1中的元素和weight较小的元素
    int ve1 = 1;
    int ve2 = 1;
    for(int i=0;i<V1.size();i++){
        if(e1.end == V1[i]) ve1 = 0.2;
        if(e2.end == V1[i]) ve2 = 0.2;
    }
    return ve1*e1.weight < ve2*e2.weight;
}

int sumWeight( vector<Edge> path ){
    int sum = 0;
    for(int i = 0; i < path.size(); i++) {
        sum += path[i].weight;
    }
    return sum;
}

bool isContain( vector<Edge> path, vector<int> V){  //Derek
    bool flag;
    for(vector<int>::iterator i = V.begin(); i < V.end(); i++) {
        flag = false;
        for(vector<Edge>::iterator j = path.begin(); j < path.end(); j++) {
            if (j->end == *i) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return true;
}

bool Valid(int current) {
    if( isVisited.find(current)->second == false)
        return true;
    else
        return false;
}

void DFS(Edge thisEdge) {

    if(mGraph.find(thisEdge.end) == mGraph.end() && thisEdge.end != endNode) return;   //说明它不是终点也没有指出去的边了

    if(thisEdge.end == endNode) {
        vector<Edge> path(paths);
        if(isContain(path,V1) && sumWeight(path) < MIN_WEIGHT){ //进一步增加条件约束,获得更精简的符合要求的path集合,最后一个即为最优解
            MIN_WEIGHT = sumWeight(path);
            totalPaths.push_back(path);
        }
        return;
    }

    vector<Edge> nextEdge(mGraph.find(thisEdge.end)->second);

    for (int i = 0; i < nextEdge.size(); i++) {
        int currentNode = nextEdge[i].start;
        if (Valid(currentNode)) {
            isVisited.find(currentNode)->second = true;
            paths.push_back(nextEdge[i]);
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

    for(it = mGraph.begin(); it != mGraph.end(); it++){ //对于每个点,将它next点的集合按重要性排序
        sort(it->second.begin(),it->second.end(),compare);
    }

    char demandV[600];
    int tempNode = 0;
    sscanf(demand,"%d,%d,%s",&startNode,&endNode,demandV);

    for(int i = 0;;i++){
        if (demandV[i] == '\0'){
            V1.push_back(tempNode);
            break;
        }
        if (demandV[i] != '|'){
            tempNode = tempNode*10 + demandV[i]-'0';
        }else{
            V1.push_back(tempNode);
            tempNode = 0;
        }

    }

    isVisited.find(startNode)->second = true;   //标记起点
    vector<Edge> startV = mGraph.find(startNode)->second;   //将起点压栈
    for (int i = 0; i < startV.size(); i++) {   //遍历起点指向节点,准备DFS深度搜索————这里可以加上最大限制(最少出度的点优先搜索)优化
        paths.push_back(startV[i]);
        DFS(startV[i]);
        paths.pop_back();
    }

    vector<Edge> resultPath = totalPaths[totalPaths.size()-1];
    for (int i = 0; i < resultPath.size(); i++){
        record_result(resultPath[i].index);
    }



    cout<<"totalPath中最后一个path即是最优";
}




