#include "src/ecma402/units.h"
#include "tests/criterion/test.h"

#include <unicode/errorcode.h>

#define TEST_SUITE ecma402Units

Test(TEST_SUITE, getAllMeasurementUnits) {
  const char **units;
  int i, j = 0;
  int unitsCount;

  units = (const char **)malloc(sizeof(const char *) * UNITS_CAPACITY);
  unitsCount = getAllMeasurementUnits(units);

  for (i = 0; i < unitsCount; i++) {
    j++;
  }

  free(units);

  /* We don't care about the values enumerated over, since we aren't testing
   * what the ICU library returns. Rather, we only care that we looped over more
   * than zero values. */
  cr_assert(gt(int, j, 1));
  cr_assert(eq(int, unitsCount, j));
}

ParameterizedTestParameters(TEST_SUITE,
                            measurementUnitsDoNotIncludeAnyCurrencyCodes) {
  char **tests = cr_malloc(sizeof(*tests) * 305);

  tests[0] = testStrdup("ADP");
  tests[1] = testStrdup("AED");
  tests[2] = testStrdup("AFA");
  tests[3] = testStrdup("AFN");
  tests[4] = testStrdup("ALK");
  tests[5] = testStrdup("ALL");
  tests[6] = testStrdup("AMD");
  tests[7] = testStrdup("ANG");
  tests[8] = testStrdup("AOA");
  tests[9] = testStrdup("AOK");
  tests[10] = testStrdup("AON");
  tests[11] = testStrdup("AOR");
  tests[12] = testStrdup("ARA");
  tests[13] = testStrdup("ARL");
  tests[14] = testStrdup("ARM");
  tests[15] = testStrdup("ARP");
  tests[16] = testStrdup("ARS");
  tests[17] = testStrdup("ATS");
  tests[18] = testStrdup("AUD");
  tests[19] = testStrdup("AWG");
  tests[20] = testStrdup("AZM");
  tests[21] = testStrdup("AZN");
  tests[22] = testStrdup("BAD");
  tests[23] = testStrdup("BAM");
  tests[24] = testStrdup("BAN");
  tests[25] = testStrdup("BBD");
  tests[26] = testStrdup("BDT");
  tests[27] = testStrdup("BEC");
  tests[28] = testStrdup("BEF");
  tests[29] = testStrdup("BEL");
  tests[30] = testStrdup("BGL");
  tests[31] = testStrdup("BGM");
  tests[32] = testStrdup("BGN");
  tests[33] = testStrdup("BGO");
  tests[34] = testStrdup("BHD");
  tests[35] = testStrdup("BIF");
  tests[36] = testStrdup("BMD");
  tests[37] = testStrdup("BND");
  tests[38] = testStrdup("BOB");
  tests[39] = testStrdup("BOL");
  tests[40] = testStrdup("BOP");
  tests[41] = testStrdup("BOV");
  tests[42] = testStrdup("BRB");
  tests[43] = testStrdup("BRC");
  tests[44] = testStrdup("BRE");
  tests[45] = testStrdup("BRL");
  tests[46] = testStrdup("BRN");
  tests[47] = testStrdup("BRR");
  tests[48] = testStrdup("BRZ");
  tests[49] = testStrdup("BSD");
  tests[50] = testStrdup("BTN");
  tests[51] = testStrdup("BUK");
  tests[52] = testStrdup("BWP");
  tests[53] = testStrdup("BYB");
  tests[54] = testStrdup("BYN");
  tests[55] = testStrdup("BYR");
  tests[56] = testStrdup("BZD");
  tests[57] = testStrdup("CAD");
  tests[58] = testStrdup("CDF");
  tests[59] = testStrdup("CHE");
  tests[60] = testStrdup("CHF");
  tests[61] = testStrdup("CHW");
  tests[62] = testStrdup("CLE");
  tests[63] = testStrdup("CLF");
  tests[64] = testStrdup("CLP");
  tests[65] = testStrdup("CNH");
  tests[66] = testStrdup("CNX");
  tests[67] = testStrdup("CNY");
  tests[68] = testStrdup("COP");
  tests[69] = testStrdup("COU");
  tests[70] = testStrdup("CRC");
  tests[71] = testStrdup("CSD");
  tests[72] = testStrdup("CSK");
  tests[73] = testStrdup("CUC");
  tests[74] = testStrdup("CUP");
  tests[75] = testStrdup("CVE");
  tests[76] = testStrdup("CYP");
  tests[77] = testStrdup("CZK");
  tests[78] = testStrdup("DDM");
  tests[79] = testStrdup("DEM");
  tests[80] = testStrdup("DJF");
  tests[81] = testStrdup("DKK");
  tests[82] = testStrdup("DOP");
  tests[83] = testStrdup("DZD");
  tests[84] = testStrdup("ECS");
  tests[85] = testStrdup("ECV");
  tests[86] = testStrdup("EEK");
  tests[87] = testStrdup("EGP");
  tests[88] = testStrdup("ERN");
  tests[89] = testStrdup("ESA");
  tests[90] = testStrdup("ESB");
  tests[91] = testStrdup("ESP");
  tests[92] = testStrdup("ETB");
  tests[93] = testStrdup("EUR");
  tests[94] = testStrdup("FIM");
  tests[95] = testStrdup("FJD");
  tests[96] = testStrdup("FKP");
  tests[97] = testStrdup("FRF");
  tests[98] = testStrdup("GBP");
  tests[99] = testStrdup("GEK");
  tests[100] = testStrdup("GEL");
  tests[101] = testStrdup("GHC");
  tests[102] = testStrdup("GHS");
  tests[103] = testStrdup("GIP");
  tests[104] = testStrdup("GMD");
  tests[105] = testStrdup("GNF");
  tests[106] = testStrdup("GNS");
  tests[107] = testStrdup("GQE");
  tests[108] = testStrdup("GRD");
  tests[109] = testStrdup("GTQ");
  tests[110] = testStrdup("GWE");
  tests[111] = testStrdup("GWP");
  tests[112] = testStrdup("GYD");
  tests[113] = testStrdup("HKD");
  tests[114] = testStrdup("HNL");
  tests[115] = testStrdup("HRD");
  tests[116] = testStrdup("HRK");
  tests[117] = testStrdup("HTG");
  tests[118] = testStrdup("HUF");
  tests[119] = testStrdup("IDR");
  tests[120] = testStrdup("IEP");
  tests[121] = testStrdup("ILP");
  tests[122] = testStrdup("ILR");
  tests[123] = testStrdup("ILS");
  tests[124] = testStrdup("INR");
  tests[125] = testStrdup("IQD");
  tests[126] = testStrdup("IRR");
  tests[127] = testStrdup("ISJ");
  tests[128] = testStrdup("ISK");
  tests[129] = testStrdup("ITL");
  tests[130] = testStrdup("JMD");
  tests[131] = testStrdup("JOD");
  tests[132] = testStrdup("JPY");
  tests[133] = testStrdup("KES");
  tests[134] = testStrdup("KGS");
  tests[135] = testStrdup("KHR");
  tests[136] = testStrdup("KMF");
  tests[137] = testStrdup("KPW");
  tests[138] = testStrdup("KRH");
  tests[139] = testStrdup("KRO");
  tests[140] = testStrdup("KRW");
  tests[141] = testStrdup("KWD");
  tests[142] = testStrdup("KYD");
  tests[143] = testStrdup("KZT");
  tests[144] = testStrdup("LAK");
  tests[145] = testStrdup("LBP");
  tests[146] = testStrdup("LKR");
  tests[147] = testStrdup("LRD");
  tests[148] = testStrdup("LSL");
  tests[149] = testStrdup("LTL");
  tests[150] = testStrdup("LTT");
  tests[151] = testStrdup("LUC");
  tests[152] = testStrdup("LUF");
  tests[153] = testStrdup("LUL");
  tests[154] = testStrdup("LVL");
  tests[155] = testStrdup("LVR");
  tests[156] = testStrdup("LYD");
  tests[157] = testStrdup("MAD");
  tests[158] = testStrdup("MAF");
  tests[159] = testStrdup("MCF");
  tests[160] = testStrdup("MDC");
  tests[161] = testStrdup("MDL");
  tests[162] = testStrdup("MGA");
  tests[163] = testStrdup("MGF");
  tests[164] = testStrdup("MKD");
  tests[165] = testStrdup("MKN");
  tests[166] = testStrdup("MLF");
  tests[167] = testStrdup("MMK");
  tests[168] = testStrdup("MNT");
  tests[169] = testStrdup("MOP");
  tests[170] = testStrdup("MRO");
  tests[171] = testStrdup("MRU");
  tests[172] = testStrdup("MTL");
  tests[173] = testStrdup("MTP");
  tests[174] = testStrdup("MUR");
  tests[175] = testStrdup("MVP");
  tests[176] = testStrdup("MVR");
  tests[177] = testStrdup("MWK");
  tests[178] = testStrdup("MXN");
  tests[179] = testStrdup("MXP");
  tests[180] = testStrdup("MXV");
  tests[181] = testStrdup("MYR");
  tests[182] = testStrdup("MZE");
  tests[183] = testStrdup("MZM");
  tests[184] = testStrdup("MZN");
  tests[185] = testStrdup("NAD");
  tests[186] = testStrdup("NGN");
  tests[187] = testStrdup("NIC");
  tests[188] = testStrdup("NIO");
  tests[189] = testStrdup("NLG");
  tests[190] = testStrdup("NOK");
  tests[191] = testStrdup("NPR");
  tests[192] = testStrdup("NZD");
  tests[193] = testStrdup("OMR");
  tests[194] = testStrdup("PAB");
  tests[195] = testStrdup("PEI");
  tests[196] = testStrdup("PEN");
  tests[197] = testStrdup("PES");
  tests[198] = testStrdup("PGK");
  tests[199] = testStrdup("PHP");
  tests[200] = testStrdup("PKR");
  tests[201] = testStrdup("PLN");
  tests[202] = testStrdup("PLZ");
  tests[203] = testStrdup("PTE");
  tests[204] = testStrdup("PYG");
  tests[205] = testStrdup("QAR");
  tests[206] = testStrdup("RHD");
  tests[207] = testStrdup("ROL");
  tests[208] = testStrdup("RON");
  tests[209] = testStrdup("RSD");
  tests[210] = testStrdup("RUB");
  tests[211] = testStrdup("RUR");
  tests[212] = testStrdup("RWF");
  tests[213] = testStrdup("SAR");
  tests[214] = testStrdup("SBD");
  tests[215] = testStrdup("SCR");
  tests[216] = testStrdup("SDD");
  tests[217] = testStrdup("SDG");
  tests[218] = testStrdup("SDP");
  tests[219] = testStrdup("SEK");
  tests[220] = testStrdup("SGD");
  tests[221] = testStrdup("SHP");
  tests[222] = testStrdup("SIT");
  tests[223] = testStrdup("SKK");
  tests[224] = testStrdup("SLE");
  tests[225] = testStrdup("SLL");
  tests[226] = testStrdup("SOS");
  tests[227] = testStrdup("SRD");
  tests[228] = testStrdup("SRG");
  tests[229] = testStrdup("SSP");
  tests[230] = testStrdup("STD");
  tests[231] = testStrdup("STN");
  tests[232] = testStrdup("SUR");
  tests[233] = testStrdup("SVC");
  tests[234] = testStrdup("SYP");
  tests[235] = testStrdup("SZL");
  tests[236] = testStrdup("THB");
  tests[237] = testStrdup("TJR");
  tests[238] = testStrdup("TJS");
  tests[239] = testStrdup("TMM");
  tests[240] = testStrdup("TMT");
  tests[241] = testStrdup("TND");
  tests[242] = testStrdup("TOP");
  tests[243] = testStrdup("TPE");
  tests[244] = testStrdup("TRL");
  tests[245] = testStrdup("TRY");
  tests[246] = testStrdup("TTD");
  tests[247] = testStrdup("TWD");
  tests[248] = testStrdup("TZS");
  tests[249] = testStrdup("UAH");
  tests[250] = testStrdup("UAK");
  tests[251] = testStrdup("UGS");
  tests[252] = testStrdup("UGX");
  tests[253] = testStrdup("USD");
  tests[254] = testStrdup("USN");
  tests[255] = testStrdup("USS");
  tests[256] = testStrdup("UYI");
  tests[257] = testStrdup("UYP");
  tests[258] = testStrdup("UYU");
  tests[259] = testStrdup("UYW");
  tests[260] = testStrdup("UZS");
  tests[261] = testStrdup("VEB");
  tests[262] = testStrdup("VEF");
  tests[263] = testStrdup("VES");
  tests[264] = testStrdup("VED");
  tests[265] = testStrdup("VND");
  tests[266] = testStrdup("VNN");
  tests[267] = testStrdup("VUV");
  tests[268] = testStrdup("WST");
  tests[269] = testStrdup("XAF");
  tests[270] = testStrdup("XAG");
  tests[271] = testStrdup("XAU");
  tests[272] = testStrdup("XBA");
  tests[273] = testStrdup("XBB");
  tests[274] = testStrdup("XBC");
  tests[275] = testStrdup("XBD");
  tests[276] = testStrdup("XCD");
  tests[277] = testStrdup("XDR");
  tests[278] = testStrdup("XEU");
  tests[279] = testStrdup("XFO");
  tests[280] = testStrdup("XFU");
  tests[281] = testStrdup("XOF");
  tests[282] = testStrdup("XPD");
  tests[283] = testStrdup("XPF");
  tests[284] = testStrdup("XPT");
  tests[285] = testStrdup("XRE");
  tests[286] = testStrdup("XSU");
  tests[287] = testStrdup("XTS");
  tests[288] = testStrdup("XUA");
  tests[289] = testStrdup("XXX");
  tests[290] = testStrdup("YDD");
  tests[291] = testStrdup("YER");
  tests[292] = testStrdup("YUD");
  tests[293] = testStrdup("YUM");
  tests[294] = testStrdup("YUN");
  tests[295] = testStrdup("YUR");
  tests[296] = testStrdup("ZAL");
  tests[297] = testStrdup("ZAR");
  tests[298] = testStrdup("ZMK");
  tests[299] = testStrdup("ZMW");
  tests[300] = testStrdup("ZRN");
  tests[301] = testStrdup("ZRZ");
  tests[302] = testStrdup("ZWD");
  tests[303] = testStrdup("ZWL");
  tests[304] = testStrdup("ZWR");

  return cr_make_param_array(const char *, tests, 305, testFreeStrings);
}

ParameterizedTest(char **input, TEST_SUITE,
                  measurementUnitsDoNotIncludeAnyCurrencyCodes) {
  const char **units;
  int unitsCount;

  units = (const char **)malloc(sizeof(const char *) * UNITS_CAPACITY);
  unitsCount = getAllMeasurementUnits(units);

  for (int i = 0; i < unitsCount; i++) {
    cr_expect(ne(str, (char *)units[i], *input),
              "Currency code \"%s\" should not be in measurement units",
              *input);
  }

  free(units);
}
