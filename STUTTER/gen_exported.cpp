#include "gen_exported.h"

namespace gen_exported {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Data m_RIGHT_13;
	Data m_LEFT_19;
	Delay m_delay_10;
	Delay m_delay_16;
	Delay m_delay_11;
	Delay m_delay_17;
	Sah __m_sah_35;
	Sah __m_sah_34;
	Sah __m_sah_36;
	int __exception;
	int vectorsize;
	t_sample __m_count_45;
	t_sample m_Div_L_29;
	t_sample __m_carry_73;
	t_sample m_RANGE_28;
	t_sample m_BPM_26;
	t_sample m_speed_27;
	t_sample __m_count_41;
	t_sample __m_count_71;
	t_sample m_Filter_R_31;
	t_sample __m_carry_47;
	t_sample m_RANDOM_33;
	t_sample m_ENV_ms_30;
	t_sample m_Div_R_25;
	t_sample __m_count_67;
	t_sample m_reverse_32;
	t_sample m_dry_wet_24;
	t_sample m_DOUBLE_21;
	t_sample m_Tail_22;
	t_sample m_history_4;
	t_sample m_history_5;
	t_sample m_history_6;
	t_sample m_history_3;
	t_sample m_history_1;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample m_ztutter_23;
	t_sample m_history_7;
	t_sample m_history_9;
	t_sample m_simple_20;
	t_sample __m_latch_89;
	t_sample m_history_8;
	t_sample m_history_18;
	t_sample m_simple_14;
	t_sample m_history_15;
	t_sample m_history_12;
	t_sample __m_latch_90;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_delay_10.reset("m_delay_10", ((int)48000));
		m_delay_11.reset("m_delay_11", samplerate);
		m_history_12 = ((int)0);
		m_RIGHT_13.reset("RIGHT", ((int)192000), ((int)1));
		m_simple_14 = ((int)0);
		m_history_15 = ((int)0);
		m_delay_16.reset("m_delay_16", ((int)48000));
		m_delay_17.reset("m_delay_17", samplerate);
		m_history_18 = ((int)0);
		m_LEFT_19.reset("LEFT", ((int)192000), ((int)1));
		m_simple_20 = ((int)0);
		m_DOUBLE_21 = 0;
		m_Tail_22 = 0;
		m_ztutter_23 = 0;
		m_dry_wet_24 = 0.5;
		m_Div_R_25 = 3;
		m_BPM_26 = 120;
		m_speed_27 = 1;
		m_RANGE_28 = 5;
		m_Div_L_29 = 1;
		m_ENV_ms_30 = 1;
		m_Filter_R_31 = 0;
		m_reverse_32 = 0;
		m_RANDOM_33 = 0;
		__m_sah_34.reset(0);
		__m_sah_35.reset(0);
		__m_sah_36.reset(0);
		__m_count_41 = 0;
		__m_count_45 = 0;
		__m_carry_47 = 0;
		__m_count_67 = 0;
		__m_count_71 = 0;
		__m_carry_73 = 0;
		__m_latch_89 = 0;
		__m_latch_90 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample sub_8670 = (m_dry_wet_24 - ((t_sample)0.5));
		t_sample scale_8667 = ((safepow((sub_8670 * ((t_sample)2)), ((int)1)) * ((int)-1)) + ((int)1));
		t_sample scale_6814 = scale_8667;
		t_sample min_6813 = ((((int)1) < scale_6814) ? ((int)1) : scale_6814);
		t_sample sub_8674 = (m_dry_wet_24 - ((int)0));
		t_sample scale_8671 = ((safepow((sub_8674 * ((t_sample)2)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample scale_6712 = scale_8671;
		t_sample min_6816 = ((((int)1) < scale_6712) ? ((int)1) : scale_6712);
		t_sample stutt_7819 = m_ztutter_23;
		t_sample stutt_6820 = stutt_7819;
		t_sample add_6819 = (stutt_6820 + ((int)1));
		t_sample stutt_6822 = stutt_7819;
		t_sample stutt_6692 = stutt_7819;
		t_sample tail_6671 = m_Tail_22;
		t_sample tail_6672 = tail_6671;
		t_sample speed_7764 = m_speed_27;
		t_sample speed_6542 = speed_7764;
		t_sample reverse_7765 = m_reverse_32;
		t_sample reverse_6543 = reverse_7765;
		t_sample stutt_6800 = stutt_7819;
		t_sample add_6799 = (stutt_6800 + ((int)1));
		t_sample mstosamps_6434 = (m_ENV_ms_30 * (samplerate * 0.001));
		t_sample envelop_L_7763 = mstosamps_6434;
		t_sample envelop_L_6435 = envelop_L_7763;
		t_sample stutt_6673 = stutt_7819;
		t_sample add_6718 = (m_DOUBLE_21 + ((int)1));
		t_sample add_6597 = (m_RANDOM_33 + ((int)1));
		t_sample randomsel_6657 = add_6597;
		t_sample randomsel_6652 = randomsel_6657;
		t_sample randomsel_6654 = randomsel_6657;
		t_sample stutt_6598 = stutt_7819;
		int not_6596 = (!stutt_6598);
		t_sample add_6634 = (((int)0) + m_RANGE_28);
		t_sample orange_8681 = (add_6634 - ((int)0));
		t_sample mul_6602 = (((t_sample)0.5) * m_RANGE_28);
		t_sample orange_8689 = (mul_6602 - ((t_sample)0.5));
		t_sample add_6618 = (((int)0) + m_RANGE_28);
		t_sample orange_8697 = (add_6618 - ((int)0));
		t_sample choice_37 = int(randomsel_6657);
		t_sample choice_39 = int(randomsel_6652);
		t_sample add_6582 = (stutt_6822 + ((int)1));
		t_sample choice_40 = int(add_6582);
		t_sample selector_6581 = ((choice_40 >= 2) ? ((int)1) : ((choice_40 >= 1) ? ((int)0) : 0));
		t_sample rsub_6572 = (((int)1) - stutt_6822);
		t_sample rec_6545 = rsub_6572;
		t_sample rec_6577 = rec_6545;
		int eq_6546 = (rec_6577 == ((int)1));
		int LEFT_dim = m_LEFT_19.dim;
		int LEFT_channels = m_LEFT_19.channels;
		t_sample add_6573 = (reverse_6543 + ((int)1));
		t_sample ramp_6549 = envelop_L_6435;
		int gt_6556 = (ramp_6549 > ((int)0));
		t_sample rdiv_6561 = safediv(((int)1), ramp_6549);
		t_sample switch_6553 = (gt_6556 ? rdiv_6561 : ((int)1));
		t_sample ramp_6548 = ramp_6549;
		int gt_6551 = (ramp_6548 > ((int)0));
		t_sample rdiv_6560 = safediv((-1), ramp_6548);
		t_sample switch_6552 = (gt_6551 ? rdiv_6560 : ((int)-1));
		int eq_6544 = (rec_6545 == ((int)1));
		t_sample choice_44 = int(add_6582);
		t_sample selector_6578 = ((choice_44 >= 2) ? speed_6542 : ((choice_44 >= 1) ? ((int)0) : 0));
		t_sample choice_49 = int(add_6573);
		t_sample add_6701 = (stutt_6692 + ((int)1));
		t_sample choice_58 = int(add_6701);
		t_sample add_6694 = (stutt_6692 + ((int)1));
		t_sample choice_59 = int(add_6694);
		t_sample selector_6695 = ((choice_59 >= 2) ? ((int)1) : ((choice_59 >= 1) ? ((t_sample)0.45) : 0));
		t_sample choice_61 = int(add_6819);
		int min_62 = (-1);
		t_sample choice_63 = int(randomsel_6654);
		t_sample choice_65 = int(add_6718);
		t_sample add_7804 = (stutt_7819 + ((int)1));
		t_sample choice_66 = int(add_7804);
		t_sample selector_7803 = ((choice_66 >= 2) ? ((int)1) : ((choice_66 >= 1) ? ((int)0) : 0));
		t_sample rsub_7794 = (((int)1) - stutt_7819);
		t_sample rec_7767 = rsub_7794;
		t_sample rec_7799 = rec_7767;
		int eq_7768 = (rec_7799 == ((int)1));
		int RIGHT_dim = m_RIGHT_13.dim;
		int RIGHT_channels = m_RIGHT_13.channels;
		t_sample add_7795 = (reverse_7765 + ((int)1));
		int eq_7766 = (rec_7767 == ((int)1));
		t_sample ramp_7771 = envelop_L_7763;
		int gt_7778 = (ramp_7771 > ((int)0));
		t_sample rdiv_7783 = safediv(((int)1), ramp_7771);
		t_sample switch_7775 = (gt_7778 ? rdiv_7783 : ((int)1));
		t_sample ramp_7770 = ramp_7771;
		int gt_7773 = (ramp_7770 > ((int)0));
		t_sample rdiv_7782 = safediv((-1), ramp_7770);
		t_sample switch_7774 = (gt_7773 ? rdiv_7782 : ((int)-1));
		t_sample choice_70 = int(add_7804);
		t_sample selector_7800 = ((choice_70 >= 2) ? speed_7764 : ((choice_70 >= 1) ? ((int)0) : 0));
		t_sample choice_75 = int(add_7795);
		t_sample add_6681 = (stutt_6673 + ((int)1));
		t_sample choice_84 = int(add_6681);
		t_sample add_6674 = (stutt_6673 + ((int)1));
		t_sample choice_85 = int(add_6674);
		t_sample selector_6675 = ((choice_85 >= 2) ? ((int)1) : ((choice_85 >= 1) ? ((t_sample)0.45) : 0));
		t_sample choice_87 = int(add_6799);
		int min_88 = (-1);
		int lte_6437 = (m_Filter_R_31 <= ((int)0));
		int not_6436 = (!lte_6437);
		__m_latch_89 = ((not_6436 != 0) ? m_Filter_R_31 : __m_latch_89);
		t_sample latch_6438 = __m_latch_89;
		t_sample sub_8712 = (latch_6438 - ((int)0));
		t_sample scale_8709 = ((safepow((sub_8712 * ((t_sample)0.01)), ((int)1)) * ((int)995)) + ((int)5));
		t_sample scale_6442 = scale_8709;
		int gte_6440 = (m_Filter_R_31 >= ((int)0));
		int not_6439 = (!gte_6440);
		__m_latch_90 = ((not_6439 != 0) ? m_Filter_R_31 : __m_latch_90);
		t_sample latch_6441 = __m_latch_90;
		t_sample sub_8716 = (latch_6441 - (-100));
		t_sample scale_8713 = ((safepow((sub_8716 * ((t_sample)0.01)), ((int)1)) * ((int)22500)) + ((int)500));
		t_sample scale_6443 = scale_8713;
		t_sample min_6480 = ((scale_6443 < ((int)0)) ? ((int)0) : scale_6443);
		t_sample omega = safediv((min_6480 * ((t_sample)6.2831853071796)), samplerate);
		t_sample sn = sin(omega);
		t_sample cs = cos(omega);
		t_sample alpha = ((sn * ((t_sample)0.5)) * ((int)2));
		t_sample b0 = safediv(((int)1), (((int)1) + alpha));
		t_sample a2 = (((((int)1) - cs) * ((t_sample)0.5)) * b0);
		t_sample a1 = ((((int)1) - cs) * b0);
		t_sample b1 = ((((int)-2) * cs) * b0);
		t_sample b2 = ((((int)1) - alpha) * b0);
		t_sample expr_6496 = a2;
		t_sample expr_6497 = a1;
		t_sample expr_6498 = a2;
		t_sample expr_6499 = b1;
		t_sample expr_6500 = b2;
		t_sample min_6452 = ((scale_6442 < ((int)0)) ? ((int)0) : scale_6442);
		t_sample omega_6506 = safediv((min_6452 * ((t_sample)6.2831853071796)), samplerate);
		t_sample sn_6508 = sin(omega_6506);
		t_sample cs_6505 = cos(omega_6506);
		t_sample alpha_6509 = ((sn_6508 * ((t_sample)0.5)) * ((t_sample)2));
		t_sample b_6502 = safediv(((int)1), (((int)1) + alpha_6509));
		t_sample a_6503 = (((((int)1) + cs_6505) * ((t_sample)0.5)) * b_6502);
		t_sample a_6510 = ((-(((int)1) + cs_6505)) * b_6502);
		t_sample b_6507 = ((((int)-2) * cs_6505) * b_6502);
		t_sample b_6504 = ((((int)1) - alpha_6509) * b_6502);
		t_sample expr_6468 = a_6503;
		t_sample expr_6469 = a_6510;
		t_sample expr_6470 = a_6503;
		t_sample expr_6471 = b_6507;
		t_sample expr_6472 = b_6504;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_6818 = (in1 * min_6813);
			t_sample mul_6798 = (in2 * min_6813);
			t_sample noise_6642 = noise();
			t_sample noise_6644 = noise();
			t_sample noise_6645 = noise();
			t_sample wrap_6643 = wrap(noise_6645, noise_6642, noise_6644);
			t_sample irange_8676 = (noise_6644 - noise_6642);
			t_sample sub_8678 = (wrap_6643 - noise_6642);
			t_sample scale_8675 = ((safepow(safediv(sub_8678, irange_8676), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_6641 = scale_8675;
			t_sample sub_8682 = (scale_6641 - ((int)0));
			t_sample scale_8679 = ((safepow((sub_8682 * ((t_sample)1)), ((int)1)) * orange_8681) + ((int)0));
			t_sample scale_6637 = scale_8679;
			t_sample ceil_6632 = ceil(scale_6637);
			t_sample sah_6631 = __m_sah_34(ceil_6632, not_6596, ((int)0));
			t_sample gen_6646 = sah_6631;
			t_sample gen_6647 = gen_6646;
			t_sample noise_6610 = noise();
			t_sample noise_6612 = noise();
			t_sample noise_6613 = noise();
			t_sample wrap_6611 = wrap(noise_6613, noise_6610, noise_6612);
			t_sample irange_8684 = (noise_6612 - noise_6610);
			t_sample sub_8686 = (wrap_6611 - noise_6610);
			t_sample scale_8683 = ((safepow(safediv(sub_8686, irange_8684), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_6609 = scale_8683;
			t_sample sub_8690 = (scale_6609 - ((int)0));
			t_sample scale_8687 = ((safepow((sub_8690 * ((t_sample)1)), ((int)1)) * orange_8689) + ((t_sample)0.5));
			t_sample scale_6605 = scale_8687;
			t_sample ceil_6600 = ceil(scale_6605);
			t_sample sah_6599 = __m_sah_35(ceil_6600, not_6596, ((int)0));
			t_sample gen_6614 = sah_6599;
			t_sample gen_6649 = gen_6614;
			t_sample noise_6626 = noise();
			t_sample noise_6628 = noise();
			t_sample noise_6629 = noise();
			t_sample wrap_6627 = wrap(noise_6629, noise_6626, noise_6628);
			t_sample irange_8692 = (noise_6628 - noise_6626);
			t_sample sub_8694 = (wrap_6627 - noise_6626);
			t_sample scale_8691 = ((safepow(safediv(sub_8694, irange_8692), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_6625 = scale_8691;
			t_sample sub_8698 = (scale_6625 - ((int)0));
			t_sample scale_8695 = ((safepow((sub_8698 * ((t_sample)1)), ((int)1)) * orange_8697) + ((int)0));
			t_sample scale_6621 = scale_8695;
			t_sample ceil_6616 = ceil(scale_6621);
			t_sample sah_6615 = __m_sah_36(ceil_6616, not_6596, ((int)0));
			t_sample gen_6630 = sah_6615;
			t_sample gen_6648 = gen_6630;
			t_sample Div_6658 = gen_6647;
			t_sample selector_6659 = ((choice_37 >= 2) ? Div_6658 : ((choice_37 >= 1) ? m_Div_L_29 : 0));
			t_sample choice_38 = int(selector_6659);
			t_sample selector_6811 = ((choice_38 >= 10) ? ((t_sample)0.090909) : ((choice_38 >= 9) ? ((t_sample)0.111111) : ((choice_38 >= 8) ? ((t_sample)0.142857) : ((choice_38 >= 7) ? ((t_sample)0.2) : ((choice_38 >= 6) ? ((t_sample)0.25) : ((choice_38 >= 5) ? ((t_sample)0.3335) : ((choice_38 >= 4) ? ((t_sample)0.5) : ((choice_38 >= 3) ? ((t_sample)0.667) : ((choice_38 >= 2) ? ((t_sample)0.75) : ((choice_38 >= 1) ? ((int)1) : 0))))))))));
			t_sample MultBPM_6651 = gen_6649;
			t_sample mul_6650 = (m_BPM_26 * MultBPM_6651);
			t_sample selector_6653 = ((choice_39 >= 2) ? mul_6650 : ((choice_39 >= 1) ? m_BPM_26 : 0));
			t_sample rdiv_6791 = safediv(((int)60), selector_6653);
			t_sample mul_6806 = (rdiv_6791 * selector_6811);
			t_sample mul_6790 = (mul_6806 * ((int)1000));
			t_sample mstosamps_6812 = (mul_6790 * (samplerate * 0.001));
			t_sample mix_8699 = (mstosamps_6812 + (((t_sample)0.9995) * (m_simple_20 - mstosamps_6812)));
			t_sample mix_6663 = mix_8699;
			t_sample gen_6665 = mix_6663;
			t_sample simple_next_6664 = fixdenorm(mix_6663);
			t_sample timesamples_L_6666 = gen_6665;
			t_sample lenght_6566 = timesamples_L_6666;
			__m_count_41 = (eq_6546 ? 0 : (fixdenorm(__m_count_41 + selector_6581)));
			t_sample counter_6589 = __m_count_41;
			int counter_6590 = ((int)0);
			int counter_6591 = ((int)0);
			t_sample clamp_6587 = ((counter_6589 <= ((int)0)) ? ((int)0) : ((counter_6589 >= ((int)191999)) ? ((int)191999) : counter_6589));
			int index_trunc_42 = fixnan(floor(clamp_6587));
			bool index_ignore_43 = ((index_trunc_42 >= LEFT_dim) || (index_trunc_42 < 0));
			if ((!index_ignore_43)) {
				m_LEFT_19.write(in1, index_trunc_42, 0);
				
			};
			t_sample sub_6563 = (lenght_6566 - ramp_6548);
			t_sample lenght_6570 = lenght_6566;
			__m_count_45 = (eq_6544 ? 0 : (fixdenorm(__m_count_45 + selector_6578)));
			int carry_46 = 0;
			if ((eq_6544 != 0)) {
				__m_count_45 = 0;
				__m_carry_47 = 0;
				
			} else if (((lenght_6570 > 0) && (__m_count_45 >= lenght_6570))) {
				int wraps_48 = (__m_count_45 / lenght_6570);
				__m_carry_47 = (__m_carry_47 + wraps_48);
				__m_count_45 = (__m_count_45 - (wraps_48 * lenght_6570));
				carry_46 = 1;
				
			};
			t_sample counter_6584 = __m_count_45;
			int counter_6585 = carry_46;
			int counter_6586 = __m_carry_47;
			t_sample clamp_6583 = ((counter_6584 <= ((int)0)) ? ((int)0) : ((counter_6584 >= ((int)191999)) ? ((int)191999) : counter_6584));
			t_sample irange_8701 = (timesamples_L_6666 - ((int)0));
			t_sample orange_8702 = (((int)0) - timesamples_L_6666);
			t_sample sub_8703 = (clamp_6583 - ((int)0));
			t_sample scale_8700 = ((safepow(safediv(sub_8703, irange_8701), ((int)1)) * orange_8702) + timesamples_L_6666);
			t_sample scale_6576 = scale_8700;
			t_sample selector_6574 = ((choice_49 >= 2) ? scale_6576 : ((choice_49 >= 1) ? clamp_6583 : 0));
			t_sample mod_6567 = safemod(selector_6574, lenght_6566);
			int index_trunc_50 = fixnan(floor(mod_6567));
			double index_fract_51 = (mod_6567 - index_trunc_50);
			int index_trunc_52 = (index_trunc_50 + 1);
			int index_wrap_53 = ((index_trunc_50 < 0) ? ((LEFT_dim - 1) + ((index_trunc_50 + 1) % LEFT_dim)) : (index_trunc_50 % LEFT_dim));
			int index_wrap_54 = ((index_trunc_52 < 0) ? ((LEFT_dim - 1) + ((index_trunc_52 + 1) % LEFT_dim)) : (index_trunc_52 % LEFT_dim));
			// samples LEFT channel 1;
			double read_LEFT_55 = m_LEFT_19.read(index_wrap_53, 0);
			double read_LEFT_56 = m_LEFT_19.read(index_wrap_54, 0);
			double readinterp_57 = linear_interp(index_fract_51, read_LEFT_55, read_LEFT_56);
			t_sample sample_LEFT_6568 = readinterp_57;
			t_sample index_LEFT_6569 = mod_6567;
			int gt_6565 = (mod_6567 > ramp_6549);
			int lt_6564 = (mod_6567 < sub_6563);
			int and_6547 = (gt_6565 && lt_6564);
			t_sample switch_6562 = (and_6547 ? switch_6553 : switch_6552);
			t_sample add_6558 = (switch_6562 + m_history_18);
			t_sample clamp_6559 = ((add_6558 <= ((int)0)) ? ((int)0) : ((add_6558 >= ((int)1)) ? ((int)1) : add_6558));
			t_sample mul_6550 = (sample_LEFT_6568 * clamp_6559);
			t_sample history_6557_next_6594 = fixdenorm(clamp_6559);
			t_sample tap_6709 = m_delay_17.read_linear(timesamples_L_6666);
			t_sample fold_6706 = fold(tap_6709, (-1), ((int)1));
			t_sample mul_6697 = (fold_6706 * ((int)1));
			t_sample tap_6699 = m_delay_16.read_step(((int)48000));
			t_sample selector_6702 = ((choice_58 >= 2) ? tap_6699 : ((choice_58 >= 1) ? ((int)1) : 0));
			t_sample add_6700 = (selector_6702 + ((int)1));
			t_sample mul_6707 = (m_history_15 * selector_6695);
			t_sample choice_60 = int(add_6700);
			t_sample selector_6704 = ((choice_60 >= 2) ? mul_6707 : ((choice_60 >= 1) ? mul_6550 : 0));
			t_sample history_6705_next_6710 = fixdenorm(fold_6706);
			t_sample mul_6669 = (mul_6697 * tail_6672);
			t_sample selector_6821 = ((choice_61 >= 2) ? mul_6550 : ((choice_61 >= 1) ? mul_6669 : 0));
			t_sample mul_6815 = (selector_6821 * min_6816);
			t_sample add_6817 = (mul_6818 + mul_6815);
			t_sample clamp_6793 = ((add_6817 <= min_62) ? min_62 : ((add_6817 >= ((int)1)) ? ((int)1) : add_6817));
			t_sample out1 = clamp_6793;
			t_sample rdiv_6726 = safediv(((int)60), selector_6653);
			t_sample Div_6655 = gen_6648;
			t_sample selector_6656 = ((choice_63 >= 2) ? Div_6655 : ((choice_63 >= 1) ? m_Div_R_25 : 0));
			t_sample choice_64 = int(selector_6656);
			t_sample selector_6733 = ((choice_64 >= 10) ? ((t_sample)0.090909) : ((choice_64 >= 9) ? ((t_sample)0.111111) : ((choice_64 >= 8) ? ((t_sample)0.142857) : ((choice_64 >= 7) ? ((t_sample)0.2) : ((choice_64 >= 6) ? ((t_sample)0.25) : ((choice_64 >= 5) ? ((t_sample)0.3335) : ((choice_64 >= 4) ? ((t_sample)0.5) : ((choice_64 >= 3) ? ((t_sample)0.667) : ((choice_64 >= 2) ? ((t_sample)0.75) : ((choice_64 >= 1) ? ((int)1) : 0))))))))));
			t_sample mul_6728 = (rdiv_6726 * selector_6733);
			t_sample mul_6725 = (mul_6728 * ((int)1000));
			t_sample mstosamps_6734 = (mul_6725 * (samplerate * 0.001));
			t_sample mix_8704 = (mstosamps_6734 + (((t_sample)0.9995) * (m_simple_14 - mstosamps_6734)));
			t_sample mix_6660 = mix_8704;
			t_sample gen_6662 = mix_6660;
			t_sample simple_next_6661 = fixdenorm(mix_6660);
			t_sample selector_6719 = ((choice_65 >= 2) ? gen_6662 : ((choice_65 >= 1) ? gen_6665 : 0));
			t_sample timesamples_selected_6667 = selector_6719;
			__m_count_67 = (eq_7768 ? 0 : (fixdenorm(__m_count_67 + selector_7803)));
			t_sample counter_7811 = __m_count_67;
			int counter_7812 = ((int)0);
			int counter_7813 = ((int)0);
			t_sample clamp_7809 = ((counter_7811 <= ((int)0)) ? ((int)0) : ((counter_7811 >= ((int)191999)) ? ((int)191999) : counter_7811));
			int index_trunc_68 = fixnan(floor(clamp_7809));
			bool index_ignore_69 = ((index_trunc_68 >= RIGHT_dim) || (index_trunc_68 < 0));
			if ((!index_ignore_69)) {
				m_RIGHT_13.write(in2, index_trunc_68, 0);
				
			};
			t_sample lenght_7792 = timesamples_selected_6667;
			t_sample lenght_7788 = lenght_7792;
			t_sample sub_7785 = (lenght_7788 - ramp_7770);
			__m_count_71 = (eq_7766 ? 0 : (fixdenorm(__m_count_71 + selector_7800)));
			int carry_72 = 0;
			if ((eq_7766 != 0)) {
				__m_count_71 = 0;
				__m_carry_73 = 0;
				
			} else if (((lenght_7792 > 0) && (__m_count_71 >= lenght_7792))) {
				int wraps_74 = (__m_count_71 / lenght_7792);
				__m_carry_73 = (__m_carry_73 + wraps_74);
				__m_count_71 = (__m_count_71 - (wraps_74 * lenght_7792));
				carry_72 = 1;
				
			};
			t_sample counter_7806 = __m_count_71;
			int counter_7807 = carry_72;
			int counter_7808 = __m_carry_73;
			t_sample clamp_7805 = ((counter_7806 <= ((int)0)) ? ((int)0) : ((counter_7806 >= ((int)191999)) ? ((int)191999) : counter_7806));
			t_sample irange_8706 = (timesamples_selected_6667 - ((int)0));
			t_sample orange_8707 = (((int)0) - timesamples_selected_6667);
			t_sample sub_8708 = (clamp_7805 - ((int)0));
			t_sample scale_8705 = ((safepow(safediv(sub_8708, irange_8706), ((int)1)) * orange_8707) + timesamples_selected_6667);
			t_sample scale_7798 = scale_8705;
			t_sample selector_7796 = ((choice_75 >= 2) ? scale_7798 : ((choice_75 >= 1) ? clamp_7805 : 0));
			t_sample mod_7789 = safemod(selector_7796, lenght_7788);
			int index_trunc_76 = fixnan(floor(mod_7789));
			double index_fract_77 = (mod_7789 - index_trunc_76);
			int index_trunc_78 = (index_trunc_76 + 1);
			int index_wrap_79 = ((index_trunc_76 < 0) ? ((RIGHT_dim - 1) + ((index_trunc_76 + 1) % RIGHT_dim)) : (index_trunc_76 % RIGHT_dim));
			int index_wrap_80 = ((index_trunc_78 < 0) ? ((RIGHT_dim - 1) + ((index_trunc_78 + 1) % RIGHT_dim)) : (index_trunc_78 % RIGHT_dim));
			// samples RIGHT channel 1;
			double read_RIGHT_81 = m_RIGHT_13.read(index_wrap_79, 0);
			double read_RIGHT_82 = m_RIGHT_13.read(index_wrap_80, 0);
			double readinterp_83 = linear_interp(index_fract_77, read_RIGHT_81, read_RIGHT_82);
			t_sample sample_RIGHT_8342 = readinterp_83;
			t_sample index_RIGHT_8343 = mod_7789;
			int gt_7787 = (mod_7789 > ramp_7771);
			int lt_7786 = (mod_7789 < sub_7785);
			int and_7769 = (gt_7787 && lt_7786);
			t_sample switch_7784 = (and_7769 ? switch_7775 : switch_7774);
			t_sample add_7780 = (switch_7784 + m_history_12);
			t_sample clamp_7781 = ((add_7780 <= ((int)0)) ? ((int)0) : ((add_7780 >= ((int)1)) ? ((int)1) : add_7780));
			t_sample mul_7772 = (sample_RIGHT_8342 * clamp_7781);
			t_sample gen_8412 = mul_7772;
			t_sample history_7779_next_8411 = fixdenorm(clamp_7781);
			t_sample tap_6689 = m_delay_11.read_linear(timesamples_selected_6667);
			t_sample fold_6686 = fold(tap_6689, (-1), ((int)1));
			t_sample mul_6677 = (fold_6686 * ((int)1));
			t_sample gen_6691 = mul_6677;
			t_sample tap_6679 = m_delay_10.read_step(((int)48000));
			t_sample selector_6682 = ((choice_84 >= 2) ? tap_6679 : ((choice_84 >= 1) ? ((int)1) : 0));
			t_sample add_6680 = (selector_6682 + ((int)1));
			t_sample mul_6687 = (m_history_9 * selector_6675);
			t_sample choice_86 = int(add_6680);
			t_sample selector_6684 = ((choice_86 >= 2) ? mul_6687 : ((choice_86 >= 1) ? gen_8412 : 0));
			t_sample history_6685_next_6690 = fixdenorm(fold_6686);
			t_sample mul_6668 = (gen_6691 * tail_6671);
			t_sample selector_6801 = ((choice_87 >= 2) ? gen_8412 : ((choice_87 >= 1) ? mul_6668 : 0));
			t_sample mul_6796 = (selector_6801 * min_6816);
			t_sample add_6797 = (mul_6798 + mul_6796);
			t_sample clamp_6792 = ((add_6797 <= min_88) ? min_88 : ((add_6797 >= ((int)1)) ? ((int)1) : add_6797));
			t_sample mul_6490 = (clamp_6792 * expr_6496);
			t_sample mul_6487 = (m_history_6 * expr_6497);
			t_sample mul_6485 = (m_history_7 * expr_6498);
			t_sample mul_6481 = (m_history_8 * expr_6500);
			t_sample mul_6483 = (m_history_5 * expr_6499);
			t_sample sub_6489 = (((mul_6485 + mul_6487) + mul_6490) - (mul_6483 + mul_6481));
			t_sample gen_6495 = sub_6489;
			t_sample history_6482_next_6491 = fixdenorm(m_history_5);
			t_sample history_6486_next_6492 = fixdenorm(m_history_6);
			t_sample history_6488_next_6493 = fixdenorm(clamp_6792);
			t_sample history_6484_next_6494 = fixdenorm(sub_6489);
			t_sample gen_6501 = gen_6495;
			t_sample mul_6462 = (gen_6501 * expr_6468);
			t_sample mul_6459 = (m_history_2 * expr_6469);
			t_sample mul_6457 = (m_history_3 * expr_6470);
			t_sample mul_6453 = (m_history_4 * expr_6472);
			t_sample mul_6455 = (m_history_1 * expr_6471);
			t_sample sub_6461 = (((mul_6457 + mul_6459) + mul_6462) - (mul_6455 + mul_6453));
			t_sample gen_6467 = sub_6461;
			t_sample history_6454_next_6463 = fixdenorm(m_history_1);
			t_sample history_6458_next_6464 = fixdenorm(m_history_2);
			t_sample history_6460_next_6465 = fixdenorm(gen_6501);
			t_sample history_6456_next_6466 = fixdenorm(sub_6461);
			t_sample out2 = gen_6467;
			m_simple_20 = simple_next_6664;
			m_history_18 = history_6557_next_6594;
			m_delay_17.write(selector_6704);
			m_history_15 = history_6705_next_6710;
			m_delay_16.write(stutt_6692);
			m_simple_14 = simple_next_6661;
			m_history_12 = history_7779_next_8411;
			m_delay_11.write(selector_6684);
			m_history_9 = history_6685_next_6690;
			m_delay_10.write(stutt_6673);
			m_history_8 = history_6482_next_6491;
			m_history_1 = history_6456_next_6466;
			m_history_2 = history_6460_next_6465;
			m_history_3 = history_6458_next_6464;
			m_history_4 = history_6454_next_6463;
			m_history_5 = history_6484_next_6494;
			m_history_6 = history_6488_next_6493;
			m_history_7 = history_6486_next_6492;
			m_delay_10.step();
			m_delay_11.step();
			m_delay_16.step();
			m_delay_17.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_RIGHT(void * _value) {
		m_RIGHT_13.setbuffer(_value);
	};
	inline void set_LEFT(void * _value) {
		m_LEFT_19.setbuffer(_value);
	};
	inline void set_DOUBLE(t_param _value) {
		m_DOUBLE_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_Tail(t_param _value) {
		m_Tail_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ztutter(t_param _value) {
		m_ztutter_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_dry_wet(t_param _value) {
		m_dry_wet_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_Div_R(t_param _value) {
		m_Div_R_25 = (_value < 1 ? 1 : (_value > 10 ? 10 : _value));
	};
	inline void set_BPM(t_param _value) {
		m_BPM_26 = (_value < 20 ? 20 : (_value > 280 ? 280 : _value));
	};
	inline void set_speed(t_param _value) {
		m_speed_27 = (_value < 0.009 ? 0.009 : (_value > 2 ? 2 : _value));
	};
	inline void set_RANGE(t_param _value) {
		m_RANGE_28 = (_value < 1 ? 1 : (_value > 10 ? 10 : _value));
	};
	inline void set_Div_L(t_param _value) {
		m_Div_L_29 = (_value < 1 ? 1 : (_value > 10 ? 10 : _value));
	};
	inline void set_ENV_ms(t_param _value) {
		m_ENV_ms_30 = (_value < 0 ? 0 : (_value > 500 ? 500 : _value));
	};
	inline void set_Filter_R(t_param _value) {
		m_Filter_R_31 = (_value < -100 ? -100 : (_value > 100 ? 100 : _value));
	};
	inline void set_reverse(t_param _value) {
		m_reverse_32 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_RANDOM(t_param _value) {
		m_RANDOM_33 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 15; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_BPM(value); break;
		case 1: self->set_DOUBLE(value); break;
		case 2: self->set_Div_L(value); break;
		case 3: self->set_Div_R(value); break;
		case 4: self->set_ENV_ms(value); break;
		case 5: self->set_Filter_R(value); break;
		case 6: self->set_LEFT(ref); break;
		case 7: self->set_RANDOM(value); break;
		case 8: self->set_RANGE(value); break;
		case 9: self->set_RIGHT(ref); break;
		case 10: self->set_Tail(value); break;
		case 11: self->set_dry_wet(value); break;
		case 12: self->set_reverse(value); break;
		case 13: self->set_speed(value); break;
		case 14: self->set_ztutter(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_BPM_26; break;
		case 1: *value = self->m_DOUBLE_21; break;
		case 2: *value = self->m_Div_L_29; break;
		case 3: *value = self->m_Div_R_25; break;
		case 4: *value = self->m_ENV_ms_30; break;
		case 5: *value = self->m_Filter_R_31; break;
		
		case 7: *value = self->m_RANDOM_33; break;
		case 8: *value = self->m_RANGE_28; break;
		
		case 10: *value = self->m_Tail_22; break;
		case 11: *value = self->m_dry_wet_24; break;
		case 12: *value = self->m_reverse_32; break;
		case 13: *value = self->m_speed_27; break;
		case 14: *value = self->m_ztutter_23; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(15 * sizeof(ParamInfo));
	self->__commonstate.numparams = 15;
	// initialize parameter 0 ("m_BPM_26")
	pi = self->__commonstate.params + 0;
	pi->name = "BPM";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_BPM_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 280;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_DOUBLE_21")
	pi = self->__commonstate.params + 1;
	pi->name = "DOUBLE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_DOUBLE_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_Div_L_29")
	pi = self->__commonstate.params + 2;
	pi->name = "Div_L";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Div_L_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_Div_R_25")
	pi = self->__commonstate.params + 3;
	pi->name = "Div_R";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Div_R_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_ENV_ms_30")
	pi = self->__commonstate.params + 4;
	pi->name = "ENV_ms";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ENV_ms_30;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_Filter_R_31")
	pi = self->__commonstate.params + 5;
	pi->name = "Filter_R";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Filter_R_31;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -100;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_LEFT_19")
	pi = self->__commonstate.params + 6;
	pi->name = "LEFT";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_RANDOM_33")
	pi = self->__commonstate.params + 7;
	pi->name = "RANDOM";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_RANDOM_33;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_RANGE_28")
	pi = self->__commonstate.params + 8;
	pi->name = "RANGE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_RANGE_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_RIGHT_13")
	pi = self->__commonstate.params + 9;
	pi->name = "RIGHT";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_Tail_22")
	pi = self->__commonstate.params + 10;
	pi->name = "Tail";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Tail_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_dry_wet_24")
	pi = self->__commonstate.params + 11;
	pi->name = "dry_wet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_dry_wet_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_reverse_32")
	pi = self->__commonstate.params + 12;
	pi->name = "reverse";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_reverse_32;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_speed_27")
	pi = self->__commonstate.params + 13;
	pi->name = "speed";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_speed_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.009;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_ztutter_23")
	pi = self->__commonstate.params + 14;
	pi->name = "ztutter";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ztutter_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // gen_exported::
