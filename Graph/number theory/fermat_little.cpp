#include <iostream>
#include <cmath>

// 计算 (base^exponent) % modulus
long long power_mod(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base %= modulus;
    while (exponent > 0) {
        if (exponent & 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent >>= 1;
    }
    return result;
}

// 检查费马小定理
bool check_fermat_little_theorem(long long a, long long p) {
    // 检查 a^(p-1) ≡ 1 (mod p)
    bool condition1 = (power_mod(a, p-1, p) == 1);
    
    // 检查 a^p ≡ a (mod p)
    bool condition2 = (power_mod(a, p, p) == a % p);
    
    return condition1 && condition2;
}

// 简单的素性测试（仅用于演示，不适用于大数）
bool is_prime(long long n) {
    if (n <= 1) return false;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    // 测试一些例子
    long long primes[] = {5, 7, 11, 13, 17, 19, 23, 29, 31};
    long long a_values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (long long p : primes) {
        if (!is_prime(p)) {
            std::cout << p << " is not prime. Skipping." << std::endl;
            continue;
        }
        
        std::cout << "Testing for prime p = " << p << ":" << std::endl;
        
        for (long long a : a_values) {
            bool result = check_fermat_little_theorem(a, p);
            std::cout << "  a = " << a << ": " << (result ? "Verified" : "Failed") << std::endl;
            
            if (!result) {
                std::cout << "    a^(p-1) mod p = " << power_mod(a, p-1, p) << std::endl;
                std::cout << "    a^p mod p = " << power_mod(a, p, p) << std::endl;
                std::cout << "    a mod p = " << a % p << std::endl;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}