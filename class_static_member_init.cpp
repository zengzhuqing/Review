#include <vector>
using namespace std;
class Example{
public:
    static double a;
    static const int N = 10;
    static vector<int> A;
};
double Example::a = 6.5;
vector<int> Example::A(N);

