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

const string file_name = kDataPath + "test.bin";

void test_binary_encoding() {
    test_unary();
    test_gamma();
    test_delta();
    test_omega();
    test_string();
    test_all();
}

void test_unary() {
    cout << "Testing unary coding ..." << endl;
    BinaryFileWriter writer;

    if (!writer.open(file_name + "_unary")) {
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
    if (!reader.open(file_name + "_unary")) {
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

    if (!writer.open(file_name + "_gamma")) {
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
    if (!reader.open(file_name + "_gamma")) {
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

    if (!writer.open(file_name + "_delta")) {
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
    if (!reader.open(file_name + "_delta")) {
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

    if (!writer.open(file_name + "omega")) {
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
    if (!reader.open(file_name + "omega")) {
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

void test_string() {
    cout << "Testing encoding string ..." << endl;
    BinaryFileWriter writer;

    if (!writer.open(file_name + "_string")) {
        return;
    }

    int n = 8;
    string a[] = {
        "cháy tiệm may, cả khu phố náo loạn.",
        "Sau vụ cháy nằm ngay khu dân cư và gần chợ",
        "Sau vụ cháy năm ngay trong khu dân cư và đối diện chợ Tân Đình",
        "Nhận được tin báo, lực lượng phòng cháy chữa cháy quận ba",
        "Nhận được tin báo, lực lượng phòng cháy chữa cháy quận ba",
        "sau, vụ hỏa hoạn đã",
        " hoàn toàn. Cơ quan chức",
        "đang làm rõ nguyên nhân và thiệt hai do vụ cháy trên gây ra"
    };

    for (int i = 0; i < n; ++i) {
        writer.write_string(a[i]);
    }
    writer.close();

    BinaryFileReader reader;
    if (!reader.open(file_name + "_string")) {
        return;
    }

    for (int i = 0; i < n; ++i) {
        string s = reader.read_string();
        if (s != a[i]) {
            cerr << "FAILED: " << s << " != " << a[i] << endl;
            return;
        } else {
            if (debug_test_binary_encoding) cout << "OK: " << s << " = " << a[i] << endl;
        }
    }

    cout << "PASSED." << endl;
    reader.close();
}

void test_all() {
    cout << "Testing all ..." << endl;

    int n = 6;
    const string a[] = {"cháy", "năm", "lượng", "nhân", "trên", "Tân Đình"};

    vector<int> numbers;
    vector<string> words;
    vector<int> which;

    int total = 100;

    BinaryFileWriter writer;

    if (!writer.open(file_name + "_all")) {
        return;
    }

    srand(unsigned(time(0)));

    for (int run = 0; run < total; ++run) {
        int t = rand() % 5;
        which.push_back(t);
        if (t == 0) {
            int at = rand() % n;
            words.push_back(a[at]);
            writer.write_string(a[at]);
        } else {
            int number = rand() % 1000000 + 1;
            numbers.push_back(number);
            if (t == 1) writer.write_unary(number);
            else if (t == 2) writer.write_gamma(number);
            else if (t == 3) writer.write_delta(number);
            else writer.write_omega(number);
        }
    }


    writer.close();

    BinaryFileReader reader;
    if (!reader.open(file_name + "_all")) {
        return;
    }

    int inumber = 0, iword = 0;
    for (int run = 0; run < total; ++run) {
        int t = which[run];
        if (t == 0) {
            string s = reader.read_string();
            string t = words[iword++];

            if (s != t) {
                cerr << "FAILED: " << s << " != " << t << endl;
                return;
            } else {
                if (debug_test_binary_encoding) cout << "OK: " << s << " = " << t << endl;
            }
        } else {
            int number = numbers[inumber++];
            int x = -1;

            if (t == 1) x = reader.read_unary();
            else if (t == 2) x = reader.read_gamma();
            else if (t == 3) x = reader.read_delta();
            else x = reader.read_omega();

            if (x != number) {
                cerr << "FAILED: " << x << " != " << number << endl;
                return;
            } else {
                if (debug_test_binary_encoding) cout << "OK: " << x << " = " << number << endl;
            }
        }
    }

    cout << "PASSED." << endl;
    reader.close();
}
