#pragma once

// Aerodynamics Data
// each data table has 10 points that correspond to airspeed1, which are:  -20, 0, 20, 30, 40, 60, 80, 100, 120, 130 knots
// LCW reduced to 10 points as I didnt have data for anything under 0kts. I fudged some numbers for -20kts
// 15876 kg

namespace CH53
{//							    -20,	  0,		20,		 30,		40,		60,		80,		100,	  120,	   130
static double _XuData[10]  = { -0.0917, -0.0917, -0.0216, -0.0160, -0.0152, -0.0272, -0.0344, -0.0400, -0.0469, -0.0540 };		// forward speed affect on force out nose
//							 {-0.0439, -0.0397, -0.0346, -0.0257, -0.0167, -0.0204, -0.0270, -0.0314, -0.0379, -0.0437, -0.0536, -0.0570 };		//Original
static double _XwData[10] = {   0.0240,  0.0240,  0.0336,  0.0434,  0.0264,  0.0295,  0.0301,  0.0309,  0.0258,  0.0162 };		// downward speed affect on force out nose
static double _XqData[10] = {  0.2652,  0.2652,  0.5671,  0.5671,  0.6279, -0.6013,  0.6293,  0.5126,  0.4686,  0.4019 };		// pitch rate affect on force out nose
static double _XvData[10] = { 0.0029,  0.0029,  0.0012, -0.0001,  0.0000, -0.006,   0.0004, -0.0042, -0.0053, -0.0055 };		// sideways speed affect on force out nose
static double _XpData[10] = { -0.8595, -0.8595, -0.8016, -0.7620, -0.7254, -0.6828, -0.6462, -0.6370, -0.6401, -0.6614 };		// roll rate affect on force out nose
static double _XrData[10] = { -0.1152, -0.1152, -0.0972, -0.0543, -0.0555, -0.0954, -0.0881, -0.1096, -0.1133, -0.0773 };		// yaw rate affect on force out nose
static double _XdcData[10] = { 0.0755,  0.0755,  0.0409,  0.0461,  0.0528,  0.0569,  0.0600,  0.0610,  0.0620,  0.0630 };		// collective input affect on force out nose
// static double _XdcData[10] = { 0.0755,  0.0755,  0.0409,  0.0061,  0.0128,  0.0129,  0.0100,  0.0110,  0.0120,  0.0130 };		// collective input affect on force out nose
//static double _XdcData[10] = { 0.0665,   0.0526,  0.0431,  0.0755,  0.4090,  0.0061,  0.0128,  0.0149,  0.0175, -0.0031, -0.0158, -0.0289 };		// collective input affect on force out nose
static double _XdbData[10] = {  0.1823,  0.1823,  0.1747,  0.1643,  0.1612,  0.1423,  0.1391,  0.1302,  0.1326,  0.1596 };		// pitch input affect on force out nose
static double _XdaData[10] = { -0.0117,  0.0117,  0.0104,  0.0082,  0.0087,  0.0030,  0.0042,  0.0032,  0.0049,  0.0143 };		// roll input affect on force out nose
static double _XdpData[10] = { 0.0001, -0.0001, -0.0010, -0.0066, -0.0012, -0.0055, -0.0069, -0.0122, -0.0087,  0.0188 };		// pedal input affect on force out nose
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
static double _ZuData[10] = {  0.0168,  0.0168, -0.0050, -0.0100, -0.0250, -0.0423, -0.0562,  0.0143,  0.0353,  0.0494 };		// forward speed affect on force down
//							 { 0.1559,  0.1980,  0.1984, -0.0422, -0.2896, -0.1420, -0.0941, -0.0371, -0.0126,  0.0023,  0.0127,  0.0178 }; 	//Original
static double _ZwData[10] = { -0.2980, -0.2980, -0.3750, -0.4740, -0.5720, -0.6570, -0.7370, -0.7920, -0.8300, -0.8610 };		// downward speed affect on force down (1st attempt at VRS at 0 airspeed)
//							 {-0.6323, -0.5453, -0.4344,  0.1240, -0.4337, -0.5473, -0.6299, -0.7150, -0.7655, -0.7977, -0.8050, -0.8096 };		//Original
static double _ZqData[10] = {-0.0881,  0.0881, -0.0913,  0.0019,  0.0403, -0.2002, -0.4512, -0.5717, -0.9049, -1.3773 };		// pitch rate affect on force down
static double _ZvData[10] = { -0.1660, -0.1660, -0.0167, -0.0140, -0.0121, -0.0148, -0.0188, -0.0243, -0.0337, -0.0457 };		// sideways speed affect on force down
static double _ZpData[10] = {  0.0924, -0.0924, -0.2637, -0.3444, -0.3962, -0.6309, -0.9083, -1.2285, -1.5571, -1.9070 };		// roll rate affect on force down
static double _ZrData[10] = {  1.0942,  1.0942,  1.0028,  0.9418,  0.9053,  0.9876,  1.0698,  1.1796,  1.3228,  1.4630 };		// yaw rate affect on force down
static double _ZdcData[10] = { -0.7761, -0.7761, -0.7519, -0.7529, -0.7822, -0.9235, -1.0203, -1.1015, -1.1635, -1.1746 };		// collective input affect on force down (most important value for overall lift)
//							 {-0.9085, -0.8591, -0.8618, -0.8912, -0.8484, -0.8853, -0.9169, -1.0060, -1.1050, -1.1490, -1.1640, -1.1780 };		// Original
static double _ZdbData[10] = {-0.0163,  0.0163,  0.0915,   0.1477,  0.1976,  0.3190,  0.4508,  0.5967,  0.7272,  0.8251 };		// pitch input affect on force down
static double _ZdaData[10] = { -0.0004, -0.0004,  0.0117,  0.0176,  0.0221,  0.0385,  0.0550,  0.0621,  0.0797,  0.0955 };		// roll input affect on force down
static double _ZdpData[10] = {-0.0001, -0.0001, 0.0002,  0.0010,  0.0001,  0.0042,  0.0030,  0.0072,  0.0102,  0.0048 };		// pedal input affect on force down
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
//static double _MuData[10]  = { 0.0459,  0.0514,  0.0502,  0.0196,  0.0052,  0.0213,  0.0320,  0.0074,  0.0073,  0.0072,  0.0074,  0.0075 };		// forward speed affect on pitch
static double _MuData[10] = {   0.0100,  0.0100,  0.0100,  0.0100,  0.0100,  0.0100,  0.0080,  0.0072,  0.0052,  0.0022 };		// forward speed affect on pitch
static double _MwData[10] = { -0.0058,  -0.0058,-0.0052, -0.0140, -0.0052,  0.0022,  0.0069,  0.0091,  0.0122,  0.0146 };		// downward speed affect on pitch
static double _MqData[10] = { -0.4990,  -0.4990,-0.3600, -0.3250, -0.3500, -0.4510, -0.5140, -0.5580, -0.6060, -0.6560 };		// pitch rate affect on pitch
static double _MvData[10] = { -0.0066,  0.0066, -0.0037, -0.0024, -0.0021, -0.0030, -0.0041, -0.0056, -0.0064, -0.0068 };		// sideways speed affect on pitch
static double _MpData[10] = {  0.1970,  0.1970,  0.2030,  0.1850,  0.1800,  0.1800,  0.1830,  0.1910,  0.2060,  0.2340 };		// roll rate affect on pitch
static double _MrData[10] = {  0.0063,  0.0063,  0.0030, -0.0109,  0.0079,  0.0155,  0.0160,  0.0183,  0.0193,  0.0178 };		// yaw rate affect on pitch
static double _MdcData[10] = { -0.0007,  0.0007,  0.0015,  0.0040,  0.0050,  0.0060,  0.0070,  0.0080,  0.0090,  0.0100 };		// collective input affect on pitch
static double _MdbData[10] = { -0.0705, -0.0705, -0.0736, -0.0693, -0.0678, -0.0685, -0.0705, -0.0723, -0.0760, -0.0834 };		// pitch input affect on pitch (most important value for pitch control)
static double _MdaData[10] = {   0.0030, -0.0030, -0.0033, -0.0031, -0.0029, -0.0027, -0.0029, -0.0029, -0.0030, -0.0036 };		// roll input affect on pitch
static double _MdpData[10] = { -0.0007,  0.0007,  0.0006,  0.0010,  0.0006,  0.0012,  0.0011,  0.0022,  0.0038,  0.0048 };		// pedal input affect on pitch
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
static double _YuData[10] = { -0.0030,  0.0030,  0.0037,  0.0035,  0.0044,  0.0058,  0.0060,  0.0094,  0.0113,  0.0137 };		// forward speed affect on force out right wing
static double _YwData[10] = {  0.0025, -0.0025,  0.0033, -0.0073, -0.0076, -0.0090, -0.0076, -0.0076, -0.0067, -0.0037 };		// downward speed affect on force out right wing
static double _YqData[10] = { -0.8382, -0.8382, -1.0424, -0.9510, -0.8656, -0.7925, -0.7711, -0.7864, -0.8443, -0.9418 };		// pitch rate affect on force out right wing
static double _YvData[10] = { -0.1450, -0.1450, -0.1780, -0.1250, -0.0953, -0.1020, -0.1200, -0.1410, -0.1630, -0.1860 };		// sideways speed affect on force out right wing
static double _YpData[10] = {-0.5852, -0.5852, -0.6031, -0.6988, -0.7404, -0.7780, -0.7821, -0.6928, -0.6362, -0.4933 };		// roll rate affect on force out right wing
static double _YrData[10] = {  0.3505,  0.3505,  0.4296,  0.4309,  0.4474,  0.4958,  0.5731,  0.5717,  0.6001,  0.6458 };		// yaw rate affect on force out right wing
static double _YdcData[10] = { -0.0117,  0.0117, -0.0046,  0.0144,  0.0220,  0.0193,  0.0268,  0.0323,  0.0367,  0.0451 };		// collective input affect on force out right wing
static double _YdbData[10] = {   0.0217, -0.0217, -0.0279, -0.0266, -0.0173, -0.0164, -0.0119, -0.0113, -0.0128, -0.0146 };		// pitch input affect on force out right wing
static double _YdaData[10] = { 0.1159,  0.1159,  0.1138,  0.1069,  0.1079,  0.1035,  0.1040,  0.1033,  0.1039,  0.1078 };		// roll input affect on force out right wing
static double _YdpData[10] = { 0.1465,  0.1465,  0.1379,  0.1254,  0.1416,  0.1475,  0.1699,  0.1842,  0.1969,  0.2132 };		// pedal input affect on force out right wing
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
static double _LuData[10] = { 0.0087,  0.0087,  0.0301,  0.0081,  0.0088,  0.0085,  0.0075,  0.0076,  0.0083,  0.0098 };		// forward speed affect on roll
static double _LwData[10] = { -0.0010, -0.0010,  0.0045, -0.0001,  0.0002,  0.0036,  0.0073,  0.0136,  0.0198,  0.0287 };		// downward speed affect on roll
static double _LqData[10] = {-0.9370, -0.9370, -1.0700, -1.0000, -0.9660, -0.9460, -0.9490, -0.9630, -1.0200, -1.1000 };		// pitch rate affect on roll
static double _LvData[10] = {-0.1017, -0.1017, -0.1161, -0.0873, -0.0577, -0.0564, -0.0621, -0.0656, -0.0719, -0.0784 };		// sideways speed affect on roll
static double _LpData[10] = {-1.9000, -1.9000, -1.5200, -1.5400, -1.5600, -1.5800, -1.5700, -1.5300, -1.4800, -1.4300 };		// roll rate affect on roll
static double _LrData[10] = {-0.2100,  0.2100,  0.2420,  0.2610,  0.2650,  0.2930,  0.3180,  0.3400,  0.3490,  0.3490 };		// yaw rate affect on roll
static double _LdcData[10] = {  0.0149, -0.0149, -0.0106,  0.0039,  0.0069,  0.0174,  0.0304,  0.0476,  0.0636,  0.0840 };		// collective input affect on roll
static double _LdbData[10] = { 0.0309, -0.0309, -0.0359, -0.0315, -0.0312, -0.0330, -0.0376, -0.0448, -0.0549, -0.0693 };		// pitch input affect on roll
static double _LdaData[10] = {  0.2029,  0.2029,  0.2011,  0.1990,  0.1964,  0.1940,  0.1928,  0.1000,  0.0500,  0.0250 };		// roll input affect on roll (most important value for roll control)
// backup static double _LdaData[10] = { 0.2029,  0.2029,  0.2011,  0.1990,  0.1964,  0.1940,  0.1928,  0.1922,  0.1926,  0.1944 };		// roll input affect on roll (most important value for roll control)
static double _LdpData[10] = {-0.0904,  0.0904,  0.0850,  0.0872,  0.0872,  0.0943,  0.1040,  0.1137,  0.1230, -0.1320 };		// pedal input affect on roll
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
static double _NuData[10] = { 0.0028, -0.0028, -0.0035, -0.0042, -0.0066, -0.0071, -0.0056, -0.0025, -0.0022, -0.0015 };		// forward speed affect on yaw
//							 { 0.0620,  0.0582,  0.0438, -0.0861, -0.0702, -0.0576, -0.0468, -0.0240, -0.0239, -0.0243, -0.0247, -0.0301 };		//Original
static double _NwData[10] = {-0.0011,  0.0011, -0.0070, -0.0016, -0.0039, -0.0079, -0.0105, -0.0077, -0.0045,  0.0014 };		// downward speed affect on yaw
static double _NqData[10] = {-0.0870,  0.0870,  0.0923,  0.1010,  0.1680,  0.1150,  0.1190,  0.1390,  0.1840,  0.2570 };		// pitch rate affect on yaw
static double _NvData[10] = {0.0089,  0.0089,  0.0338,  0.0277,  0.0254,  0.0268,  0.0262,  0.0279, 0.0295,  0.0319 };		// sideways speed affect on yaw
static double _NpData[10] = {-0.1000, -0.1000, -0.1340, -0.0220, -0.0939, -0.0826, -0.0785, -0.0701, -0.0676, -0.0771 };		// roll rate affect on yaw
static double _NrData[10] = {-0.3400, -0.3400, -0.4770, -0.4970, -0.5020, -0.5610, -0.6450, -0.7220, -0.8060, -0.9060 };		// yaw rate affect on yaw
static double _NdcData[10] = { 0.0327,  0.0327,  0.0362,  0.0155,  0.0105,  0.0033,  -0.0056,  -0.0091,  -0.0091,  -0.0081 };		// collective input affect on yaw
static double _NdbData[10] = {-0.0019,  0.0019,  0.0063,  0.0011,  0.0017,  0.0050,  0.0071,  0.0094,  0.0098,  0.0087 };		// pitch input affect on yaw
static double _NdaData[10] = {0.0128,  0.0128,  0.0126,  0.0122,  0.0113,  0.0118,  0.0113,  0.0114,  0.0113,  0.0109 };		// roll input affect on yaw
static double _NdpData[10] = {-0.1385, -0.1385, -0.1302, -0.1327, -0.1342, -0.1421, -0.1589, -0.1711, -0.1837, -0.1977 };		// pedal input affect on yaw (most important value for yaw control)
//							 {-1.0293, -0.9832, -1.0879, -0.8109, -0.8245, -0.7061, -0.6862, -0.6514, -0.8815, -0.8102, -0.8019, -1.2815 };		//Original
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

static const size_t airspeed1_size = 10;
static double airspeed1[10] = { -20, 0, 20, 30, 40, 60, 80, 100, 120, 130 };


}





/*

static double _XuData[10]  = { -0.0917, -0.0917, -0.0216, -0.0160, -0.0152, -0.0272, -0.0344, -0.0400, -0.0469, -0.0540 };		// forward speed affect on force out nose
//							 {-0.0439, -0.0397, -0.0346, -0.0257, -0.0167, -0.0204, -0.0270, -0.0314, -0.0379, -0.0437, -0.0536, -0.0570 };		//Original
static double _XwData[10] = {   0.0240,  0.0240,  0.0336,  0.0434,  0.0264,  0.0295,  0.0301,  0.0309,  0.0258,  0.0162 };		// downward speed affect on force out nose
static double _XqData[10] = {  0.2652,  0.2652,  0.5671,  0.5671,  0.6279, -0.6013,  0.6293,  0.5126,  0.4686,  0.4019 };		// pitch rate affect on force out nose
static double _XvData[10] = { 0.0029,  0.0029,  0.0012, -0.0001,  0.0000, -0.006,   0.0004, -0.0042, -0.0053, -0.0055 };		// sideways speed affect on force out nose
static double _XpData[10] = { -0.8595, -0.8595, -0.8016, -0.7620, -0.7254, -0.6828, -0.6462, -0.6370, -0.6401, -0.6614 };		// roll rate affect on force out nose
static double _XrData[10] = { -0.1152, -0.1152, -0.0972, -0.0543, -0.0555, -0.0954, -0.0881, -0.1096, -0.1133, -0.0773 };		// yaw rate affect on force out nose
static double _XdcData[10] = { 0.0755,  0.0755,  0.0409,  0.0061,  0.0128,  0.0129,  0.0100,  0.0110,  0.0120,  0.0130 };		// collective input affect on force out nose
//static double _XdcData[10] = { 0.0665,   0.0526,  0.0431,  0.0755,  0.4090,  0.0061,  0.0128,  0.0149,  0.0175, -0.0031, -0.0158, -0.0289 };		// collective input affect on force out nose
static double _XdbData[10] = {  0.1823,  0.1823,  0.1747,  0.1643,  0.1612,  0.1423,  0.1391,  0.1302,  0.1326,  0.1596 };		// pitch input affect on force out nose
static double _XdaData[10] = { -0.0117,  0.0117,  0.0104,  0.0082,  0.0087,  0.0030,  0.0042,  0.0032,  0.0049,  0.0143 };		// roll input affect on force out nose
static double _XdpData[10] = { 0.0001, -0.0001, -0.0010, -0.0066, -0.0012, -0.0055, -0.0069, -0.0122, -0.0087,  0.0188 };		// pedal input affect on force out nose
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
static double _ZuData[10] = {  0.0168,  0.0168, -0.0050, -0.0100, -0.0250, -0.0423, -0.0562,  0.0143,  0.0353,  0.0494 };		// forward speed affect on force down
//							 { 0.1559,  0.1980,  0.1984, -0.0422, -0.2896, -0.1420, -0.0941, -0.0371, -0.0126,  0.0023,  0.0127,  0.0178 }; 	//Original
static double _ZwData[10] = { -0.2980, -0.2980, -0.3750, -0.4740, -0.5720, -0.6570, -0.7370, -0.7920, -0.8300, -0.8610 };		// downward speed affect on force down (1st attempt at VRS at 0 airspeed)
//							 {-0.6323, -0.5453, -0.4344,  0.1240, -0.4337, -0.5473, -0.6299, -0.7150, -0.7655, -0.7977, -0.8050, -0.8096 };		//Original
static double _ZqData[10] = {-0.0881,  0.0881, -0.0913,  0.0019,  0.0403, -0.2002, -0.4512, -0.5717, -0.9049, -1.3773 };		// pitch rate affect on force down
static double _ZvData[10] = { -0.1660, -0.1660, -0.0167, -0.0140, -0.0121, -0.0148, -0.0188, -0.0243, -0.0337, -0.0457 };		// sideways speed affect on force down
static double _ZpData[10] = {  0.0924, -0.0924, -0.2637, -0.3444, -0.3962, -0.6309, -0.9083, -1.2285, -1.5571, -1.9070 };		// roll rate affect on force down
static double _ZrData[10] = {  1.0942,  1.0942,  1.0028,  0.9418,  0.9053,  0.9876,  1.0698,  1.1796,  1.3228,  1.4630 };		// yaw rate affect on force down
static double _ZdcData[10] = { -0.7761, -0.7761, -0.7519, -0.7529, -0.7822, -0.9235, -1.0203, -1.1015, -1.1635, -1.1746 };		// collective input affect on force down (most important value for overall lift)
//							 {-0.9085, -0.8591, -0.8618, -0.8912, -0.8484, -0.8853, -0.9169, -1.0060, -1.1050, -1.1490, -1.1640, -1.1780 };		// Original
static double _ZdbData[10] = {-0.0163,  0.0163,  0.0915,   0.1477,  0.1976,  0.3190,  0.4508,  0.5967,  0.7272,  0.8251 };		// pitch input affect on force down
static double _ZdaData[10] = { -0.0004, -0.0004,  0.0117,  0.0176,  0.0221,  0.0385,  0.0550,  0.0621,  0.0797,  0.0955 };		// roll input affect on force down
static double _ZdpData[10] = {-0.0001, -0.0001, 0.0002,  0.0010,  0.0001,  0.0042,  0.0030,  0.0072,  0.0102,  0.0048 };		// pedal input affect on force down
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
//static double _MuData[10]  = { 0.0459,  0.0514,  0.0502,  0.0196,  0.0052,  0.0213,  0.0320,  0.0074,  0.0073,  0.0072,  0.0074,  0.0075 };		// forward speed affect on pitch
static double _MuData[10] = {   0.0100,  0.0100,  0.0100,  0.0100,  0.0100,  0.0100,  0.0080,  0.0072,  0.0052,  0.0022 };		// forward speed affect on pitch
static double _MwData[10] = { -0.0058,  -0.0058,-0.0052, -0.0140, -0.0052,  0.0022,  0.0069,  0.0091,  0.0122,  0.0146 };		// downward speed affect on pitch
static double _MqData[10] = { -0.4990,  -0.4990,-0.3600, -0.3250, -0.3500, -0.4510, -0.5140, -0.5580, -0.6060, -0.6560 };		// pitch rate affect on pitch
static double _MvData[10] = { -0.0066,  0.0066, -0.0037, -0.0024, -0.0021, -0.0030, -0.0041, -0.0056, -0.0064, -0.0068 };		// sideways speed affect on pitch
static double _MpData[10] = {  0.1970,  0.1970,  0.2030,  0.1850,  0.1800,  0.1800,  0.1830,  0.1910,  0.2060,  0.2340 };		// roll rate affect on pitch
static double _MrData[10] = {  0.0063,  0.0063,  0.0030, -0.0109,  0.0079,  0.0155,  0.0160,  0.0183,  0.0193,  0.0178 };		// yaw rate affect on pitch
static double _MdcData[10] = { -0.0007,  0.0007,  0.0015,  0.0040,  0.0050,  0.0060,  0.0070,  0.0080,  0.0090,  0.0100 };		// collective input affect on pitch
static double _MdbData[10] = { -0.0705, -0.0705, -0.0736, -0.0693, -0.0678, -0.0685, -0.0705, -0.0723, -0.0760, -0.0834 };		// pitch input affect on pitch (most important value for pitch control)
static double _MdaData[10] = {   0.0030, -0.0030, -0.0033, -0.0031, -0.0029, -0.0027, -0.0029, -0.0029, -0.0030, -0.0036 };		// roll input affect on pitch
static double _MdpData[10] = { -0.0007,  0.0007,  0.0006,  0.0010,  0.0006,  0.0012,  0.0011,  0.0022,  0.0038,  0.0048 };		// pedal input affect on pitch
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
static double _YuData[10] = { -0.0030,  0.0030,  0.0037,  0.0035,  0.0044,  0.0058,  0.0060,  0.0094,  0.0113,  0.0137 };		// forward speed affect on force out right wing
static double _YwData[10] = {  0.0025, -0.0025,  0.0033, -0.0073, -0.0076, -0.0090, -0.0076, -0.0076, -0.0067, -0.0037 };		// downward speed affect on force out right wing
static double _YqData[10] = { -0.8382, -0.8382, -1.0424, -0.9510, -0.8656, -0.7925, -0.7711, -0.7864, -0.8443, -0.9418 };		// pitch rate affect on force out right wing
static double _YvData[10] = { -0.1450, -0.1450, -0.1780, -0.1250, -0.0953, -0.1020, -0.1200, -0.1410, -0.1630, -0.1860 };		// sideways speed affect on force out right wing
static double _YpData[10] = {-0.5852, -0.5852, -0.6031, -0.6988, -0.7404, -0.7780, -0.7821, -0.6928, -0.6362, -0.4933 };		// roll rate affect on force out right wing
static double _YrData[10] = {  0.3505,  0.3505,  0.4296,  0.4309,  0.4474,  0.4958,  0.5731,  0.5717,  0.6001,  0.6458 };		// yaw rate affect on force out right wing
static double _YdcData[10] = { -0.0117,  0.0117, -0.0046,  0.0144,  0.0220,  0.0193,  0.0268,  0.0323,  0.0367,  0.0451 };		// collective input affect on force out right wing
static double _YdbData[10] = {   0.0217, -0.0217, -0.0279, -0.0266, -0.0173, -0.0164, -0.0119, -0.0113, -0.0128, -0.0146 };		// pitch input affect on force out right wing
static double _YdaData[10] = { 0.1159,  0.1159,  0.1138,  0.1069,  0.1079,  0.1035,  0.1040,  0.1033,  0.1039,  0.1078 };		// roll input affect on force out right wing
static double _YdpData[10] = { 0.1465,  0.1465,  0.1379,  0.1254,  0.1416,  0.1475,  0.1699,  0.1842,  0.1969,  0.2132 };		// pedal input affect on force out right wing
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
static double _LuData[10] = { 0.0087,  0.0087,  0.0301,  0.0081,  0.0088,  0.0085,  0.0075,  0.0076,  0.0083,  0.0098 };		// forward speed affect on roll
static double _LwData[10] = { -0.0010, -0.0010,  0.0045, -0.0001,  0.0002,  0.0036,  0.0073,  0.0136,  0.0198,  0.0287 };		// downward speed affect on roll
static double _LqData[10] = {-0.9370, -0.9370, -1.0700, -1.0000, -0.9660, -0.9460, -0.9490, -0.9630, -1.0200, -1.1000 };		// pitch rate affect on roll
static double _LvData[10] = {-0.1017, -0.1017, -0.1161, -0.0873, -0.0577, -0.0564, -0.0621, -0.0656, -0.0719, -0.0784 };		// sideways speed affect on roll
static double _LpData[10] = {-1.9000, -1.9000, -1.5200, -1.5400, -1.5600, -1.5800, -1.5700, -1.5300, -1.4800, -1.4300 };		// roll rate affect on roll
static double _LrData[10] = {-0.2100,  0.2100,  0.2420,  0.2610,  0.2650,  0.2930,  0.3180,  0.3400,  0.3490,  0.3490 };		// yaw rate affect on roll
static double _LdcData[10] = {  0.0149, -0.0149, -0.0106,  0.0039,  0.0069,  0.0174,  0.0304,  0.0476,  0.0636,  0.0840 };		// collective input affect on roll
static double _LdbData[10] = { 0.0309, -0.0309, -0.0359, -0.0315, -0.0312, -0.0330, -0.0376, -0.0448, -0.0549, -0.0693 };		// pitch input affect on roll
static double _LdaData[10] = {  0.2029,  0.2029,  0.2011,  0.1990,  0.1964,  0.1940,  0.1928,  0.1922,  0.1926,  0.1944 };		// roll input affect on roll (most important value for roll control)
static double _LdpData[10] = {-0.0904,  0.0904,  0.0850,  0.0872,  0.0872,  0.0943,  0.1040,  0.1137,  0.1230, -0.1320 };		// pedal input affect on roll
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
static double _NuData[10] = { 0.0028, -0.0028, -0.0035, -0.0042, -0.0066, -0.0071, -0.0056, -0.0051, -0.0059, -0.0070 };		// forward speed affect on yaw
//							 { 0.0620,  0.0582,  0.0438, -0.0861, -0.0702, -0.0576, -0.0468, -0.0240, -0.0239, -0.0243, -0.0247, -0.0301 };		//Original
static double _NwData[10] = {-0.0011,  0.0011, -0.0070, -0.0016, -0.0039, -0.0079, -0.0105, -0.0077, -0.0045,  0.0014 };		// downward speed affect on yaw
static double _NqData[10] = {-0.0870,  0.0870,  0.0923,  0.1010,  0.1680,  0.1150,  0.1190,  0.1390,  0.1840,  0.2570 };		// pitch rate affect on yaw
static double _NvData[10] = {0.0089,  0.0089,  0.0338,  0.0277,  0.0254,  0.0268,  0.0262,  0.0279, 0.0295,  0.0319 };		// sideways speed affect on yaw
static double _NpData[10] = {-0.1000, -0.1000, -0.1340, -0.0220, -0.0939, -0.0826, -0.0785, -0.0701, -0.0676, -0.0771 };		// roll rate affect on yaw
static double _NrData[10] = {-0.3400, -0.3400, -0.4770, -0.4970, -0.5020, -0.5610, -0.6450, -0.7220, -0.8060, -0.9060 };		// yaw rate affect on yaw
static double _NdcData[10] = { 0.0327,  0.0327,  0.0362,  0.0155,  0.0105,  0.0033,  -0.0056,  -0.0091,  -0.0091,  -0.0081 };		// collective input affect on yaw
static double _NdbData[10] = {-0.0019,  0.0019,  0.0063,  0.0011,  0.0017,  0.0050,  0.0071,  0.0094,  0.0098,  0.0087 };		// pitch input affect on yaw
static double _NdaData[10] = {0.0128,  0.0128,  0.0126,  0.0122,  0.0113,  0.0118,  0.0113,  0.0114,  0.0113,  0.0109 };		// roll input affect on yaw
static double _NdpData[10] = {-0.1385, -0.1385, -0.1302, -0.1327, -0.1342, -0.1421, -0.1589, -0.1711, -0.1837, -0.1977 };		// pedal input affect on yaw (most important value for yaw control)

*/