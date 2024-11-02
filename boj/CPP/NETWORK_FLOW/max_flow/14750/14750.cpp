#include <iostream>
#include <vector>
#include <cmath>

#define MAX_H 50
#define MAX_M 250
#define epsilon 1e-9

// #define DEBUG_INPUT
// #define DEBUG_CREATE_EDGE
using namespace std;

int n,k,h,m;

struct vector2{
public:
    double x,y;
    
    vector2() : x(0), y(0) {};
    vector2(const double x_, const double y_) : x(x_), y(y_) {};
    
    bool operator == (const vector2 & rhs){
        return x == rhs.x && y == rhs.y;
    }
    
    bool operator < (const vector2 & rhs) const {
        if(x == rhs.x) return y < rhs.y;
        return x < rhs.x;
    }
    
    // vector2 operator = (const vector2 & rhs){
    //     return vector2(rhs.x, rhs.y);
    // }
    
    vector2 operator - (const vector2 & rhs){
        return vector2(x - rhs.x, y - rhs.y);
    }
    
    vector2 operator + (const vector2 & rhs){
        return vector2(x + rhs.x, y + rhs.y);
    }
    
    vector2 operator * (const double rhs){
        return vector2(x * rhs, y * rhs);
    }
    
    double dot(const vector2 & rhs){
        return x*rhs.x + y*rhs.y;
    }
    
    double cross(const vector2 & rhs){
        return x*rhs.y - y*rhs.x;
    }
};

bool ccw(vector2 u, vector2 v){
    return u.cross(v);
}

bool ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p,b-p);
}

// L : a + (b-a)t
// walls[i]  = {a,b};
vector<pair<vector2,vector2>> walls;
vector<pair<double,double>> holes;

bool lineIntersect(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & p){
    double det = (b-a).cross(d-c);
	if( abs(det) < epsilon) return false;
	// printf("%f \n", (c-a).cross(d-c)/det);
    p = a + (b-a) * ( (c-a).cross(d-c) / det );
// printf("b-a * (~) : (%f,%f)  ", ((b-a) *  ((c-a).cross(d-c) / det )).x, ((b-a) * ( (c-a).cross(d-c) / det )).y);
// printf("pcal : (%f,%f)  ", ( a + (b-a) *  ((c-a).cross(d-c) / det )).x, (a + (b-a) *  ((c-a).cross(d-c) / det )).y);
// printf("p : (%f,%f)  ", p.x, p.y);

    return true;
}

// 두 선분이 만나지 않을 경우 true를 반환한다
// 두 선분이 만날 경우, hole에서 만날 경우 true, 아닌 경우 false를 반환한다.
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & p){
    vector2 hole = b;
    if( b < a) swap(a,b);
    if( d < c) swap(c,d);
    
    // 한 직선위에 없거나, 두 선분이 겹치지 않을 경우
    if( ccw(a,b,c) != 0 || b < c || d < a) return true;
    
    // 두 선분은 확실히 겹친다
    // 교차점이 hole일 경우에만 true를, 아닌 경우 false를 반환한다.
    if( hole == b){
        if( hole == c) return true;
        else return false;
    } else {
        if( hole == d) return true;
        else return false;
    }
}

bool inBound(vector2 p, vector2 a, vector2 b){
	if(b < a) swap(a,b);
	return p == a || p == b || (a < p && p < b);
}

// 선분 (a,b)와 선분 (c,d)의 교점이 hole인 경우 true, 아닌 경우 false를 반환한다.
// 두 선분이 교차하지 않을 경우 true를 반환한다.
bool segmentIntersect(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & p){
// printf("a : (%f,%f), b : (%f, %f), c: (%f, %f), d : (%f, %f) \n", a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y);
    //두 직선이 평행한 경우를 우선 예외로 처리한다
    if(!lineIntersect(a,b,c,d,p))
        return parallelSegments(a,b,c,d,p);
	
	// vector2 hole = b;
	// 두 선분이 교차하지 않을 경우 true를 반환한다.
	// printf("p : (%f, %f) \n", p.x, p.y);
	if( !(inBound(p,a,b) && inBound(p,c,d)) ) return true;
	
	// 만약 두 선분이 교차한다면 p가 hole인 경우에만 참을 반환한다.
	return p == b;
}

bool canSee(const double x, const double y, const double hx, const double hy){
#ifdef DEBUG_CREATE_EDGE
	printf("cansee(%.2f,%.2f,%.2f,%.2f) \n",x,y,hx,hy);
#endif
    bool cansee = true;
    vector2 interp;
    vector2 mouse(x,y);
    vector2 hole(hx,hy);
    for(auto wall : walls){
        if( !segmentIntersect( mouse, hole, wall.first, wall.second, interp) ){
	#ifdef DEBUG_CREATE_EDGE
		printf("got false wall : ( (%f,%f), (%f,%f) ) \n", wall.first.x, wall.first.y , wall.second.x, wall.second.y);
	#endif
            cansee = false;
            break;
        }
    }
#ifdef DEBUG_CREATE_EDGE
	printf("cansee : %d \n",cansee);
#endif
    return cansee;
}

int max_flow = 0;
vector<int> adjHM[MAX_H];
vector<int> hMatch;
vector<int> mMatch;
vector<bool> visited;

bool dfs(const int here){
    if(visited[here]) return false;
    visited[here] = true;
    for(auto next : adjHM[here]){
        if( mMatch[next] == -1 || dfs(mMatch[next])){
            hMatch[here] = next;
            mMatch[next] = here;
            return true;    
        }
    }
    return false;
}

void bipartiteMatch(){
    hMatch = vector<int> (h, -1);
    mMatch = vector<int> (m, -1);
    for(int i = 0; i < h; i++){
        for(int j = 0; j < k; j++){
            visited = vector<bool> (h,false);
            if( dfs(i) ) max_flow++;
        }
    }
}

int main(){
    cin>>n>>k>>h>>m;
    double x,y;
    
    //wall points
    cin>>x>>y; 
    vector2 prev(x,y);
    for(int i = 1 ; i < n; i++){
        cin>>x>>y;
        walls.push_back( {prev, vector2(x,y)} );
        prev.x = x; prev.y = y;
    }
    walls.push_back({prev, walls[0].first});
#ifdef DEBUG_INPUT
for(int i = 0 ; i < walls.size(); i++){
	printf("wall[%d] : ( (%f,%f) , (%f,%f) ) \n", i, walls[i].first.x, walls[i].first.y , walls[i].second.x, walls[i].second.y);
}
#endif
	
    //hole posi
    for(int i = 0 ; i < h; i++){
        cin>>x>>y;
        holes.push_back({x,y});
    }
#ifdef DEBUG_INPUT
for(int i = 0; i < h; i++){
	printf("hole[%d] : (%f,%f)\n", i, holes[i].first, holes[i].second);
}
#endif
    // mouse posi
    for(int i = 0; i < m; i++){
       cin>>x>>y; 
       // create edges
       for(int j = 0 ; j < h; j++){
           double hx = holes[j].first;
           double hy = holes[j].second;
           if( canSee(x,y,hx,hy) ){
               adjHM[j].push_back(i);
           }
       }
    }
    
#ifdef DEBUG_CREATE_EDGE
for(int i = 0; i < h; i++){
	printf("adjHM[%d] : ", i);
	for(auto next : adjHM[i]){
		cout<<next<<" ";
	}
	cout<<endl;
}
#endif
    // maxflow
    bipartiteMatch();
    if(max_flow >= m){
        cout<<"Possible"<<endl;
    } else {
        cout<<"Impossible"<<endl;
    }
    return 0;
}