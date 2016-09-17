/**
* UnicodeType:
 * @UNICODE_CONTROL: General category "Other, Control" (Cc)
 * @UNICODE_FORMAT: General category "Other, Format" (Cf)
 * @UNICODE_UNASSIGNED: General category "Other, Not Assigned" (Cn)
 * @UNICODE_PRIVATE_USE: General category "Other, Private Use" (Co)
 * @UNICODE_SURROGATE: General category "Other, Surrogate" (Cs)
 * @UNICODE_LOWERCASE_LETTER: General category "Letter, Lowercase" (Ll)
 * @UNICODE_MODIFIER_LETTER: General category "Letter, Modifier" (Lm)
 * @UNICODE_OTHER_LETTER: General category "Letter, Other" (Lo)
 * @UNICODE_TITLECASE_LETTER: General category "Letter, Titlecase" (Lt)
 * @UNICODE_UPPERCASE_LETTER: General category "Letter, Uppercase" (Lu)
 * @UNICODE_SPACING_MARK: General category "Mark, Spacing" (Mc)
 * @UNICODE_ENCLOSING_MARK: General category "Mark, Enclosing" (Me)
 * @UNICODE_NON_SPACING_MARK: General category "Mark, Nonspacing" (Mn)
 * @UNICODE_DECIMAL_NUMBER: General category "Number, Decimal Digit" (Nd)
 * @UNICODE_LETTER_NUMBER: General category "Number, Letter" (Nl)
 * @UNICODE_OTHER_NUMBER: General category "Number, Other" (No)
 * @UNICODE_CONNECT_PUNCTUATION: General category "Punctuation, Connector" (Pc)
 * @UNICODE_DASH_PUNCTUATION: General category "Punctuation, Dash" (Pd)
 * @UNICODE_CLOSE_PUNCTUATION: General category "Punctuation, Close" (Pe)
 * @UNICODE_FINAL_PUNCTUATION: General category "Punctuation, Final quote" (Pf)
 * @UNICODE_INITIAL_PUNCTUATION: General category "Punctuation, Initial quote" (Pi)
 * @UNICODE_OTHER_PUNCTUATION: General category "Punctuation, Other" (Po)
 * @UNICODE_OPEN_PUNCTUATION: General category "Punctuation, Open" (Ps)
 * @UNICODE_CURRENCY_SYMBOL: General category "Symbol, Currency" (Sc)
 * @UNICODE_MODIFIER_SYMBOL: General category "Symbol, Modifier" (Sk)
 * @UNICODE_MATH_SYMBOL: General category "Symbol, Math" (Sm)
 * @UNICODE_OTHER_SYMBOL: General category "Symbol, Other" (So)
 * @UNICODE_LINE_SEPARATOR: General category "Separator, Line" (Zl)
 * @UNICODE_PARAGRAPH_SEPARATOR: General category "Separator, Paragraph" (Zp)
 * @UNICODE_SPACE_SEPARATOR: General category "Separator, Space" (Zs)
 *
 * These are the possible character classifications from the
 * Unicode specification.
 * See <ulink url="http://www.unicode.org/reports/tr44/#General_Category_Values">Unicode Character Database</unlink>.
 */
typedef enum
{
  UNICODE_CONTROL,
  UNICODE_FORMAT,
  UNICODE_UNASSIGNED,
  UNICODE_PRIVATE_USE,
  UNICODE_SURROGATE,
  UNICODE_LOWERCASE_LETTER,
  UNICODE_MODIFIER_LETTER,
  UNICODE_OTHER_LETTER,
  UNICODE_TITLECASE_LETTER,
  UNICODE_UPPERCASE_LETTER,
  UNICODE_SPACING_MARK,
  UNICODE_ENCLOSING_MARK,
  UNICODE_NON_SPACING_MARK,
  UNICODE_DECIMAL_NUMBER,
  UNICODE_LETTER_NUMBER,
  UNICODE_OTHER_NUMBER,
  UNICODE_CONNECT_PUNCTUATION,
  UNICODE_DASH_PUNCTUATION,
  UNICODE_CLOSE_PUNCTUATION,
  UNICODE_FINAL_PUNCTUATION,
  UNICODE_INITIAL_PUNCTUATION,
  UNICODE_OTHER_PUNCTUATION,
  UNICODE_OPEN_PUNCTUATION,
  UNICODE_CURRENCY_SYMBOL,
  UNICODE_MODIFIER_SYMBOL,
  UNICODE_MATH_SYMBOL,
  UNICODE_OTHER_SYMBOL,
  UNICODE_LINE_SEPARATOR,
  UNICODE_PARAGRAPH_SEPARATOR,
  UNICODE_SPACE_SEPARATOR
} UnicodeType;
/**
* UnicodeBreakType:
 * @UNICODE_BREAK_MANDATORY: Mandatory Break (BK)
 * @UNICODE_BREAK_CARRIAGE_RETURN: Carriage Return (CR)
 * @UNICODE_BREAK_LINE_FEED: Line Feed (LF)
 * @UNICODE_BREAK_COMBINING_MARK: Attached Characters and Combining Marks (CM)
 * @UNICODE_BREAK_SURROGATE: Surrogates (SG)
 * @UNICODE_BREAK_ZERO_WIDTH_SPACE: Zero Width Space (ZW)
 * @UNICODE_BREAK_INSEPARABLE: Inseparable (IN)
 * @UNICODE_BREAK_NON_BREAKING_GLUE: Non-breaking ("Glue") (GL)
 * @UNICODE_BREAK_CONTINGENT: Contingent Break Opportunity (CB)
 * @UNICODE_BREAK_SPACE: Space (SP)
 * @UNICODE_BREAK_AFTER: Break Opportunity After (BA)
 * @UNICODE_BREAK_BEFORE: Break Opportunity Before (BB)
 * @UNICODE_BREAK_BEFORE_AND_AFTER: Break Opportunity Before and After (B2)
 * @UNICODE_BREAK_HYPHEN: Hyphen (HY)
 * @UNICODE_BREAK_NON_STARTER: Nonstarter (NS)
 * @UNICODE_BREAK_OPEN_PUNCTUATION: Opening Punctuation (OP)
 * @UNICODE_BREAK_CLOSE_PUNCTUATION: Closing Punctuation (CL)
 * @UNICODE_BREAK_QUOTATION: Ambiguous Quotation (QU)
 * @UNICODE_BREAK_EXCLAMATION: Exclamation/Interrogation (EX)
 * @UNICODE_BREAK_IDEOGRAPHIC: Ideographic (ID)
 * @UNICODE_BREAK_NUMERIC: Numeric (NU)
 * @UNICODE_BREAK_INFIX_SEPARATOR: Infix Separator (Numeric) (IS)
 * @UNICODE_BREAK_SYMBOL: Symbols Allowing Break After (SY)
 * @UNICODE_BREAK_ALPHABETIC: Ordinary Alphabetic and Symbol Characters (AL)
 * @UNICODE_BREAK_PREFIX: Prefix (Numeric) (PR)
 * @UNICODE_BREAK_POSTFIX: Postfix (Numeric) (PO)
 * @UNICODE_BREAK_COMPLEX_CONTEXT: Complex Content Dependent (South East Asian) (SA)
 * @UNICODE_BREAK_AMBIGUOUS: Ambiguous (Alphabetic or Ideographic) (AI)
 * @UNICODE_BREAK_UNKNOWN: Unknown (XX)
 * @UNICODE_BREAK_NEXT_LINE: Next Line (NL)
 * @UNICODE_BREAK_WORD_JOINER: Word Joiner (WJ)
 * @UNICODE_BREAK_HANGUL_L_JAMO: Hangul L Jamo (JL)
 * @UNICODE_BREAK_HANGUL_V_JAMO: Hangul V Jamo (JV)
 * @UNICODE_BREAK_HANGUL_T_JAMO: Hangul T Jamo (JT)
 * @UNICODE_BREAK_HANGUL_LV_SYLLABLE: Hangul LV Syllable (H2)
 * @UNICODE_BREAK_HANGUL_LVT_SYLLABLE: Hangul LVT Syllable (H3)
 * @UNICODE_BREAK_CLOSE_PARANTHESIS: Closing Parenthesis (CP). Since 2.28
 * @UNICODE_BREAK_CONDITIONAL_JAPANESE_STARTER: Conditional Japanese Starter (CJ). Since: 2.32
 * @UNICODE_BREAK_HEBREW_LETTER: Hebrew Letter (HL). Since: 2.32
 * @UNICODE_BREAK_REGIONAL_INDICATOR: Regional Indicator (RI). Since: 2.36
 *
 * These are the possible line break classifications.
 *
 * Since new unicode versions may add new types here, applications should be ready 
 * to handle unknown values. They may be regarded as %UNICODE_BREAK_UNKNOWN.
 *
 * See <ulink url="http://www.unicode.org/unicode/reports/tr14/">http://www.unicode.org/unicode/reports/tr14/</ulink>.
 */
typedef enum
{
  UNICODE_BREAK_MANDATORY,
  UNICODE_BREAK_CARRIAGE_RETURN,
  UNICODE_BREAK_LINE_FEED,
  UNICODE_BREAK_COMBINING_MARK,
  UNICODE_BREAK_SURROGATE,
  UNICODE_BREAK_ZERO_WIDTH_SPACE,
  UNICODE_BREAK_INSEPARABLE,
  UNICODE_BREAK_NON_BREAKING_GLUE,
  UNICODE_BREAK_CONTINGENT,
  UNICODE_BREAK_SPACE,
  UNICODE_BREAK_AFTER,
  UNICODE_BREAK_BEFORE,
  UNICODE_BREAK_BEFORE_AND_AFTER,
  UNICODE_BREAK_HYPHEN,
  UNICODE_BREAK_NON_STARTER,
  UNICODE_BREAK_OPEN_PUNCTUATION,
  UNICODE_BREAK_CLOSE_PUNCTUATION,
  UNICODE_BREAK_QUOTATION,
  UNICODE_BREAK_EXCLAMATION,
  UNICODE_BREAK_IDEOGRAPHIC,
  UNICODE_BREAK_NUMERIC,
  UNICODE_BREAK_INFIX_SEPARATOR,
  UNICODE_BREAK_SYMBOL,
  UNICODE_BREAK_ALPHABETIC,
  UNICODE_BREAK_PREFIX,
  UNICODE_BREAK_POSTFIX,
  UNICODE_BREAK_COMPLEX_CONTEXT,
  UNICODE_BREAK_AMBIGUOUS,
  UNICODE_BREAK_UNKNOWN,
  UNICODE_BREAK_NEXT_LINE,
  UNICODE_BREAK_WORD_JOINER,
  UNICODE_BREAK_HANGUL_L_JAMO,
  UNICODE_BREAK_HANGUL_V_JAMO,
  UNICODE_BREAK_HANGUL_T_JAMO,
  UNICODE_BREAK_HANGUL_LV_SYLLABLE,
  UNICODE_BREAK_HANGUL_LVT_SYLLABLE,
  UNICODE_BREAK_CLOSE_PARANTHESIS,
  UNICODE_BREAK_CONDITIONAL_JAPANESE_STARTER,
  UNICODE_BREAK_HEBREW_LETTER,
  UNICODE_BREAK_REGIONAL_INDICATOR
} UnicodeBreakType;
/**
* UnicodeScript:
 * @UNICODE_SCRIPT_INVALID_CODE:
 *                               a value never returned from g_unichar_get_script()
 * @UNICODE_SCRIPT_COMMON:     a character used by multiple different scripts
 * @UNICODE_SCRIPT_INHERITED:  a mark glyph that takes its script from the
 *                               base glyph to which it is attached
 * @UNICODE_SCRIPT_ARABIC:     Arabic
 * @UNICODE_SCRIPT_ARMENIAN:   Armenian
 * @UNICODE_SCRIPT_BENGALI:    Bengali
 * @UNICODE_SCRIPT_BOPOMOFO:   Bopomofo
 * @UNICODE_SCRIPT_CHEROKEE:   Cherokee
 * @UNICODE_SCRIPT_COPTIC:     Coptic
 * @UNICODE_SCRIPT_CYRILLIC:   Cyrillic
 * @UNICODE_SCRIPT_DESERET:    Deseret
 * @UNICODE_SCRIPT_DEVANAGARI: Devanagari
 * @UNICODE_SCRIPT_ETHIOPIC:   Ethiopic
 * @UNICODE_SCRIPT_GEORGIAN:   Georgian
 * @UNICODE_SCRIPT_GOTHIC:     Gothic
 * @UNICODE_SCRIPT_GREEK:      Greek
 * @UNICODE_SCRIPT_GUJARATI:   Gujarati
 * @UNICODE_SCRIPT_GURMUKHI:   Gurmukhi
 * @UNICODE_SCRIPT_HAN:        Han
 * @UNICODE_SCRIPT_HANGUL:     Hangul
 * @UNICODE_SCRIPT_HEBREW:     Hebrew
 * @UNICODE_SCRIPT_HIRAGANA:   Hiragana
 * @UNICODE_SCRIPT_KANNADA:    Kannada
 * @UNICODE_SCRIPT_KATAKANA:   Katakana
 * @UNICODE_SCRIPT_KHMER:      Khmer
 * @UNICODE_SCRIPT_LAO:        Lao
 * @UNICODE_SCRIPT_LATIN:      Latin
 * @UNICODE_SCRIPT_MALAYALAM:  Malayalam
 * @UNICODE_SCRIPT_MONGOLIAN:  Mongolian
 * @UNICODE_SCRIPT_MYANMAR:    Myanmar
 * @UNICODE_SCRIPT_OGHAM:      Ogham
 * @UNICODE_SCRIPT_OLD_ITALIC: Old Italic
 * @UNICODE_SCRIPT_ORIYA:      Oriya
 * @UNICODE_SCRIPT_RUNIC:      Runic
 * @UNICODE_SCRIPT_SINHALA:    Sinhala
 * @UNICODE_SCRIPT_SYRIAC:     Syriac
 * @UNICODE_SCRIPT_TAMIL:      Tamil
 * @UNICODE_SCRIPT_TELUGU:     Telugu
 * @UNICODE_SCRIPT_THAANA:     Thaana
 * @UNICODE_SCRIPT_THAI:       Thai
 * @UNICODE_SCRIPT_TIBETAN:    Tibetan
 * @UNICODE_SCRIPT_CANADIAN_ABORIGINAL:
 *                               Canadian Aboriginal
 * @UNICODE_SCRIPT_YI:         Yi
 * @UNICODE_SCRIPT_TAGALOG:    Tagalog
 * @UNICODE_SCRIPT_HANUNOO:    Hanunoo
 * @UNICODE_SCRIPT_BUHID:      Buhid
 * @UNICODE_SCRIPT_TAGBANWA:   Tagbanwa
 * @UNICODE_SCRIPT_BRAILLE:    Braille
 * @UNICODE_SCRIPT_CYPRIOT:    Cypriot
 * @UNICODE_SCRIPT_LIMBU:      Limbu
 * @UNICODE_SCRIPT_OSMANYA:    Osmanya
 * @UNICODE_SCRIPT_SHAVIAN:    Shavian
 * @UNICODE_SCRIPT_LINEAR_B:   Linear B
 * @UNICODE_SCRIPT_TAI_LE:     Tai Le
 * @UNICODE_SCRIPT_UGARITIC:   Ugaritic
 * @UNICODE_SCRIPT_NEW_TAI_LUE:
 *                               New Tai Lue
 * @UNICODE_SCRIPT_BUGINESE:   Buginese
 * @UNICODE_SCRIPT_GLAGOLITIC: Glagolitic
 * @UNICODE_SCRIPT_TIFINAGH:   Tifinagh
 * @UNICODE_SCRIPT_SYLOTI_NAGRI:
 *                               Syloti Nagri
 * @UNICODE_SCRIPT_OLD_PERSIAN:
 *                               Old Persian
 * @UNICODE_SCRIPT_KHAROSHTHI: Kharoshthi
 * @UNICODE_SCRIPT_UNKNOWN:    an unassigned code point
 * @UNICODE_SCRIPT_BALINESE:   Balinese
 * @UNICODE_SCRIPT_CUNEIFORM:  Cuneiform
 * @UNICODE_SCRIPT_PHOENICIAN: Phoenician
 * @UNICODE_SCRIPT_PHAGS_PA:   Phags-pa
 * @UNICODE_SCRIPT_NKO:        N'Ko
 * @UNICODE_SCRIPT_KAYAH_LI:   Kayah Li. Since 2.16.3
 * @UNICODE_SCRIPT_LEPCHA:     Lepcha. Since 2.16.3
 * @UNICODE_SCRIPT_REJANG:     Rejang. Since 2.16.3
 * @UNICODE_SCRIPT_SUNDANESE:  Sundanese. Since 2.16.3
 * @UNICODE_SCRIPT_SAURASHTRA: Saurashtra. Since 2.16.3
 * @UNICODE_SCRIPT_CHAM:       Cham. Since 2.16.3
 * @UNICODE_SCRIPT_OL_CHIKI:   Ol Chiki. Since 2.16.3
 * @UNICODE_SCRIPT_VAI:        Vai. Since 2.16.3
 * @UNICODE_SCRIPT_CARIAN:     Carian. Since 2.16.3
 * @UNICODE_SCRIPT_LYCIAN:     Lycian. Since 2.16.3
 * @UNICODE_SCRIPT_LYDIAN:     Lydian. Since 2.16.3
 * @UNICODE_SCRIPT_AVESTAN:    Avestan. Since 2.26
 * @UNICODE_SCRIPT_BAMUM:      Bamum. Since 2.26
 * @UNICODE_SCRIPT_EGYPTIAN_HIEROGLYPHS:
 *                               Egyptian Hieroglpyhs. Since 2.26
 * @UNICODE_SCRIPT_IMPERIAL_ARAMAIC:
 *                               Imperial Aramaic. Since 2.26
 * @UNICODE_SCRIPT_INSCRIPTIONAL_PAHLAVI:
 *                               Inscriptional Pahlavi. Since 2.26
 * @UNICODE_SCRIPT_INSCRIPTIONAL_PARTHIAN:
 *                               Inscriptional Parthian. Since 2.26
 * @UNICODE_SCRIPT_JAVANESE:   Javanese. Since 2.26
 * @UNICODE_SCRIPT_KAITHI:     Kaithi. Since 2.26
 * @UNICODE_SCRIPT_LISU:       Lisu. Since 2.26
 * @UNICODE_SCRIPT_MEETEI_MAYEK:
 *                               Meetei Mayek. Since 2.26
 * @UNICODE_SCRIPT_OLD_SOUTH_ARABIAN:
 *                               Old South Arabian. Since 2.26
 * @UNICODE_SCRIPT_OLD_TURKIC: Old Turkic. Since 2.28
 * @UNICODE_SCRIPT_SAMARITAN:  Samaritan. Since 2.26
 * @UNICODE_SCRIPT_TAI_THAM:   Tai Tham. Since 2.26
 * @UNICODE_SCRIPT_TAI_VIET:   Tai Viet. Since 2.26
 * @UNICODE_SCRIPT_BATAK:      Batak. Since 2.28
 * @UNICODE_SCRIPT_BRAHMI:     Brahmi. Since 2.28
 * @UNICODE_SCRIPT_MANDAIC:    Mandaic. Since 2.28
 * @UNICODE_SCRIPT_CHAKMA:               Chakma. Since: 2.32
 * @UNICODE_SCRIPT_MEROITIC_CURSIVE:     Meroitic Cursive. Since: 2.32
 * @UNICODE_SCRIPT_MEROITIC_HIEROGLYPHS: Meroitic Hieroglyphs. Since: 2.32
 * @UNICODE_SCRIPT_MIAO:                 Miao. Since: 2.32
 * @UNICODE_SCRIPT_SHARADA:              Sharada. Since: 2.32
 * @UNICODE_SCRIPT_SORA_SOMPENG:         Sora Sompeng. Since: 2.32
 * @UNICODE_SCRIPT_TAKRI:                Takri. Since: 2.32
 * @UNICODE_SCRIPT_BASSA_VAH:            Bassa. Since: 2.42
 * @UNICODE_SCRIPT_CAUCASIAN_ALBANIAN:   Caucasian Albanian. Since: 2.42
 * @UNICODE_SCRIPT_DUPLOYAN:             Duployan. Since: 2.42
 * @UNICODE_SCRIPT_ELBASAN:              Elbasan. Since: 2.42
 * @UNICODE_SCRIPT_GRANTHA:              Grantha. Since: 2.42
 * @UNICODE_SCRIPT_KHOJKI:               Kjohki. Since: 2.42
 * @UNICODE_SCRIPT_KHUDAWADI:            Khudawadi, Sindhi. Since: 2.42
 * @UNICODE_SCRIPT_LINEAR_A:             Linear A. Since: 2.42
 * @UNICODE_SCRIPT_MAHAJANI:             Mahajani. Since: 2.42
 * @UNICODE_SCRIPT_MANICHAEAN:           Manichaean. Since: 2.42
 * @UNICODE_SCRIPT_MENDE_KIKAKUI:        Mende Kikakui. Since: 2.42
 * @UNICODE_SCRIPT_MODI:                 Modi. Since: 2.42
 * @UNICODE_SCRIPT_MRO:                  Mro. Since: 2.42
 * @UNICODE_SCRIPT_NABATAEAN:            Nabataean. Since: 2.42
 * @UNICODE_SCRIPT_OLD_NORTH_ARABIAN:    Old North Arabian. Since: 2.42
 * @UNICODE_SCRIPT_OLD_PERMIC:           Old Permic. Since: 2.42
 * @UNICODE_SCRIPT_PAHAWH_HMONG:         Pahawh Hmong. Since: 2.42
 * @UNICODE_SCRIPT_PALMYRENE:            Palmyrene. Since: 2.42
 * @UNICODE_SCRIPT_PAU_CIN_HAU:          Pau Cin Hau. Since: 2.42
 * @UNICODE_SCRIPT_PSALTER_PAHLAVI:      Psalter Pahlavi. Since: 2.42
 * @UNICODE_SCRIPT_SIDDHAM:              Siddham. Since: 2.42
 * @UNICODE_SCRIPT_TIRHUTA:              Tirhuta. Since: 2.42
 * @UNICODE_SCRIPT_WARANG_CITI:          Warang Citi. Since: 2.42
 * @UNICODE_SCRIPT_AHOM:                 Ahom. Since: 2.48
 * @UNICODE_SCRIPT_ANATOLIAN_HIEROGLYPHS: Anatolian Hieroglyphs. Since: 2.48
 * @UNICODE_SCRIPT_HATRAN:               Hatran. Since: 2.48
 * @UNICODE_SCRIPT_MULTANI:              Multani. Since: 2.48
 * @UNICODE_SCRIPT_OLD_HUNGARIAN:        Old Hungarian. Since: 2.48
 * @UNICODE_SCRIPT_SIGNWRITING:          Signwriting. Since: 2.48
 *
 * The #GUnicodeScript enumeration identifies different writing
 * systems. The values correspond to the names as defined in the
 * Unicode standard. The enumeration has been added in GLib 2.14,
 * and is interchangeable with #PangoScript.
 *
 * Note that new types may be added in the future. Applications
 * should be ready to handle unknown values.
 * See <ulink
 * url="http://www.unicode.org/reports/tr24/">Unicode Standard Annex
 * #24: Script names</ulink>.
 */
typedef enum
{                         /* ISO 15924 code */
  UNICODE_SCRIPT_INVALID_CODE = -1,
  UNICODE_SCRIPT_COMMON       = 0,   /* Zyyy */
  UNICODE_SCRIPT_INHERITED,          /* Zinh (Qaai) */
  UNICODE_SCRIPT_ARABIC,             /* Arab */
  UNICODE_SCRIPT_ARMENIAN,           /* Armn */
  UNICODE_SCRIPT_BENGALI,            /* Beng */
  UNICODE_SCRIPT_BOPOMOFO,           /* Bopo */
  UNICODE_SCRIPT_CHEROKEE,           /* Cher */
  UNICODE_SCRIPT_COPTIC,             /* Copt (Qaac) */
  UNICODE_SCRIPT_CYRILLIC,           /* Cyrl (Cyrs) */
  UNICODE_SCRIPT_DESERET,            /* Dsrt */
  UNICODE_SCRIPT_DEVANAGARI,         /* Deva */
  UNICODE_SCRIPT_ETHIOPIC,           /* Ethi */
  UNICODE_SCRIPT_GEORGIAN,           /* Geor (Geon, Geoa) */
  UNICODE_SCRIPT_GOTHIC,             /* Goth */
  UNICODE_SCRIPT_GREEK,              /* Grek */
  UNICODE_SCRIPT_GUJARATI,           /* Gujr */
  UNICODE_SCRIPT_GURMUKHI,           /* Guru */
  UNICODE_SCRIPT_HAN,                /* Hani */
  UNICODE_SCRIPT_HANGUL,             /* Hang */
  UNICODE_SCRIPT_HEBREW,             /* Hebr */
  UNICODE_SCRIPT_HIRAGANA,           /* Hira */
  UNICODE_SCRIPT_KANNADA,            /* Knda */
  UNICODE_SCRIPT_KATAKANA,           /* Kana */
  UNICODE_SCRIPT_KHMER,              /* Khmr */
  UNICODE_SCRIPT_LAO,                /* Laoo */
  UNICODE_SCRIPT_LATIN,              /* Latn (Latf, Latg) */
  UNICODE_SCRIPT_MALAYALAM,          /* Mlym */
  UNICODE_SCRIPT_MONGOLIAN,          /* Mong */
  UNICODE_SCRIPT_MYANMAR,            /* Mymr */
  UNICODE_SCRIPT_OGHAM,              /* Ogam */
  UNICODE_SCRIPT_OLD_ITALIC,         /* Ital */
  UNICODE_SCRIPT_ORIYA,              /* Orya */
  UNICODE_SCRIPT_RUNIC,              /* Runr */
  UNICODE_SCRIPT_SINHALA,            /* Sinh */
  UNICODE_SCRIPT_SYRIAC,             /* Syrc (Syrj, Syrn, Syre) */
  UNICODE_SCRIPT_TAMIL,              /* Taml */
  UNICODE_SCRIPT_TELUGU,             /* Telu */
  UNICODE_SCRIPT_THAANA,             /* Thaa */
  UNICODE_SCRIPT_THAI,               /* Thai */
  UNICODE_SCRIPT_TIBETAN,            /* Tibt */
  UNICODE_SCRIPT_CANADIAN_ABORIGINAL, /* Cans */
  UNICODE_SCRIPT_YI,                 /* Yiii */
  UNICODE_SCRIPT_TAGALOG,            /* Tglg */
  UNICODE_SCRIPT_HANUNOO,            /* Hano */
  UNICODE_SCRIPT_BUHID,              /* Buhd */
  UNICODE_SCRIPT_TAGBANWA,           /* Tagb */

  /* Unicode-4.0 additions */
  UNICODE_SCRIPT_BRAILLE,            /* Brai */
  UNICODE_SCRIPT_CYPRIOT,            /* Cprt */
  UNICODE_SCRIPT_LIMBU,              /* Limb */
  UNICODE_SCRIPT_OSMANYA,            /* Osma */
  UNICODE_SCRIPT_SHAVIAN,            /* Shaw */
  UNICODE_SCRIPT_LINEAR_B,           /* Linb */
  UNICODE_SCRIPT_TAI_LE,             /* Tale */
  UNICODE_SCRIPT_UGARITIC,           /* Ugar */

  /* Unicode-4.1 additions */
  UNICODE_SCRIPT_NEW_TAI_LUE,        /* Talu */
  UNICODE_SCRIPT_BUGINESE,           /* Bugi */
  UNICODE_SCRIPT_GLAGOLITIC,         /* Glag */
  UNICODE_SCRIPT_TIFINAGH,           /* Tfng */
  UNICODE_SCRIPT_SYLOTI_NAGRI,       /* Sylo */
  UNICODE_SCRIPT_OLD_PERSIAN,        /* Xpeo */
  UNICODE_SCRIPT_KHAROSHTHI,         /* Khar */

  /* Unicode-5.0 additions */
  UNICODE_SCRIPT_UNKNOWN,            /* Zzzz */
  UNICODE_SCRIPT_BALINESE,           /* Bali */
  UNICODE_SCRIPT_CUNEIFORM,          /* Xsux */
  UNICODE_SCRIPT_PHOENICIAN,         /* Phnx */
  UNICODE_SCRIPT_PHAGS_PA,           /* Phag */
  UNICODE_SCRIPT_NKO,                /* Nkoo */

  /* Unicode-5.1 additions */
  UNICODE_SCRIPT_KAYAH_LI,           /* Kali */
  UNICODE_SCRIPT_LEPCHA,             /* Lepc */
  UNICODE_SCRIPT_REJANG,             /* Rjng */
  UNICODE_SCRIPT_SUNDANESE,          /* Sund */
  UNICODE_SCRIPT_SAURASHTRA,         /* Saur */
  UNICODE_SCRIPT_CHAM,               /* Cham */
  UNICODE_SCRIPT_OL_CHIKI,           /* Olck */
  UNICODE_SCRIPT_VAI,                /* Vaii */
  UNICODE_SCRIPT_CARIAN,             /* Cari */
  UNICODE_SCRIPT_LYCIAN,             /* Lyci */
  UNICODE_SCRIPT_LYDIAN,             /* Lydi */

  /* Unicode-5.2 additions */
  UNICODE_SCRIPT_AVESTAN,                /* Avst */
  UNICODE_SCRIPT_BAMUM,                  /* Bamu */
  UNICODE_SCRIPT_EGYPTIAN_HIEROGLYPHS,   /* Egyp */
  UNICODE_SCRIPT_IMPERIAL_ARAMAIC,       /* Armi */
  UNICODE_SCRIPT_INSCRIPTIONAL_PAHLAVI,  /* Phli */
  UNICODE_SCRIPT_INSCRIPTIONAL_PARTHIAN, /* Prti */
  UNICODE_SCRIPT_JAVANESE,               /* Java */
  UNICODE_SCRIPT_KAITHI,                 /* Kthi */
  UNICODE_SCRIPT_LISU,                   /* Lisu */
  UNICODE_SCRIPT_MEETEI_MAYEK,           /* Mtei */
  UNICODE_SCRIPT_OLD_SOUTH_ARABIAN,      /* Sarb */
  UNICODE_SCRIPT_OLD_TURKIC,             /* Orkh */
  UNICODE_SCRIPT_SAMARITAN,              /* Samr */
  UNICODE_SCRIPT_TAI_THAM,               /* Lana */
  UNICODE_SCRIPT_TAI_VIET,               /* Tavt */

  /* Unicode-6.0 additions */
  UNICODE_SCRIPT_BATAK,                  /* Batk */
  UNICODE_SCRIPT_BRAHMI,                 /* Brah */
  UNICODE_SCRIPT_MANDAIC,                /* Mand */

  /* Unicode-6.1 additions */
  UNICODE_SCRIPT_CHAKMA,                 /* Cakm */
  UNICODE_SCRIPT_MEROITIC_CURSIVE,       /* Merc */
  UNICODE_SCRIPT_MEROITIC_HIEROGLYPHS,   /* Mero */
  UNICODE_SCRIPT_MIAO,                   /* Plrd */
  UNICODE_SCRIPT_SHARADA,                /* Shrd */
  UNICODE_SCRIPT_SORA_SOMPENG,           /* Sora */
  UNICODE_SCRIPT_TAKRI,                  /* Takr */

  /* Unicode 7.0 additions */
  UNICODE_SCRIPT_BASSA_VAH,              /* Bass */
  UNICODE_SCRIPT_CAUCASIAN_ALBANIAN,     /* Aghb */
  UNICODE_SCRIPT_DUPLOYAN,               /* Dupl */
  UNICODE_SCRIPT_ELBASAN,                /* Elba */
  UNICODE_SCRIPT_GRANTHA,                /* Gran */
  UNICODE_SCRIPT_KHOJKI,                 /* Khoj */
  UNICODE_SCRIPT_KHUDAWADI,              /* Sind */
  UNICODE_SCRIPT_LINEAR_A,               /* Lina */
  UNICODE_SCRIPT_MAHAJANI,               /* Mahj */
  UNICODE_SCRIPT_MANICHAEAN,             /* Manu */
  UNICODE_SCRIPT_MENDE_KIKAKUI,          /* Mend */
  UNICODE_SCRIPT_MODI,                   /* Modi */
  UNICODE_SCRIPT_MRO,                    /* Mroo */
  UNICODE_SCRIPT_NABATAEAN,              /* Nbat */
  UNICODE_SCRIPT_OLD_NORTH_ARABIAN,      /* Narb */
  UNICODE_SCRIPT_OLD_PERMIC,             /* Perm */
  UNICODE_SCRIPT_PAHAWH_HMONG,           /* Hmng */
  UNICODE_SCRIPT_PALMYRENE,              /* Palm */
  UNICODE_SCRIPT_PAU_CIN_HAU,            /* Pauc */
  UNICODE_SCRIPT_PSALTER_PAHLAVI,        /* Phlp */
  UNICODE_SCRIPT_SIDDHAM,                /* Sidd */
  UNICODE_SCRIPT_TIRHUTA,                /* Tirh */
  UNICODE_SCRIPT_WARANG_CITI,            /* Wara */

  /* Unicode 8.0 additions */
  UNICODE_SCRIPT_AHOM,                   /* Ahom */
  UNICODE_SCRIPT_ANATOLIAN_HIEROGLYPHS,  /* Hluw */
  UNICODE_SCRIPT_HATRAN,                 /* Hatr */
  UNICODE_SCRIPT_MULTANI,                /* Mult */
  UNICODE_SCRIPT_OLD_HUNGARIAN,          /* Hung */
  UNICODE_SCRIPT_SIGNWRITING             /* Sgnw */
} UnicodeScript;
/**
* NormalizeMode:
 * @NORMALIZE_DEFAULT: standardize differences that do not affect the
 *     text content, such as the above-mentioned accent representation
 * @NORMALIZE_NFD: another name for %G_NORMALIZE_DEFAULT
 * @NORMALIZE_DEFAULT_COMPOSE: like %G_NORMALIZE_DEFAULT, but with
 *     composed forms rather than a maximally decomposed form
 * @NORMALIZE_NFC: another name for %G_NORMALIZE_DEFAULT_COMPOSE
 * @NORMALIZE_ALL: beyond %G_NORMALIZE_DEFAULT also standardize the
 *     "compatibility" characters in Unicode, such as SUPERSCRIPT THREE
 *     to the standard forms (in this case DIGIT THREE). Formatting
 *     information may be lost but for most text operations such
 *     characters should be considered the same
 * @NORMALIZE_NFKD: another name for %G_NORMALIZE_ALL
 * @NORMALIZE_ALL_COMPOSE: like %G_NORMALIZE_ALL, but with composed
 *     forms rather than a maximally decomposed form
 * @NORMALIZE_NFKC: another name for %G_NORMALIZE_ALL_COMPOSE
 *
 * Defines how a Unicode string is transformed in a canonical
 * form, standardizing such issues as whether a character with
 * an accent is represented as a base character and combining
 * accent or as a single precomposed character. Unicode strings
 * should generally be normalized before comparing them.
 */
typedef enum {
  NORMALIZE_DEFAULT,
  NORMALIZE_NFD = G_NORMALIZE_DEFAULT,
  NORMALIZE_DEFAULT_COMPOSE,
  NORMALIZE_NFC = G_NORMALIZE_DEFAULT_COMPOSE,
  NORMALIZE_ALL,
  NORMALIZE_NFKD = G_NORMALIZE_ALL,
  NORMALIZE_ALL_COMPOSE,
  NORMALIZE_NFKC = G_NORMALIZE_ALL_COMPOSE
} NormalizeMode;
