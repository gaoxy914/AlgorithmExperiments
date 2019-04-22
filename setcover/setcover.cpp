#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
extern "C"{
#include "glpk.h"
}

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

vector<int> v_intersection(vector<int> &va, vector<int> &vb) {
    vector<int> vc(va.size() + vb.size());
    vector<int>::iterator it;
    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());
    it = set_intersection(va.begin(), va.end(), vb.begin(), vb.end(), vc.begin());
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

vector<int> gen_s(vector<int> X, int *xrn) {
    vector<int> s;
    // int n = rand()%X.size() + 1;
    // n = n*6/10;
    int n = rand()%20+1;
    for (int i = 0; i < n; i++) s.push_back(X[xrn[i]]);
    return s;
}

vector<int> gen_x(int count) {
    vector<int> X;
    for (int i = 0; i < count; i++) X.push_back(i);
    return X;
}

vector<vector<int> > gen_data(vector<int> X, int countf) {
    vector<vector<int> > S;
    vector<int> XS = X, US;
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
    int left = countf - S.size();
    while (left > 0) {
        int *usrn = no_repeat_rn(US.size());
        vector<int> s = gen_s(US, usrn);
        S.push_back(s);
        delete usrn;
        left--;
    }
    return S;
}

vector<int> max_union(vector<int> U, vector<vector<int> > F) {
    int maxsize = 0, index = 0;
    for (int i = 0; i < F.size(); i++) {
        vector<int> uf = v_intersection(U, F[i]);
        if (uf.size() > maxsize) {
            maxsize = uf.size();
            index = i;
        }
    }
    return F[index];
}

vector<vector<int> > greedy_sc(vector<int> X, vector<vector<int> > F) {
    vector<int> U = X;
    vector<vector<int> > C;
    while (U.size() != 0) {
        // std::cout << U.size() << std::endl;
        vector<int> S = max_union(U, F);
        U = v_difference(U, S);
        C.push_back(S);
    }
    return C;
}

int get_f(vector<int> X, vector<vector<int> > F) {
    int count = 0, maxcount = 0;
    for (int i = 0; i < X.size(); i++) {
        for (int j =  0; j < F.size(); j++) {
            vector<int> S = F[j];
            vector<int>::iterator it = find(S.begin(), S.end(), X[i]);
            if (it != S.end()) count++;
        }
        if (count > maxcount) maxcount = count;
        count = 0;
    }
    return maxcount;
}

vector<double> cal_lp(vector<int> X, vector<vector<int> > F) {
    vector<double> x;
    int n = X.size();
    int m = F.size();
    // std::cout << n << m << std::endl;
initialize:
    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_obj_dir(lp, GLP_MIN);
auxiliary_variables_rows:
    glp_add_rows(lp, n);
    for (int i = 1; i <= n; i++) glp_set_row_bnds(lp, i, GLP_LO, 1.0, 0.0);
variables_columns:
    glp_add_cols(lp, m);
    for (int i = 1; i <= m; i++) glp_set_col_bnds(lp, i, GLP_DB, 0.0, 1.0);
to_minimize:
    for (int i = 1; i <= m; i++) glp_set_obj_coef(lp, i, 1.0);
constrant_matrix:
    int size = m*n;
    // std::cout << size << std::endl;
    int *ia = new int[size + 1];
    int *ja = new int[size + 1];
    // std::cout << size << std::endl;
    double *ar = new double[size + 1];
    // std::cout << size << std::endl;
    for (int i = 1; i <= n; i++) {
        // std::cout << i << std::endl;
        for (int j = 1; j <= m; j++) {
            int k = (i - 1)*m + j;
            // std::cout << k << std::endl;
            ia[k] = i;
            ja[k] = j;
            vector<int> f = F[j-1];
            vector<int>::iterator it = find(f.begin(), f.end(), i-1);
            if (it != f.end()) ar[k] = 1;
            else ar[k] = 0;
        }
    }
    glp_load_matrix(lp, size, ia, ja, ar);
calculate:
    glp_simplex(lp, NULL);
output:
    // std::cout << "opt:" << glp_get_obj_val(lp) << std::endl;
    for (int i = 1; i <= m; i++) x.push_back(glp_get_col_prim(lp, i));
cleanup:
    glp_delete_prob(lp);
    return x;
}

/**
 * g++ -lglpk -o
 */
vector<vector<int> > lp_sc(vector<int> X, vector<vector<int> > F) {
    vector<vector<int> > C;
    vector<double> x = cal_lp(X, F);
    int f = get_f(X, F);
    // std::cout << f << std::endl;
    for (int i = 0; i < x.size(); i++) {
        // std::cout << "i " << x[i] << std::endl;
        if (x[i] >= 1.0/f) C.push_back(F[i]);
    }
    return C;
}

void test(int type, int count) {
    vector<int> X = gen_x(count);
    vector<vector<int> > F = gen_data(X, count), C;
    clock_t start, end;
    double time;
    switch (type) {
        case 1:
            start = clock();
            C = greedy_sc(X, F);
            end = clock();
            time = (double)(end - start)/CLOCKS_PER_SEC;
            std::cout << "Total Time: " << time << "s, C's size : " << C.size() << std::endl;
            break;
        case 2:
            start = clock();
            C = lp_sc(X, F);
            end = clock();
            time = (double)(end - start)/CLOCKS_PER_SEC;
            std::cout << "Total Time: " << time << "s, C's size : " << C.size() << std::endl;
            break;
        default:
            std::cout << "invalid input" << std::endl;
    }
}

int main(int argc, const char *argv[])
{
    srand((int)time(NULL));
    /* vector<int> va, vb; */
    // for (int i = 0; i < 10; i++) va.push_back(i);
    // for (int i = 0; i < 15; i++) vb.push_back(i);
    // va = v_difference(va, vb);
    /* for (int i = 0; i < va.size(); i++) std::cout << va[i] << std::endl; */
    /* vector<int> X; */
    // vector<vector<int> > S;
    // for (int i = 0; i < 500; i++) X.push_back(i);
    // S = gen_data(X, 500);
    // for (int i = 0; i < S.size(); i++) {
        // std::cout << "S" << i << std::endl;
        // vector<int> s = S[i];
        // for (int j = 0; j < s.size(); j++) {
            // std::cout << s[j] << " ";
        // }
        // std::cout << std::endl;
    // }
    /* vector<vector<int> > C = greedy_sc(X, S); */
    // vector<vector<int> > C = lp_sc(X, S);
    /* std::cout << "C size:" << C.size() << std::endl; */
    // for (int i = 0; i < C.size(); i++) {
        // vector<int> c = C[i];
        // std::cout << "C" << i << " size " << c.size() << std::endl;
        // for (int j = 0; j < c.size(); j++) {
            // std::cout << c[j] << " ";
        // }
        // std::cout << std::endl;
    /* } */
    // std::cout << get_f(X, S) << std::endl;
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
    /* vector<int> S; */
    // for (int i = 0; i < 30; i++) S.push_back(i);
    // vector<int>::iterator it;
    // it = find(S.begin(), S.end(), 35);
    /* std::cout << *it << std::endl; */
    // std::cout << glp_version() << std::endl;
    test(1, 1000);
    return 0;
}
