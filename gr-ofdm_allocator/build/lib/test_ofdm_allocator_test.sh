#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/alice/rfnoc/src/gr-ofdm_allocator/lib
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/alice/rfnoc/src/gr-ofdm_allocator/build/lib:$PATH
export LD_LIBRARY_PATH=/home/alice/rfnoc/src/gr-ofdm_allocator/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-ofdm_allocator 
