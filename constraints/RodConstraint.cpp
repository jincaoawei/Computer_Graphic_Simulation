#include "RodConstraint.h"

#if defined(__CYGWIN__) || defined(WIN32)
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

RodConstraint::RodConstraint(Particle *p1, Particle * p2, float dist) :
  Constraint({p1, p2}), p1(p1), p2(p2), dist(dist) {}

float RodConstraint::C() {
  Vector3f delta = p1->position - p2->position;

  return delta.dot(delta) - dist * dist;
}

float RodConstraint::Cd() {
    Vector3f pDiff = (p1->position - p2->position) * 2;
    Vector3f vDiff = (p1->velocity - p2->velocity) * 2;

    return pDiff.dot(vDiff);
}

std::vector<Vector3f> RodConstraint::j() {
    std::vector <Vector3f> j;

    j.push_back((p1->position - p2->position) * 2);
    j.push_back((p2->position - p1->position) * 2);

    return j;
}

vector<Vector3f> RodConstraint::jd() {
    vector <Vector3f> jd;

    jd.push_back((p1->velocity - p2->velocity) * 2);
    jd.push_back((p2->velocity - p1->velocity) * 2);

    return jd;
}


void RodConstraint::draw()
{
  glBegin( GL_LINES );
  glColor3f(0.8, 0.7, 0.6);
  glVertex3f( p1->position[0], p1->position[1], p1->position[2] );
  glColor3f(0.8, 0.7, 0.6);
  glVertex3f( p2->position[0], p2->position[1], p2->position[2] );
  glEnd();
}
