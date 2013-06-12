/*
 * File:   test_binary_encoding.cpp
 * Author: quangpham
 *
 * Created on June 11, 2013, 9:59 AM
 */

#include <vector>
#include <cstdlib>

#include "test_binary_encoding.h"

using namespace std;

const string file_name = "data/test.bin";

void test_binary_encoding() {
    test_unary();
    test_gamma();
    test_delta();
    test_omega();
}

void test_unary() {
    cout << "Testing unary coding ..." << endl;
    BinaryFileWriter writer;

    if (!writer.open(file_name)) {
        return;
    }

    vector<int> a;
    int n = 100;
    srand(unsigned(time(0)));
    for (int i = 0; i < n; ++i) {
        a.push_back(rand() % 1000000 + 1);
    }
    for (int i = 0; i < n; ++i) {
        if (!writer.write_unary(a[i])) {
            cerr << "FAILED write unary " << a[i] << endl;
            return;
        }
    }

    writer.close();

    BinaryFileReader reader;
    if (!reader.open(file_name)) {
        return;
    }

    for (int i = 0; i < n; ++i) {
        int x = reader.read_unary();
        if (x != a[i]) {
            cerr << "FAILED: " << x << " != " << a[i] << endl;
            return;
        } else {
            if (debug_test_binary_encoding) cout << "OK: " << x << " = " << a[i] << endl;
        }
    }

    cout << "PASSED." << endl;
    reader.close();
}

void test_gamma() {
    cout << "Testing gamma coding ..." << endl;
    BinaryFileWriter writer;

    if (!writer.open(file_name)) {
        return;
    }

    vector<int> a;
    int n = 100;
    srand(unsigned(time(0)));
    for (int i = 0; i < n; ++i) {
        a.push_back(rand() % 1000000 + 1);
    }
    for (int i = 0; i < n; ++i) {
        if (!writer.write_gamma(a[i])) {
            cerr << "FAILED write gamma " << a[i] << endl;
            return;
        }
    }

    writer.close();

    BinaryFileReader reader;
    if (!reader.open(file_name)) {
        return;
    }

    for (int i = 0; i < n; ++i) {
        int x = reader.read_gamma();
        if (x != a[i]) {
            cerr << "FAILED: " << x << " != " << a[i] << endl;
            return;
        } else {
        	if (debug_test_binary_encoding) cout << "OK: " << x << " = " << a[i] << endl;
        }
    }

    cout << "PASSED." << endl;
    reader.close();
}

void test_delta() {
    cout << "Testing delta coding ..." << endl;
    BinaryFileWriter writer;

    if (!writer.open(file_name)) {
        return;
    }

    vector<int> a;
    int n = 100;
    srand(unsigned(time(0)));
    for (int i = 0; i < n; ++i) {
        a.push_back(rand() % 1000000 + 1);
    }
    for (int i = 0; i < n; ++i) {
        if (!writer.write_delta(a[i])) {
            cerr << "FAILED write delta " << a[i] << endl;
            return;
        }
    }

    writer.close();

    BinaryFileReader reader;
    if (!reader.open(file_name)) {
        return;
    }

    for (int i = 0; i < n; ++i) {
        int x = reader.read_delta();
        if (x != a[i]) {
            cerr << "FAILED: " << x << " != " << a[i] << endl;
            return;
        } else {
        	if (debug_test_binary_encoding) cout << "OK: " << x << " = " << a[i] << endl;
        }
    }

    cout << "PASSED." << endl;
    reader.close();
}

void test_omega() {
    cout << "Testing omega coding ..." << endl;
    BinaryFileWriter writer;

    if (!writer.open(file_name)) {
        return;
    }

    vector<int> a;
    int n = 100;
    srand(unsigned(time(0)));
    for (int i = 0; i < n; ++i) {
        a.push_back(rand() % 1000000 + 1);
    }
    for (int i = 0; i < n; ++i) {
        if (!writer.write_omega(a[i])) {
            cerr << "FAILED write omega " << a[i] << endl;
            return;
        }
    }

    writer.close();

    BinaryFileReader reader;
    if (!reader.open(file_name)) {
        return;
    }

    for (int i = 0; i < n; ++i) {
        int x = reader.read_omega();
        if (x != a[i]) {
            cerr << "FAILED: " << x << " != " << a[i] << endl;
            return;
        } else {
        	if (debug_test_binary_encoding) cout << "OK: " << x << " = " << a[i] << endl;
        }
    }

    cout << "PASSED." << endl;
    reader.close();
}
