#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

// 检查是否为偶数
bool isEven(int n) {
    return n % 2 == 0;
}

// 在实数域中进行部分因式分解
std::vector<std::string> partialFactorizeReal(int n) {
    std::vector<std::string> factors;
    int k = n / 2;
    factors.push_back("(x^" + std::to_string(k) + " + 1)");
    factors.push_back("(x^" + std::to_string(k) + " - 1)");
    return factors;
}

// 在复数域中进行完全因式分解
std::vector<std::complex<double>> fullFactorizeComplex(int n) {
    std::vector<std::complex<double>> roots;
    for (int k = 0; k < n; k++) {
        double angle = M_PI * (2 * k + 1) / n;
        roots.push_back(std::complex<double>(cos(angle), sin(angle)));
    }
    return roots;
}

void factorize(int n) {
    std::cout << "Factorizing x^" << n << " + 1:" << std::endl;

    if (isEven(n)) {
        std::cout << "Real domain partial factorization:" << std::endl;
        auto realFactors = partialFactorizeReal(n);
        for (const auto& factor : realFactors) {
            std::cout << factor << std::endl;
        }
    } else {
        std::cout << "Cannot be factored in real domain." << std::endl;
    }

    std::cout << "Complex domain full factorization:" << std::endl;
    std::cout << "x^" << n << " + 1 = ";
    auto complexRoots = fullFactorizeComplex(n);
    for (size_t i = 0; i < complexRoots.size(); ++i) {
        std::cout << "(x - (" << complexRoots[i].real() << " + " << complexRoots[i].imag() << "i))";
        if (i < complexRoots.size() - 1) {
            std::cout << " * ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> testCases = {2, 3, 4, 5, 6};
    for (int n : testCases) {
        factorize(n);
        std::cout << std::endl;
    }
    return 0;
}