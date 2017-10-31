# Build environment reqiorements

1. c++ compiler with c++14 and srd::experimental::fs support (tested with gcc-5.4.0)
2. Autotools-2.69+ (Need only if get sources from github)
3. Libtool-2.4.6+  (Need only if get sources from github)

# Build instructions

autoreconf --install
./configure
make
make check #run unittests

