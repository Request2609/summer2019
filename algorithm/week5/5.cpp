#include <iostream>
#include <vector>
using namespace std ;
/*
 5.git 是一种分布式代码管理工具，git 通过树的形式记录文件的更
改历史，比如： base'<--base<--A<--A' ^ | --- B<--B' 小米工程
师常常需要寻找两个分支最近的分割点，即 base.假设 git 树是多叉
树，请实现一个算法，计算 git 树上任意两点的最近分割点。 （假
设 git 树节点数为 n,用邻接矩阵的形式表示 git 树：字符串数组
matrix 包含 n 个字符串，每个字符串由字符'0'或'1'组成，长度为 n。
matrix[i][j]=='1'当且仅当 git 树种第 i 个和第 j 个节点有连接。
节点 0 为 git 树的根节点。）（题目来源：小米面试题）
示例:
输入:
[01011,10100,01000,10000,10000],1,2
输出:
1
 * */
class Solution {
public:
    /**
     * 返回git树上两点的最近分割点
     *
     * @param matrix 接邻矩阵，表示git树，matrix[i][j] == '1' 当且仅当git树中第i个和第j个节点有连接，节点0为git树的跟节点
     * @param indexA 节点A的index
     * @param indexB 节点B的index
     * @return 整型
     */
    int getSplitNode(vector<string> matrix, int indexA, int indexB) {
        int n=matrix.size();
    vector<vector<int> > adjList(n);
        vector<int> parent(n,-1);
        vector<int> depth(n,0);

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(matrix[i][j]=='1'){
                    adjList[i].push_back(j);
                    adjList[j].push_back(i);
                }
            }
        }

        vector<int> stk;
        stk.push_back(0);
        int count=0;
//        depth[0]=0;
        while(!stk.empty() && count<n){
            int node=stk.back();
            stk.pop_back();
            for(int k=0;k<adjList[node].size();k++){
                int v=adjList[node][k];
                if(parent[v]!=-1)
                    continue;
                parent[v]=node;
                depth[v]=depth[node]+1;
                stk.push_back(v);
                count++;
            }
        }

        int a=indexA;
        int b=indexB;
        while(depth[a]>depth[b])
            a=parent[a];
        while(depth[a]<depth[b])
            b=parent[b];
        while(a!=b){
            a=parent[a];
            b=parent[b];
        }
        return a;
    }
};
int main() {
       
    return 0;
}

