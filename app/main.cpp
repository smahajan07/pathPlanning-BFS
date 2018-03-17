#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <fstream>
#include <cmath>
using namespace std;

// Global Variables
#define MAX 37500
#define ROOT 0

int totalNodesCreated=0;
queue<int> levelQ;

tuple<int, int> goalNode(249,149);
tuple<int, int> finalPath[300];
int pathNodes=0;

// put this in the Node file

void generateNodes();
bool checkObstacle(tuple<int, int> nodePos);
void createSpace();


class Node{

    public:

        int idNum;
        int parentNum;
        int cost;
        tuple<int, int> currNodePos;
        tuple<int, int> prevNodePos;

        void callActions(const int& idx);

        void addNode(Node& newNode,const int& x, const int& y, int& id,int pNum);

        void actionMoveEast(const int& idx,int x,int y, const int& x_old);
        void actionMoveNorth(const int& idx,int x,int y, const int& y_old);
        void actionMoveNorthEast(const int& idx,int x,int y, const int& x_old, const int& y_old);

        void actionMoveSouthEast(const int& idx,int x,int y, const int& x_old, const int& y_old);
        void actionMoveSouth(const int& idx,int x,int y, const int& y_old);
        void actionMoveSouthWest(const int& idx,int x,int y, const int& x_old, const int& y_old);
        void actionMoveWest(const int& idx,int x,int y, const int& x_old);
        void actionMoveNorthWest(const int& idx,int x,int y, const int& x_old, const int& y_old);

        bool checkDuplicate(tuple<int, int> nodePos);
};

Node nodesInfo[MAX];     // Array of objects of the class Node

void generateNodes(){
    while(!levelQ.empty()){ //&& totalNodesCreated<MAX
        int idx = levelQ.front();
        if(nodesInfo[idx-1].currNodePos != goalNode){
            nodesInfo[idx-1].callActions(idx);
        }
        else
          break;
    levelQ.pop();
    }
}

void printNode(tuple<int, int> nodePos){

    int x=get<0>(nodePos);
    int y=get<1>(nodePos);
    get<0>(finalPath[pathNodes])=x;
    get<1>(finalPath[pathNodes])=y;
    //cout<<"\nX : "<<x<<"\t"<<"Y : "<<y<<endl;
    pathNodes++;
}

// members of class Node

void Node::callActions(const int& idx){       // idx - parent , so now we will make the child nodes from this parent
    int x = get<0>(nodesInfo[idx-1].currNodePos);
    int y = get<1>(nodesInfo[idx-1].currNodePos);

    int x_old = get<0>(nodesInfo[idx-1].prevNodePos);
    int y_old = get<1>(nodesInfo[idx-1].prevNodePos);

    actionMoveEast(idx, x, y, x_old);
    actionMoveNorth(idx, x, y, y_old);
    actionMoveNorthEast(idx, x, y, x_old, y_old);

    actionMoveSouthEast(idx, x, y, x_old, y_old);
    actionMoveSouth(idx, x, y, y_old);

    actionMoveSouthWest(idx, x, y, x_old, y_old);
    actionMoveWest(idx, x, y, x_old);
    actionMoveNorthWest(idx, x, y, x_old, y_old);

}

void Node::actionMoveNorth(const int& idx,int x, int y, const int& y_old){

    y++;

    if(y<150 && y!=y_old){
        bool check1 = checkDuplicate(make_tuple(x,y));
        bool check2 = checkObstacle(make_tuple(x,y));
        if(check1 && check2){
            totalNodesCreated++;
            nodesInfo[totalNodesCreated-1].addNode(nodesInfo[totalNodesCreated-1], x, y, totalNodesCreated, idx);
            nodesInfo[totalNodesCreated-1].prevNodePos = make_tuple(x,y-1);
            levelQ.push(totalNodesCreated);
        }
    }

}

void Node::actionMoveNorthEast(const int& idx,int x, int y, const int& x_old, const int& y_old){

    y++;x++;

    if(y<150 && x<250 && y!=y_old && x!=x_old){
        bool check1 = checkDuplicate(make_tuple(x,y));
        bool check2 = checkObstacle(make_tuple(x,y));
        if(check1 && check2){
            totalNodesCreated++;
            nodesInfo[totalNodesCreated-1].addNode(nodesInfo[totalNodesCreated-1], x, y, totalNodesCreated, idx);
            nodesInfo[totalNodesCreated-1].prevNodePos = make_tuple(x-1,y-1);
            levelQ.push(totalNodesCreated);
        }
    }

}

void Node::actionMoveEast(const int& idx,int x, int y, const int& x_old){

    x++;

    if(x<250 && x!=x_old){
        bool check1 = checkDuplicate(make_tuple(x,y));
        bool check2 = checkObstacle(make_tuple(x,y));
        if(check1 && check2){
            totalNodesCreated++;
            nodesInfo[totalNodesCreated-1].addNode(nodesInfo[totalNodesCreated-1], x, y, totalNodesCreated, idx);
            nodesInfo[totalNodesCreated-1].prevNodePos = make_tuple(x-1,y);
            levelQ.push(totalNodesCreated);
        }
    }

}

void Node::actionMoveSouthEast(const int& idx,int x, int y, const int& x_old, const int& y_old){

    y--;x++;

    if(y>0 && x<250 && y!=y_old && x!=x_old){
        bool check1 = checkDuplicate(make_tuple(x,y));
        bool check2 = checkObstacle(make_tuple(x,y));
        if(check1 && check2){
            totalNodesCreated++;
            nodesInfo[totalNodesCreated-1].addNode(nodesInfo[totalNodesCreated-1], x, y, totalNodesCreated, idx);
            nodesInfo[totalNodesCreated-1].prevNodePos = make_tuple(x-1,y+1);
            levelQ.push(totalNodesCreated);
        }
    }

}

void Node::actionMoveSouth(const int& idx,int x, int y, const int& y_old){

    y--;

    if(y>0 && y!=y_old){
        bool check1 = checkDuplicate(make_tuple(x,y));
        bool check2 = checkObstacle(make_tuple(x,y));
        if(check1 && check2){
            totalNodesCreated++;
            nodesInfo[totalNodesCreated-1].addNode(nodesInfo[totalNodesCreated-1], x, y, totalNodesCreated, idx);
            nodesInfo[totalNodesCreated-1].prevNodePos = make_tuple(x,y+1);
            levelQ.push(totalNodesCreated);
        }
    }

}

void Node::actionMoveSouthWest(const int& idx,int x, int y, const int& x_old, const int& y_old){

    y--;x--;

    if(y>0 && x>0 && y!=y_old && x!=x_old){
        bool check1 = checkDuplicate(make_tuple(x,y));
        bool check2 = checkObstacle(make_tuple(x,y));
        if(check1 && check2){
            totalNodesCreated++;
            nodesInfo[totalNodesCreated-1].addNode(nodesInfo[totalNodesCreated-1], x, y, totalNodesCreated, idx);
            nodesInfo[totalNodesCreated-1].prevNodePos = make_tuple(x+1,y+1);
            levelQ.push(totalNodesCreated);
        }
    }

}

void Node::actionMoveWest(const int& idx,int x, int y, const int& x_old){

    x--;

    if(x>0 && x!=x_old){
        bool check1 = checkDuplicate(make_tuple(x,y));
        bool check2 = checkObstacle(make_tuple(x,y));
        if(check1 && check2){
            totalNodesCreated++;
            nodesInfo[totalNodesCreated-1].addNode(nodesInfo[totalNodesCreated-1], x, y, totalNodesCreated, idx);
            nodesInfo[totalNodesCreated-1].prevNodePos = make_tuple(x+1,y);
            levelQ.push(totalNodesCreated);
        }
    }

}

void Node::actionMoveNorthWest(const int& idx,int x, int y, const int& x_old, const int& y_old){

    y++;x--;

    if(y<150 && x>0 && y!=y_old && x!=x_old){
        bool check1 = checkDuplicate(make_tuple(x,y));
        bool check2 = checkObstacle(make_tuple(x,y));
        if(check1 && check2){
            totalNodesCreated++;
            nodesInfo[totalNodesCreated-1].addNode(nodesInfo[totalNodesCreated-1], x, y, totalNodesCreated, idx);
            nodesInfo[totalNodesCreated-1].prevNodePos = make_tuple(x+1,y-1);
            levelQ.push(totalNodesCreated);
        }
    }

}

void Node::addNode(Node& newNode,const int& x, const int& y, int& id, int pNum){
    newNode.currNodePos = make_tuple(x,y);
    newNode.idNum = id;
    newNode.parentNum = pNum;
    newNode.cost = nodesInfo[pNum-1].cost + 1;
}

bool Node::checkDuplicate(tuple<int, int> nodePos){
    for(int i=0;i<totalNodesCreated;++i){
        if(nodePos == nodesInfo[i].currNodePos)
        return false;
    }
    return true;
}

bool checkObstacle(tuple<int, int> nodePos){
    int x=get<0>(nodePos);
    int y=get<1>(nodePos);

    if(x>=55 && y>=37 && x<=105 && y<=83){
         return false;
    }

    else if(pow((x-180),2) + pow((y-30),2)- pow(15,2) <= 0){
        return false;
    }

    else if(((y+0.75*x-185.6) >= 0) && ((y-1.64*x +101.8) <= 0) && (y-136 <=0) && ((y+1.85*x-446.8) <= 0) && ((y-1.65*x + 211.6) >= 0) )  { // ((y-0.1*x - 82.36) <= 0) && ((y+5.42*x - 956.71) > 0) && ((y+1.85*x-446.8) >= 0) && ((y-1.65*x + 211.6) >= 0) && ((y+3.75*x - 679.75) <= 0)
      if(((y+0.75*x-185.6) >= 0) && ((y-0.1*x -82.36) < 0) && (y+5.42*x - 956.7 <0)){
        return true;
      }
      else
        return false;
    }
    else
      return true;
}

bool checkPathNode(tuple<int, int> pos){

    for(int i=0;i<pathNodes;++i){
        if((get<0>(pos) == get<0>(finalPath[i])) && (get<1>(pos) == get<1>(finalPath[i])))
            return true;
    }

    return false;
}

void findPathBFS(tuple<int, int> nodePos){

    int flag=1;
    for(int i=totalNodesCreated;i>0;--i){
        if(nodePos==nodesInfo[i].currNodePos){
            flag=0;
            int p=nodesInfo[i].parentNum;
            printNode(nodesInfo[--p].currNodePos);
            ++p;
            for(int j=nodesInfo[i].cost;j>0;--j){
              printNode(nodesInfo[--p].currNodePos);
              p=nodesInfo[p].parentNum;
            }
            break;
        }
    }

    if(flag)
        cout<<"\nNode not found!\n";
}

void createSpace(){
    FILE *f = fopen("../output/out.ppm", "wb");
    int height=150,width=250,red_value=0,green_value=0,blue_value=255;
    fprintf(f, "P6\n%i %i 255\n", width, height);
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {

            bool checkPath = checkPathNode(make_tuple(x,y));

            if(checkPath){

                fputc(120, f);
                fputc(255, f);
                fputc(0, f);
            }

            else{

                if(x>=55 && y>=37 && x<=105 && y<=83){
                    fputc(255, f);
                    fputc(0, f);
                    fputc(0, f);
                }

                else if(pow((x-180),2) + pow((y-30),2)- pow(15,2) <= 0){
                    fputc(255, f);
                    fputc(0, f);
                    fputc(0, f);
                }

                else if(((y+0.75*x-185.6) >= 0) && ((y-1.64*x +101.8) <= 0) && (y-136 <=0) && ((y+1.85*x-446.8) <= 0) && ((y-1.65*x + 211.6) >= 0) ){ // ((y-0.1*x - 82.36) <= 0) && ((y+5.42*x - 956.71) > 0) && ((y+1.85*x-446.8) >= 0) && ((y-1.65*x + 211.6) >= 0) && ((y+3.75*x - 679.75) <= 0)

                    if(((y+0.75*x-185.6) >= 0) && ((y-0.1*x -82.36) <= 0) && (y+5.42*x - 956.7 <=0)){
                      fputc(red_value, f);
                      fputc(green_value, f);
                      fputc(blue_value, f);
                    }

                    else{
                      fputc(255, f);
                      fputc(0, f);
                      fputc(0, f);
                    }

                }

                else{
                    fputc(red_value, f);
                    fputc(green_value, f);
                    fputc(blue_value, f);
                }

            }
        }

    }
    fclose(f);
}

//Main function

int main()
{


    // Enter the start node
    int startX = 1;
    int startY = 1;

    int beginFlag = checkObstacle(goalNode);

    if(beginFlag){

        // Initializing start node
        tuple<int, int> startNode(startX,startY);
        totalNodesCreated++;

        int rootID = 1;
        nodesInfo[ROOT].addNode(nodesInfo[ROOT],startX, startY, rootID, 0);
        tuple<int, int> prevNodePosRoot(-1,-1);
        nodesInfo[ROOT].prevNodePos = prevNodePosRoot;
        nodesInfo[ROOT].cost = 0;

        levelQ.push(1);


        generateNodes();

        cout<<totalNodesCreated<<endl;

        // Goal node is set as a global variable, please set the global variable "goalNode"...
                                                                     //...to see the path accordingly
        printNode(goalNode);
        findPathBFS(goalNode);


        // For visual representation, optionally you can print nodes which form the final path
        createSpace();
    }
    else
        cout<<"\nPlease change Goal Node location!\n";

    return 0;
}
