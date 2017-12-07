/* -*- c++ -*- */

#define OFDM_ALLOCATOR_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ofdm_allocator_swig_doc.i"

%{
#include "ofdm_allocator/vector_source_tagged.h"
#include "ofdm_allocator/allocator_subcarrier.h"
#include "ofdm_allocator/serializer_subcarrier.h"
#include "ofdm_allocator/packet_header_default_alix.h"
#include "ofdm_allocator/packet_header_gen.h"
#include "ofdm_allocator/packet_header_ofdm_alix.h"
#include "ofdm_allocator/ofdm_equalizer_base_alix.h"
#include "ofdm_allocator/ofdm_equalizer_simpledfe_alix.h"
#include "ofdm_allocator/frame_equalizer_alix.h"
#include "ofdm_allocator/constellation_alix.h"
#include "ofdm_allocator/metric_type_alix.h"
#include "ofdm_allocator/constellation_decoder_alix.h"
%}


%include "ofdm_allocator/vector_source_tagged.h"
GR_SWIG_BLOCK_MAGIC2(ofdm_allocator, vector_source_tagged);
%include "ofdm_allocator/allocator_subcarrier.h"
GR_SWIG_BLOCK_MAGIC2(ofdm_allocator, allocator_subcarrier);
%include "ofdm_allocator/serializer_subcarrier.h"
GR_SWIG_BLOCK_MAGIC2(ofdm_allocator, serializer_subcarrier);

%include "ofdm_allocator/packet_header_default_alix.h"
%include "ofdm_allocator/packet_header_gen.h"
GR_SWIG_BLOCK_MAGIC2(ofdm_allocator, packet_header_gen);
%include "ofdm_allocator/packet_header_ofdm_alix.h"

%include "ofdm_allocator/ofdm_equalizer_base_alix.h"
%include "ofdm_allocator/frame_equalizer_alix.h"
GR_SWIG_BLOCK_MAGIC2(ofdm_allocator, frame_equalizer_alix);
%include "ofdm_allocator/ofdm_equalizer_simpledfe_alix.h"

%template(packet_header_default_alix_sptr) boost::shared_ptr<gr::ofdm_allocator::packet_header_default_alix>;
%pythoncode %{
packet_header_default_alix_sptr.__repr__ = lambda self: "<packet_header_default_alix>"
packet_header_default_alix = packet_header_default_alix .make;
%}

%template(packet_header_ofdm_alix_sptr) boost::shared_ptr<gr::ofdm_allocator::packet_header_ofdm_alix>;
%pythoncode %{
packet_header_ofdm_alix_sptr.__repr__ = lambda self: "<packet_header_ofdm_alix>"
packet_header_ofdm_alix = packet_header_ofdm_alix .make;
%}

// %template(ofdm_equalizer_base_alix_sptr) boost::shared_ptr<gr::ofdm_allocator::ofdm_equalizer_base_alix>;
// %pythoncode %{
// ofdm_equalizer_base_alix_sptr.__repr__ = lambda self: "<ofdm_equalizer_base_alix>"
// ofdm_equalizer_base_alix = ofdm_equalizer_base_alix .make;
// %}
%template(ofdm_equalizer_base_alix_sptr) boost::shared_ptr<gr::ofdm_allocator::ofdm_equalizer_base_alix>;
%template(ofdm_equalizer_1d_pilots_alix_sptr) boost::shared_ptr<gr::ofdm_allocator::ofdm_equalizer_1d_pilots_alix>;
%pythoncode %{
ofdm_equalizer_1d_pilots_alix_sptr.__repr__ = lambda self: "<OFDM equalizer 1D base class>"
%}

%template(ofdm_equalizer_simpledfe_alix_sptr) boost::shared_ptr<gr::ofdm_allocator::ofdm_equalizer_simpledfe_alix>;
%pythoncode %{
ofdm_equalizer_simpledfe_alix_sptr.__repr__ = lambda self: "<ofdm_equalizer_simpledfe_alix>"
ofdm_equalizer_simpledfe_alix = ofdm_equalizer_simpledfe_alix .make;
%}
%include "ofdm_allocator/constellation_alix.h"
%include "ofdm_allocator/metric_type_alix.h"

%template(constellation_alix_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_alix>;

%template(constellation_calcdist_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_calcdist>;
%pythoncode %{
constellation_calcdist_sptr.__repr__ = lambda self: "<constellation calcdist (m=%d)>" % (len(self.points()))
constellation_calcdist = constellation_calcdist.make;
%}

%template(constellation_rect_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_rect>;
%pythoncode %{
constellation_rect_sptr.__repr__ = lambda self: "<constellation rect (m=%d)>" % (len(self.points()))
constellation_rect = constellation_rect.make;
%}

%template(constellation_expl_rect_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_expl_rect>;
%pythoncode %{
constellation_expl_rect_sptr.__repr__ = lambda self: "<constellation expl rect (m=%d)>" % (len(self.points()))
constellation_expl_rect = constellation_expl_rect.make;
%}

%template(constellation_psk_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_psk>;
%pythoncode %{
constellation_psk_sptr.__repr__ = lambda self: "<constellation PSK (m=%d)>" % (len(self.points()))
constellation_psk = constellation_psk.make;
%}

%template(constellation_bpsk_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_bpsk>;
%pythoncode %{
constellation_bpsk_sptr.__repr__ = lambda self: "<constellation BPSK>"
constellation_bpsk = constellation_bpsk.make;
%}

%template(constellation_qpsk_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_qpsk>;
%pythoncode %{
constellation_qpsk_sptr.__repr__ = lambda self: "<constellation QPSK>"
constellation_qpsk = constellation_qpsk.make;
%}

%template(constellation_dqpsk_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_dqpsk>;
%pythoncode %{
constellation_dqpsk_sptr.__repr__ = lambda self: "<constellation DQPSK>"
constellation_dqpsk = constellation_dqpsk.make;
%}

%template(constellation_8psk_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_8psk>;
%pythoncode %{
constellation_8psk_sptr.__repr__ = lambda self: "<constellation 8PSK>"
constellation_8psk = constellation_8psk.make;
%}

%template(constellation_8psk_natural_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_8psk_natural>;
%pythoncode %{
constellation_8psk_natural_sptr.__repr__ = lambda self: "<constellation 8PSK_natural>"
constellation_8psk_natural = constellation_8psk_natural.make;
%}

%template(constellation_16qam_sptr) boost::shared_ptr<gr::ofdm_allocator::constellation_16qam>;
%pythoncode %{
constellation_16qam_sptr.__repr__ = lambda self: "<constellation 16qam>"
constellation_16qam = constellation_16qam.make;
%}
%include "ofdm_allocator/constellation_decoder_alix.h"
GR_SWIG_BLOCK_MAGIC2(ofdm_allocator, constellation_decoder_alix);
