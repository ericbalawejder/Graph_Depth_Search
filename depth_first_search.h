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
	// c_str() returns a pointer to an array of characters that reprevioussent the string object 
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
                    //cout << n << " "; // for monitoring purposes
                    stream >> n;
                    //cout << n << " "; // for monitoring purposes
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
    else cout << "Unable to open file. \n\n";    
}   

// printAll function definition
void GraphTable::printAll() 
{   
    // keeps track of backbone
	NodeTypeBackbone* tmp1 = node; 
	// keeps track of neighbor
    NodeTypeNeighbor* tmp2;    
    while(tmp1) 
		{   
		// as long as there's a backbone
        cout << tmp1->node_value;
        if (tmp1->next_neighbor) 
		{   // if backbone has a neighbor(s)
            cout << " -> ";  
            // first neighbor
			tmp2 = tmp1->next_neighbor; 
            cout<< tmp2->node_value;
			
            while (tmp2->next_neighbor) 
			{    
				// rest of neighbors
                cout << " -> ";  // visual purpose
                tmp2 = tmp2->next_neighbor;
                cout<< tmp2->node_value;
            }
        }
        cout << endl;
		
		// visual purpose
        if(tmp1->next_backbone)
		{ 
            cout << "---------------------------\n";
		}
		// continue to next backbone on graph table
        tmp1 = tmp1->next_backbone; 
    }
    cout << endl;
}   

// depthfirstsearch function definition
void GraphTable::depthFirstSearch(int source, int destination)
{ 
	// stack of nodes to look at
    Stack<NodeTypeBackbone*> SL;
	// stack of nodes visited
    Stack<NodeTypeBackbone*> ST;    
    // u node
	NodeTypeBackbone* u = node;    
    // v node
	NodeTypeBackbone* v;           
    // keeps track of neighbor
	NodeTypeNeighbor* current_neighbor;    
    
    while(u) 
	{  
		// checks to see if starting node is valid
		// if starting node exists in graph table, continue
        if(u->node_value == source)
		{   
            // poor practice
			break;
		}
        else if(!u->next_backbone && u->node_value != source)
		{  
			// if starting node doesn't exist, end
            cout << "Node " << source << " is not a valid starting point.\n";
            return;
        }
        else 
		{   
			// keep moving down the backbone
            u = u->next_backbone;
		}
    }
	
    cout << "Depth First Search:\n";
	
    SL.push(u); 
    //cout << u->node_value << " has been pushed into SL.\n"; 
	
	// Step 1
    while(!SL.isEmpty()) 
	{  
        if(!ST.inStack(u)) 
		{ 
            cout << u->node_value << " -> ";  
            if(u->node_value == destination) 
			{  
                cout << "\nThe mouse can reach the cheese from node " 
						<< source << " to node " << destination << ".\n";
                break;
            }
            ST.push(u); 
            //cout << u->node_value << " has been pushed into ST.\n"; 
        }
        current_neighbor = u->next_neighbor;
		
        while(current_neighbor) 
		{   
			// Step 2
            v = node;
			// find starting backbone
            while(v->node_value != current_neighbor->node_value) 
			{  
                v = v->next_backbone;
			}
            //cout << "SL: \n";   
            //SL.printall();
            //cout << "ST: \n";  
            //ST.printall();
            //cout << v->node_value << endl;
            if(!ST.inStack(v))
			{ 
				// Step 3
                SL.push(v);
                //cout << v->node_value << " has been pushed into SL.\n";
                u = v;
                break;
            }
            current_neighbor = current_neighbor->next_neighbor;
        }
		
        if(!current_neighbor) 
		{ 
			// Step 4
            u = SL.peek();
            SL.pop();
            //cout << u->node_value << " has been popped from SL.\n";
            if(!SL.isEmpty())
                u = SL.peek();
        }
    }
    if(SL.isEmpty() && u->node_value != destination)
	{
        cout << "The mouse cannot reach the cheese from node " 
				<< source << " to node " << destination << ".\n";
	}
}   