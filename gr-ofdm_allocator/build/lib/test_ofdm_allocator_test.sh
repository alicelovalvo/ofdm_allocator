#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/Users/Alice/ofdm_allocator/gr-ofdm_allocator/lib
export GR_CONF_CONTROLPORT_ON=False
export PATH=/Users/Alice/ofdm_allocator/gr-ofdm_allocator/build/lib:$PATH
export DYLD_LIBRARY_PATH=/Users/Alice/ofdm_allocator/gr-ofdm_allocator/build/lib:$DYLD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-ofdm_allocator 
