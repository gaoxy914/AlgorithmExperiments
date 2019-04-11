#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int rand_partition(vector<int> &v, int p, int r)
{
    int index = (rand() % (r-p+1))+ p;
    swap(v[index], v[r]);
    int pivot = v[r], i = p - 1;
    for (int j = p; j < r; j++) {
        if (v[j] <= pivot) {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[++i], v[r]);
    return i;
}

void quicksort(vector<int> &v, int p, int r)
{
    if (p < r) {
        int q = rand_partition(v, p, r);
        quicksort(v, p, q-1);
        quicksort(v, q+1, r);
    }
}

int randint32()
{
    return (rand()<<17)|(rand()<<2)|(rand());
}
void int32test(int count, bool type)
{
    vector<int> v;
    for (int i = 0; i < count; i++) {
        v.push_back(randint32());
    }
    if (type) {
        clock_t start = clock();
        quicksort(v, 0, count-1);
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    } else {
        clock_t start = clock();
        sort(v.begin(), v.end());
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    }
    for (int i = 0; i < count; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void all1test(int count, bool type)
{
    vector<int> v;
    for (int i = 0; i < count; i++) {
        v.push_back(1);
    }
    if (type) {
        clock_t start = clock();
        quicksort(v, 0, count-1);
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    } else {
        clock_t start = clock();
        sort(v.begin(), v.end());
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    }
    for (int i = 0; i < count; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void x1test(int count, int x, bool type)
{
    vector<int> v;
    int pivot = count/100*x;
    for (int i = 0; i < count; i++) {
        if (i < pivot) {
            v.push_back(1);
        } else {
            v.push_back(randint32());
        }
    }
    if (type) {
        clock_t start = clock();
        quicksort(v, 0, count-1);
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    } else {
        clock_t start = clock();
        sort(v.begin(), v.end());
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    }
    for (int i = 0; i < count; i++) {
        cout << v[i] << " ";
    }
    cout << endl;

}

int main(int argc, const char *argv[])
{
    srand((int)time(NULL));
    // int a[] = {3, 5, 1, 9, 7, 6, 4, 2, 8};
    // vector<int> v(a, a+9);
    // quicksort(v, 0, v.size()-1);
    // for (int i = 0; i < v.size(); i++) {
        // cout << v[i] << " ";
    // }
    // cout << endl;
    /* cout << sizeof(int); */
    // int32test(10, false);
    // all1test(10, false);
    x1test(100, 20, false);
    return 0;
}

