#pragma once
const char *const introTextData =
	"\blCyens Toy CI - Version " MTOS(SAVE_VERSION) "." MTOS(MINOR_VERSION) " - Current codebase: " MTOS(BUILD_NUM) " - http://thecyentist.io"
	"\n"
	"\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\n"
	"\n"
	"\btCyens Toy\bg by firefreak11\n"
	"\bgSpecial thanks to Michael238 and LBPHacker\n"
	"\n"
	"Mod info here"
	"\n"
	"Contributors: \bgStanislaw K Skowronek (Designed the original Powder Toy),\n"
	"\bgSimon Robertshaw, Skresanov Savely, cracker64, Catelite, Bryan Hoyle, Nathan Cousins, jacksonmj,\n"
	"\bgFelix Wallin, Lieuwe Mosch, Anthony Boot, Matthew \"me4502\", MaksProg, jacob1, mniip, LBPHacker\n"
	"\n"
#ifndef BETA
	"\bgTo use online features such as saving, you need to register at: \brhttps://powdertoy.co.uk/Register.html\n"
#else
	"\brThis is a BETA, you cannot save things publicly. If you are planning on publishing any saves, use the release version\n"
#endif
	"\n"
	"\bt" MTOS(SAVE_VERSION) "." MTOS(MINOR_VERSION) " " IDENT_PLATFORM " "
#ifdef SNAPSHOT
	"SNAPSHOT " MTOS(SNAPSHOT_ID) " "
#elif MOD_ID > 0
	"MODVER " MTOS(SNAPSHOT_ID) " "
#endif
#ifdef X86
	"X86 "
#endif
#ifdef X86_SSE
	"X86_SSE "
#endif
#ifdef X86_SSE2
	"X86_SSE2 "
#endif
#ifdef X86_SSE3
	"X86_SSE3 "
#endif
#ifdef LUACONSOLE
	"LUACONSOLE "
#endif
#ifdef GRAVFFT
	"GRAVFFT "
#endif
#ifdef REALISTIC
	"REALISTIC"
#endif
	;
