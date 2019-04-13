#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

using namespace std;

typedef struct {
    double x;
    double y;
} point;

point pminus(point A, point B)
{
    point C = {B.x-A.x, B.y-A.y};
    return C;
}

point pplus(point A, point B)
{
    point C = {B.x+A.x, B.y+A.y};
    return C;
}
void swap(point &A, point &B)
{
    point p = A;
    A = B;
    B = p;
}

double crossproduct(point A, point B)
{
    return A.x*B.y - B.x*A.y;
}

bool testInTrian(point A, point B, point C, point D)
{
    double cp1 = crossproduct(pminus(A, B), pminus(A, C));
    double cp2 = crossproduct(pminus(A, C), pminus(A, D));
    double cp3 = crossproduct(pminus(A, D), pminus(A, B));
    return cp1*cp2 >= 0 && cp1*cp3 >= 0;
}

vector<point> enumerate(vector<point> &Q)
{
    vector<point> S;
    int i = 0;
    int convexhull[Q.size()];
    while (i < Q.size()) {
        convexhull[i] = 1;
        for (int j = 0; j < Q.size()-2; j++) {
            for (int k = j+1; k < Q.size()-1; k++) {
                for (int l = k+1; l < Q.size(); l++) {
                    if (i != j && i != k && i != l) {
                        if (testInTrian(Q[i], Q[j], Q[k], Q[l])) {
                            convexhull[i] = 0;
                            break;
                        }
                    }
                }
                if (!convexhull[i]) break;
            }
            if (!convexhull[i]) break;
        }
        i++;
    }
    for (int i = 0; i < Q.size(); i++) {
        if (convexhull[i]) S.push_back(Q[i]);
    }
    return S;
}

int get_minY(vector<point> &Q)
{
    int min = 0;
    for (int i = 1; i < Q.size(); i++) {
        if ((Q[i].y < Q[min].y) ||
                (Q[i].y == Q[min].y && Q[i].x < Q[min].x)) {
            min = i;
        }
    }
    return min;
}

int compare(const void *vp1, const void *vp2)
{
    point *p1 = (point *) vp1;
    point *p2 = (point *) vp2;
    double val = crossproduct(*p1, *p2);
    if (val == 0) return abs(p1->x) > abs(p2->x) ? 1 : -1;
    return val > 0 ? -1 : 1;
}

void sort(vector<point> &Q)
{
    int min = get_minY(Q);
    swap(Q[0], Q[min]);
    for (int i = 1; i < Q.size(); i++) {
        Q[i] = pminus(Q[0], Q[i]);
    }
    qsort(&Q[1], Q.size()-1, sizeof(point), compare);
    for (int i = 1; i < Q.size(); i++) {
        Q[i] = pplus(Q[0], Q[i]);
    }
}

vector<point> graham_scan(vector<point> &Q)
{
    vector<point> S;
    sort(Q);
    S.push_back(Q[0]);
    S.push_back(Q[1]);
    S.push_back(Q[2]);
    for (int i = 3; i < Q.size(); i++) {
        while (crossproduct(pminus(S[S.size()-2], S[S.size()-1]),
                    pminus(S[S.size()-2], Q[i])) < 0) {
            S.pop_back();
        }
        S.push_back(Q[i]);
    }
    return S;
}

int partition(vector<point> &Q, int start, int end, int k)
{
    double pivot = Q[end].x;
    int j = start - 1;
    for (int i = start; i < end; i++) {
        if (Q[i].x <= pivot) {
            swap(Q[i], Q[++j]);
        }
    }
    swap(Q[++j], Q[end]);
    if (j - start + 1 == k) return j;
    else if (j - start < k) return partition(Q, j+1, end, k-(j-start+1));
    else return partition(Q, start, j-1, k);
}

vector<point> merge(vector<point> &CH1, vector<point> &CH2)
{
    CH1.insert(CH1.end(), CH2.begin(), CH2.end());
    return graham_scan(CH1);
}

vector<point> convexhull(vector<point> &Q, int start, int end)
{
    if (end - start < 3) {
        vector<point> S(Q.begin()+start, Q.begin()+end+1);
        return S;
    }
    int p = partition(Q, start, end, (end - start + 1)/2);
    // std::cout << p << "," << start << "," << end << std::endl;
    vector<point> CH1 = convexhull(Q, start, p);
    vector<point> CH2 = convexhull(Q, p+1, end);
    return merge(CH1, CH2);
}

vector<point> gen_data(int count)
{
    srand((int)time(NULL));
    vector<point> Q;
    for (int i = 0; i < count; i++) {
        point q = {rand()%100, rand()%100};
        // std::cout << "(" << q.x << "," << q.y <<")" << std::endl;
        Q.push_back(q);
    }
    return Q;
}

void test(int type, int count)
{
    vector<point> Q = gen_data(count);
    vector<point> S;
    clock_t start, end;
    double time;
    switch (type) {
        case 1:
            start = clock();
            enumerate(Q);
            end = clock();
            time = (double)(end - start)/CLOCKS_PER_SEC;
            cout << "Total Time:" << time << "s" << endl;
            break;
        case 2:
            start = clock();
            S = graham_scan(Q);
            end = clock();
            time = (double)(end - start)/CLOCKS_PER_SEC;
            cout << "Total Time:" << time << "s" << endl;
            break;
        case 3:
            start = clock();
            S = convexhull(Q, 0, Q.size()-1);
            end = clock();
            time = (double)(end - start)/CLOCKS_PER_SEC;
            cout << "Total Time:" << time << "s" << endl;
            break;
        default:
            std::cout << "invalid input" << std::endl;
    }
}

int main(int argc, const char *argv[])
{
    point A = {2, 0};
    point B = {-1, 1};
    point C = {-1, 0};
    point D = {0, -1};
    point E = {-2, 2};
    point F = {-0.5, 2};
    point G = {-0.5, 1};
    /* std::cout << testInTrian(A, B, C, D) << std::endl */;
    vector<point> Q;
    Q.push_back(A);
    Q.push_back(B);
    Q.push_back(C);
    Q.push_back(D);
    Q.push_back(E);
    Q.push_back(F);
    Q.push_back(G);
    // point E = get_minY(Q);
    /* std::cout << E.y << std::endl; */
    /* std::cout << compare(&C, &B) << std::endl; */
    /* for (int i = 0; i < Q.size(); i++) { */
        // std::cout <<"(" << Q[i].x << ", " << Q[i].y << ")" << std::endl;
    // }
    // sort(Q);
    // for (int i = 0; i < Q.size(); i++) {
        // std::cout <<"(" << Q[i].x << ", " << Q[i].y << ")" << std::endl;
    /* } */
    // vector<point> S = convexhull(Q, 0, Q.size()-1);
    /* vector<point> S = graham_scan(Q); */
    vector<point> S = enumerate(Q);
    for (int i = 0; i < S.size(); i++) {
        std::cout <<"(" << S[i].x << ", " << S[i].y << ")" << std::endl;
    }
    /* int p = partition(Q, 2, 6, 3); */
    // std::cout << Q[p].x << std::endl;
    // for (int i = 0; i < Q.size(); i++) {
        // std::cout << Q[i].x  << ", " << Q[i].y << std::endl;
    /* } */
    /* vector<point> S(Q.begin()+2, Q.begin()+4); */
    // for (int i = 0; i < S.size(); i++) {
        // std::cout << S[i].x << "," << S[i].y << std::endl;
    /* } */
    // test(2, 1000);
    // gen_data(10);
    return 0;
}
