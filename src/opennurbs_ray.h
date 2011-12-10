/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// Copyright (c) 2011 Clifford Yapp. All rights reserved.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
// ON_Ray is based off of ON_Line, using ideas from BRL-CAD's 
// opennurbs_ext logic.
//
////////////////////////////////////////////////////////////////
*/

#if !defined(ON_RAY_INC_)
#define ON_RAY_INC_

class ON_CLASS ON_Ray
{
public:

  ON_Ray();
  ON_Ray( const ON_3dPoint& origin, const ON_3dVector& dir );
  ON_Ray( const ON_Line& line );
  ~ON_Ray();

  /*
  Returns:
    True if .
  */
  bool IsValid() const;

  // Description:
  //   Create a ray from a point and a vector.
  // Parameters:
  //   origin - [in] point at origin of ray
  //   dir - [in] direction in which ray is pointing
  // Returns:
  //   true if dir is non-zero.
  bool Create( 
    const ON_3dPoint& origin, 
    const ON_3dVector& dir
    );

  /*
  Description:
    Get a plane that contains the ray.
  Parameters:
    plane - [out] a plane that contains the ray.  The orgin
       of the plane is at the start of the ray.  
       If possible a plane parallel to the world xy, yz or zx
       plane is returned.
  Returns:
    true if a coordinate of the ray's direction vector is
    larger than tolerance.
  */
  bool InPlane( ON_Plane& plane, double tolerance = 0.0 ) const;

  // Returns:
  //   direction vector = line.to - line.from
  // See Also:
  //   ON_Ray::Tangent
  ON_3dVector Direction() const;

  // Returns:
  //   Unit tangent vector.
  // See Also:
  //   ON_Ray::Direction
  ON_3dVector Tangent() const;

  // Returns:
  //   unit line segment along ray 
  ON_Line Line() const;

  /*
  Description:
    Evaluate point on the ray.
  Parameters:
    t - [in] evaluation parameter. t=0 returns ray.origin.
  Returns:
    ray.origin + t*ray.dir.
  See Also:
    ON_Line::Direction
    ON_Line::Tangent
  */
  ON_3dPoint PointAt(
    double t
    ) const;


  /*
  Description:
    Find the point on the ray that is
    closest to the test_point.
  Parameters:
    test_point - [in]
  Returns:
    The point on the ray that is closest to test_point.
  */
  ON_3dPoint ClosestPointTo( 
    const ON_3dPoint& test_point
    ) const;

  /*
  Description:
    Find the point on the ray that is
    closest to the test_point.
  Parameters:
    test_point - [in]
  Returns:
    distance from the point on the ray that is closest
    to test_point.
  See Also:
    ON_3dPoint::DistanceTo
    ON_Ray::ClosestPointTo
  */
  double DistanceTo( ON_3dPoint test_point ) const;


  /*
  Description:
    Finds the shortest distance between the ray 
    and the other object.
  Parameters:
    P - [in]
    L - [in] (a finite chord)
    R - [in] (another ray)
  Returns:
    A value d such that if Q is any point on 
    this ray and P is any point on the other object, 
    then d <= Q.DistanceTo(P).
  */
  double MinimumDistanceTo( const ON_3dPoint& P ) const;
  double MinimumDistanceTo( const ON_Line& L ) const;
  double MinimumDistanceTo( const ON_Ray& R ) const;

  /*
  Description:
    Quickly determine if the shortest distance from
    this ray to the other object is greater than d.
  Parameters:
    d - [in] distance (> 0.0)
    P - [in] 
    L - [in] 
    R - [in] 
  Returns:
    True if if the shortest distance from this ray
    to the other object is greater than d.
  */
  bool IsFartherThan( double d, const ON_3dPoint& P ) const;
  bool IsFartherThan( double d, const ON_Line& L ) const;
  bool IsFartherThan( double d, const ON_Ray& L ) const;


  // For intersections see ON_Intersect();

  // Description:
  //   Reverse ray by reversing direction vector.
  void Reverse();

  bool Transform( 
    const ON_Xform& xform
    );

  // rotate ray about a point and axis
  bool Rotate(
        double sin_angle,
        double cos_angle,
        const ON_3dVector& axis_of_rotation,
        const ON_3dPoint& center_of_rotation
        );

  bool Rotate(
        double angle_in_radians,
        const ON_3dVector& axis_of_rotation,
        const ON_3dPoint& center_of_rotation
        );

  bool Translate(
        const ON_3dVector& delta
        );

  /*
  Description:
    Intersect ray with bbox.
  Parameters:
    ray - [in]
    bbox - [in]
    x - [out] Intersection events are appended to this array.
  Returns:
    Number of intersection events appended to x.
  */
  int IntersectBoundingBox( 
          const class ON_Ray* ray,
          const ON_BoundingBox* bbox,
          ON_SimpleArray<ON_X_EVENT>& x,
          ) const;

  /*
  Description:
    Intersect ray with surfaceB.
  Parameters:
    surfaceB - [in]
    x - [out] Intersection events are appended to this array.
    intersection_tolerance - [in]  If the distance from a point
      on this ray to the surface is <= intersection tolerance,
      then the point will be part of an intersection event.
      If the input intersection_tolerance <= 0.0, then 0.001 is used.
    overlap_tolerance - [in] If t1 and t2 are curve parameters of
      intersection events and the distance from the ray to the
      surface is <= overlap_tolerance,
      then the event will be returened as an overlap event.
      If the input overlap_tolerance <= 0.0, then 
      intersection_tolerance*2.0 is used.
    surfaceB_udomain - [in] optional restriction on surfaceB u domain
    surfaceB_vdomain - [in] optional restriction on surfaceB v domain
  Returns:
    Number of intersection events appended to x.
  */
  int IntersectSurface( 
          const class ON_Surface* surfaceB,
          ON_SimpleArray<ON_X_EVENT>& x,
          double intersection_tolerance = 0.0,
          double overlap_tolerance = 0.0,
          const ON_Interval* surfaceB_udomain = 0,
          const ON_Interval* surfaceB_vdomain = 0
          ) const;


public:
  ON_3dPoint origin; // origin point
  ON_3dVector dir;   // direction vector
};

#endif
