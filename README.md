#Solution approach

The program reads input file line-by-line. File medianvals_by_zip.txt is being created line by line, in small batches, as the reading of the input file advances.
File medianvals_by_date.txt however, is being generated all at once, after entire input file has been read. While generating, all lines are sorted using counting sort, which has linear time complexity.

# Build environment requirements

1. c++ compiler with c++14 and std::experimental::fs support (tested with GCC-5.4.0)
2. Autotools-2.69+ (Need only if get sources from GitHub)
3. Libtool-2.4.6+  (Need only if get sources from GitHub)

# Build instructions

autoreconf --install
./configure
make
make check #run unittests
