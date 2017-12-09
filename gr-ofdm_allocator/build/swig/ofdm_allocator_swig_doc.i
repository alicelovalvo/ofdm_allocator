
/*
 * This file was automatically generated using swig_doc.py.
 *
 * Any changes to it will be lost next time it is regenerated.
 */




%feature("docstring") gr::ofdm_allocator::allocator_subcarrier "<+description of block+>"

%feature("docstring") gr::ofdm_allocator::allocator_subcarrier::len_tag_key "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::allocator_subcarrier::fft_len "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::allocator_subcarrier::make "Return a shared_ptr to a new instance of ofdm_allocator::allocator_subcarrier.

To avoid accidental use of raw pointers, ofdm_allocator::allocator_subcarrier's constructor is in a private implementation class. ofdm_allocator::allocator_subcarrier::make is the public interface for creating new instances.

Params: (fft_len, vector_len, fixed_data, fixed_pilot, max_len_data_subcarr, max_len_pilot_subcarr, max_vector_data_subcarr, max_vector_pilot_subcarr, pilot_carriers, pilot_symbols, sync_words, len_tag_key, output_is_shifted)"

%feature("docstring") gr::ofdm_allocator::constellation_16qam "Digital constellation for 16qam."

%feature("docstring") gr::ofdm_allocator::constellation_16qam::make "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_16qam::~constellation_16qam "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_16qam::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_16qam::constellation_16qam "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_8psk "Digital constellation for 8PSK."

%feature("docstring") gr::ofdm_allocator::constellation_8psk::make "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_8psk::~constellation_8psk "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_8psk::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_8psk::constellation_8psk "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_8psk_natural "Digital constellation for natually mapped 8PSK."

%feature("docstring") gr::ofdm_allocator::constellation_8psk_natural::make "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_8psk_natural::~constellation_8psk_natural "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_8psk_natural::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_8psk_natural::constellation_8psk_natural "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix "An abstracted constellation object.

The constellation objects hold the necessary information to pass around constellation information for modulators and demodulators. These objects contain the mapping between the bits and the constellation points used to represent them as well as methods for slicing the symbol space. Various implementations are possible for efficiency and ease of use.

Standard constellations (BPSK, QPSK, QAM, etc) can be inherited from this class and overloaded to perform optimized slicing and constellation mappings."

%feature("docstring") gr::ofdm_allocator::constellation_alix::constellation_alix "

Params: (constell, pre_diff_code, rotational_symmetry, dimensionality)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::~constellation_alix "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::map_to_points "Returns the constellation points for a symbol value.

Params: (value, points)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::map_to_points_v "

Params: (value)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::decision_maker_v "Takes a vector rather than a pointer. Better for SWIG wrapping.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::decision_maker_pe "Also calculates the phase error.

Params: (sample, phase_error)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::calc_metric "Calculates distance.

Calculates metrics for all points in the constellation. For use with the viterbi algorithm.

Params: (sample, metric, type)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::calc_euclidean_metric "

Params: (sample, metric)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::calc_hard_symbol_metric "

Params: (sample, metric)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::points "Returns the set of points in this constellation.

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::s_points "Returns the vector of points in this constellation. Raise error if dimensionality is not one.

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::v_points "Returns a vector of vectors of points.

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::apply_pre_diff_code "Whether to apply an encoding before doing differential encoding. (e.g. gray coding)

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::set_pre_diff_code "Whether to apply an encoding before doing differential encoding. (e.g. gray coding)

Params: (a)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::pre_diff_code "Returns the encoding to apply before differential encoding.

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::rotational_symmetry "Returns the order of rotational symmetry.

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::dimensionality "Returns the number of complex numbers in a single symbol.

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::bits_per_symbol "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::arity "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::base "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::as_pmt "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::gen_soft_dec_lut "Generates the soft decision LUT based on constellation and symbol map.

Generates the soft decision LUT based on constellation and symbol map. It can be given a estimate of the noise power in the channel as .


This is expensive to compute.

Params: (precision, npwr)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::calc_soft_dec "Calculate soft decisions for the given .

Calculate the soft decisions from the given  at the given noise power .

This is a very costly algorithm (especially for higher order modulations) and should be used sparingly. It uses the gen_soft_dec_lut function to generate the LUT, which should be done once or if a large change in the noise floor is detected.

Instead of using this function, generate the LUT using the gen_soft_dec_lut after creating the constellation object and then use the soft_decision_maker function to return the answer from the LUT.

Params: (sample, npwr)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::set_soft_dec_lut "Define a soft decision look-up table.

Define a soft decision look-up table (LUT). Because soft decisions can be calculated in various ways with various levels of accuracy and complexity, this function allows users to create a LUT in their own way.

Setting the LUT here means that has_soft_dec_lut will return true. Decision vectors returned by soft_decision_maker will be calculated using this LUT.

Params: (soft_dec_lut, precision)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::has_soft_dec_lut "Returns True if the soft decision LUT has been defined, False otherwise.

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::soft_dec_lut "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::soft_decision_maker "Returns the soft decisions for the given .

Returns the soft decisions for the given . If a LUT is defined for the object, the decisions will be calculated from there. Otherwise, this function will call calc_soft_dec directly to calculate the soft decisions.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::get_distance "

Params: (index, sample)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::get_closest_point "

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::calc_arity "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_alix::max_min_axes "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_bpsk "Digital constellation for BPSK ."

%feature("docstring") gr::ofdm_allocator::constellation_bpsk::make "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_bpsk::~constellation_bpsk "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_bpsk::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_bpsk::constellation_bpsk "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_calcdist "Calculate Euclidian distance for any constellation.

Constellation which calculates the distance to each point in the constellation for decision making. Inefficient for large constellations."

%feature("docstring") gr::ofdm_allocator::constellation_calcdist::make "Make a general constellation object that calculates the Euclidean distance for hard decisions.

Params: (constell, pre_diff_code, rotational_symmetry, dimensionality)"

%feature("docstring") gr::ofdm_allocator::constellation_calcdist::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_calcdist::constellation_calcdist "

Params: (constell, pre_diff_code, rotational_symmetry, dimensionality)"

%feature("docstring") gr::ofdm_allocator::constellation_decoder_alix "<+description of block+>"

%feature("docstring") gr::ofdm_allocator::constellation_decoder_alix::make "Return a shared_ptr to a new instance of ofdm_allocator::constellation_decoder_alix.

To avoid accidental use of raw pointers, ofdm_allocator::constellation_decoder_alix's constructor is in a private implementation class. ofdm_allocator::constellation_decoder_alix::make is the public interface for creating new instances.

Params: (constellation)"

%feature("docstring") gr::ofdm_allocator::constellation_dqpsk "Digital constellation for DQPSK."

%feature("docstring") gr::ofdm_allocator::constellation_dqpsk::make "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_dqpsk::~constellation_dqpsk "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_dqpsk::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_dqpsk::constellation_dqpsk "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_expl_rect "Rectangular digital constellation.

Only implemented for 1-(complex)dimensional constellation.

Constellation space is divided into rectangular sectors. Each sector is associated with the nearest constellation point.

This class is different from constellation_rect in that the mapping from sector to constellation point is explicitly passed into the constructor as sector_values. Usually we do not need this, since we want each sector to be automatically mapped to the closest constellation point, however sometimes it's nice to have the flexibility."

%feature("docstring") gr::ofdm_allocator::constellation_expl_rect::make "

Params: (constellation, pre_diff_code, rotational_symmetry, real_sectors, imag_sectors, width_real_sectors, width_imag_sectors, sector_values)"

%feature("docstring") gr::ofdm_allocator::constellation_expl_rect::~constellation_expl_rect "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_expl_rect::constellation_expl_rect "

Params: (constellation, pre_diff_code, rotational_symmetry, real_sectors, imag_sectors, width_real_sectors, width_imag_sectors, sector_values)"

%feature("docstring") gr::ofdm_allocator::constellation_expl_rect::calc_sector_value "

Params: (sector)"

%feature("docstring") gr::ofdm_allocator::constellation_psk "constellation_psk

Constellation space is divided into pie slices sectors.

Each slice is associated with the nearest constellation point.

Works well for PSK but nothing else.

Assumes that there is a constellation point at 1.x"

%feature("docstring") gr::ofdm_allocator::constellation_psk::make "

Params: (constell, pre_diff_code, n_sectors)"

%feature("docstring") gr::ofdm_allocator::constellation_psk::~constellation_psk "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_psk::get_sector "

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_psk::calc_sector_value "

Params: (sector)"

%feature("docstring") gr::ofdm_allocator::constellation_psk::constellation_psk "

Params: (constell, pre_diff_code, n_sectors)"

%feature("docstring") gr::ofdm_allocator::constellation_qpsk "Digital constellation for QPSK."

%feature("docstring") gr::ofdm_allocator::constellation_qpsk::make "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_qpsk::~constellation_qpsk "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_qpsk::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_qpsk::constellation_qpsk "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_rect "Rectangular digital constellation

Only implemented for 1-(complex)dimensional constellation.

Constellation space is divided into rectangular sectors. Each sector is associated with the nearest constellation point.

Works well for square QAM.

Works for any generic constellation provided sectors are not too large."

%feature("docstring") gr::ofdm_allocator::constellation_rect::make "Make a rectangular constellation object.

Params: (constell, pre_diff_code, rotational_symmetry, real_sectors, imag_sectors, width_real_sectors, width_imag_sectors)"

%feature("docstring") gr::ofdm_allocator::constellation_rect::~constellation_rect "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_rect::constellation_rect "

Params: (constell, pre_diff_code, rotational_symmetry, real_sectors, imag_sectors, width_real_sectors, width_imag_sectors)"

%feature("docstring") gr::ofdm_allocator::constellation_rect::get_sector "

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_rect::calc_sector_center "

Params: (sector)"

%feature("docstring") gr::ofdm_allocator::constellation_rect::calc_sector_value "

Params: (sector)"

%feature("docstring") gr::ofdm_allocator::constellation_sector "Sectorized digital constellation.

constellation_sector

Constellation space is divided into sectors. Each sector is associated with the nearest constellation point."

%feature("docstring") gr::ofdm_allocator::constellation_sector::constellation_sector "Make a sectorized constellation object.

Params: (constell, pre_diff_code, rotational_symmetry, dimensionality, n_sectors)"

%feature("docstring") gr::ofdm_allocator::constellation_sector::~constellation_sector "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::constellation_sector::decision_maker "Returns the constellation point that matches best.

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_sector::get_sector "

Params: (sample)"

%feature("docstring") gr::ofdm_allocator::constellation_sector::calc_sector_value "

Params: (sector)"

%feature("docstring") gr::ofdm_allocator::constellation_sector::find_sector_values "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::frame_equalizer_alix "<+description of block+>"

%feature("docstring") gr::ofdm_allocator::frame_equalizer_alix::make "Return a shared_ptr to a new instance of ofdm_allocator::frame_equalizer_alix.

To avoid accidental use of raw pointers, ofdm_allocator::frame_equalizer_alix's constructor is in a private implementation class. ofdm_allocator::frame_equalizer_alix::make is the public interface for creating new instances.

Params: (equalizer, vector_len, cp_len, fixed_pilot, max_len_data_subcarr, max_len_pilot_subcarr, max_vector_pilot_subcarr, tsb_key, propagate_channel_state, fixed_frame_len, input_is_shifted)"



%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_1d_pilots_alix::ofdm_equalizer_1d_pilots_alix "

Params: (fft_len, occupied_carriers, pilot_carriers, pilot_symbols, symbols_skipped, input_is_shifted)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_1d_pilots_alix::~ofdm_equalizer_1d_pilots_alix "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_1d_pilots_alix::reset "Reset the channel information state knowledge.

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_1d_pilots_alix::get_channel_state "Return the current channel state.

Params: (taps)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_base_alix "<+description+>"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_base_alix::ofdm_equalizer_base_alix "

Params: (fft_len)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_base_alix::~ofdm_equalizer_base_alix "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_base_alix::reset "Reset the channel information state knowledge.

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_base_alix::equalize "Run the actual equalization.

Params: (frame, n_sym, initial_taps, occupied_carriers, tags)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_base_alix::get_channel_state "Return the current channel state.

Params: (taps)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_base_alix::fft_len "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_base_alix::base "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_simpledfe_alix "<+description+>"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_simpledfe_alix::ofdm_equalizer_simpledfe_alix "

Params: (fft_len, constellation, occupied_carriers, pilot_carriers, pilot_symbols, symbols_skipped, alpha, input_is_shifted)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_simpledfe_alix::~ofdm_equalizer_simpledfe_alix "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_simpledfe_alix::equalize "Run the actual equalization.

Params: (frame, n_sym, initial_taps, occupied_carriers, tags)"

%feature("docstring") gr::ofdm_allocator::ofdm_equalizer_simpledfe_alix::make "

Params: (fft_len, constellation, occupied_carriers, pilot_carriers, pilot_symbols, symbols_skipped, alpha, input_is_shifted)"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix "<+description+>"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix::packet_header_default_alix "

Params: (header_len, len_tag_key, num_tag_key, bits_per_byte)"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix::~packet_header_default_alix "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix::base "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix::formatter "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix::set_header_num "

Params: (header_num)"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix::header_len "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix::len_tag_key "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix::header_formatter "Encodes the header information in the given tags into bits and places them into .

Uses the following header format: Bits 0-11: The packet length (what was stored in the tag with key ) Bits 12-23: The header number (counts up everytime this function is called) Bit 24-31: 8-Bit CRC All other bits: Are set to zero

If the header length is smaller than 32, bits are simply left out. For this reason, they always start with the LSB.

However, it is recommended to stay above 32 Bits, in order to have a working CRC.

Params: (packet_len, out, tags)"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix::header_parser "Inverse function to header_formatter().

Reads the bit stream in  and writes a corresponding tag into .

Params: (header, tags)"

%feature("docstring") gr::ofdm_allocator::packet_header_default_alix::make "

Params: (header_len, len_tag_key, num_tag_key, bits_per_byte)"

%feature("docstring") gr::ofdm_allocator::packet_header_gen "<+description of block+>"

%feature("docstring") gr::ofdm_allocator::packet_header_gen::make "Return a shared_ptr to a new instance of ofdm_allocator::packet_header_gen.

To avoid accidental use of raw pointers, ofdm_allocator::packet_header_gen's constructor is in a private implementation class. ofdm_allocator::packet_header_gen::make is the public interface for creating new instances.

Params: (header_formatter, max_len_data_subcarr, max_len_pilot_subcarr, max_vector_data_subcarr, max_vector_pilot_subcarr, fixed_pilot, vector_len, len_tag_key)"

%feature("docstring") gr::ofdm_allocator::packet_header_gen::set_header_formatter "

Params: (header_formatter)"

%feature("docstring") gr::ofdm_allocator::packet_header_ofdm_alix "<+description+>"

%feature("docstring") gr::ofdm_allocator::packet_header_ofdm_alix::packet_header_ofdm_alix "

Params: (occupied_carriers, n_syms, len_tag_key, frame_len_tag_key, num_tag_key, bits_per_header_sym, bits_per_payload_sym, scramble_header)"

%feature("docstring") gr::ofdm_allocator::packet_header_ofdm_alix::~packet_header_ofdm_alix "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::packet_header_ofdm_alix::header_formatter "Header formatter.

Does the same as packet_header_default::header_formatter(), but optionally scrambles the bits (this is more important for OFDM to avoid PAPR spikes).

Params: (packet_len, out, tags)"

%feature("docstring") gr::ofdm_allocator::packet_header_ofdm_alix::header_parser "Inverse function to header_formatter().

Does the same as packet_header_default::header_parser(), but adds another tag that stores the number of OFDM symbols in the packet. Note that there is usually no linear connection between the number of OFDM symbols and the packet length because a packet might finish mid-OFDM-symbol.

Params: (header, tags)"

%feature("docstring") gr::ofdm_allocator::packet_header_ofdm_alix::make "

Params: (occupied_carriers, n_syms, len_tag_key, frame_len_tag_key, num_tag_key, bits_per_header_sym, bits_per_payload_sym, scramble_header)"

%feature("docstring") gr::ofdm_allocator::serializer_subcarrier "<+description of block+>"

%feature("docstring") gr::ofdm_allocator::serializer_subcarrier::make "Return a shared_ptr to a new instance of ofdm_allocator::serializer_subcarrier.

To avoid accidental use of raw pointers, ofdm_allocator::serializer_subcarrier's constructor is in a private implementation class. ofdm_allocator::serializer_subcarrier::make is the public interface for creating new instances.

Params: (fft_len, vector_len, len_tag_key, packet_len_tag_key, symbols_skipped, carr_offset_key, input_is_shifted)"

%feature("docstring") gr::ofdm_allocator::vector_source_tagged "<+description of block+>"

%feature("docstring") gr::ofdm_allocator::vector_source_tagged::make "Return a shared_ptr to a new instance of ofdm_allocator::vector_source_tagged.

To avoid accidental use of raw pointers, ofdm_allocator::vector_source_tagged's constructor is in a private implementation class. ofdm_allocator::vector_source_tagged::make is the public interface for creating new instances.

Params: (data, repeat, vlen, fixed_data, fft_len, max_len_data_subcarr, max_len_pilot_subcarr, max_vector_data_subcarr, max_vector_pilot_subcarr, fixed_pilot, pilot, length_tag_key, tags)"

%feature("docstring") gr::ofdm_allocator::vector_source_tagged::rewind "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::vector_source_tagged::set_data "

Params: (data, tags)"

%feature("docstring") gr::ofdm_allocator::vector_source_tagged::final_update "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::vector_source_tagged::set_random_vector_data "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::vector_source_tagged::set_random_vector_pilot "

Params: (NONE)"

%feature("docstring") gr::ofdm_allocator::vector_source_tagged::set_repeat "

Params: (repeat)"