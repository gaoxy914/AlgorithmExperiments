#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

typedef struct {
    int x;
    int y;
} point;

point pminus(point p, point q) {
    point r = {p.x - q.x, p.y - q.y};
    return r;
}

point pplus(point p, point q) {
    point r = {p.x + q.x, p.y + q.y};
    return r;
}

void swap(point &p, point &q) {
    point r = p;
    p = q;
    q = r;
}

int crossproduct(point p, point q) {
    return p.x*q.y - q.x*p.y;
}

bool intrain(point a, point b, point c, point d) {
    int cp1 = crossproduct(pminus(b, a), pminus(c, a));
    /* std::cout << cp1 << std::endl; */
    int cp2 = crossproduct(pminus(c, a), pminus(d, a));
    /* std::cout << cp2 << std::endl; */
    int cp3 = crossproduct(pminus(d, a), pminus(b, a));
    /* std::cout << cp3 << std::endl; */
    return cp1*cp2 >= 0 && cp1*cp3 >= 0;
}

bool notline(point a, point b, point c) {
    point p = pminus(b, a);
    point q = pminus(c, a);
    if (crossproduct(p, q) == 0) {
        if (a.x > b.x && a.x > c.x) return false;
        if (a.x < b.x && a.x < c.x) return false;
        if (a.y > b.y && a.y > c.y) return false;
        if (a.y < b.y && a.y < c.y) return false;
    }
    return true;
}

bool notequal(point a, point b, point c, point d) {
    if (a.x == b.x && a.y == b.y) return false;
    if (a.x == c.x && a.y == c.y) return false;
    if (a.x == d.x && a.y == d.y) return false;
    if (b.x == c.x && b.y == c.y) return false;
    if (b.x == d.x && b.y == d.y) return false;
    if (c.x == d.x && c.y == d.y) return false;
    return true;
}

vector<point> enumerate(vector<point> &Q) {
    /* ofstream fout; */
    /* fout.open("log.txt"); */
    vector<point> S;
    int convexhull[Q.size()];
    for (int i = 0; i < Q.size(); i++) {
        convexhull[i] = 1;
    }
    int i = 0;
    while (i < Q.size()) {
        for (int j = 0; j < Q.size()-2; j++) {
            for (int k = j+1; k < Q.size()-1; k++) {
                for (int l = k+1; l < Q.size(); l++) {
                    if (i != j && i != k && i != l && notline(Q[i], Q[j], Q[k]) &&
                            convexhull[j] && convexhull[k] && convexhull[l]) {
                        if (intrain(Q[i], Q[j], Q[k], Q[l])) {
                            convexhull[i] = 0;
                            /* fout << i << "," << j << "," << k << "," << l << std::endl; */
                            // fout <<"(" << Q[i].x << ", " << Q[i].y << ")" << std::endl;
                            // fout <<"(" << Q[j].x << ", " << Q[j].y << ")" << std::endl;
                            // fout <<"(" << Q[k].x << ", " << Q[k].y << ")" << std::endl;
                            // fout <<"(" << Q[l].x << ", " << Q[l].y << ")" << std::endl;
                            // int cp1 = crossproduct(pminus(Q[j], Q[i]), pminus(Q[k], Q[i]));
                            // int cp2 = crossproduct(pminus(Q[k], Q[i]), pminus(Q[l], Q[i]));
                            // int cp3 = crossproduct(pminus(Q[l], Q[i]), pminus(Q[j], Q[i]));
                            // fout << cp1 << std::endl;
                            // fout << cp2 << std::endl;
                            // fout << cp3 << std::endl;
                            // fout << cp1*cp2 << std::endl;
                            // fout << cp1*cp3 << std::endl;
                            // if (cp1*cp2 >= 0) fout << "cp1 x cp2 >= 0" << std::endl;
                            // if (cp1*cp3 >= 0) fout << "cp1 x cp3 >= 0" << std::endl;
                            /* fout << intrain(Q[i], Q[j], Q[k], Q[l]) << std::endl; */
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
    /* fout.close(); */
    for (int i = 0; i < Q.size(); i++) {
        if (convexhull[i]) S.push_back(Q[i]);
    }
    return S;
}

int get_miny(vector<point> &Q) {
    int min = 0;
    for (int i = 1; i < Q.size(); i++) {
        if ((Q[i].y < Q[min].y) ||
                (Q[i].y == Q[min].y && Q[i].x < Q[min].x)) {
            min = i;
        }
    }
    return min;
}

int dist(point p) {
    return p.x*p.x + p.y*p.y;
}

int compare(const void *vp1, const void *vp2) {
    point *p1 = (point *) vp1;
    point *p2 = (point *) vp2;
    int cp = crossproduct(*p1, *p2);
    if (cp == 0) {
        if (p1->x*p2->x >= 0 && p1->y*p2->y >= 0) return dist(*p1) > dist(*p2) ? 1 : -1;
        else return p1->x > 0 ? -1 : 1;
    }
    return cp > 0 ? -1 : 1;
}

void sort(vector<point> &Q) {
    int min = get_miny(Q);
    swap(Q[0], Q[min]);
    for (int i = 1; i < Q.size(); i++) {
        Q[i] = pminus(Q[i], Q[0]);
    }
    qsort(&Q[1], Q.size()-1, sizeof(point), compare);
    for (int i = 1; i < Q.size(); i++) {
        Q[i] = pplus(Q[i], Q[0]);
    }
}

void print(vector<point> Q) {
    for (int i = 0; i < Q.size(); i++) {
        std::cout << "(" << Q[i].x << "," << Q[i].y << ")" << std::endl;
    }
}


vector<point> graham_scan(vector<point> &Q) {
    vector<point> S;
    sort(Q);
    /* std::cout << "sorted Q:" << std::endl; */
    /* print(Q); */
    int j = 1;
    while (j < Q.size()-1 && crossproduct(pminus(Q[j], Q[0]), pminus(Q[j+1], Q[j])) == 0) {
        // std::cout << j << std::endl;
        j++;
    }
    /* std::cout << j << std::endl; */
    if (j == Q.size()-1) {
        S.push_back(Q[0]);
        S.push_back(Q[j]);
        /* std::cout << "S in graham_scan:" << std::endl; */
        /* print(S); */
        return S;
    }
    S.push_back(Q[0]);
    S.push_back(Q[j]);
    S.push_back(Q[j+1]);
    for (int i = j+2; i < Q.size(); i++) {
        while (crossproduct(pminus(S[S.size()-1], S[S.size()-2]),
                    pminus(Q[i], S[S.size()-1])) <= 0) {
            S.pop_back();
        }
        S.push_back(Q[i]);
    }
    // print(S);
    return S;
}

int partition(vector<point> &Q, int start, int end, int k) {
    int index = rand()%(end-start+1) + start;
    swap(Q[index], Q[end]);
    int pivot = Q[end].x;
    int j = start - 1;
    for (int i = start; i < end; i++) {
        if (Q[i].x <= pivot) swap(Q[i], Q[++j]);
    }
    swap(Q[++j], Q[end]);
    bool flagx = true;
    if (j == end) {
        for (int i = start+1; i <= end; i++) {
            if (Q[start].x != Q[i].x) flagx = false;
        }
    }
    if (flagx) return (start + end)/2;
    if (j - start + 1 == k) return j;
    else if (j - start + 1 < k) return partition(Q, j+1, end, k-(j-start+1));
    else return partition(Q, start, j-1, k);
}

vector<point> merge(vector<point> &CH1, vector<point> &CH2) {
    CH1.insert(CH1.end(), CH2.begin(), CH2.end());
    // std::cout << "union of CH1 and CH2:" << std::endl;
    // print(CH1);
    return graham_scan(CH1);
}


vector<point> convexhull(vector<point> &Q, int start, int end) {
    // std::cout << start << "," << end << std::endl;
    if (end - start + 1 <= 3) {
        // std::cout << "|S| <= 3 return S" << std::endl;
        vector<point> S;
        for (int i = start; i <= end; i++) S.push_back(Q[i]);
        return S;
    }
    int p = partition(Q, start, end, (end - start + 1)/2);
    vector<point> CH1 = convexhull(Q, start, p);
    /* std::cout << "CH1:" << std::endl; */
    /* print(CH1); */
    vector<point> CH2 = convexhull(Q, p+1, end);
    /* std::cout << "CH2:" << std::endl; */
    /* print(CH2); */
    return merge(CH1, CH2);
}

vector<point> gen_data(int count) {
    vector<point> Q;
    for (int i = 0; i < count; i++) {
        point q = {rand()%100, rand()%100};
        Q.push_back(q);
    }
    return Q;
}

void test(int type, int count) {
    vector<point> Q = gen_data(count);
    vector<point> S;
    clock_t start, end;
    double time;
    ofstream fout;
    switch (type) {
        case 1:
            start = clock();
            S = enumerate(Q);
            end = clock();
            time = (double)(end - start)/CLOCKS_PER_SEC;
            cout << "Total Time:" << time << "s, S's size : " << S.size() << endl;
            break;
        case 2:
            start = clock();
            S = graham_scan(Q);
            end = clock();
            time = (double)(end - start)/CLOCKS_PER_SEC;
            cout << "Total Time:" << time << "s, S's size : " << S.size() << endl;
            break;
        case 3:
            start = clock();
            S = convexhull(Q, 0, Q.size()-1);
            end = clock();
            time = (double)(end - start)/CLOCKS_PER_SEC;
            cout << "Total Time:" << time << "s, S's size : " << S.size() << endl;
            break;
        case 4:
           /*  S = enumerate(Q); */
            // sort(S);
            // std::cout << "convexhul size: " << S.size() << std::endl;
            // fout.open("point1.txt");
            // for (int i = 0; i < S.size(); i++) {
                // // std::cout << "(" << S[i].x << "," << S[i].y << ")" << std::endl;
                // fout << "(" << S[i].x << "," << S[i].y << ")" << endl;
            /* } */
            // fout.close();
            S = graham_scan(Q);
            // sort(S);
            std::cout << "convexhul size: " << S.size() << std::endl;
            /* fout.open("point2.txt"); */
            // for (int i = 0; i < S.size(); i++) {
                // fout << "(" << S[i].x << "," << S[i].y << ")" << endl;
            // }
            /* fout.close(); */
            S = convexhull(Q, 0, Q.size()-1);
            // sort(S);
            std::cout << "convexhul size: " << S.size() << std::endl;
            /* fout.open("point3.txt"); */
            // for (int i = 0; i < S.size(); i++) {
                // fout << "(" << S[i].x << "," << S[i].y << ")" << endl;
            // }
            /* fout.close(); */
            break;
        default:
            std::cout << "invalid input" << std::endl;
    }
}

int main(int argc, const char *argv[])
{
    srand((int)time(NULL));
    /* point A = {2, 0}; */
    /* point B = {-1, 1}; */
    // point C = {-1, 0};
    /* point D = {0, 0}; */
    // point E = {-2, 2};
    // point F = {-5, 2};
    /* point G = {-5, 1}; */
    /* std::cout << testInTrian(A, B, C, D) << std::endl */;
    /* vector<point> Q; */
    // Q.push_back(A);
    /* Q.push_back(B); */
    // Q.push_back(C);
    /* Q.push_back(D); */
    // Q.push_back(E);
    // Q.push_back(F);
    /* Q.push_back(G); */
    // point E = get_minY(Q);
    /* std::cout << E.y << std::endl; */
    /* std::cout << compare(&C, &B) << std::endl; */
    /* for (int i = 0; i < Q.size(); i++) { */
        // std::cout <<"(" << Q[i].x << ", " << Q[i].y << ")" << std::endl;
    // }
    /* sort(Q); */
    // for (int i = 0; i < Q.size(); i++) {
        // std::cout <<"(" << Q[i].x << ", " << Q[i].y << ")" << std::endl;
    /* } */
    // vector<point> S = convexhull(Q, 0, Q.size()-1);
    /* vector<point> S = graham_scan(Q); */
    /* vector<point> S = enumerate(Q); */
    /* for (int i = 0; i < S.size(); i++) { */
        // std::cout <<"(" << S[i].x << ", " << S[i].y << ")" << std::endl;
    /* } */
    /* int p = partition(Q, 2, 6, 3); */
    // std::cout << Q[p].x << std::endl;
    // for (int i = 0; i < Q.size(); i++) {
        // std::cout << Q[i].x  << ", " << Q[i].y << std::endl;
    /* } */
    /* vector<point> S(Q.begin()+2, Q.begin()+4); */
    // for (int i = 0; i < S.size(); i++) {
        // std::cout << S[i].x << "," << S[i].y << std::endl;
    /* } */
    test(4, 3000);
    // gen_data(10);
    return 0;
}
