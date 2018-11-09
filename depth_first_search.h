// Using stacks, apply depth first search to see if the mouse can reach the cheese.  
#include "stack.h"

// Neighbor node structure
struct NodeTypeNeighbor
{   
    // 1 to 25 - labels for the node
    int node_value;
    // indicates next node in neighbor(s) link
    NodeTypeNeighbor* next_neighbor;
};

// Backbone node structure
struct NodeTypeBackbone
{
    // 1 to 25 - labels for the node
    int node_value;
    // indicates next node in backbone link
    NodeTypeBackbone* next_backbone;
    // indicates next node in neighbor(s) link
    NodeTypeNeighbor* next_neighbor;
};

// GraphTable class definition
class GraphTable
{
    public:
        GraphTable();
        // construct graph table from file input
        void make_graphtable();
        // print the backbones and their neighbors
        void printAll();
        // see if mouse can reach cheese, given start and destination nodes
        void depthFirstSearch(int, int);

	private:
        NodeTypeBackbone* node;
};

// constructor
GraphTable::GraphTable()
{
    node = NULL;
}

void GraphTable::make_graphtable()
{
    // input value as a string to hold numbers
    string input;
    NodeTypeBackbone* current_backbone;
    NodeTypeNeighbor* current_neighbor;
    NodeTypeBackbone* previous_backbone;
    NodeTypeNeighbor* previous_neighbor;

    // input file
    string filename = "graph_table.txt";
    // c_str() returns a pointer to an array of characters that represents the string object
    ifstream inFile(filename.c_str());

    if (inFile.is_open())
    {
        while(getline(inFile, input))
        {
            // n is value of input, counter keeps track of getline
            int n, counter = 0;
            stringstream stream(input);
            while(stream >> n)
            {
                if(n == 1)
                {
                    // if path value is 1, then skip the block value by taking it in
                    stream >> n;
                    if(counter == 0)
                    {
                        // if a backbone node has path value 1, break
                        break;
                    }
                    //cout << "Block " << n << " is not accessible.\n";
                }
                else
                {
                    // if path value is 0
                    //cout << n << " ";
                    stream >> n;
                    //cout << n << " ";
                    //cout << "Block " << n << " is accessible.\n";
                    if(counter == 0)
                    {
                        // if backbone
                        if(!node)
                        {
                            // if first backbone
                            current_backbone = new NodeTypeBackbone;
                            current_backbone->node_value = n;
                            current_backbone->next_backbone = NULL;
                            current_backbone->next_neighbor = NULL;
                            node = previous_backbone = current_backbone;
                        }
                        else
                        {
                            // if not first backbone
                            current_backbone = new NodeTypeBackbone;
                            current_backbone->node_value = n;
                            current_backbone->next_backbone = NULL;
                            current_backbone->next_neighbor = NULL;
                            previous_backbone->next_backbone = current_backbone;
                            previous_backbone = current_backbone;
                        }
                    }
                    // if neighbor
                    else
                    {
                        current_neighbor = new NodeTypeNeighbor;
                        current_neighbor->node_value = n;
                        current_neighbor->next_neighbor = NULL;
                        if(counter == 1)
                        {
                            // if first neighbor
                            previous_backbone->next_neighbor = current_neighbor;
                            previous_neighbor = current_neighbor;
                        }
                        else
                        {
                            // if not first neighbor
                            previous_neighbor->next_neighbor = current_neighbor;
                            previous_neighbor = current_neighbor;
                        }
                    }
                    counter++;
                }
            }
            //cout << endl;
        }
        // close file
        inFile.close();
    }
    // output message if file could not be opened/found.
    else
    {
        cout << "Unable to open file. \n\n";
    }
}

// printAll function definition
void GraphTable::printAll()
{
    cout << endl;
    // keeps track of backbone
    NodeTypeBackbone* temp1 = node;
    // keeps track of neighbor
    NodeTypeNeighbor* temp2;
    while(temp1)
        {
        // as long as there's a backbone
        cout << temp1->node_value;
        if (temp1->next_neighbor)
        {
            // if backbone has a neighbor(s)
            cout << " -> ";
            // first neighbor
            temp2 = temp1->next_neighbor;
            cout<< temp2->node_value;

            while (temp2->next_neighbor)
            {
                // rest of neighbors
                cout << " -> ";
                temp2 = temp2->next_neighbor;
                cout<< temp2->node_value;
            }
        }
        cout << endl;

        // visual display
        if(temp1->next_backbone)
        {
            cout << "---------------------------\n";
        }
        // continue to next backbone on graph table
        temp1 = temp1->next_backbone;
    }
    cout << endl;
}

// depthfirstsearch function definition
void GraphTable::depthFirstSearch(int source, int destination)
{
    // stack of nodes to look at
    Stack<NodeTypeBackbone*> nodeStack;
    // stack of nodes visited
    Stack<NodeTypeBackbone*> visitedNodeStack;
    // u node
    NodeTypeBackbone* currentNode = node;
    // v node
    NodeTypeBackbone* neighborNode;
    // keeps track of neighbor
    NodeTypeNeighbor* current_neighbor;

    while(currentNode)
    {
        // checks to see if starting node is valid
        // if starting node exists in graph table, continue
        if(currentNode->node_value == source)
        {
            // poor practice
            break;
        }
        else if(!currentNode->next_backbone && currentNode->node_value != source)
        {
            // if starting node doesn't exist, end
            cout << "Node " << source << " is not a valid starting point.\n";
            return;
        }
        else 
        {
            // keep moving down the backbone
            currentNode = currentNode->next_backbone;
        }
    }

    cout << "Depth First Search:\n";

    nodeStack.push(currentNode);
    //cout << currentNode->node_value << " has been pushed into nodeStack.\n";

    // Step 1
    while(!nodeStack.isEmpty())
    {
        if(!visitedNodeStack.inStack(currentNode))
        {
            cout << currentNode->node_value << " -> ";
            if(currentNode->node_value == destination)
            {
                cout << "\n\nThe mouse can reach the cheese from node "
                    << source << " to node " << destination << ".\n\n";
                break;
            }
            visitedNodeStack.push(currentNode);
            //cout << currentNode->node_value << " has been pushed into visitedNodeStack.\n";
        }
        current_neighbor = currentNode->next_neighbor;

        while(current_neighbor)
        {
            // Step 2
            neighborNode = node;
            // find starting backbone
            while(neighborNode->node_value != current_neighbor->node_value)
            {
                neighborNode = neighborNode->next_backbone;
            }
            //cout << "nodeStack: \n";
            //nodeStack.printall();
            //cout << "visitedNodeStack: \n";
            //visitedNodeStack.printall();
            //cout << neighborNode->node_value << endl;
            if(!visitedNodeStack.inStack(neighborNode))
            {
                // Step 3
                nodeStack.push(neighborNode);
                //cout << neighborNode->node_value << " has been pushed into nodeStack.\n";
                currentNode = neighborNode;
                break;
            }
            current_neighbor = current_neighbor->next_neighbor;
        }

        if(!current_neighbor)
        {
            // Step 4
            currentNode = nodeStack.peek();
            nodeStack.pop();
            //cout << currentNode->node_value << " has been popped from nodeStack.\n";
            if(!nodeStack.isEmpty())
                currentNode = nodeStack.peek();
        }
    }
    // no path found
    if(nodeStack.isEmpty() && currentNode->node_value != destination)
    {
        cout << "The mouse cannot reach the cheese from node "
                << source << " to node " << destination << ".\n";
    }
}
