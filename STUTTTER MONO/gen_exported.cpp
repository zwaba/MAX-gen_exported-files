#include "gen_exported.h"

namespace gen_exported {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2022 Cycling '74
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
	Data m_LEFT_2;
	Sah __m_sah_13;
	Sah __m_sah_14;
	int __exception;
	int vectorsize;
	t_sample m_dry_wet_10;
	t_sample __m_count_19;
	t_sample m_RANDOM_11;
	t_sample m_BPM_9;
	t_sample m_ENV_ms_12;
	t_sample m_reverse_8;
	t_sample m_Div_L_7;
	t_sample m_speed_6;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample __m_count_23;
	t_sample m_simple_3;
	t_sample m_ztutter_5;
	t_sample m_RANGE_4;
	t_sample __m_carry_25;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_LEFT_2.reset("LEFT", ((int)192000), ((int)1));
		m_simple_3 = ((int)0);
		m_RANGE_4 = 5;
		m_ztutter_5 = 0;
		m_speed_6 = 1;
		m_Div_L_7 = 1;
		m_reverse_8 = 0;
		m_BPM_9 = 120;
		m_dry_wet_10 = 0.5;
		m_RANDOM_11 = 0;
		m_ENV_ms_12 = 1;
		__m_sah_13.reset(0);
		__m_sah_14.reset(0);
		__m_count_19 = 0;
		__m_count_23 = 0;
		__m_carry_25 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample sub_545 = (m_dry_wet_10 - ((t_sample)0.5));
		t_sample scale_542 = ((safepow((sub_545 * ((t_sample)2)), ((int)1)) * ((int)-1)) + ((int)1));
		t_sample min_535 = ((((int)1) < scale_542) ? ((int)1) : scale_542);
		t_sample stutt_541 = m_ztutter_5;
		t_sample speed_416 = m_speed_6;
		t_sample reverse_417 = m_reverse_8;
		t_sample sub_549 = (m_dry_wet_10 - ((int)0));
		t_sample scale_546 = ((safepow((sub_549 * ((t_sample)2)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample min_538 = ((((int)1) < scale_546) ? ((int)1) : scale_546);
		t_sample mstosamps_414 = (m_ENV_ms_12 * (samplerate * 0.001));
		t_sample envelop_L_415 = mstosamps_414;
		t_sample add_471 = (m_RANDOM_11 + ((int)1));
		t_sample randomsel_511 = add_471;
		t_sample randomsel_509 = randomsel_511;
		t_sample stutt_472 = stutt_541;
		int not_470 = (!stutt_472);
		t_sample mul_476 = (((t_sample)0.5) * m_RANGE_4);
		t_sample orange_556 = (mul_476 - ((t_sample)0.5));
		t_sample add_492 = (((int)0) + m_RANGE_4);
		t_sample orange_564 = (add_492 - ((int)0));
		t_sample choice_15 = int(randomsel_511);
		t_sample choice_17 = int(randomsel_509);
		t_sample add_456 = (stutt_541 + ((int)1));
		t_sample choice_18 = int(add_456);
		t_sample selector_455 = ((choice_18 >= 2) ? ((int)1) : ((choice_18 >= 1) ? ((int)0) : 0));
		t_sample rsub_446 = (((int)1) - stutt_541);
		t_sample rec_451 = rsub_446;
		int eq_420 = (rec_451 == ((int)1));
		int LEFT_dim = m_LEFT_2.dim;
		int LEFT_channels = m_LEFT_2.channels;
		t_sample add_447 = (reverse_417 + ((int)1));
		t_sample ramp_422 = envelop_L_415;
		int gt_425 = (ramp_422 > ((int)0));
		t_sample rdiv_434 = safediv((-1), ramp_422);
		t_sample switch_426 = (gt_425 ? rdiv_434 : ((int)-1));
		t_sample ramp_423 = ramp_422;
		int gt_430 = (ramp_423 > ((int)0));
		t_sample rdiv_435 = safediv(((int)1), ramp_423);
		t_sample switch_427 = (gt_430 ? rdiv_435 : ((int)1));
		t_sample choice_22 = int(add_456);
		t_sample selector_452 = ((choice_22 >= 2) ? speed_416 : ((choice_22 >= 1) ? ((int)0) : 0));
		t_sample rec_419 = rec_451;
		int eq_418 = (rec_419 == ((int)1));
		t_sample choice_27 = int(add_447);
		int min_36 = (-1);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample mul_540 = (in1 * min_535);
			t_sample noise_484 = noise();
			t_sample noise_486 = noise();
			t_sample noise_487 = noise();
			t_sample wrap_485 = wrap(noise_487, noise_484, noise_486);
			t_sample irange_551 = (noise_486 - noise_484);
			t_sample sub_553 = (wrap_485 - noise_484);
			t_sample scale_550 = ((safepow(safediv(sub_553, irange_551), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_483 = scale_550;
			t_sample sub_557 = (scale_483 - ((int)0));
			t_sample scale_554 = ((safepow((sub_557 * ((t_sample)1)), ((int)1)) * orange_556) + ((t_sample)0.5));
			t_sample scale_479 = scale_554;
			t_sample ceil_474 = ceil(scale_479);
			t_sample sah_473 = __m_sah_13(ceil_474, not_470, ((int)0));
			t_sample gen_488 = sah_473;
			t_sample gen_506 = gen_488;
			t_sample noise_500 = noise();
			t_sample noise_502 = noise();
			t_sample noise_503 = noise();
			t_sample wrap_501 = wrap(noise_503, noise_500, noise_502);
			t_sample irange_559 = (noise_502 - noise_500);
			t_sample sub_561 = (wrap_501 - noise_500);
			t_sample scale_558 = ((safepow(safediv(sub_561, irange_559), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_499 = scale_558;
			t_sample sub_565 = (scale_499 - ((int)0));
			t_sample scale_562 = ((safepow((sub_565 * ((t_sample)1)), ((int)1)) * orange_564) + ((int)0));
			t_sample scale_495 = scale_562;
			t_sample ceil_490 = ceil(scale_495);
			t_sample sah_489 = __m_sah_14(ceil_490, not_470, ((int)0));
			t_sample gen_504 = sah_489;
			t_sample gen_505 = gen_504;
			t_sample Div_512 = gen_505;
			t_sample selector_513 = ((choice_15 >= 2) ? Div_512 : ((choice_15 >= 1) ? m_Div_L_7 : 0));
			t_sample choice_16 = int(selector_513);
			t_sample selector_533 = ((choice_16 >= 10) ? ((t_sample)0.090909) : ((choice_16 >= 9) ? ((t_sample)0.111111) : ((choice_16 >= 8) ? ((t_sample)0.142857) : ((choice_16 >= 7) ? ((t_sample)0.2) : ((choice_16 >= 6) ? ((t_sample)0.25) : ((choice_16 >= 5) ? ((t_sample)0.3335) : ((choice_16 >= 4) ? ((t_sample)0.5) : ((choice_16 >= 3) ? ((t_sample)0.667) : ((choice_16 >= 2) ? ((t_sample)0.75) : ((choice_16 >= 1) ? ((int)1) : 0))))))))));
			t_sample MultBPM_508 = gen_506;
			t_sample mul_507 = (m_BPM_9 * MultBPM_508);
			t_sample selector_510 = ((choice_17 >= 2) ? mul_507 : ((choice_17 >= 1) ? m_BPM_9 : 0));
			t_sample rdiv_525 = safediv(((int)60), selector_510);
			t_sample mul_528 = (rdiv_525 * selector_533);
			t_sample mul_524 = (mul_528 * ((int)1000));
			t_sample mstosamps_534 = (mul_524 * (samplerate * 0.001));
			t_sample mix_566 = (mstosamps_534 + (((t_sample)0.9995) * (m_simple_3 - mstosamps_534)));
			t_sample mix_514 = mix_566;
			t_sample gen_516 = mix_514;
			t_sample simple_next_515 = fixdenorm(mix_514);
			t_sample timesamples_L_517 = gen_516;
			__m_count_19 = (eq_420 ? 0 : (fixdenorm(__m_count_19 + selector_455)));
			t_sample counter_463 = __m_count_19;
			int counter_464 = ((int)0);
			int counter_465 = ((int)0);
			t_sample clamp_461 = ((counter_463 <= ((int)0)) ? ((int)0) : ((counter_463 >= ((int)191999)) ? ((int)191999) : counter_463));
			int index_trunc_20 = fixnan(floor(clamp_461));
			bool index_ignore_21 = ((index_trunc_20 >= LEFT_dim) || (index_trunc_20 < 0));
			if ((!index_ignore_21)) {
				m_LEFT_2.write(in1, index_trunc_20, 0);
				
			};
			t_sample lenght_444 = timesamples_L_517;
			t_sample lenght_440 = lenght_444;
			t_sample sub_437 = (lenght_440 - ramp_422);
			__m_count_23 = (eq_418 ? 0 : (fixdenorm(__m_count_23 + selector_452)));
			int carry_24 = 0;
			if ((eq_418 != 0)) {
				__m_count_23 = 0;
				__m_carry_25 = 0;
				
			} else if (((lenght_444 > 0) && (__m_count_23 >= lenght_444))) {
				int wraps_26 = (__m_count_23 / lenght_444);
				__m_carry_25 = (__m_carry_25 + wraps_26);
				__m_count_23 = (__m_count_23 - (wraps_26 * lenght_444));
				carry_24 = 1;
				
			};
			t_sample counter_458 = __m_count_23;
			int counter_459 = carry_24;
			int counter_460 = __m_carry_25;
			t_sample clamp_457 = ((counter_458 <= ((int)0)) ? ((int)0) : ((counter_458 >= ((int)191999)) ? ((int)191999) : counter_458));
			t_sample irange_568 = (timesamples_L_517 - ((int)0));
			t_sample orange_569 = (((int)0) - timesamples_L_517);
			t_sample sub_570 = (clamp_457 - ((int)0));
			t_sample scale_567 = ((safepow(safediv(sub_570, irange_568), ((int)1)) * orange_569) + timesamples_L_517);
			t_sample scale_450 = scale_567;
			t_sample selector_448 = ((choice_27 >= 2) ? scale_450 : ((choice_27 >= 1) ? clamp_457 : 0));
			t_sample mod_441 = safemod(selector_448, lenght_440);
			int index_trunc_28 = fixnan(floor(mod_441));
			double index_fract_29 = (mod_441 - index_trunc_28);
			int index_trunc_30 = (index_trunc_28 + 1);
			int index_wrap_31 = ((index_trunc_28 < 0) ? ((LEFT_dim - 1) + ((index_trunc_28 + 1) % LEFT_dim)) : (index_trunc_28 % LEFT_dim));
			int index_wrap_32 = ((index_trunc_30 < 0) ? ((LEFT_dim - 1) + ((index_trunc_30 + 1) % LEFT_dim)) : (index_trunc_30 % LEFT_dim));
			// samples LEFT channel 1;
			double read_LEFT_33 = m_LEFT_2.read(index_wrap_31, 0);
			double read_LEFT_34 = m_LEFT_2.read(index_wrap_32, 0);
			double readinterp_35 = linear_interp(index_fract_29, read_LEFT_33, read_LEFT_34);
			t_sample sample_LEFT_442 = readinterp_35;
			t_sample index_LEFT_443 = mod_441;
			int gt_439 = (mod_441 > ramp_423);
			int lt_438 = (mod_441 < sub_437);
			int and_421 = (gt_439 && lt_438);
			t_sample switch_436 = (and_421 ? switch_427 : switch_426);
			t_sample add_432 = (switch_436 + m_history_1);
			t_sample clamp_433 = ((add_432 <= ((int)0)) ? ((int)0) : ((add_432 >= ((int)1)) ? ((int)1) : add_432));
			t_sample mul_424 = (sample_LEFT_442 * clamp_433);
			t_sample history_431_next_468 = fixdenorm(clamp_433);
			t_sample mul_537 = (mul_424 * min_538);
			t_sample add_539 = (mul_540 + mul_537);
			t_sample clamp_526 = ((add_539 <= min_36) ? min_36 : ((add_539 >= ((int)1)) ? ((int)1) : add_539));
			t_sample out1 = clamp_526;
			m_simple_3 = simple_next_515;
			m_history_1 = history_431_next_468;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			
		};
		return __exception;
		
	};
	inline void set_LEFT(void * _value) {
		m_LEFT_2.setbuffer(_value);
	};
	inline void set_RANGE(t_param _value) {
		m_RANGE_4 = (_value < 1 ? 1 : (_value > 10 ? 10 : _value));
	};
	inline void set_ztutter(t_param _value) {
		m_ztutter_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_speed(t_param _value) {
		m_speed_6 = (_value < 0.009 ? 0.009 : (_value > 2 ? 2 : _value));
	};
	inline void set_Div_L(t_param _value) {
		m_Div_L_7 = (_value < 1 ? 1 : (_value > 10 ? 10 : _value));
	};
	inline void set_reverse(t_param _value) {
		m_reverse_8 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_BPM(t_param _value) {
		m_BPM_9 = (_value < 20 ? 20 : (_value > 280 ? 280 : _value));
	};
	inline void set_dry_wet(t_param _value) {
		m_dry_wet_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_RANDOM(t_param _value) {
		m_RANDOM_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ENV_ms(t_param _value) {
		m_ENV_ms_12 = (_value < 0 ? 0 : (_value > 500 ? 500 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 1;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 10; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1" };

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
		case 1: self->set_Div_L(value); break;
		case 2: self->set_ENV_ms(value); break;
		case 3: self->set_LEFT(ref); break;
		case 4: self->set_RANDOM(value); break;
		case 5: self->set_RANGE(value); break;
		case 6: self->set_dry_wet(value); break;
		case 7: self->set_reverse(value); break;
		case 8: self->set_speed(value); break;
		case 9: self->set_ztutter(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_BPM_9; break;
		case 1: *value = self->m_Div_L_7; break;
		case 2: *value = self->m_ENV_ms_12; break;
		
		case 4: *value = self->m_RANDOM_11; break;
		case 5: *value = self->m_RANGE_4; break;
		case 6: *value = self->m_dry_wet_10; break;
		case 7: *value = self->m_reverse_8; break;
		case 8: *value = self->m_speed_6; break;
		case 9: *value = self->m_ztutter_5; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(10 * sizeof(ParamInfo));
	self->__commonstate.numparams = 10;
	// initialize parameter 0 ("m_BPM_9")
	pi = self->__commonstate.params + 0;
	pi->name = "BPM";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_BPM_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 280;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_Div_L_7")
	pi = self->__commonstate.params + 1;
	pi->name = "Div_L";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Div_L_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ENV_ms_12")
	pi = self->__commonstate.params + 2;
	pi->name = "ENV_ms";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ENV_ms_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_LEFT_2")
	pi = self->__commonstate.params + 3;
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
	// initialize parameter 4 ("m_RANDOM_11")
	pi = self->__commonstate.params + 4;
	pi->name = "RANDOM";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_RANDOM_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_RANGE_4")
	pi = self->__commonstate.params + 5;
	pi->name = "RANGE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_RANGE_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_dry_wet_10")
	pi = self->__commonstate.params + 6;
	pi->name = "dry_wet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_dry_wet_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_reverse_8")
	pi = self->__commonstate.params + 7;
	pi->name = "reverse";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_reverse_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_speed_6")
	pi = self->__commonstate.params + 8;
	pi->name = "speed";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_speed_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.009;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_ztutter_5")
	pi = self->__commonstate.params + 9;
	pi->name = "ztutter";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ztutter_5;
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
