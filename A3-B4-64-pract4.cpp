

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Result {
    int low;
    int high;
    int sum;
};

Result Find_Max_Crossing_Subarray(vector<int>& A, int low, int mid, int high, int constraint) {
    int left_sum = 0;
    int max_left_sum = -1;
    int sum = 0;
    int max_left = -1;

    for (int i = mid; i >= low; i--) {
        sum += A[i];
        if (sum <= constraint && sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }

    int right_sum = 0;
    sum = 0;
    int max_right = -1;

    for (int j = mid + 1; j <= high; j++) {
        sum += A[j];
        if (left_sum + sum <= constraint && (left_sum + sum) > right_sum) {
            right_sum = left_sum + sum;
            max_right = j;
        }
    }

    Result res;
    if (max_left != -1 && max_right != -1) {
        res.low = max_left;
        res.high = max_right;
        res.sum = right_sum;
    } else {
        res.low = res.high = -1;
        res.sum = -1;
    }

    return res;
}

Result Find_Maximum_Subarray(vector<int>& A, int low, int high, int constraint) {
    if (low == high) {
        Result base;
        if (A[low] <= constraint) {
            base.low = base.high = low;
            base.sum = A[low];
        } else {
            base.low = base.high = -1;
            base.sum = -1;
        }
        return base;
    }

    int mid = (low + high) / 2;

    Result left = Find_Maximum_Subarray(A, low, mid, constraint);
    Result right = Find_Maximum_Subarray(A, mid + 1, high, constraint);
    Result cross = Find_Max_Crossing_Subarray(A, low, mid, high, constraint);

    Result best;
    if (left.sum >= right.sum && left.sum >= cross.sum)
        best = left;
    else if (right.sum >= left.sum && right.sum >= cross.sum)
        best = right;
    else
        best = cross;

    return best;
}

int main() {
    vector<vector<int>> testCases = {
        {2, 1, 3, 4},     // 1
        {2, 2, 2, 2},     // 2
        {1, 5, 2, 3},     // 3
        {6, 7, 8},        // 4
        {1, 2, 3, 2, 1},  // 5
        {1, 1, 1, 1, 1},  // 6
        {4, 2, 3, 1},     // 7
        {},               // 8
        {1, 2, 3}         // 9
    };

    int constraints[] = {5, 4, 5, 5, 5, 4, 5, 10, 0};

    for (int t = 0; t < testCases.size(); t++) {
        cout << "Test Case " << t + 1 << ": ";
        if (testCases[t].empty()) {
            cout << "No feasible subarray (empty array)\n";
            continue;
        }

        Result ans = Find_Maximum_Subarray(testCases[t], 0, testCases[t].size() - 1, constraints[t]);

        if (ans.sum == -1) {
            cout << "No feasible subarray\n";
        } else {
            cout << "Max Sum = " << ans.sum << ", Subarray = [";
            for (int i = ans.low; i <= ans.high; i++) {
                cout << testCases[t][i];
                if (i != ans.high) cout << ", ";
            }
            cout << "]\n";
        }
    }
    return 0;
}