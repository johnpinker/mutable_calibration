// Copyright 2017 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Settings storage.

#include "stages/settings.h"

#include <algorithm>

#include "stmlib/system/storage.h"

namespace stages {

using namespace std;

#define FIX_OUTLIER(destination, expected_value) if (fabsf(destination / expected_value - 1.0f) > 0.1f) { destination = expected_value; }
#define FIX_OUTLIER_ABSOLUTE(destination, expected_value) if (fabsf(destination - expected_value) > 0.1f) { destination = expected_value; }


bool Settings::Init() {
  ChannelCalibrationData default_calibration_data;

  default_calibration_data.dac_offset = 32768.0f;
  default_calibration_data.dac_scale = -32263.0f;
  default_calibration_data.adc_offset = 0.0f;
  default_calibration_data.adc_scale = -1.0f;

  fill(
      &persistent_data_.channel_calibration_data[0],
      &persistent_data_.channel_calibration_data[kNumChannels],
      default_calibration_data);
  
  fill(
      &state_.segment_configuration[0],
      &state_.segment_configuration[kNumChannels],
      0);

#if 0 
  // module 1 sheet
  persistent_data_.channel_calibration_data[0].dac_offset = 32932.521532589f;
  persistent_data_.channel_calibration_data[0].dac_scale = -32200.3455036758f;
  persistent_data_.channel_calibration_data[1].dac_offset = 32874.5871294953f;
  persistent_data_.channel_calibration_data[1].dac_scale = -32176.582243317f;
  persistent_data_.channel_calibration_data[2].dac_offset = 32902.782498445f;
  persistent_data_.channel_calibration_data[2].dac_scale = -32110.7123403894f;
  persistent_data_.channel_calibration_data[3].dac_offset = 32833.6504463455f;
  persistent_data_.channel_calibration_data[3].dac_scale = -32113.1373498226f;
  persistent_data_.channel_calibration_data[4].dac_offset = 32859.8900949065f;
  persistent_data_.channel_calibration_data[4].dac_scale = -32263.7541512523f;
  persistent_data_.channel_calibration_data[5].dac_offset = 32719.972917077f;
  persistent_data_.channel_calibration_data[5].dac_scale = -32184.2087781925f;

  persistent_data_.channel_calibration_data[0].adc_offset = 0.0414887808f;
  persistent_data_.channel_calibration_data[0].adc_scale = -0.9928514694f;
  persistent_data_.channel_calibration_data[1].adc_offset = 0.0416019177f;
  persistent_data_.channel_calibration_data[1].adc_scale = -0.9918994875f;
  persistent_data_.channel_calibration_data[2].adc_offset = 0.0498775402f;
  persistent_data_.channel_calibration_data[2].adc_scale = -0.9929171907f;
  persistent_data_.channel_calibration_data[3].adc_offset = 0.0460532819f;
  persistent_data_.channel_calibration_data[3].adc_scale = -0.988533017f;
  persistent_data_.channel_calibration_data[4].adc_offset = 0.0534028004f;
  persistent_data_.channel_calibration_data[4].adc_scale = -0.976880495f;
  persistent_data_.channel_calibration_data[5].adc_offset = 0.0511007599f;
  persistent_data_.channel_calibration_data[5].adc_scale = -0.9999333378f;
#endif



#if 0 
  // first module manual
  persistent_data_.channel_calibration_data[0].dac_offset = 31578.0f;
  persistent_data_.channel_calibration_data[0].dac_scale = -32203.0f;
  persistent_data_.channel_calibration_data[1].dac_offset = 31508.0f;
  persistent_data_.channel_calibration_data[1].dac_scale = -32203.0f;
  persistent_data_.channel_calibration_data[2].dac_offset = 31298.0f;
  persistent_data_.channel_calibration_data[2].dac_scale = -32113.0f;
  persistent_data_.channel_calibration_data[3].dac_offset = 31330.0f;
  persistent_data_.channel_calibration_data[3].dac_scale = -32133.0f;
  persistent_data_.channel_calibration_data[4].dac_offset = 31155.0f;
  persistent_data_.channel_calibration_data[4].dac_scale = -32173.0f;
  persistent_data_.channel_calibration_data[5].dac_offset = 31079.0f;
  persistent_data_.channel_calibration_data[5].dac_scale = -32200.0f;

  persistent_data_.channel_calibration_data[0].adc_offset = 0.0000f;
  persistent_data_.channel_calibration_data[0].adc_scale = -0.9960f;
  persistent_data_.channel_calibration_data[1].adc_offset = -0.0010f;
  persistent_data_.channel_calibration_data[1].adc_scale = -0.9990f;
  persistent_data_.channel_calibration_data[2].adc_offset = 0.0000f;
  persistent_data_.channel_calibration_data[2].adc_scale = -0.9948f;
  persistent_data_.channel_calibration_data[3].adc_offset = 0.0000f;
  persistent_data_.channel_calibration_data[3].adc_scale = -0.9900f;
  persistent_data_.channel_calibration_data[4].adc_offset = 0.0000f;  //jacked
  persistent_data_.channel_calibration_data[4].adc_scale = -0.9900f; // jacked
  persistent_data_.channel_calibration_data[5].adc_offset = 0.0000f; 
  persistent_data_.channel_calibration_data[5].adc_scale = -1.0005f;
#endif

  
#if 0 
  // module 2 manual
  persistent_data_.channel_calibration_data[0].dac_offset = 31328.0f;
  persistent_data_.channel_calibration_data[0].dac_scale = -32403.0f;
  persistent_data_.channel_calibration_data[1].dac_offset = 31228.0f;
  persistent_data_.channel_calibration_data[1].dac_scale = -32293.0f;
  persistent_data_.channel_calibration_data[2].dac_offset = 31698.0f;
  persistent_data_.channel_calibration_data[2].dac_scale = -32463.0f;
  persistent_data_.channel_calibration_data[3].dac_offset = 31648.0f;
  persistent_data_.channel_calibration_data[3].dac_scale = -32283.0f;
  persistent_data_.channel_calibration_data[4].dac_offset = 33160.0f;
  persistent_data_.channel_calibration_data[4].dac_scale = -32223.0f;
  persistent_data_.channel_calibration_data[5].dac_offset = 31428.0f;
  persistent_data_.channel_calibration_data[5].dac_scale = -32260.0f;

  persistent_data_.channel_calibration_data[0].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[0].adc_scale = -1.0f /* FIXME */;
  persistent_data_.channel_calibration_data[1].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[1].adc_scale = -1.0f /* FIXME */;
  persistent_data_.channel_calibration_data[2].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[3].adc_scale = -1.0f /* FIXME */;
  persistent_data_.channel_calibration_data[3].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[3].adc_scale = -1.0f /* FIXME */;
  persistent_data_.channel_calibration_data[4].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[4].adc_scale = -1.0f /* FIXME */;
  persistent_data_.channel_calibration_data[5].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[5].adc_scale = -1.0f /* FIXME */;
#endif

#if 1 // mod 2 spreadsheet try
  persistent_data_.channel_calibration_data[0].dac_offset = 33032.3679503735f;
  persistent_data_.channel_calibration_data[0].dac_scale = -32350.3912971294f;
  persistent_data_.channel_calibration_data[1].dac_offset = 32993.5606642668f;
  persistent_data_.channel_calibration_data[1].dac_scale = -32260.5553362721f;
  persistent_data_.channel_calibration_data[2].dac_offset = 33192.3053705531f;
  persistent_data_.channel_calibration_data[2].dac_scale = -32553.1893475529f;
  persistent_data_.channel_calibration_data[3].dac_offset = 33077.2746298551f;
  persistent_data_.channel_calibration_data[3].dac_scale = -32329.4707065742f;
  persistent_data_.channel_calibration_data[4].dac_offset = 33179.9318375387;
  persistent_data_.channel_calibration_data[4].dac_scale = -32279.5811360557f;
  persistent_data_.channel_calibration_data[5].dac_offset = 33055.9276455064f;
  persistent_data_.channel_calibration_data[5].dac_scale = -32224.6182195101f;

  persistent_data_.channel_calibration_data[0].adc_offset = 0.0521991498f;
  persistent_data_.channel_calibration_data[0].adc_scale = -0.9810333551f;
  persistent_data_.channel_calibration_data[1].adc_offset = 0.054225237f;
  persistent_data_.channel_calibration_data[1].adc_scale = -0.9807126512f;
  persistent_data_.channel_calibration_data[2].adc_offset = 0.0456634399f;
  persistent_data_.channel_calibration_data[2].adc_scale = -0.9778038525f;
  persistent_data_.channel_calibration_data[3].adc_offset = 0.0436679083f;
  persistent_data_.channel_calibration_data[3].adc_scale = -0.9801999608f;
  persistent_data_.channel_calibration_data[4].adc_offset = 0.0009751341f;
  persistent_data_.channel_calibration_data[4].adc_scale = -0.9751340809f;
  persistent_data_.channel_calibration_data[5].adc_offset = 0.0515972361f;
  persistent_data_.channel_calibration_data[5].adc_scale = -1.0014019627f;
#endif
  state_.color_blind = 0;
  
  bool success = chunk_storage_.Init(&persistent_data_, &state_);
  
  // Sanitize settings read from flash.
  if (success) {
    for (size_t i = 0; i < kNumChannels; ++i) {
      ChannelCalibrationData* c = &persistent_data_.channel_calibration_data[i];
      FIX_OUTLIER_ABSOLUTE(c->adc_offset, 0.0f);
      
      FIX_OUTLIER(c->dac_offset, 32768.0f);
      FIX_OUTLIER(c->dac_scale, -32263.0f);
      FIX_OUTLIER(c->adc_scale, -1.0f);

      uint8_t type_bits = state_.segment_configuration[i] & 0x3;
      uint8_t loop_bit = state_.segment_configuration[i] & 0x4;
      CONSTRAIN(type_bits, 0, 3);
      state_.segment_configuration[i] = type_bits | loop_bit;
    }
  }

  return success;
}

void Settings::SavePersistentData() {
  chunk_storage_.SavePersistentData();
}

void Settings::SaveState() {
  chunk_storage_.SaveState();
}

}  // namespace stages
