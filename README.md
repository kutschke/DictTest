# DictTest

Example of making a root dictionary two different ways, one using rootcling and the other using genreflex.
The rootcling example is drawn from KinKal and the genreflex example is drawn from the Mu2e Offline scons
based build system.  The examples are designed to be run on a machine that can see:
```
/cvmfs/mu2e.opensciencegrid.org/
```

The problem is that the header lines in the rootmap files are built differently using the two systems.
A rootmap file made by genreflex has header lines that look like:
```
header DictTest/General/ParticleState.hh
```
A rootmap file made by rootcling has header lines that look like:
```
header ParticleState.hh
```
A side effect of this difference is that to use the genreflex build we need only add one element to
ROOT_INCLUDE_PATH: the path to the root of the package.  On the other hand, to use the rootcling
build we need to add the full path to every directory in the package that contains dictionary source.

We would like to alter the rootmap files made by rootcling so that the header lines look like
those made by genreflex.

For historical reasons, building dictionaries using rootcling is done using a cmake based build system
and a LinkDef.h file, while building dictionaries using genreflex is done using an scons based build system
using the files classes.h and classses_def.xml. The source code in this example contains the files
to control both the cmake builds and the scons builds; each build system ignores the control files
for the other build system.

Hopefully the solution will be as simple as adding an option to the rootcling command line or adding
a line to the LinkDef.h file.

The stretch goal is to learn how to build dictionaries so that ROOT_INCLUDE_PATH is not needed at run-time;
that is to build a fully self contained dictionary that does not need to reference back to the header
file source.

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
make -j 1 VERBOSE=1 >& build.log
```

Now look at the rootmap file to see this side of the issue:
```
grep header lib/libGeneral.rootmap
```

You can inspect the build.log file to find the rootcling command that was generated by cmake.

## Using genreflex via scons via muse

In clean working directory, with a clean environment
```bash
source /cvmfs/mu2e.opensciencegrid.org/setupmu2e-art.sh
git clone https://github.com/kutschke/DictTest.git
muse setup -1 -q p020
muse build -j 1 >& build.log
```

Now look at the rootmap file to see the other side of the issue:
```
grep header build/sl7-prof-e20-p020/DictTest/lib/libdicttestGeneral_dict.rootmap
```

You can inspect the build.log file to the find the genreflex command that was generated by
the Mu2e scons helper scripts.

### About Muse

Muse is a thin layer on top of scons.  The command
```muse setup -q p020``` says to setup the environment using:
```/cvmfs/mu2e.opensciencegrid.org/DataFiles/Muse/p020``` .
The -1 argument is not important for this example - it says that include
directives in code must have a leading "Package/" or the compiler won't find
the includes.

The command ```muse build -j 1``` does book keeping, calls:
```
scons -C $MUSE_WORK_DIR -f $MUSE_DIR/python/SConstruct "$@"
```
and does a little more bookkeeping.  The combination of Muse and the SConstruct
file will inspect the tree rooted at the working directory for work to do and will
then do it.
