/*
 **********************************************
 *  CS314 Principles of Programming Languages *
 *  Fall 2018                                 *
 *  File: oneway.c                            *
 *  Date: 11/25/2018                          *
 **********************************************
 */
#include "oneway.h"
#include "utils.h"

void extend_one_hand(int threadId, int threadNum, GraphData graph,
                     int nodeNum, int *nodeToProcess,
                     int *res, int *strongNeighbor)
{
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
	int u;
	for(;v<end;v++){
		int vt = nodeToProcess[v];
		int off = graph.offset[vt];
		int end = off + graph.degree[vt];
		strongNeighbor[vt] = nodeNum;
		
		for(u = off;u < end;u++){
			int neighbour = graph.index[u];
			
			if(res[neighbour] == UNMATCHED){
				strongNeighbor[vt] = neighbour;
				break;
			}
	}
		if (strongNeighbor[vt] == nodeNum){
            res[vt] = NO_MATCHED_NODES;
        }
    
	}
    /* Your Code Goes Here */
}

void check_handshaking(int threadId, int threadNum,
                       int nodeNum, int *nodeToProcess,
                       int *strongNeighbor, int *res)
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
    int s;
    for(;v < end;v++){
    	int vt = nodeToProcess[v];
    	s = strongNeighbor[vt];
    	if(vt == strongNeighbor[s]){
    		res[vt] = s;
		}
	}
}


