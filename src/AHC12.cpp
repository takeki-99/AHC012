#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9 + 7;
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
        ifstream in("./input.in");
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
        Output_t ret;
        return ret;
    }
};

int CalcScore()
{
    int score;
    return score;
}

int main()
{
    START_CLOCK = clock();
    Input_t input;
    input.In();
    Solver_t solver(input);
    Output_t output = solver.solve();
    output.Out();
}
