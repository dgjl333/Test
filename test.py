struct State{
    int x, y, rotation
}

struct Node{
    visited, State
}
]

bestState = None
bestScore = -inf

int main(){
    vector<vector<vector<Node>>> aiSearchGraph;

    q = initState;

    while(!q.empty()){
        current = q.pop();

        if(Collisionbelow(current)){
            int score = evalScore(current);
            if(score > bestScore){
                bestScore = score;
                bestState = current;
            }
        }

        for each possible move from allmoves{
             nextState = applyMove(current, move);
             if (collision(nextState)){
                 continue;
             }

             if(graph[nextState.x][nextState.y][nextState.rotation].visited){
                 continue;
             }

                graph[nextState.x][nextState.y][nextState.rotation].visited = true;
                graph[nextState.x][nextState.y][nextState.rotation].State = nextState;
                q.push(nextState);

            }
        }
    }
}