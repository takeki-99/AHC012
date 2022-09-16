#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9 + 7;
const double PI = acos(-1);
double START_CLOCK;
const double TimeLimit = 2.90;
double GetRuntime()
{
    return (clock() - START_CLOCK) / CLOCKS_PER_SEC;
}
double RangeRand(double FLOAT_MIN = 0.0, double FLOAT_MAX = 1.0)
{
    return FLOAT_MIN + ((double)rand() / RAND_MAX) * (FLOAT_MAX - FLOAT_MIN);
}

struct Input_t
{
    int N, K;
    vector<int> a_1; // 1-index
    vector<int> x, y;

    void In()
    {
        ifstream in("./input2.in");
        cin.rdbuf(in.rdbuf());

        cin >> N >> K;
        a_1.resize(11);
        for (int i = 1; i <= 10; i++)
        {
            cin >> a_1[i];
        }
        x.resize(N);
        y.resize(N);
        for (int i = 0; i < N; i++)
        {
            cin >> x[i] >> y[i];
        }
    }
};

struct Output_t
{
    struct line
    {
        int px, py, qx, qy;
    };
    vector<line> lines;

    void Out()
    {
        cout << /* k= */ lines.size() << endl;
        for (auto [px, py, qx, qy] : lines)
        {
            cout << px << " " << py << " " << qx << " " << qy << endl;
        }
    }
};

struct Solver_t
{
    Input_t input;
    Solver_t(const Input_t &input) : input(input) {}

    Output_t solve()
    {
        // 縦横に直線を引き,縦線を動かして焼きなます。
        // 評価関数: イチゴ(=sb)の数 Σd×min(a[d],b[d]) を最大化

        int nh;                         // 横線の数
        int nv;                         // 縦線の数
        vector<int> hLines;             // 横線
        vector<int> vLines;             // 縦線
        vector<int> b_1;                // b[i]:=sbがi個乗っているピースの数　1-index
        vector<vector<int>> sbCount;    // sbCount[i][j]:=(i,j)のグリッド上のsbの数
        vector<int> sbXs;               // sbのX座標圧縮 重複削除なし
        vector<int> sbYs;               // sbのY座標圧縮 重複削除なし
        map<int, vector<int>> sbSort_Y; // sbSort_Y[i]:= (x座標=i)のsbのy座標配列（昇順)
        // todo mapをvectorにする
        solve_init(input, nh, nv, hLines, vLines, b_1, sbCount, sbXs, sbYs, sbSort_Y);

        Output_t ret;
        for (int x : vLines)
        {
            ret.lines.push_back({x, 1, x, -1});
        }
        for (int y : hLines)
        {
            ret.lines.push_back({1, y, -1, y});
        }

        return ret;
    }

    void solve_init(Input_t &input, int &nh, int &nv,
                    vector<int> &hLines, vector<int> &vLines, vector<int> &b_1,
                    vector<vector<int>> &sbCount, vector<int> &sbXs, vector<int> &sbYs,
                    map<int, vector<int>> &sbSort_Y)
    {
        // 縦線*横線≒合計人数*4/PI になるように縦線を決める
        // 横線は8で固定
        nh = 8;
        nv = min(int(input.N * 4 / PI / nh + 10), input.K - nh);

        // 等間隔
        for (int i = 0; i < nh; i++)
        {
            hLines.push_back((int)(-10000 + 20000 * (double)i / nh));
        }
        for (int i = 0; i < nv; i++)
        {
            vLines.push_back((int)(-10000 + 20000 * (double)i / nv));
        }

        sbXs.clear();
        sbYs.clear();
        sbSort_Y.clear();
        for (int i = 0; i < input.N; i++)
        {
            sbXs.push_back(input.x[i]);
            sbYs.push_back(input.y[i]);
            sbSort_Y[input.x[i]].push_back(input.y[i]);
        }
        sort(sbXs.begin(), sbXs.end());
        sort(sbYs.begin(), sbYs.end());
        for (auto &[x, vec] : sbSort_Y)
        {
            sort(vec.begin(), vec.end());
        }

        sbCount.resize(nv, vector<int>(nh));
        for (int i = 0; i < input.N; i++)
        {
            int x_index = upper_bound(vLines.begin(), vLines.end(), input.x[i]) - vLines.begin() - 1;
            int y_index = upper_bound(hLines.begin(), hLines.end(), input.y[i]) - hLines.begin() - 1;
            sbCount[x_index][y_index]++;
        }

        b_1.resize(20);
        for (int i = 0; i < nh; i++)
        {
            for (int j = 0; j < nv; j++)
            {
                if (sbCount[i][j] < 20)
                {
                    b_1[sbCount[i][j]]++;
                }
            }
        }

        for (int i = 0; i < 20; i++)
            cout << i << " " << b_1[i] << endl;
    }
};

int main()
{
    START_CLOCK = clock();

    Input_t input;
    input.In();

    Solver_t solver(input);

    Output_t output = solver.solve();
    output.Out();
}
