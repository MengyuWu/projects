#include <stdio.h> 
#include <math.h> 
#include <iostream> 
using namespace std; 
#define inf 1e9 
#define exp 1e-9 

struct node 
{ 
    double x; 
    double y; 
}; 
node nodes[105], p; 
struct segment 
{ 
    node st; 
    node en; 
}; 
int n; 
//叉积 if > 0 p1在p2的顺时针方向 
double multi(node p1, node p2, node p0) 
{ 
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x); 
} 
//if叉积为零说明共线，如果该点在以side为对角线的矩形中说明p在side上 
int isonline(node p, segment side) 
{ 
    return (fabs(multi(p, side.st, side.en)) < exp && 
        min(side.st.x, side.en.x) <= p.x && p.x <= max(side.st.x, side.en.x) && 
        p.y >= min(side.st.y, side.en.y) && p.y <= max(side.st.y,side.en.y)); 
} 
//线段相交，跨立试验（叉积判断），快速排斥试验 
int intersect(segment l, segment r) 
{ 
    return (   max(l.st.x, l.en.x) >= min(r.st.x, r.en.x)//快速排斥试验用来确定以两线段为对角线的矩形是否相交 
            && max(r.st.x, r.en.x) >= min(l.st.x, l.en.x) 
            && max(l.st.y, l.en.y) >= min(r.st.y, r.en.y) 
            && max(r.st.y, r.en.y) >= min(l.st.y, l.en.y) 
            && multi(r.st, l.en, l.st) * multi(r.en, l.en, l.st) <= 0 
            && multi(l.st, r.en, r.st) * multi(l.en, r.en, r.st) <= 0); 
} 
int isinpolygon(node p) 
{ 
    int i, count = 0; 
    segment line, side; 
    if(n == 1) return fabs(p.x - nodes[0].x) < exp && fabs(p.y - nodes[0].y) < exp; 
    if(n == 2) 
    { 
        side.st = nodes[0]; 
        side.en = nodes[1]; 
        return isonline(p, side); 
    } 
    line.st = p; 
    line.en.y = p.y; 
    line.en.x = -inf; 
    for( i = 0; i < n; i ++ ) 
    { 
        side.st = nodes[i]; 
        side.en = nodes[(i + 1) % n]; 
        if(isonline(p,side)) return 1;// 如果p在side上 
        if(fabs(side.st.y - side.en.y) < exp) continue;//如果是水平的则不考虑 
        //两端点相交line，取y坐标大的以避免重复计数 
        if(isonline(side.st, line) && side.st.y > side.en.y) count ++; 
        else if(isonline(side.en, line) && side.en.y > side.st.y) count ++; 
        else if(intersect(line, side)) count ++; 
    } 
    return count % 2; 
} 
int main() 
{ 
    while(scanf("%d",&n) && n) 
    { 
       for(int i = 0; i < n; i ++) 
           scanf("%lf%lf",&nodes[i].x, &nodes[i].y); 
       scanf("%lf%lf",&p.x,&p.y); 
       if(isinpolygon(p)) printf("Within\n"); 
       else printf("Outside\n"); 
    } 
    return 0; 
}
 


