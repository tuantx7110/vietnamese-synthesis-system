#Các loại nén dữ liệu nhị phân sử dụng trong chương trình

# Unary Coding #

Một số nguyên dương N được biểu diễn bằng (N-1) bit 0 theo sau là một bit 1.

Ví dụ:

5 => 00001

3 => 001

1 => 1

http://en.wikipedia.org/wiki/Unary_coding

```
void write_unary(int number) {
    write_bits(0, number - 1);
    write_bits(1);
}

```

# Elias Gamma Coding #

Một số nguyên dương N được mã hoá như sau:

- Tính số mũ cao nhất trong biểu diễn nhị phân của N, gọi là K

- Thêm vào trước dãy nhị phân này K bit 0.

Ví dụ:

6   => 00110

10 => 0001010

http://en.wikipedia.org/wiki/Elias_gamma_coding

```
void write_gamma(int number) {
    int n = 0;
    for (int temp = number; temp > 0; temp >>= 1) ++n;
    --n;

    write_bits(0, n);
    for (int i = n; i >= 0; --i) {
        write_bits(bit_at(number, i));
    }
}

```

# Elias Delta Coding #

Một số nguyên dương N được mã hoá như sau:

- Tính số mũ cao nhất trong biểu diễn nhị phân của N, gọi là K

- Viết (K + 1) bằng Elias Gamma coding

- Viết tiếp K bit ở cuối trong biểu diễn nhị phân của N

Ví dụ:

6 => 01110

13 => 00100101

http://en.wikipedia.org/wiki/Elias_delta_coding

```
void write_delta(int number) {
    int n = 0;
    for (int temp = number; temp > 0; temp >>= 1) ++n;
    n--;

    write_gamma(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        write_bits(bit_at(number, i));
    }
}

```

# Elias Omega Coding #

Một số nguyên dương N được mã hoá như sau:

- Nếu N = 1, nó được mã hoá bằng một bit 0

- Nếu N > 1 thì lặp lại quá trình sau cho tới khi N = 1, rồi chèn thêm bit 0 vào cuối.

> + Mã hoá cho số mũ cao nhất K, trong biểu diễn nhị phân của N

> + Sau đó chèn thêm K bit ở cuối trong biểu diễn nhị phân của N

Ví dụ:

17 => 10 100 10001 0

1000 => 11 1001 1111101000 0

http://en.wikipedia.org/wiki/Elias_omega_coding

```
void write_omega(int number) {
    write_recursive_omega(number);
    write_bits(0);
}

void write_recursive_omega(int number) {
    if (number == 1) return;

    int n = 0;
    for (int temp = number; temp > 0; temp >>= 1) ++n;
    write_recursive_omega(n - 1);

    for (int i = n - 1; i >= 0; --i) {
        write_bits(bit_at(number, i));
    }
}
```