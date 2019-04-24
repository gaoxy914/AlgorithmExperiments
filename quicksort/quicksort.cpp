#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <fstream>

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


void check_quicksort(vector<int> &v, int p, int r)
{
    bool order = true;
    for (int i = p; i < r; i++) {
        if (v[i] > v[i+1]) {
            order = false;
            break;
        }
    }
    if (!order) {
        if (p < r) {
        int q = rand_partition(v, p, r);
        quicksort(v, p, q-1);
        quicksort(v, q+1, r);
        }
    }
}

int randint32()
{
    return (rand()<<17)|(rand()<<2)|(rand());
}

/**
 * 32 bit randonm integer test
 * count : the size of number
 * stl : true, c++ stl sort
 *       false, quicksort
 */
void int32test(int count, bool stl)
{
    std::cout << "start to generate " << count << " int32 number."<< std::endl;
    vector<int> v;
    for (int i = 0; i < count; i++) {
        v.push_back(randint32());
    }
    if (!stl) {
        std::cout << "start to test quicksort." << std::endl;
        clock_t start = clock();
        quicksort(v, 0, count-1);
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    } else {
        std::cout << "start to test C++ STL sort." << std::endl;
        clock_t start = clock();
        sort(v.begin(), v.end());
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    }
}


/**
 * all 1 test
 * count : the size of number
 * stl : true, c++ stl sort
 *       false, quicksort
 */
void all1test(int count, bool stl)
{
    std::cout << "start to generate " << count << " 1."<< std::endl;
    vector<int> v;
    for (int i = 0; i < count; i++) {
        v.push_back(1);
    }
    if (!stl) {
        std::cout << "start to test check_quicksort." << std::endl;
        clock_t start = clock();
        check_quicksort(v, 0, count-1);
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    } else {
        std::cout << "start to test C++ STL sort." << std::endl;
        clock_t start = clock();
        sort(v.begin(), v.end());
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    }
    /* for (int i = 0; i < count; i++) { */
        // cout << v[i] << " ";
    // }
    /* cout << endl; */
}


/**
 * x percents 1 test
 * count : the size of number
 * x : percents of 1
 * stl : true, c++ stl sort
 *       false, quicksort
 */
void x1test(int count, int x, bool stl)
{
    std::cout << "start to generate " << count << " number: " << x << "% 1, " << 100-x << "% int32 number."<< std::endl;
    vector<int> v;
    int pivot = count/100*x;
    for (int i = 0; i < count; i++) {
        if (i < pivot) {
            v.push_back(1);
        } else {
            v.push_back(randint32());
        }
    }
    if (!stl) {
        std::cout << "start to test quicksort." << std::endl;
        clock_t start = clock();
        quicksort(v, 0, count-1);
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    } else {
        std::cout << "start to test C++ STL sort." << std::endl;
        clock_t start = clock();
        sort(v.begin(), v.end());
        clock_t end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Total Time:" << time << "s" << endl;
    }
}

void test_to_file(int type, int round) {
    ofstream out;
    int unit = 2000000/round;
    clock_t start, end;
    double time1, time2;
    switch (type) {
        case 1:
            out.open("time.txt");
            for (int i = 1; i <= round; i++) {
                int n = i*unit;
                vector<int> v;
                for (int j = 0; j < n; j++) {
                    v.push_back(randint32());
                }
                start = clock();
                quicksort(v, 0, n-1);
                end = clock();
                time1 = (double)(end - start)/CLOCKS_PER_SEC*1000;
                v.clear();
                for (int j = 0; j < n; j++) {
                    v.push_back(randint32());
                }
                start = clock();
                sort(v.begin(), v.end());
                end = clock();
                time2 = (double)(end - start)/CLOCKS_PER_SEC*1000;
                out << i << " " << time1 << " " << time2 << endl;
            }
            out.close();
            break;
        case 2:
            out.open("time.txt");
            for (int i = 5; i <= 10; i++) {
                vector<int> v;
                int pivot = 1000/100*10*i;
                for (int j = 0; j < 1000; j++) {
                    if (j < pivot) {
                        v.push_back(1);
                    } else {
                        v.push_back(randint32());
                    }
                }
                start = clock();
                quicksort(v, 0, v.size()-1);
                end = clock();
                time1 = (double)(end - start)/CLOCKS_PER_SEC*1000;
                v.clear();
                for (int j = 0; j < 1000; j++) {
                    if (j < pivot) {
                        v.push_back(1);
                    } else {
                        v.push_back(randint32());
                    }
                }
                start = clock();
                sort(v.begin(), v.end());
                end = clock();
                time2 = (double)(end - start)/CLOCKS_PER_SEC*1000;
                out << i*10 << " " << time1 << " " << time2 << endl;
            }
            out.close();
            break;
        default:
            std::cout << "invalid input." << std::endl;
    }
}

int main(int argc, const char *argv[])
{
    srand((int)time(NULL));
    /* int a[] = {3, 5, 1, 9, 7, 6, 4, 2, 8}; */
    // vector<int> v(a, a+9);
    // quicksort(v, 0, v.size()-1);
    // for (int i = 0; i < v.size(); i++) {
        // cout << v[i] << " ";
    // }
    /* cout << endl; */
    /* cout << sizeof(int); */
    // for (int i = 1; i < 100; i++) int32test(10000*i, false);
    // all1test(1000000, false);
    // for (int i = 5; i < 11; i++) x1test(5000, 10*i, true);
    // x1test(10000, 100, false);
    // test_to_file(2, 10);
    return 0;
}

