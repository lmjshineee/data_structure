#include <iostream>
#include <vector>

// 计算高度为 h 的平衡二叉树的个数

long long countBalancedTrees(int h) {
    if (h <= 0) return 0;
    if (h == 1) return 1;
    if (h == 2) return 3;

    std::vector<long long> dp(h + 1, 0);
    dp[1] = 1;
    dp[2] = 3;

    for (int i = 3; i <= h; i++) {
        dp[i] = 2 * dp[i-1] * dp[i-2]+dp[i-1]*dp[i-1];
    }

    return dp[h];
}

// 计算高度为 h 的二叉树的个数

long long countBinaryTrees(int h) {
    if (h == 1) return 1;  // 

    std::vector<long long> T(h + 1, 0);
    T[0] = 1;
    T[1] = 1;
    for(int i=2;i<=h;i++){
        for(int j=0;j<i-1;j++){
            T[i]+=2*T[j]*T[i-1];
        }
        T[i]+=T[i-1]*T[i-1];
    }

    return T[h];
}

// 计算高度为 h 的平衡二叉树最少节点数

int minNodesForBalancedTree(int h) {
    if (h <= 0) return 0;
    if (h == 1) return 1;
    return minNodesForBalancedTree(h - 1) + minNodesForBalancedTree(h - 2) + 1;

}


int main() {
    for (int h = 1; h <= 4; h++) {
        std::cout << "Depth " << h << "平衡二叉树数量：" << countBalancedTrees(h) << std::endl;
    }

    for (int h = 1; h <= 4; h++) {
        std::cout << "Depth " << h << "二叉树数量：" << countBinaryTrees(h) << std::endl;
    }

    for (int h = 1; h <= 10; h++) {
        std::cout << h << "深度，平衡二叉树所需最少结点数 " << ": " << minNodesForBalancedTree(h) << std::endl;
    }
    return 0;
}
