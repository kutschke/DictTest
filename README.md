# DictTest

Example of making a root dictionary two different ways, one using rootcling and the other using genreflex.

## Using rootcling via cmake

In clean working directory, with a clean environment
```bash
source /cvmfs/mu2e.opensciencegrid.org/setupmu2e-art.sh
git clone https://github.com/kutschke/DictTest.git
setup -B cmake v3_22_0
setup -B root v6_24_06b -q+e20:+p399:+prof
mkdir dicttest_profile
cd dicttest_profile
cmake ../DictTest  -DCMAKE_BUILD_TYPE=Release
make -j 1 VERBOSE=1
```

## Using genreflex via scons via muse

In clean working directory, with a clean environment
```bash
source /cvmfs/mu2e.opensciencegrid.org/setupmu2e-art.sh
git clone https://github.com/kutschke/DictTest.git
muse setup -1 -q p020
mkdir dicttest_profile
cd dicttest_profile
cmake ../DictTest  -DCMAKE_BUILD_TYPE=Release
make -j 1 VERBOSE=1
```

