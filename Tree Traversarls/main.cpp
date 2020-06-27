#include <iostream>
#include "tree_utils.h"
using namespace std;

int main()
{
    Node * head = createTree();
    parallel_tree_search(head, 20);
    return 0;
}
