#pragma once
#include <asmjit/asmjit.h>
#include <vector>
#include "../libray/exceptions.hpp"
using asmjit::CodeHolder;
using asmjit::Error;
using asmjit::Label;
using asmjit::x86::Assembler;

using creg = asmjit::x86::Gp;
using creg128 = asmjit::x86::Xmm;
using creg64 = asmjit::x86::Gpq;
using creg32 = asmjit::x86::Gpd;
using creg16 = asmjit::x86::Gpw;
using creg8 = asmjit::x86::Gpb;
#ifdef _WIN64
constexpr creg8 resr_8l = asmjit::x86::al;
constexpr creg8 argr0_8l = asmjit::x86::cl;
constexpr creg8 argr1_8l = asmjit::x86::dl;
constexpr creg8 argr2_8l = asmjit::x86::r8b;
constexpr creg8 argr3_8l = asmjit::x86::r9b;
constexpr creg8 resr_8h = asmjit::x86::ah;
constexpr creg8 argr0_8h = asmjit::x86::ch;
constexpr creg8 argr1_8h = asmjit::x86::dh;

constexpr creg16 resr_16 = asmjit::x86::ax;
constexpr creg16 argr0_16 = asmjit::x86::cx;
constexpr creg16 argr1_16 = asmjit::x86::dx;
constexpr creg16 argr2_16 = asmjit::x86::r8w;
constexpr creg16 argr3_16 = asmjit::x86::r9w;

constexpr creg32 resr_32 = asmjit::x86::eax;
constexpr creg32 argr0_32 = asmjit::x86::ecx;
constexpr creg32 argr1_32 = asmjit::x86::edx;
constexpr creg32 argr2_32 = asmjit::x86::r8d;
constexpr creg32 argr3_32 = asmjit::x86::r9d;

constexpr creg64 resr = asmjit::x86::rax;
constexpr creg64 argr0 = asmjit::x86::rcx;
constexpr creg64 argr1 = asmjit::x86::rdx;
constexpr creg64 argr2 = asmjit::x86::r8;
constexpr creg64 argr3 = asmjit::x86::r9;

constexpr creg64 arg_ptr = asmjit::x86::r13;
constexpr creg64 enviro_ptr = asmjit::x86::r12;


constexpr creg64 stack_ptr = asmjit::x86::rsp;
constexpr creg64 frame_ptr = asmjit::x86::rbp;
constexpr creg64 mut_temp_ptr = asmjit::x86::r11;



constexpr creg128 vec0 = asmjit::x86::xmm0;
constexpr creg128 vec1 = asmjit::x86::xmm1;
constexpr creg128 vec2 = asmjit::x86::xmm2;
constexpr creg128 vec3 = asmjit::x86::xmm3;
constexpr creg128 vec4 = asmjit::x86::xmm4;
constexpr creg128 vec5 = asmjit::x86::xmm5;
constexpr creg128 vec6 = asmjit::x86::xmm6;
constexpr creg128 vec7 = asmjit::x86::xmm7;
constexpr creg128 vec8 = asmjit::x86::xmm8;
constexpr creg128 vec9 = asmjit::x86::xmm9;
constexpr creg128 vec10 = asmjit::x86::xmm10;
constexpr creg128 vec11 = asmjit::x86::xmm11;
constexpr creg128 vec12 = asmjit::x86::xmm12;
constexpr creg128 vec13 = asmjit::x86::xmm13;
constexpr creg128 vec14 = asmjit::x86::xmm14;
constexpr creg128 vec15 = asmjit::x86::xmm15;

#elif
constexpr creg8 resr_8h = asmjit::x86::ah;
constexpr creg8 resr1_8h = asmjit::x86::dh;
constexpr creg8 argr0_8h = asmjit::x86::dh;
constexpr creg8 argr1_8h = asmjit::x86::sh;
constexpr creg8 argr2_8h = asmjit::x86::dh;
constexpr creg8 argr3_8h = asmjit::x86::ch;

constexpr creg8 resr_8l = asmjit::x86::al;
constexpr creg8 resr1_8l = asmjit::x86::dl;
constexpr creg8 argr0_8l = asmjit::x86::dl;
constexpr creg8 argr1_8l = asmjit::x86::sl;
constexpr creg8 argr2_8l = asmjit::x86::dl;
constexpr creg8 argr3_8l = asmjit::x86::cl;
constexpr creg8 argr4_8l = asmjit::x86::r8b;
constexpr creg8 argr5_8l = asmjit::x86::r9b;


constexpr creg16 resr_16 = asmjit::x86::ax;
constexpr creg16 resr0_16 = asmjit::x86::dx;
constexpr creg16 argr0_16 = asmjit::x86::di;
constexpr creg16 argr1_16 = asmjit::x86::si;
constexpr creg16 argr2_16 = asmjit::x86::dx;
constexpr creg16 argr3_16 = asmjit::x86::cx;
constexpr creg16 argr4_16 = asmjit::x86::r8w;
constexpr creg16 argr5_16 = asmjit::x86::r9w;

constexpr creg32 resr_32 = asmjit::x86::eax;
constexpr creg32 resr1_32 = asmjit::x86::edx;
constexpr creg32 argr0_32 = asmjit::x86::edi;
constexpr creg32 argr1_32 = asmjit::x86::esi;
constexpr creg64 argr2_32 = asmjit::x86::edx;
constexpr creg64 argr3_32 = asmjit::x86::ecx;
constexpr creg32 argr4_32 = asmjit::x86::r8d;
constexpr creg32 argr5_32 = asmjit::x86::r9d;

constexpr creg64 resr = asmjit::x86::rax;
constexpr creg64 resr1 = asmjit::x86::rdx;
constexpr creg64 argr0 = asmjit::x86::rdi;
constexpr creg64 argr1 = asmjit::x86::rsi;
constexpr creg64 argr2 = asmjit::x86::rdx;
constexpr creg64 argr3 = asmjit::x86::rcx;
constexpr creg64 argr4 = asmjit::x86::r8;
constexpr creg64 argr5 = asmjit::x86::r9;

constexpr creg64 enviro_ptr = asmjit::x86::r13;

constexpr creg64 arg_ptr = asmjit::x86::r12;
constexpr creg64 temp_ptr = asmjit::x86::r14;
constexpr creg64 mut_temp_ptr = asmjit::x86::r11;


constexpr creg64 stack_ptr = asmjit::x86::rsp;
constexpr creg64 frame_ptr = asmjit::x86::rbp;



constexpr creg128 vec0 = asmjit::x86::xmm0;
constexpr creg128 vec1 = asmjit::x86::xmm1;
constexpr creg128 vec2 = asmjit::x86::xmm2;
constexpr creg128 vec3 = asmjit::x86::xmm3;
constexpr creg128 vec4 = asmjit::x86::xmm4;
constexpr creg128 vec5 = asmjit::x86::xmm5;
constexpr creg128 vec6 = asmjit::x86::xmm6;
constexpr creg128 vec7 = asmjit::x86::xmm7;
constexpr creg128 vec8 = asmjit::x86::xmm8;
constexpr creg128 vec9 = asmjit::x86::xmm9;
constexpr creg128 vec10 = asmjit::x86::xmm10;
constexpr creg128 vec11 = asmjit::x86::xmm11;
constexpr creg128 vec12 = asmjit::x86::xmm12;
constexpr creg128 vec13 = asmjit::x86::xmm13;
constexpr creg128 vec14 = asmjit::x86::xmm14;
constexpr creg128 vec15 = asmjit::x86::xmm15;
#endif


#if  defined(__x86_64__) || defined(_M_X64)



class CASM {
	asmjit::x86::Assembler a;
public:
	bool resr_used = false;
	CASM(asmjit::CodeHolder& holder) :a(&holder) {}
	void movEnviro(uint16_t off, creg64 res) {
		a.mov(asmjit::x86::ptr_64(enviro_ptr, (int32_t(off) << 1) * 8), res);
	}
	void movEnviro(uint16_t off, asmjit::Imm res) {
		a.mov(asmjit::x86::ptr_64(enviro_ptr, (int32_t(off) << 1) * 8), res);
	}
	void movEnviroMeta(uint16_t off, creg64 res) {
		a.mov(asmjit::x86::ptr_64(enviro_ptr, ((int32_t(off) << 1) & 1) * 8), res);
	}
	void movEnviroMeta(uint16_t off, asmjit::Imm res) {
		a.mov(asmjit::x86::ptr_64(enviro_ptr, ((int32_t(off) << 1) & 1) * 8), res);
	}
	void movEnviro(creg64 res, uint16_t off = 0) {
		a.mov(res, asmjit::x86::ptr_64(enviro_ptr, (int32_t(off) << 1) * 8));
	}
	void movEnviroMeta(creg64 res, uint16_t off = 0) {
		a.mov(res, asmjit::x86::ptr_64(enviro_ptr, ((int32_t(off) << 1) & 1) * 8));
	}
	void leaEnviro(creg64 res, uint16_t off = 0) {
		a.lea(res, asmjit::x86::ptr(enviro_ptr, (int32_t(off) << 1) * 8));
	}
	void leaEnviroMeta(creg64 res, uint16_t off = 0) {
		a.lea(res, asmjit::x86::ptr_64(enviro_ptr, ((int32_t(off) << 1) & 1) * 8));
	}


	void stackAlloc(size_t bytes_count) {
		a.mov(resr, stack_ptr);
		a.sub(stack_ptr, bytes_count);
	}
	void stackAlloc(creg64 bytes_count) {
		a.mov(resr, stack_ptr);
		a.sub(stack_ptr, bytes_count);
	}
	void stackReduce(size_t bytes_count) {
		a.add(stack_ptr, bytes_count);
	}
	void stackReduce(creg64 bytes_count) {
		a.add(stack_ptr, bytes_count);
	}
	void stackAlign() {
		a.and_(stack_ptr,-16);
	}


	void getEnviro(creg64 c0) {
		a.mov(c0, enviro_ptr);
	}
	void movA(creg c0, creg c1) {
		a.mov(c0, c1);
	}
	void mov(creg64 c0, creg64 c1) {
		a.mov(c0, c1);
	}
	void mov(creg32 c0, creg32 c1) {
		a.mov(c0, c1);
	}
	void mov(creg16 c0, creg16 c1) {
		a.mov(c0, c1);
	}
	void mov(creg8 c0, creg8 c1) {
		a.mov(c0, c1);
	}
	void mov_byte(creg8 res, creg64 base, int32_t off) {
		a.mov(res, asmjit::x86::ptr_8(base, off));
	}
	void mov_short(creg16 res, creg64 base, int32_t off) {
		a.mov(res, asmjit::x86::ptr_16(base, off));
	}
	void mov_int(creg32 res, creg64 base, int32_t off) {
		a.mov(res, asmjit::x86::ptr_32(base, off));
	}
	void mov_long(creg64 res, creg64 base, int32_t off) {
		a.mov(res, asmjit::x86::ptr_64(base, off));
	}
	void mov_vector(creg128 res, creg64 base, int32_t off) {
		a.movdqu(res, asmjit::x86::ptr_128(base, off));
	}
	void mov_default(creg res, creg64 base, int32_t off, uint32_t v_siz) {
		a.mov(res, asmjit::x86::ptr(base, off, v_siz));
	}
	void mov(creg64 res, creg64 base, int32_t off) {
		a.mov(res, asmjit::x86::ptr_64(res, off));
	}
	void mov(creg128 res, const asmjit::Imm& v) {
		if (resr_used)
			a.push(resr);

		a.mov(resr, v);
		a.vmovq(res, resr);

		if (resr_used)
			a.pop(resr);
	}
	void mov(creg res, const asmjit::Imm& v) {
		if (res.isVec())
			throw CompileTimeException("Invalid operation");
		a.mov(res, v);
	}
	void mov(creg64 res, int32_t res_off, int32_t vsize, const asmjit::Imm& v) {
		a.mov(asmjit::x86::ptr(res, res_off, vsize), v);
	}
	void mov(creg64 res, int32_t res_off, creg128 v) {
		a.movdqu(asmjit::x86::ptr(res, res_off, 16), v);
	}
	void mov(creg64 res, int32_t res_off, creg64 v) {
		a.mov(asmjit::x86::ptr(res, res_off, 8), v);
	}
	void mov(creg64 res, int32_t res_off, creg32 v) {
		a.mov(asmjit::x86::ptr(res, res_off, 4), v);
	}
	void mov(creg64 res, int32_t res_off, creg16 v) {
		a.mov(asmjit::x86::ptr(res, res_off, 2), v);
	}
	void mov(creg64 res, int32_t res_off, creg8 v) {
		a.mov(asmjit::x86::ptr(res, res_off, 1), v);
	}

	void mov(creg64 res, int32_t res_off, int32_t vsize, creg v) {
		a.mov(asmjit::x86::ptr(res, res_off, vsize), v);
	}



	void test(creg64 c0, creg64 c1) {
		a.test(c0, c1);
	}
	void test(creg32 c0, creg32 c1) {
		a.test(c0, c1);
	}
	void test(creg16 c0, creg16 c1) {
		a.test(c0, c1);
	}
	void test(creg8 c0, creg8 c1) {
		a.test(c0, c1);
	}
	void test(creg reg, const asmjit::Imm& v) {
		if (reg.isVec())
			throw CompileTimeException("Invalid operation");
		a.test(reg, v);
	}
	void test(creg64 res, int32_t res_off, int32_t vsize, const asmjit::Imm& v) {
		a.test(asmjit::x86::ptr(res, res_off, vsize), v);
	}

	void cmp(creg64 c0, creg64 c1) {
		a.cmp(c0, c1);
	}
	void cmp(creg32 c0, creg32 c1) {
		a.cmp(c0, c1);
	}
	void cmp(creg16 c0, creg16 c1) {
		a.cmp(c0, c1);
	}
	void cmp(creg8 c0, creg8 c1) {
		a.cmp(c0, c1);
	}
	void cmp(creg reg, const asmjit::Imm& v) {
		if (reg.isVec())
			throw CompileTimeException("Invalid operation");
		a.cmp(reg, v);
	}
	void cmp(creg64 res, int32_t res_off, int32_t vsize, const asmjit::Imm& v) {
		a.cmp(asmjit::x86::ptr(res, res_off, vsize), v);
	}


	void lea(creg64 res, creg64 base, int32_t off = 0, uint8_t vsize = 0) {
		a.lea(res, asmjit::x86::Mem(base, off, vsize));
	}

	void push(const asmjit::Imm& val) {
		a.push(val);
	}
	void push(creg val) {
		a.push(val);
	}
	void pop(creg res) {
		a.pop(res);
	}
	void pop() {
		stackReduce(8);
	}

	template<class FUNC>
	void call(FUNC fun) {
		a.call((*(void**)(&fun)));
	}

	void jmp(const asmjit::Imm& pos) {
		a.jmp(pos);
	}
	void jmp(creg64 pos) {
		a.jmp(pos);
	}
	void jmp(asmjit::Label label) {
		a.jmp(label);
	}
	void jmp_eq(asmjit::Label label) {
		a.je(label);
	}
	void jmp_not_eq(asmjit::Label label) {
		a.jne(label);
	}
	void jmp_more(asmjit::Label label) {
		a.ja(label);
	}
	void jmp_lower(asmjit::Label label) {
		a.jb(label);
	}
	void jmp_more_or_eq(asmjit::Label label) {
		a.jae(label);
	}
	void jmp_lower_or_eq(asmjit::Label label) {
		a.jbe(label);
	}

	void jmp_zero(asmjit::Label label) {
		a.jz(label);
	}
	void jmp_not_zero(asmjit::Label label) {
		a.jnz(label);
	}

	void push_flags() {
		a.pushf();
	}
	void pop_flags() {
		a.popf();
	}
	void load_flag8h() {
		a.lahf();
	}
	void store_flag8h() {
		a.sahf();
	}

	void int3() {
		a.int3();
	}



	void xor_(creg64 c0, creg64 c1) {
		a.xor_(c0, c1);
	}
	void xor_(creg32 c0, creg32 c1) {
		a.xor_(c0, c1);
	}
	void xor_(creg16 c0, creg16 c1) {
		a.xor_(c0, c1);
	}
	void xor_(creg8 c0, creg8 c1) {
		a.xor_(c0, c1);
	}
	void xor_byte(creg8 res, creg64 base, int32_t off) {
		a.xor_(res, asmjit::x86::ptr_8(res, off));
	}
	void xor_short(creg16 res, creg64 base, int32_t off) {
		a.xor_(res, asmjit::x86::ptr_16(res, off));
	}
	void xor_int(creg32 res, creg64 base, int32_t off) {
		a.xor_(res, asmjit::x86::ptr_32(res, off));
	}
	void xor_long(creg64 res, creg64 base, int32_t off) {
		a.xor_(res, asmjit::x86::ptr_64(res, off));
	}
	void xor_(creg64 res, creg64 base, int32_t off) {
		a.xor_(res, asmjit::x86::ptr_64(res, off));
	}
	void xor_(creg res, const asmjit::Imm& v) {
		a.xor_(res, v);
	}
	void xor_(creg64 res, int32_t res_off, int32_t vsize, const asmjit::Imm& v) {
		a.xor_(asmjit::x86::ptr(res, res_off, vsize), v);
	}

	void and_(creg64 c0, creg64 c1) {
		a.and_(c0, c1);
	}
	void and_(creg32 c0, creg32 c1) {
		a.and_(c0, c1);
	}
	void and_(creg16 c0, creg16 c1) {
		a.and_(c0, c1);
	}
	void and_(creg8 c0, creg8 c1) {
		a.and_(c0, c1);
	}
	void and_byte(creg8 res, creg64 base, int32_t off) {
		a.and_(res, asmjit::x86::ptr_8(res, off));
	}
	void and_short(creg16 res, creg64 base, int32_t off) {
		a.and_(res, asmjit::x86::ptr_16(res, off));
	}
	void and_int(creg32 res, creg64 base, int32_t off) {
		a.and_(res, asmjit::x86::ptr_32(res, off));
	}
	void and_long(creg64 res, creg64 base, int32_t off) {
		a.and_(res, asmjit::x86::ptr_64(res, off));
	}
	void and_(creg64 res, creg64 base, int32_t off) {
		a.and_(res, asmjit::x86::ptr_64(res, off));
	}
	void and_(creg res, const asmjit::Imm& v) {
		a.and_(res, v);
	}
	void and_(creg64 res, int32_t res_off, int32_t vsize, const asmjit::Imm& v) {
		a.and_(asmjit::x86::ptr(res, res_off, vsize), v);
	}




	void ret() {
		a.ret();
	}

	void label_bind(asmjit::Label label) {
		a.bind(label);
	}

	void noting() {
		a.nop();
	}
	asmjit::Label newLabel() {
		return a.newLabel();
	}

	asmjit::CodeHolder* code() { return a.code(); };

	size_t offset() {
		return a.offset();
	}

	void sub(creg res, creg val) {
		a.sub(res, val);
	}
	void sub(creg res, uint64_t val) {
		a.sub(res, val);
	}
	void sub(creg64 res, int32_t off, creg val, uint8_t vsize = 0) {
		a.sub(asmjit::x86::ptr(res, off, vsize), val);
	}
	void sub(creg64 res, int32_t off, uint64_t val, uint8_t vsize = 0) {
		a.sub(asmjit::x86::ptr(res, off, vsize), val);
	}

	void sub(creg res, creg64 val, int32_t off, uint8_t vsize = 0) {
		a.sub(asmjit::x86::ptr(res, off, vsize), val);
	}

	void add(creg res, creg val) {
		a.add(res, val);
	}
	void add(creg res, uint64_t val) {
		a.add(res, val);
	}
	void add(creg64 res, int32_t off, creg val, uint8_t vsize = 0) {
		a.add(asmjit::x86::ptr(res, off, vsize), val);
	}
	void add(creg64 res, int32_t off, uint64_t val, uint8_t vsize = 0) {
		a.add(asmjit::x86::ptr(res, off, vsize), val);
	}

	void add(creg res, creg64 val, int32_t off, uint8_t vsize = 0) {
		a.add(asmjit::x86::ptr(res, off, vsize), val);
	}

};


namespace {
	union UWCODE {
		struct {
			uint8_t offset;
			uint8_t op : 4;
			uint8_t info : 4;
		};
		uint16_t solid;
	};
	struct UWINFO_head {
		uint8_t Version : 3 = 1;
		uint8_t Flags : 5 = 0;
		uint8_t SizeOfProlog = 0;
		uint8_t CountOfUnwindCodes = 0;
		uint8_t FrameRegister : 4 = 5;
		uint8_t FrameOffset : 4 = 0;
	};
}
struct StackTraceItem {
	std::string fn_name;
	std::string file_path;
	size_t line;
	constexpr static size_t nline = -1;
};
struct FrameResult {
	std::vector<uint16_t> prolog;
	UWINFO_head head;
	uint32_t exHandleOff = 0;
	bool use_handle = false;

	//return uwind_info_ptr
	void* init(uint8_t*& frame, CodeHolder* code, asmjit::JitRuntime& runtime, const char* symbol_name="AttachA unnamed_symbol", const char* file_path ="");
	static bool deinit(uint8_t* frame, void* funct, asmjit::JitRuntime& runtime);
	static std::vector<StackTraceItem> JitCaptureStackTrace(uint32_t framesToSkip = 0, bool includeNativeFrames = true, uint32_t max_frames = 32);
};


#include <unordered_map>
class BuildCall {
	std::unordered_map<size_t, creg> Dargs;
	std::unordered_map<size_t, asmjit::Imm> Sargs;
	std::unordered_map<size_t, std::pair<creg64, size_t>> leas;
	std::unordered_map<size_t, std::pair<creg64, size_t>> movs;
	CASM& csm;
	size_t arg_c = 0;

public:
	BuildCall(CASM& a) : csm(a) {}
	void addArg(creg reg) {
		Dargs[arg_c++] = reg;
	}
	void addArg(const asmjit::Imm& val) {
		Sargs[arg_c++] = val;
	}
	void lea(creg64 reg, size_t off) {
		leas[arg_c++] = { reg,off };
	}
	void leaEnviro(uint16_t off) {
		leas[arg_c++] = { enviro_ptr,(int32_t(off) << 1) * 8 };
	}
	void leaEnviroMeta(uint16_t off) {
		leas[arg_c++] = { enviro_ptr,(int32_t(off) << 1) * 8 + 8 };
	}
	void mov(creg64 reg, size_t off) {
		movs[arg_c++] = { reg,off };
	}
	void movEnviro(uint16_t off) {
		movs[arg_c++] = { enviro_ptr,(int32_t(off) << 1) * 8 };
	}
	void movEnviroMeta(uint16_t off) {
		movs[arg_c++] = { enviro_ptr,(int32_t(off) << 1) * 8 + 8 };
	}
	template<class F>
	void finalize(F func) {
		size_t pushed = 0;
#if defined(_M_X64) || defined(__x86_64__)
		for (size_t i = 0; i < arg_c; i++) {
			if (Sargs.contains(i)) {
				switch (i) {
				case 0:
					csm.mov(argr0, Sargs[i]);
					break;
				case 1:
					csm.mov(argr1, Sargs[i]);
					break;
				case 2:
					csm.mov(argr2, Sargs[i]);
					break;
				case 3:
					csm.mov(argr3, Sargs[i]);
					break;
#ifndef _WIN64
				case 4:
					csm.mov(argr4, Sargs[i]);
					break;
				case 5:
					csm.mov(argr5, Sargs[i]);
					break;
#endif
				default:
					csm.push(Sargs[i]);
					pushed += Sargs[i].size();
				}
			}
			else if (Dargs.contains(i)) {
				switch (i) {
				case 0:
					csm.movA(argr0, Dargs[i]);
					break;
				case 1:
					csm.movA(argr1, Dargs[i]);
					break;
				case 2:
					csm.movA(argr2, Dargs[i]);
					break;
				case 3:
					csm.movA(argr3, Dargs[i]);
					break;
#ifndef _WIN64
				case 4:
					csm.movA(argr4, Dargs[i]);
					break;
				case 5:
					csm.movA(argr5, Dargs[i]);
					break;
#endif
				default:
					csm.push(Dargs[i]);
					pushed += 8;
				}
			}
			else if (leas.contains(i)) {
				switch (i) {
				case 0:
					csm.lea(argr0, leas[i].first, leas[i].second);
					break;
				case 1:
					csm.lea(argr1, leas[i].first, leas[i].second);
					break;
				case 2:
					csm.lea(argr2, leas[i].first, leas[i].second);
					break;
				case 3:
					csm.lea(argr3, leas[i].first, leas[i].second);
					break;
#ifndef _WIN64
				case 4:
					csm.lea(argr4, leas[i].first, leas[i].second);
					break;
				case 5:
					csm.lea(argr5, leas[i].first, leas[i].second);
					break;
#endif
				default:
					csm.lea(mut_temp_ptr, leas[i].first, leas[i].second);
					csm.push(mut_temp_ptr);
					pushed += 8;
				}
			}
			else if (movs.contains(i)) {
				switch (i) {
				case 0:
					csm.mov(argr0, movs[i].first, movs[i].second);
					break;
				case 1:
					csm.mov(argr1, movs[i].first, movs[i].second);
					break;
				case 2:
					csm.mov(argr2, movs[i].first, movs[i].second);
					break;
				case 3:
					csm.mov(argr3, movs[i].first, movs[i].second);
					break;
#ifndef _WIN64
				case 4:
					csm.mov(argr4, movs[i].first, movs[i].second);
					break;
				case 5:
					csm.mov(argr5, movs[i].first, movs[i].second);
					break;
#endif
				default:
					csm.mov(mut_temp_ptr, movs[i].first, movs[i].second);
					csm.push(mut_temp_ptr);
					pushed += 8;
				}
			}
			else
				throw CompileTimeException("Unexcepted exception when building function call");
		}
#else
		for (size_t i = 0; i < arg_c; i++) {
			if (Sargs.contains(i)) {
				csm.push(Sargs[i]);
				pushed += Sargs[i].size();
			}
			else if (Dargs.contains(i)) {
				csm.push(Dargs[i]);
				pushed += 4;
			}
			else if (leas.contains(i)) {
				csm.lea(mut_temp_ptr, leas[i].first, leas[i].second);
				csm.push(mut_temp_ptr);
				pushed += 4;
			}
			else if (movs.contains(i)) {
				csm.mov(mut_temp_ptr, movs[i].first, movs[i].second);
				csm.push(mut_temp_ptr);
				pushed += 4;
			}
			else
				throw CompileTimeException("Unexcepted exception when building function call");
		}
#endif
		csm.call(func);
		if (pushed) 
			csm.stackReduce(pushed);
	}
};

void _______dbgOut(const char*);
class BuildProlog {
	FrameResult res;
	std::vector<std::pair<uint16_t, creg>> pushes;
	std::vector<std::pair<uint16_t, uint32_t>> stack_alloc;
	std::vector<std::pair<uint16_t, uint16_t>> set_frame;
	std::vector<std::pair<uint16_t, std::pair<creg, size_t>>> save_to_stack;


	CASM& csm;
	enum UWC {
		UWOP_PUSH_NONVOL = 0,
		UWOP_ALLOC_LARGE = 1,
		UWOP_ALLOC_SMALL = 2,
		UWOP_SET_FPREG = 3,
		UWOP_SAVE_NONVOL = 4,
		UWOP_SAVE_NONVOL_FAR = 5,
		UWOP_SAVE_XMM128 = 8,
		UWOP_SAVE_XMM128_FAR = 9,
		UWOP_PUSH_MACHFRAME = 10,
	};
	size_t stack_align = 0;
	uint16_t cur_op = 0;
	bool frame_inited = false;
	bool prolog_preEnd = false;
public:
	BuildProlog(CASM& a) : csm(a) {}
	~BuildProlog() {
		if (frame_inited)
			return; 
		_______dbgOut("Frame not initalized!");
		::abort();
	}
	void pushReg(creg reg) {
		csm.push(reg.fromTypeAndId(asmjit::RegType::kGp64, reg.id()));
		UWCODE c;
		c.op = UWC::UWOP_PUSH_NONVOL;
		c.info = reg.id();
		c.offset = csm.offset();
		res.prolog.push_back(c.solid);
		pushes.push_back({ cur_op++,reg });
		stack_align += 8;
	}
	void stackAlloc(uint32_t size) {
		if (size == 0)
			return;
		//align stack
		size = (size / 8 + ((size % 8) ? 1 : 0)) * 8;
		csm.sub(stack_ptr, size);
		if (size <= 128) {
			UWCODE c;
			c.op = UWC::UWOP_ALLOC_SMALL;
			c.info = size / 8 - 1;
			c.offset = csm.offset();
			res.prolog.push_back(c.solid);
		}
		else if (size <= 524280) {
			//512K - 8
			UWCODE c;
			c.op = UWC::UWOP_ALLOC_LARGE;
			c.info = 0;
			c.offset = csm.offset();
			res.prolog.push_back(size / 8);
			res.prolog.push_back(c.solid);
		}
		else if(size <= 4294967288) {
			//4gb - 8
			UWCODE c;
			c.op = UWC::UWOP_ALLOC_LARGE;
			c.info = 1;
			c.offset = csm.offset();
			res.prolog.push_back((uint16_t)(size >> 16));
			res.prolog.push_back((uint16_t)size);
			res.prolog.push_back(c.solid);
		}
		else 
			throw CompileTimeException("Invalid uwind code, too large stack alocation");
		stack_alloc.push_back({ cur_op++, size });
		stack_align += size;
	}
	void setFrame(uint16_t stack_offset = 0) {
		if(frame_inited)
			throw CompileTimeException("Frame already inited");
		if (stack_offset % 16)
			throw CompileTimeException("Invalid frame offset, it must be aligned by 16");
		if(uint8_t(stack_offset / 16) != stack_offset / 16)
			throw CompileTimeException("frameoffset too large");

		csm.lea(frame_ptr, stack_ptr, stack_offset);
		UWCODE c;
		c.op = UWC::UWOP_SET_FPREG;
		c.info = 0;
		c.offset = csm.offset();
		res.prolog.push_back(c.solid);
		set_frame.push_back({ cur_op++, stack_offset });
		res.head.FrameOffset = stack_offset / 16;
		frame_inited = true;
	}
	void saveToStack(creg reg, int32_t stack_back_offset) {
		if (reg.isVec()) {
			if (reg.type() == asmjit::RegType::kVec128) {
				if (INT32_MAX > stack_back_offset)
					throw CompileTimeException("Overflow, fail convert 64 point to 32 point");
				if (UINT16_MAX > stack_back_offset || stack_back_offset % 16) {
					csm.mov(stack_ptr, stack_back_offset, reg.as<creg128>());
					UWCODE c;
					c.op = UWC::UWOP_SAVE_XMM128_FAR;
					c.info = reg.id();
					c.offset = csm.offset();
					res.prolog.push_back(stack_back_offset & (UINT32_MAX ^ UINT16_MAX));
					res.prolog.push_back(stack_back_offset & UINT16_MAX);
					res.prolog.push_back(c.solid);
				}
				else {
					csm.mov(stack_ptr, stack_back_offset, reg.as<creg128>());
					UWCODE c;
					c.op = UWC::UWOP_SAVE_XMM128;
					c.info = reg.id();
					c.offset = csm.offset();
					res.prolog.push_back(uint16_t(stack_back_offset / 16));
					res.prolog.push_back(c.solid);
				}
			}
			else
				throw CompileTimeException("Supported only 128 bit vector register");
		}
		else {
			csm.mov(stack_ptr, stack_back_offset, reg.size(), reg);
			if (stack_back_offset % 8) {
				UWCODE c;
				c.op = UWC::UWOP_SAVE_NONVOL_FAR;
				c.info = reg.id();
				c.offset = csm.offset();
				res.prolog.push_back(stack_back_offset & (UINT32_MAX ^ UINT16_MAX));
				res.prolog.push_back(stack_back_offset & UINT16_MAX);
				res.prolog.push_back(c.solid);
			}
			else {
				UWCODE c;
				c.op = UWC::UWOP_SAVE_NONVOL;
				c.info = reg.id();
				c.offset = csm.offset();
				res.prolog.push_back(uint16_t(stack_back_offset / 8));
				res.prolog.push_back(c.solid);
			}
		}
		save_to_stack.push_back({ cur_op++, {reg,stack_back_offset} });
	}
	void alignPush() {
		if (prolog_preEnd)
			throw CompileTimeException("alignPush will be used only once");
		if (stack_align & 0xF)
			stackAlloc(8);
		prolog_preEnd = true;
	}
	size_t cur_stack_offset() {
		return stack_align;
	}
	FrameResult& finalize() {
		while (cur_op--) {
			if (pushes.size()) {
				if (pushes.back().first == cur_op) {
					csm.pop(pushes.back().second);
					pushes.pop_back();
					continue;
				}
			}
			if (stack_alloc.size()) {
				if (stack_alloc.back().first == cur_op) {
					csm.stackReduce(stack_alloc.back().second);
					stack_alloc.pop_back();
					continue;
				}
			}
			if (set_frame.size()) {
				if (set_frame.back().first == cur_op) {
					csm.lea(stack_ptr, frame_ptr, -set_frame.back().second);
					set_frame.pop_back();
					continue;
				}
			}
			if (save_to_stack.size()) {
				if (save_to_stack.back().first == cur_op) {
					auto& reg = save_to_stack.back().second;
					if (reg.first.isVec())
						csm.mov_vector(reg.first.as<creg128>(), stack_ptr, reg.second);
					else
						csm.mov_default(reg.first, stack_ptr, reg.second, reg.first.size());
					save_to_stack.pop_back();
					continue;
				}
			}
			throw CompileTimeException("fail build prolog");
		}
		csm.ret();
		res.head.SizeOfProlog = csm.offset();
		res.head.CountOfUnwindCodes = res.prolog.size();

		if (res.head.CountOfUnwindCodes & 1)
			res.prolog.push_back(0);
		return res;
	}
};



#elif defined(__aarch64__) || defined(_M_ARM64)

#else
#error INVALID BUILD ARCHITECTURE, supported only x64 or aarch64 archetectures
#endif