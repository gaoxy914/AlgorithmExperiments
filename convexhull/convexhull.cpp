#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

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

/* vector<point> enumerate(vector<point> &Q) */
// {

/* } */

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
    if (val == 0) return p1->x > p2->x ? 1 : -1;
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

int main(int argc, const char *argv[])
{
    point A = {2, 0};
    point B = {1, 1};
    point C = {-1, 0};
    point D = {0, -1};
    point E = {1, 0};
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
    vector<point> S = graham_scan(Q);
    for (int i = 0; i < S.size(); i++) {
        std::cout <<"(" << S[i].x << ", " << S[i].y << ")" << std::endl;
    }
    return 0;
}
