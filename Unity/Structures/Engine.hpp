#pragma once

namespace Unity
{  
    struct Bounds
    {
        Vector3 m_vCenter;
        Vector3 m_vExtents;
    };

    struct Plane
    {
        Vector3 m_vNormal;
        float fDistance;
    };

    struct Ray
    {
        Vector3 m_vOrigin;
        Vector3 m_vDirection;
    };
}