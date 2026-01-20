#include "LineareAlgebra.hpp"

Vector4d normalZuKoordinate(Vector3d n, Vector3d p){
    int d;
    Vector4d ret;
    d = p.dot(n);
    ret << n[0], n[1], n[2], d;
    return ret;
}

//g := {p + s * a : s - R}
//E := {e1*x1 + e2*x2 + e3*x3 = d : (x1, x2, x3) - R^3}
bool GeradeEbene_Schnittpunkt(Vector4d ebeneInKoord, Vector3d p, Vector3d a, double& ret){
    Vector3d e;
    int d;
    e << ebeneInKoord[0], ebeneInKoord[1], ebeneInKoord[2];
    d = ebeneInKoord[3];

    if(a.dot(e) == 0){
        return false;
    }
    ret = (d - (p.dot(e))) / (a.dot(e));
    return true;
}