//-----------------------------------------------------------------------
// Assignment 3 kargeMinCut
//-----------------------------------------------------------------------
/*
The file contains the adjacency list representation of a simple undirected graph. 
There are 200 vertices labeled 1 to 200. The first column in the file represents the vertex label, 
and the particular row (other entries except the first column) 
tells all the vertices that the vertex is adjacent to. So for example, 
the 6th row looks like : "6   155 56  52  120 ......". 
This just means that the vertex with label 6 is adjacent to 
(i.e., shares an edge with) the vertices with labels 155,56,52,120,......,etc

Your task is to code up and run the randomized contraction algorithm for 
the min cut problem and use it on the above graph to compute the min cut.
 (HINT: Note that you'll have to figure out an implementation of edge contractions. 
    Initially, you might want to do this naively, creating a new graph from the old every time there'
    s an edge contraction. But you should also think about more efficient implementations.) 
 (WARNING: As per the video lectures, please make sure to run the algorithm many times with 
    different random seeds, and remember the smallest cut that you ever find.) 
 Write your numeric answer in the space provided. 
 So e.g., if your answer is 5, just type 5 in the space provided.
*/
//-----------------------------------------------------------------------
// Author: MiracleZhang 
// Date:  07/16/16
//----------------------------------------------------------------------
// the right answer for my kargerMincut.txt is that:
// 17
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//----------------------------
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int mincut(vector < vector<int> > &edges , vector <int> &nodes)
{
    
    if(nodes.size() == 2)
    {
        return edges.size();
    }

    int no_edges = edges.size();
    // random pick the num
    int num = rand() % (no_edges);
    int nd1 = edges[num][0];
    int nd2 = edges[num][1];
     //    cout <<num <<endl;
    for( int i=0;i < edges.size();i++)
    {
        if (edges[i][0] ==  nd2)
        {
            edges[i][0] = nd1;
        }

        if (edges[i][1] ==  nd2)
        {
            edges[i][1] = nd1;
        }
    }
 
    for (int j=0; j< edges.size();j++)
    {
        if (edges[j][0] == edges[j][1])
        {
            edges.erase(edges.begin()+j);
            j--;
        }
    }

    for (int k=0; k< nodes.size();k++)
    {
        if (nd2 == nodes[k])
        {
            nodes.erase(nodes.begin()+k);
        }
    }
    return mincut(edges,nodes);
}                              

int main ()
{
    ifstream in("kargerMinCut.txt");
    int number = 0;
    vector < vector<int> > values;
    int i =0;
    string line = "";

    // put 200 elements in the matrix, initiation 
    for(int h=0; h<200;h++)
    {
        vector <int> row;
        values.push_back(row);
    }
    int total=0;

    // every line contains the adjacent vertex, store them in the vector representing for the i th node
    while (getline(in,line))
    {
        stringstream stream(line);
        int j=0;
        int n;
        while (stream >>n)
        {
            values[i].push_back(n);
            j++;  
            total++;   
        }
        i++;
    }

    //total stands for the number of vertex
    cout << total <<endl;
    vector <int> nodes;

    // stands for edge
    vector < vector <int> > edges (total-200);

    int edge_row =0;
    for (int w=0; w<values.size();w++)
    {
        int e =1;
        for (e; e<values[w].size();e++)
        {
            edges[edge_row].push_back(values[w][0]);
            edges[edge_row].push_back(values[w][e]);
            edge_row++;
            //cout<<1<<endl;
        }
    }

    for (int q= 0 ; q<values.size();q++)
    {
        nodes.push_back(values[q][0]);
        //cout<<2<<endl;
    }

    // To sort edges  
    for (int r =0; r <edges.size(); r++)
    {
        if (edges[r][1] < edges[r][0]){
            int temp = edges[r][1];
            edges[r][1] = edges[r][0];
            edges[r][0] = temp;
        }
        //cout<<3<<endl;
    }           

    // To remove duplicates (edges present in the initial list)
    sort(edges.begin(),edges.end());     
    edges.erase(unique(edges.begin(),edges.end()),edges.end());      

    int cuts;
    int lowest = total/2;

    for(int times=0; times < 400; times++)
    {
        vector <int> nodes1;
        vector < vector <int> > edges1 ((total-200)/2);
        edges1 = edges;
        nodes1 = nodes;
        //cout<<"end"<<times;
        //cout<<4<<endl;
        cuts = mincut(edges1,nodes1);
        //cout <<cuts<<endl;
        if (cuts < lowest) 
            lowest = cuts;
    }
    // To display the nodes
    /*for (int y =0; y<nodes.size();y++){
           cout << nodes[y] <<endl;}     
    */

    // To display the edges ( 2x times the number i.e. with duplicates
    /*for( int k=0; k<edges.size(); k++){
        cout << edges[k][0] <<" " ; 
        cout << edges[k][1];    
        cout << endl ;}  */
    cout<<"Ans is"<<endl;
    cout <<lowest<<endl;
    in.close();
    return 0;
}



