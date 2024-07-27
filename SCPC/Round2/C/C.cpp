#include <iostream>
#include <vector>


#define EPSILON 1e-6
using namespace std;

vector<pair<double,double>> A;
vector<double> P;
int main(int argc, char** argv)
{
	int T, test_case;
	cin >> T;
    int n,m;
	for(test_case = 0; test_case  < T; test_case++)
	{

        
		/////////////////////////////////////////////////////////////////////////////////////////////
        cin>>n;
        A.resize(n);
        P.resize(n);
        double x,y;
        for(int i = 0; i < n; i++){
            cin>>x>>y;
            A[i] = {x,y};
        }

        for(int i = 0; i < n ; i++){
            cin>>P[i];
        }

        //query
        cout << "Case #" << test_case+1 << endl;
        cin>>m;
        double v,w;
        for(int i = 0; i < m; i++){
            cin>>v>>w;
            double res = 0;
            for(int i = 0; i < n; i++){
                res += P[i] * (fabs(v - A[i].first) + fabs(w - A[i].second));
            }
            printf("%.7f \n",res);
        }

		/////////////////////////////////////////////////////////////////////////////////////////////
        A.clear();
        P.clear();
	}

	return 0;//Your program should return 0 on normal termination.
}