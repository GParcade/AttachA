﻿#include "run_time.hpp"
#include <atomic>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cassert>

#include "run_time/attacha_abi_structs.hpp"
#include "run_time/run_time_compiler.hpp"
#include <stdio.h>
#include <typeinfo>
#include <windows.h>
#include "run_time/CASM.hpp"
struct test_struct {
	uint64_t a, b;
};


void SOVER() {
	void* test = alloca(100000);
	SOVER();
}


void TestCall() {
	std::cout << "Hello from proxy" << std::endl;
}
void ThrowCall() {
	throw std::exception();
}



template<class T>
void bbWrite(std::vector<uint8_t>& data, T v) {
	uint8_t* res = reinterpret_cast<uint8_t*>(&v);
	for (size_t i = 0; i < sizeof(T); i++)
		data.push_back(res[i]);
}
void bbWriteString(std::vector<uint8_t>& data,const std::string& str) {
	bbWrite(data, (uint32_t)str.size());
	for (char it : str)
		data.push_back(it);
}


void bNoting(std::vector<uint8_t>& b) {
	b.push_back(0);
}



void bSet(std::vector<uint8_t>& b, uint16_t vp, const std::string& str) {
	b.push_back(Command(Opcode::set).toCmd());
	bbWrite(b, vp);
	b.push_back((uint8_t)VType::string);
	b.push_back(0);
	bbWriteString(b, str);
}
void bSet(std::vector<uint8_t>& b, uint16_t vp, uint8_t v) {
	b.push_back(Command(Opcode::set).toCmd());
	bbWrite(b, vp);
	b.push_back((uint8_t)VType::ui8);
	b.push_back(0);
	b.push_back(v);
}
void bSet(std::vector<uint8_t>& b, uint16_t vp, int8_t v) {
	b.push_back(Command(Opcode::set).toCmd());
	bbWrite(b, vp);
	b.push_back((uint8_t)VType::i8);
	b.push_back(0);
	b.push_back(v);
}
void bSet(std::vector<uint8_t>& b, uint16_t vp, uint16_t v) {
	b.push_back(Command(Opcode::set).toCmd());
	bbWrite(b, vp);
	b.push_back((uint8_t)VType::ui16);
	b.push_back(0);
	bbWrite(b, v);
}
void bSet(std::vector<uint8_t>& b, uint16_t vp, int16_t v) {
	b.push_back(Command(Opcode::set).toCmd());
	bbWrite(b, vp);
	b.push_back((uint8_t)VType::i16);
	b.push_back(0);
	bbWrite(b, v);
}
void bSet(std::vector<uint8_t>& b, uint16_t vp, uint32_t v) {
	b.push_back(Command(Opcode::set).toCmd());
	bbWrite(b, vp);
	b.push_back((uint8_t)VType::ui32);
	b.push_back(0);
	bbWrite(b, v);
}
void bSet(std::vector<uint8_t>& b, uint16_t vp, int32_t v) {
	b.push_back(Command(Opcode::set).toCmd());
	bbWrite(b, vp);
	b.push_back((uint8_t)VType::i32);
	b.push_back(0);
	bbWrite(b, v);
}
void bSet(std::vector<uint8_t>& b, uint16_t vp, uint64_t v) {
	b.push_back(Command(Opcode::set).toCmd());
	bbWrite(b, vp);
	b.push_back((uint8_t)VType::ui64);
	b.push_back(0);
	bbWrite(b, v);
}
void bSet(std::vector<uint8_t>& b, uint16_t vp, int64_t v) {
	b.push_back(Command(Opcode::set).toCmd());
	bbWrite(b, vp);
	b.push_back((uint8_t)VType::i64);
	b.push_back(0);
	bbWrite(b, v);
}
void bSetArr(std::vector<uint8_t>& b, uint16_t vp) {
	b.push_back(Command(Opcode::set).toCmd());
	bbWrite(b, vp);
	b.push_back((uint8_t)VType::uarr);
	b.push_back(0);
}


void bCall(std::vector<uint8_t>& b, uint16_t vp) {
	b.push_back(Command(Opcode::call).toCmd());
	CallFlags f;
	f.in_memory = true;
	f.async_mode = false;
	f.use_result = false;
	b.push_back(f.encoded);
	bbWrite(b, vp);
}
void bAsyncCall(std::vector<uint8_t>& b, uint16_t vp) {
	b.push_back(Command(Opcode::call).toCmd());
	CallFlags f;
	f.in_memory = true;
	f.async_mode = true;
	f.use_result = false;
	b.push_back(f.encoded);
	bbWrite(b, vp);
}
void bCall(std::vector<uint8_t>& b, const std::string& str) {
	b.push_back(Command(Opcode::call).toCmd());
	CallFlags f;
	f.in_memory = false;
	f.async_mode = false;
	f.use_result = false;
	b.push_back(f.encoded);
	bbWriteString(b, str);
}
void bAsyncCall(std::vector<uint8_t>& b, const std::string& str) {
	b.push_back(Command(Opcode::call).toCmd());
	CallFlags f;
	f.in_memory = false;
	f.async_mode = true;
	f.use_result = false;
	b.push_back(f.encoded);
	bbWriteString(b, str);
}

void bCall(std::vector<uint8_t>& b, uint16_t vp, uint16_t res) {
	b.push_back(Command(Opcode::call).toCmd());
	CallFlags f;
	f.in_memory = true;
	f.async_mode = false;
	f.use_result = true;
	b.push_back(f.encoded);
	bbWrite(b, vp);
	bbWrite(b, res);
}
void bAsyncCall(std::vector<uint8_t>& b, uint16_t vp, uint16_t res) {
	b.push_back(Command(Opcode::call).toCmd());
	CallFlags f;
	f.in_memory = true;
	f.async_mode = true;
	f.use_result = true;
	b.push_back(f.encoded);
	bbWrite(b, vp);
	bbWrite(b, res);
}
void bCall(std::vector<uint8_t>& b, const std::string& str, uint16_t res) {
	b.push_back(Command(Opcode::call).toCmd());
	CallFlags f;
	f.in_memory = false;
	f.async_mode = false;
	f.use_result = true;
	b.push_back(f.encoded);
	bbWriteString(b, str);
	bbWrite(b, res);
}
void bAsyncCall(std::vector<uint8_t>& b, const std::string& str, uint16_t res) {
	b.push_back(Command(Opcode::call).toCmd());
	CallFlags f;
	f.in_memory = false;
	f.async_mode = true;
	f.use_result = true;
	b.push_back(f.encoded);
	bbWriteString(b, str);
	bbWrite(b, res);
}

void bCallReturn(std::vector<uint8_t>& b, uint16_t vp) {
	b.push_back(Command(Opcode::call_and_ret).toCmd());
	CallFlags f;
	f.in_memory = true;
	f.async_mode = false;
	b.push_back(f.encoded);
	bbWrite(b, vp);
}
void bAsyncCallReturn(std::vector<uint8_t>& b, uint16_t vp) {
	b.push_back(Command(Opcode::call_and_ret).toCmd());
	CallFlags f;
	f.in_memory = true;
	f.async_mode = true;
	b.push_back(f.encoded);
	bbWrite(b, vp);
}
void bCallReturn(std::vector<uint8_t>& b,const std::string& str) {
	b.push_back(Command(Opcode::call_and_ret).toCmd());
	CallFlags f;
	f.in_memory = false;
	f.async_mode = false;
	b.push_back(f.encoded);
	bbWriteString(b, str);
}
void bAsyncCallReturn(std::vector<uint8_t>& b, const std::string& str) {
	b.push_back(Command(Opcode::call_and_ret).toCmd());
	CallFlags f;
	f.in_memory = false;
	f.async_mode = true;
	b.push_back(f.encoded);
	bbWriteString(b, str);
}

void bArgSet(std::vector<uint8_t>& b, uint16_t vp) {
	b.push_back(Command(Opcode::arg_set).toCmd());
	bbWrite(b, vp);
}


void bJlistS(std::vector<uint8_t>& b, uint8_t s) {
	b.push_back(s);
}

void bArrPushEnd(std::vector<uint8_t>& b, uint16_t vp, uint16_t v) {
	b.push_back(Command(Opcode::arr_op).toCmd());
	bbWrite(b, vp);
	b.push_back(18);//push end
	bbWrite(b, v);
}









//#include "windows.h"
//
//typedef uint8_t UBYTE;
//typedef uint16_t USHORT;
//
//typedef union _UNWIND_CODE {
//	struct {
//		UBYTE CodeOffset;
//		UBYTE UnwindOp : 4;
//		UBYTE OpInfo : 4;
//	};
//	USHORT FrameOffset;
//} UNWIND_CODE, * PUNWIND_CODE;
//
//typedef struct _UNWIND_INFO {
//	UBYTE Version : 3;
//	UBYTE Flags : 5;
//	UBYTE SizeOfProlog;
//	UBYTE CountOfCodes;
//	UBYTE FrameRegister : 4;
//	UBYTE FrameOffset : 4;
//	UNWIND_CODE UnwindCode[1];
//	/*	UNWIND_CODE MoreUnwindCode[((CountOfCodes + 1) & ~1) - 1];
//	 *	OPTIONAL ULONG ExceptionHandler;
//	 *	OPTIONAL ULONG ExceptionData[]; */
//} UNWIND_INFO, * PUNWIND_INFO;
//
//typedef struct {
//	uint8_t code[0x1000];
//	RUNTIME_FUNCTION function_table[1];
//	UNWIND_INFO unwind_info[1];
//} DYNSECTION;
//
//static EXCEPTION_DISPOSITION handler(PEXCEPTION_RECORD ExceptionRecord, ULONG64 EstablisherFrame, PCONTEXT ContextRecord, PDISPATCHER_CONTEXT DispatcherContext) {
//	printf("handler!\n");
//	ContextRecord->Rip += 3;
//	return ExceptionContinueExecution;
//}
//
//int masin() {
//	int ret;
//	RUNTIME_FUNCTION* q;
//	DYNSECTION* dynsection = (DYNSECTION*)VirtualAlloc(NULL, 0x2000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
//
//	uint8_t* code = dynsection->code;
//	size_t p = 0;
//	code[p++] = 0xb8; // mov rax, 42
//	code[p++] = 0x2a;
//	code[p++] = 0x00;
//	code[p++] = 0x00;
//	code[p++] = 0x00;
//	code[p++] = 0xc6; // mov byte [rax], 0  -- raises exception!
//	code[p++] = 0x00;
//	code[p++] = 0x00;
//	code[p++] = 0xc3; // ret
//
//	size_t trampoline = p;
//	code[p++] = 0x48; // mov rax, 
//	code[p++] = 0xb8;
//	size_t patch_handler_address = p;
//	code[p++] = 0x00; // address to handler patched here
//	code[p++] = 0x00;
//	code[p++] = 0x00;
//	code[p++] = 0x00;
//	code[p++] = 0x00;
//	code[p++] = 0x00;
//	code[p++] = 0x00;
//	code[p++] = 0x00;
//	code[p++] = 0xff; // jmp rax
//	code[p++] = 0xe0;
//
//	DWORD64 dyn_base = 0;
//	q = RtlLookupFunctionEntry((DWORD64)code, &dyn_base, NULL);
//	printf("lookup 'code' %p %llx\n", q, dyn_base); // no function table entry
//
//	dyn_base = (DWORD64)dynsection;
//	UNWIND_INFO* unwind_info = dynsection->unwind_info;
//	unwind_info[0].Version = 1;
//	unwind_info[0].Flags = UNW_FLAG_EHANDLER;
//	unwind_info[0].SizeOfProlog = 0;
//	unwind_info[0].CountOfCodes = 0;
//	unwind_info[0].FrameRegister = 0;
//	unwind_info[0].FrameOffset = 0;
//	*(DWORD*)&unwind_info[0].UnwindCode = trampoline;
//
//	RUNTIME_FUNCTION* function_table = dynsection->function_table;
//	function_table[0].BeginAddress = 0; // set RVA of dynamic code start
//	function_table[0].EndAddress = trampoline; // RVA of dynamic code end
//	function_table[0].UnwindInfoAddress = (DWORD64)unwind_info - dyn_base; // RVA of unwind info
//
//	*(DWORD64*)&code[patch_handler_address] = (DWORD64)handler; // VA of handler
//
//	printf("code VA %016llx\n", (DWORD64)code);
//	printf("function table VA %016llx\n", (DWORD64)function_table);
//	printf("unwind info VA %016llx\n", (DWORD64)unwind_info);
//	printf("handler VA %016llx\n", (DWORD64)handler);
//	printf("RUNTIME_FUNCTION begin RVA %08x, end RVA %08x, unwind RVA %08x\n",
//		function_table[0].BeginAddress, function_table[0].EndAddress,
//		function_table[0].UnwindInfoAddress);
//	printf("UNWIND_INFO handler RVA %08x\n", *(DWORD*)&unwind_info[0].UnwindCode);
//
//	if (!RtlAddFunctionTable(function_table, 1, dyn_base)) {
//		printf("RtlAddFunctionTable() failed, exit.\n");
//		exit(EXIT_FAILURE);
//	}
//
//	q = RtlLookupFunctionEntry((DWORD64)code, &dyn_base, NULL);
//	printf("lookup 'code' %p %llx\n", q, dyn_base); // should return address of function table entry
//
//	uint64_t(*call)() = (uint64_t(*)()) code;
//	uint64_t result = (*call)();
//	printf("result = %llx\n", result);
//
//	if (!RtlDeleteFunctionTable(function_table)) {
//		printf("RtlDeleteFunctionTable() failed, exit.\n");
//		exit(EXIT_FAILURE);
//	}
//
//	return EXIT_SUCCESS;
//}

#include "libray/console.hpp"
typedef void (*functs)(...);
int main() {
	std::thread(ignoredAsyncGC).detach();

	initStandardFunctions();
	console::setBgColor(123, 21, 2);

	std::function test([]() {});
	std::vector<uint8_t> programm;
	bbWrite(programm, (uint16_t)3);
	bJlistS(programm, 0);

	bSet(programm, 0, "The test text");
	bSetArr(programm, 1);


	bSet(programm, 2, (uint8_t)12);
	bArrPushEnd(programm, 1, 2);

	bSet(programm, 2, (uint8_t)128);
	bArrPushEnd(programm, 1, 2);

	bSet(programm, 2, (uint8_t)12);
	bArrPushEnd(programm, 1, 2);

	bArgSet(programm, 1);
	bCall(programm, "console setTextColor");
	bArgSet(programm, 0);
	bAsyncCallReturn(programm, "console printLine");

	FuncEnviropment::AddNative(TestCall, "test");
	FuncEnviropment::AddNative(ThrowCall, "throwcall");
	FuncEnviropment::AddNative(SOVER, "stack_owerflower");
	FuncEnviropment::Load(programm, "start");


	try {
		callFunction("start", false);
	}
	catch (const std::exception&) {
		std::cout << "Catched!\n";
	}
	catch (const StackOverflowException&) {
		std::cout << "Catched!\n";
	}


	std::cout << "Hello!\n";
	size_t e = 0;
	{
		std::vector<uint8_t> programm;
		bbWrite(programm, (uint16_t)0);
		bJlistS(programm, 0);
		bCallReturn(programm, "Yay");
		FuncEnviropment::Load(programm, "Yay");
	}
	auto* env = FuncEnviropment::enviropment("Yay");
	for (size_t i = 0; i < 10000; i++) {
		try {
			//console::setTextColor(2, 128, 2);
			//console::print("The test text\n");
			env->FuncWraper(nullptr, false);
			//SOVER();
		}
		catch (const std::exception&) {
		}
		catch (const StackOverflowException&) {
			e++;
		}
		//restore_stack_fault();
	}

	//bool need_restore = false;
	//try {
	//	int s = 0;
	//	int a = 1 / s;
	//}
	//catch (const DevideByZeroException& seq) {
	//	std::cout << "dev_z" << std::endl;
	//}
	//try {
	//	SOVER();
	//}
	//catch (const AttachARuntimeException& seq) {
	//	std::cout << seq.name() << std::endl;
	//}
	//restore_fault();
	//try {
	//	SOVER();
	//}
	//catch (const AttachARuntimeException& seq) {
	//	std::cout << seq.name() << std::endl;
	//}
	//restore_fault();
	//NativeLib testlib("C:\\WINDOWS\\System32\\msvcrt.dll");
	//DynamicCall::ArgumentsHolder call;
	//
	//
	//test_struct tmp;
	//test_struct tmp1;
	//tmp1.b = tmp.a = 1;
	//tmp1.a = tmp.b = 2;
	//
	//call.push_value((uint64_t)1);
	//call.push_value((uint64_t)2);
	//call.push_value((uint64_t)3);
	//call.push_value((uint64_t)4);
	//call.push_value(tmp);
	//call.push_value(tmp1);
	//call.push_value(tmp1);
	//try {
	//	DynamicCall::Calls::call((DynamicCall::PROC)test_call, call);
	//}
	//catch (SegmentationFaultException) {
	//	std::cout << "Hello!\n";
	//}
	console::resetBgColor();
	return e;
}
//6 073 direct
//5 124 wrap




//288230376151711740   / 43580400600
// 
// 
// 
// 2882303761517117.4
// 1441151880758558.7
//   11716681957386.65609756097560975609756
//    1065152905216.968736141906873614190687
//      96832082292.45170328562789760129006245
//       8802916572.041063935057081600117278404
//        800265142.9128239940960983272833889458
//         72751376.6284385449178271206621262678
//          6613761.511676231356166101878375115254



//6613761.5116762313561661018783751152576601143037680107970370515593654272191339149828742051535891572322995121802528818424858627848409452206825285584914976664991922997605487821055045556419231263330791869774597712165133241111142975587975664454998148869700844374523716516731606179866093291487550024953189622584607448514367258937036939490638826298443892688769822827190808337819639042051394084706968021767106014165459507042714058943276441566257653905090537419245292573102230730756522692450881233982966186868874261793729358238161766691056988585827731009888881104043821019855425560268943466297553951351241135676940060069112811230101450696623472524940488959158397456309752232979703265967683647221911952778148624911905926812430448379127565890250214909681211145177036302874186980282140866782211267695414438205049450600965792866071084257082299514245401406429476465161267930152987166437382404419660153376378095982899248521363982138337663651490160923394540801903505219270517673947219291967683289262834357699777546331228538546293216038037062009016961629306363007594748911050624899487500351247344890170651620857289687236147159234695056933460129781367819735002619503226870291779741005868587632946173514522489267801728284250787726811304254050386127015087603393898127682653747795058129869508358764375378412652774008690502950539651533171083333272526182331605276707805205443659918995788212190045816146077372221309961983231517151313198346322681577185869190931668489527377130168004926508179000080141530410805815309554543195272968647286826454734333029513271615038802557496454036725857907786189556045521986321530050368559484971783393840578877101923656938573437528245208466486652717919256575167874890989414172571878561391654577860856102364511077945437702103178923050101563316056346668828005220309975764656004561830484871678761025432152636063652888954857381462436579805097064665348670521399475157646898729976337115175577344279850424321248666998256092212240931075791900820663865122891963503428649070288720567658113725553959226340842768664223797887713771956469808127463610327620531326
//6613761.51167623135616610187837511525766011430376801079703705155936542721913391498287420515358915723229951218025288184248586278484094522068252855849149766649919229976054878210550455564192312633307918697745977121651332411111429755879756644549981488697008443745237165167316061798660932914875500249531896225846074485143672589370369394906388262984438926887698228271908083378196390420513940847069680217671060141654595070427140589432764415662576539050905374192452925731022307307565226924508812339829661868688742617937293582381617666910569885858277310098888811040438210198554255602689434662975539513512411356769400600691128112301014506966234725249404889591583974563097522329797032659676836472219119527781486249119059268124304483791275658902502149096812111451770363028741869802821408667822112676954144382050494506009657928660710842570822995142454014064294764651612679301529871664373824044196601533763780959828992485213639821383376636514901609233945408019035052192705176739472192919676832892628343576997775463312285385462932160380370620090169616293063630075947489110506248994875003512473448901706516208572896872361471592346950569334601297813678197350026195032268702917797410058685876329461735145224892678017282842507877268113042540503861270150876033938981276826537477950581298695083587643753784126527740086905029505396515331710833332725261823316052767078052054436599189957882121900458161460773722213099619832315171513131983463226815771858691909316684895273771301680049265081790000801415304108058153095545431952729686472868264547343330295132716150388025574964540367258579077861895560455219863215300503685594849717833938405788771019236569385734375282452084664866527179192565751678748909894141725718785613916545778608561023645110779454377021031789230501015633160563466688280052203099757646560045618304848716787610254321526360636528889548573814624365798050970646653486705213994751576468987299763371151755773442798504243212486669982560922122409310757919008206638651228919635034286490702887205676581137255539592263408427686642237978877137719564698081274636103276205313266441153365625555998216317451657385636790130836934068935566416064564583190178384913699026438045179419484271560367437283263522823147247526678311442598350048209515540800237618742770345254696901524122290881373862359585561037729423717137652929239021267739333263494599450744837806745631429555973379464529291178658876302298148218490676288092679900698296931212697480343950762123099896424540897864073328412680997705193191822105462701965158163323537691390565143175852311922070766829986413663209878800425712470389728358761346493909925187791871743372638938064282043336701223439419232874146641047627267565778181488308760521122882931920547788631387660993644009779937635543441975611394448723814622300649526383656051110278229062446938590096393010210190679155895597710499246764610970556337657896609605740980728846260307207914926784771225806492471755755269491487877695185757425093517841595976517939580390181176994504268049339592348767900036237849543769453096766623113602126915740191704433299770998433639914728089947846876836648445126959204684318574161982347633582789966368505570827634842805919503181437024238827212616306239277662812489153667853158743107102140772886791683140241716823502535678848257305831190546697269230700922010340584156998318184344546846593236685392010829749004188823358360776518424201910617590789195269581803706503790146435689257982635432681176409378852749692255008780254305418202144750362850037684141893821875515297580812049717597134708302796096830739091462137683975305174225498055655780272933057893919405596285409088231281655543111276494323918628687410459462366667643711379743489553879869566871305905343146386772773263584915279553442195756227169697012835627766120167330449000048888949405389357526924614823297425127386277399203163818553792734066790565481860210344188529556564011942561170490938534419988787344924039087424083935566209549712124491118147271000533207581391530393596244271329621508802743772850954472410242139903596939400322997489839503678174082686151352174582810053379821386956227290852392944731214792917713565028587644511005252209636641109719399871693698933093331868087509044145867718343093890697278262283802870779485216572332288290163170276135552549280604823077280294665304200989836701960009059668900794821973251893421099024959398835815199000258845716071733402101861358291415063311740186252441194861343243366147487868663602876564654616782021962413993964066498278127346998274265519257296593092813378131269403705297743408076886746194802073480710500857580460148409007511509657852938598274381167574673464566546458042425612765018961298855063760015092656123954950519660895453081264241522369117460567813137541466289320892566554333142132704489182690073757605615034204160115040337651233063699740291051844989235826345295228883233349626437348535983856926730499122580346358725302768327466911811728504395620447784502467377502720798762001283668787569612198562488661474121465510346869092341477925744445772717380665839955587741889642014901533511832839829379631723715729221635470693676918610059770767687711434208339975654101720212273587957794036432056111021613693014102307265160843886322605304367027778078754053490733630383379266137356250001979100669395865993944075860560125277967270452305112587698425149400760671300483639886504393445158005270837276332884374633307065103022481165535683487957657736629433369641856848833096775159060837086476896680935971019963501666388995974488586963562698411725935350855861568193111102333465011792479943380786637376619250259943686703972152105458158638404071944212463251198292105648978362075909875872045104606037054188987881859901948675524565967390396131420600112611172280045539553851645870368617033777335217978698433533903770494482329288180063218601987793567918694166386345700548700325622981997095272226570583658196111212433416685940238924742697294067553844376547562070826856970194991736721208570074502711202705190369452455193814808577046444130208385463992269956325275266056182145328879790058653109306204954894333853369856356942253532199059225719921445605068623439868058486823547005210411030503469029607772811523903247461199335556360168015527603938546631900396069328467806695654835260968206887019758143297104065628988275064181030038535258439088327242223652253439818081892528541832632901497468107257371103651580476752203145190914100959411557130110456120956354861960585098430692259400662783260418216531951750806072214031001816903904274803752033431285163542071708262360488719325815467607243610330649415829371701553381315177722345214054778560250315826605779296117805764272850672235445215251187938827712382249189329388587584484021470881109798701575037839372224586664308909542240417129162415271602620376096313350547768943638393264333600458000379188804427832634471010346793370228909736089025303727933148003233361741975359446328724201768810725434221914885289053538438561301338749052251713353915337804398245939942094061429990618305605937913292150875731050531004067915796074623508623736698739754126996253448849664773388980733692475511572052873694786550447634021978219264005572266354981601522956170347823741666110338600237649031615372530559069711718069888508551249985526750756852840861678540880599431662865439561838263597788038690034437177706897903090867870544540152758485657426471660290337028246592115998126001622848781247779535096793029479403179235575911617480634172968111724975745174770146559873522594466467570745552072782001916705648639677717877609413255370580508156228375743751194430277908000689649465957410221694933203528193359470862688673862259081666174495881068151539662533528890966642468174099345016117176307002556557499840880306180572374086896300810965927651431455634668947949046617988178842027441115353125046767009296376224682982836096279482111965716992514290931047568204317974993557080794709353819019277211508698247257506852747929994934466022324723651117608129559047697234797791188729917273867372389413051884612552184754354919812279100527589000638970721164045472312615685317954603657314705822139689096845979887573589674620843205374298463883326487824896221812151033783750946061748684338619870327672022363190484302248474512645943874136852243620725230322917224400181397139336989022537805675884493819912247433540