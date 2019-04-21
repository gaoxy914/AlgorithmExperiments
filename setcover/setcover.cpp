#include <iostream>
#include <vector>
#include <set>
#include <time.h>
#include <stdlib.h>

using namespace std;

/* vector<set<int> > gen_data(set<int> X) { */

/* } */


/**
 * S = union of S0 to Si
 */
set<int> gen_s(set<int> X, set<int> S) {
    set<int> c;
    set_difference(X.begin(), X.end(), S.begin(), S.end(), inserter(c, c.begin()));
    if (c.size() < 20) return c;
    int n = rand()%20 + 1;
    int x = rand()%n + 1;
    set<int> s;
    set<int>::iterator it = c.begin();
    int index = 0;
    for (int i = 0; i < x; i++) {
        index = rand()%c.size();
    }
}


int main(int argc, const char *argv[])
{
    srand((int)time(NULL));
    return 0;
}
