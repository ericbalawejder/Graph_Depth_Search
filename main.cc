#include "depth_first_search.h"

int main()
{
    GraphTable a;
    a.make_graphtable();
    a.printAll();
	// depthFirstSearch(source, destination)
    a.depthFirstSearch(25, 1);
	
	// reverse depthfirstsearch(destination, source) 
	//a.depthFirstSearch(1, 25);
    return 0;
}