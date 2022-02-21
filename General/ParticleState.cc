#include "KinKal/General/ParticleState.hh"

KinKal::ParticleState::ParticleState(int a): _a(a){}

KinKal::ParticleState::ParticleState():_a(0){}

int KinKal::ParticleState::a() const { return _a;}
