#include "depth_first_search.h"

int main()
{
    GraphTable graphTable;
    graphTable.make_graphtable();

    // print the table
    graphTable.printAll();

    // depthFirstSearch(source, destination) uses graph_table2.txt (mouse = 25, cheese = 1)
    //graphTable.depthFirstSearch(25, 1);

    // depthFirstSearch(source, destination) uses graph_table.txt (mouse = 1, cheese = 25)
    graphTable.depthFirstSearch(1, 25);

    return 0;
}
