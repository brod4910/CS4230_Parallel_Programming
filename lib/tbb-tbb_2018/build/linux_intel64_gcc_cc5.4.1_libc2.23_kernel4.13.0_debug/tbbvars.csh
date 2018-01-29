#!/bin/csh
setenv TBBROOT "/home/vinu/CS_4230/lib/tbb-tbb_2018" #
setenv tbb_bin "/home/vinu/CS_4230/lib/tbb-tbb_2018/build/linux_intel64_gcc_cc5.4.1_libc2.23_kernel4.13.0_debug" #
if (! $?CPATH) then #
    setenv CPATH "${TBBROOT}/include" #
else #
    setenv CPATH "${TBBROOT}/include:$CPATH" #
endif #
if (! $?LIBRARY_PATH) then #
    setenv LIBRARY_PATH "${tbb_bin}" #
else #
    setenv LIBRARY_PATH "${tbb_bin}:$LIBRARY_PATH" #
endif #
if (! $?LD_LIBRARY_PATH) then #
    setenv LD_LIBRARY_PATH "${tbb_bin}" #
else #
    setenv LD_LIBRARY_PATH "${tbb_bin}:$LD_LIBRARY_PATH" #
endif #
 #
