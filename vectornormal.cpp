#include "vectornormal.h"
#include "math.h"

CVector3 Cross(CVector3 vVector1, CVector3 vVector2)
{
    CVector3 vNormal;                       // результирующий вектор

    // Значение X для векторы вычисляется так:  (V1.y * V2.z) - (V1.z * V2.y)
    vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));

    // Значение Y для векторы вычисляется так:  (V1.z * V2.x) - (V1.x * V2.z)
    vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));

    // Значение Z для векторы вычисляется так:  (V1.x * V2.y) - (V1.y * V2.x)
    vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

    return vNormal;  // Возвращаем результат (направление, куда направлен полигон - нормаль)
}

float Magnitude(CVector3 vNormal)
{
    return (float)sqrt( (vNormal.x * vNormal.x) +
                (vNormal.y * vNormal.y) +
                (vNormal.z * vNormal.z) );
}

CVector3 Vector(CVector3 vPoint1, CVector3 vPoint2)
{
    CVector3 vVector = {0,0,0};
    vVector.x = vPoint1.x - vPoint2.x;
    vVector.y = vPoint1.y - vPoint2.y;
    vVector.z = vPoint1.z - vPoint2.z;

    // Теперь возвращаем полученный результат

    return vVector;
}

CVector3 Normalize(CVector3 vNormal)
{
    float magnitude = Magnitude(vNormal);

    vNormal.x /= magnitude;
    vNormal.y /= magnitude;
    vNormal.z /= magnitude;

    return vNormal;
}

CVector3 Normal(CVector3 vTriangle[])
{
    CVector3 vVector1 = Vector(vTriangle[2], vTriangle[0]);
    CVector3 vVector2 = Vector(vTriangle[1], vTriangle[0]);
    CVector3 vNormal = Cross(vVector1, vVector2);
    vNormal = Normalize(vNormal);
    return vNormal;
}
