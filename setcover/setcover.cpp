#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void swap(int &x, int &y) {
    int z = x;
    x = y;
    y = z;
}

/**
 *generate random number without repeat
 */
int *no_repeat_rn(int up) {
    if (up == 0) return nullptr;
    int *rn = new int[up];
    for (int i = 0; i < up; i++) rn[i] = i;
    for (int i =up-1; i > 0; i--) swap(rn[i], rn[rand()%i]);
    return rn;
}

vector<int> v_union(vector<int> &va, vector<int> &vb) {
    vector<int> vc(va.size() + vb.size());
    vector<int>::iterator it;
    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());
    it = set_union(va.begin(), va.end(), vb.begin(), vb.end(), vc.begin());
    vc.resize(it - vc.begin());
    return vc;
}

vector<int> v_difference(vector<int> &va, vector<int> &vb) {
    vector<int> vc(va.size() + vb.size());
    vector<int>::iterator it;
    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());
    it = set_difference(va.begin(), va.end(), vb.begin(), vb.end(), vc.begin());
    vc.resize(it - vc.begin());
    return vc;
}

/**
 * US = S0 + ... + Si
 * XS = X - S
 * xsrn is the random number without repeat and record the item has been choiced of XS.
 * usrn is the same as xsrn
 */
vector<int> gen_s(vector<int> XS, vector<int> US, int *xsrn, int *usrn) {
    vector<int> s;
    if (US.size() == 0) {
        for (int i = 0; i < 20; i++) s.push_back(XS[xsrn[i]]);
        return s;
    }
    if (XS.size() < 20) {
        for (int i = 0; i < XS.size(); i++) s.push_back(XS[i]);
        return s;
    }
    int n = rand()%20 + 1;
    int x = rand()%n + 1;
    for (int i = 0; i < x; i++) s.push_back(XS[xsrn[i]]);
    for (int i = 0; i < n-x; i++) s.push_back(US[usrn[i]]);
    return s;
}

vector<vector<int> > gen_data(vector<int> X) {
    vector<vector<int> > S;
    vector<int> XS = X;
    vector<int> US;
    while (XS.size() > 0) {
        // std::cout << XS.size() << std::endl;
        int *xsrn = no_repeat_rn(XS.size());
        int *usrn = no_repeat_rn(US.size());
        vector<int> s = gen_s(XS, US, xsrn, usrn);
        S.push_back(s);
        delete xsrn;
        delete usrn;
        US = v_union(US, s);
        XS = v_difference(XS, US);
    }
    return S;
}

int main(int argc, const char *argv[])
{
    srand((int)time(NULL));
    /* vector<int> va, vb; */
    // for (int i = 0; i < 10; i++) va.push_back(i);
    // for (int i = 0; i < 15; i++) vb.push_back(i);
    // va = v_difference(va, vb);
    /* for (int i = 0; i < va.size(); i++) std::cout << va[i] << std::endl; */
    vector<int> X;
    vector<vector<int> > S;
    for (int i = 0; i < 50; i++) X.push_back(i);
    S = gen_data(X);
    for (int i = 0; i < S.size(); i++) {
        std::cout << "S" << i << std::endl;
        vector<int> s = S[i];
        for (int j = 0; j < s.size(); j++) {
            std::cout << s[j] << " ";
        }
        std::cout << std::endl;
    }
    /* vector<int> XS, US; */
    // for (int i = 0; i < 50; i++) XS.push_back(i);
    // for (int i = 0; i < 20; i++) US.push_back(i);
    // int a[50], b[20];
    // for (int i = 0; i < 50; i++) a[i] = i;
    // for (int i = 0; i < 20; i++) b[i] = i;
    // XS = v_difference(XS, US);
    // vector<int> s = gen_s(XS, US, a, b);
    // for (int i = 0; i < s.size(); i++) {
        // std::cout << s[i] << std::endl;
    // }
    // int *p = no_repeat_rn(10);
    /* for (int i = 0; i < 10; i++) std::cout << p[i] << std::endl; */
    return 0;
}
