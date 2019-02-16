#include <dlib/matrix.h>
#include <dlib/optimization.h>
#include <iostream>
#include <vector>

using namespace std;

using column_vector = dlib::matrix<double, 0, 1>;

double f(const column_vector& col) {
    assert(col.nr() == 2);

    const double x1 = col(0);
    const double x2 = col(1);

    const double ret = -(x1 - 2) * (x1 - 2) - (x2 - 3) * (x2 - 3) + 5;

    printf("func called at x1 = %f, x2 = %f, f = %f\n", x1, x2, ret);

    return ret;
}

int main() {
    column_vector x = {0, 0};

    double ret = dlib::find_max_bobyqa(
        f, x, 5, dlib::uniform_matrix<double>(2, 1, -100.0),
        dlib::uniform_matrix<double>(2, 1, 100.0), 10, 1.E-6, 100);

    cout << x << endl;
    cout << ret << endl;

    return 0;
}