#include "AP.h"
#include "pch.h"
AP::AP(void)
{

}

double AP::Ragra_f(AP armature, double i, double t)
{
	return sqrt(armature.ucdla0) * sqrt(armature.pdzla0 + armature.Ba * i / armature.ha) * sqrt(3.1415926) / (armature.ha * sqrt(2 * (t + 1e-8)));
}

double AP::Ra_f(AP armature, double x)
{
	return armature.Rgrad * x;
}

double AP::Ua_f(double Ra, double i)
{
	return  Ra * i;
}