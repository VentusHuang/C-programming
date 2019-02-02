/*
 **********************************************
 *  CS314 Principles of Programming Languages *
 *  Fall 2018                                 *
 *  File: filter.c                            *
 *  Date: 11/25/2018                          *
 **********************************************
 */

#include "filter.h"

void count_unmatched_vertices(int threadId, int threadNum, int nodeNum,
                              int *nodeToProcess, int *res,
                              int *nodeCount)
{
    /* Your Code Goes Here */
    int i = threadId;
	int workchunk = (nodeNum + threadNum - 1)/ threadNum;
	int	beg = i * workchunk;
	int end;
	if (beg+workchunk > nodeNum){
		end = nodeNum;
	}
	else{
		end = beg+workchunk;
	}
	nodeCount[threadId] = 0;
    int v = beg;
    for(;v < end;v++){
    	int vt = nodeToProcess[v];
    	if(res[vt] == UNMATCHED){
    		nodeCount[i]++;
		}
	}
}

void update_remain_nodes_index(int threadId, int threadNum,
                               int *nodeToProcess, int *startLocations,
                               int *res,
                               int nodeNum, int *newNodeToProcess)
{
    /* Your Code Goes Here */
    int i = threadId;
	int workchunk = (nodeNum + threadNum - 1)/ threadNum;
	int	beg = i * workchunk;
	int end;
	if (beg+workchunk > nodeNum){
		end = nodeNum;
	}
	else{
		end = beg+workchunk;
	}
	
    int v = beg;
    for(;v < end;v++){
    	int vt = nodeToProcess[v];
    	if(res[vt] == UNMATCHED){
    		int offset = startLocations[i]++;
    		newNodeToProcess[offset] = vt;
		}
	}
}
