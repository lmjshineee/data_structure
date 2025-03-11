#include <array>
#include <string_view>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

constexpr int alphSize = 3;

// ×Ó×Ö·û´®²éÕÒ
struct KMP
{
    explicit KMP(std::string_view strpat, char chr)
        : pat(strpat)
        , dfa()
    {
        if (std::any_of(strpat.begin(), strpat.end(), [chr](char c) { return c - chr >= alphSize; }))
        {
            throw std::invalid_argument("Pattern contains characters outside the allowed range");
        }

        std::size_t patSize = pat.size();
        for (auto& row : dfa) {
            row.resize(patSize);
        }

        dfa[pat.at(0) - chr][0] = 1;

        for (int X = 0, patPtr = 1; patPtr != patSize; ++patPtr)
        {
            for (int i = 0; i != alphSize; ++i)
            {
                dfa[i][patPtr] = dfa[i][X];
            }
            dfa[pat.at(patPtr) - chr][patPtr] = patPtr + 1;
            X = dfa[pat.at(patPtr) - chr][X];
        }

        std::for_each(pat.begin(), pat.end(),
                      [](char a) { std::cout << a << '\t'; });

        std::cout << '\n';
    }

    auto search(std::string_view txt, char chr) -> std::size_t
    {
        std::size_t txtPtr = 0;
        std::size_t patPtr = 0;
        std::size_t txtSize = txt.size();
        std::size_t patSize = pat.size();
        while (txtPtr != txtSize && patPtr != patSize)
        {
            patPtr = dfa[txt.at(txtPtr) - chr][patPtr];
            ++txtPtr;
        }
        if (patPtr == patSize)
        {
            return txtPtr - patSize;
        }
        return std::string_view::npos;
    }

    void printDfa()
    {
        for (const auto& row : dfa)
        {
            for (int j : row)
            {
                std::cout << j << '\t';
            }
            std::cout << '\n';
        }
    }

  private:
    std::string_view pat;
    std::array<std::vector<int>, alphSize> dfa;
};

auto main() -> int
{
    try 
    {
        KMP test("ababac", 'a');
        test.printDfa();
        std::cout << "find sub at: " << test.search("baabababac", 'a') << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}