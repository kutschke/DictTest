#ifndef KinKal_ParticleState_hh
#define KinKal_ParticleState_hh
//
// Very stripped down version of
//   https://github.com/KFTrack/KinKal/blob/main/General/ParticleState.hh
//

namespace KinKal {

  class ParticleState {
  public:

    ParticleState(int a);
    ParticleState();

    int a() const;

  private:
    int _a;
  };
}
#endif
