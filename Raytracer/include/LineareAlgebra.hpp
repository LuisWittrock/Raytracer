#include <eigen3/Eigen/Dense>
using Eigen::Vector3d, Eigen::Vector4d;

Vector4d normalZuKoordinate(Vector3d n, Vector3d p);
bool GeradeEbene_Schnittpunkt(Vector4d ebeneInKoord, Vector3d p, Vector3d a, double& ret);