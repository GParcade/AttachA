// Copyright Danyil Melnytskyi 2022
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include <asmjit/asmjit.h>
#include <vector>
#include "library/exceptions.hpp"
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
#if defined(_M_X64) || defined(__x86_64__)
#define CASM_X64
#endif

#ifdef CASM_X64



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

	static uint32_t enviroValueOffset(uint16_t off) {
		return (int32_t(off) << 1) * 8;
	}
	static uint32_t enviroMetaOffset(uint16_t off) {
		return ((int32_t(off) << 1) & 1) * 8;
	}

	void stackAlloc(size_t bytes_count) {
		a.mov(resr, stack_ptr);
		a.sub(stack_ptr, bytes_count);
	}
	void stackAlloc(creg64 bytes_count) {
		a.mov(resr, stack_ptr);
		a.sub(stack_ptr, bytes_count);
	}
	void stackIncrease(size_t bytes_count) {
		a.sub(stack_ptr, bytes_count);
	}
	void stackIncrease(creg64 bytes_count) {
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
		a.mov(res, asmjit::x86::ptr_64(base, off));
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


	void shift_left(creg64 c0, creg64 c1) {
		a.shl(c0, c1);
	}
	void shift_left(creg32 c0, creg32 c1) {
		a.shl(c0, c1);
	}
	void shift_left(creg16 c0, creg16 c1) {
		a.shl(c0, c1);
	}
	void shift_left(creg8 c0, creg8 c1) {
		a.shl(c0, c1);
	}
	void shift_right(creg64 c0, creg64 c1) {
		a.shr(c0, c1);
	}
	void shift_right(creg32 c0, creg32 c1) {
		a.shr(c0, c1);
	}
	void shift_right(creg16 c0, creg16 c1) {
		a.shr(c0, c1);
	}
	void shift_right(creg8 c0, creg8 c1) {
		a.shr(c0, c1);
	}

	void shift_left(creg64 c0, int8_t c1) {
		a.shl(c0, c1);
	}
	void shift_left(creg32 c0, int8_t c1) {
		a.shl(c0, c1);
	}
	void shift_left(creg16 c0, int8_t c1) {
		a.shl(c0, c1);
	}
	void shift_left(creg8 c0, int8_t c1) {
		a.shl(c0, c1);
	}
	void shift_right(creg64 c0, int8_t c1) {
		a.shr(c0, c1);
	}
	void shift_right(creg32 c0, int8_t c1) {
		a.shr(c0, c1);
	}
	void shift_right(creg16 c0, int8_t c1) {
		a.shr(c0, c1);
	}
	void shift_right(creg8 c0, int8_t c1) {
		a.shr(c0, c1);
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


	void or_(creg64 c0, creg64 c1) {
		a.or_(c0, c1);
	}
	void or_(creg32 c0, creg32 c1) {
		a.or_(c0, c1);
	}
	void or_(creg16 c0, creg16 c1) {
		a.or_(c0, c1);
	}
	void or_(creg8 c0, creg8 c1) {
		a.or_(c0, c1);
	}
	void or_byte(creg8 res, creg64 base, int32_t off) {
		a.or_(res, asmjit::x86::ptr_8(res, off));
	}
	void or_short(creg16 res, creg64 base, int32_t off) {
		a.or_(res, asmjit::x86::ptr_16(res, off));
	}
	void or_int(creg32 res, creg64 base, int32_t off) {
		a.or_(res, asmjit::x86::ptr_32(res, off));
	}
	void or_long(creg64 res, creg64 base, int32_t off) {
		a.or_(res, asmjit::x86::ptr_64(res, off));
	}
	void or_(creg64 res, creg64 base, int32_t off) {
		a.or_(res, asmjit::x86::ptr_64(res, off));
	}
	void or_(creg res, const asmjit::Imm& v) {
		a.or_(res, v);
	}
	void or_(creg64 res, int32_t res_off, int32_t vsize, const asmjit::Imm& v) {
		a.or_(asmjit::x86::ptr(res, res_off, vsize), v);
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
		uint16_t solid = 0;
		UWCODE() = default;
		UWCODE(const UWCODE& copy) = default;
		UWCODE(uint8_t off, uint8_t oper, uint8_t inf) { offset = off; op = oper; info = inf; }
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
	static std::vector<void*>* JitCaptureStackChainTrace(uint32_t framesToSkip = 0, bool includeNativeFrames = true, uint32_t max_frames = 32);
	static std::vector<StackTraceItem> JitCaptureStackTrace(uint32_t framesToSkip = 0, bool includeNativeFrames = true, uint32_t max_frames = 32);
};


#include <unordered_map>
class BuildCall {
	CASM& csm;
	size_t arg_c = 0;
	size_t pushed = 0;
	bool red_zone_inited = false;
#ifdef _WIN64
	void callStart() {
		if (!arg_c) {
			if (red_zone_inited)
				csm.stackIncrease(0x20);//function visual c++ abi
			red_zone_inited = true;
		}
	}
#else
#define callStart()
#endif // _WIN64
public:
	BuildCall(CASM& a) : csm(a) {}
	~BuildCall() noexcept(false) {
		if (arg_c)
			throw InvalidOperation("Build call is incomplete, need finalization");
	}
	void iniRedzone() {
		callStart();
		red_zone_inited = true;
	}
	void addArg(creg reg) {
		callStart();
		switch (arg_c++) {
		case 0:
			if (argr0 != reg)
				csm.movA(argr0, reg);
			break;
		case 1:
			if (argr1 != reg)
				csm.movA(argr1, reg);
			break;
		case 2:
			if (argr2 != reg)
				csm.movA(argr2, reg);
			break;
		case 3:
			if (argr3 != reg)
				csm.movA(argr3, reg);
			break;
#ifndef _WIN64
		case 4:
			if (argr4 != reg)
				csm.movA(argr4, reg);
			break;
		case 5:
			if (argr5 != reg)
				csm.movA(argr5, reg);
			break;
#endif
		default:
			csm.push(reg);
			pushed += 8;
		}
	}
	void addArg(const asmjit::Imm& val) {
		callStart();
		switch (arg_c++) {
		case 0:
			csm.mov(argr0, val);
			break;
		case 1:
			csm.mov(argr1, val);
			break;
		case 2:
			csm.mov(argr2, val);
			break;
		case 3:
			csm.mov(argr3, val);
			break;
#ifndef _WIN64
		case 4:
			csm.mov(argr4, val);
			break;
		case 5:
			csm.mov(argr5, val);
			break;
#endif
		default:
			csm.push(val);
			pushed += val.size();
		}
	}
	void lea(creg64 reg, int32_t off) {
		callStart();
		switch (arg_c++) {
		case 0:
			csm.lea(argr0, reg, off);
			break;
		case 1:
			csm.lea(argr1, reg, off);
			break;
		case 2:
			csm.lea(argr2, reg, off);
			break;
		case 3:
			csm.lea(argr3, reg, off);
			break;
#ifndef _WIN64
		case 4:
			csm.lea(argr4, reg, off);
			break;
		case 5:
			csm.lea(argr5, reg, off);
			break;
#endif
		default:
			if (off) {
				csm.lea(mut_temp_ptr, reg, off);
				csm.push(mut_temp_ptr);
			} else csm.push(reg);
			pushed += 8;
		}
	}
	void leaEnviro(uint16_t off) {
		callStart();
		lea(enviro_ptr,(size_t(off) << 1) * 8 );
	}
	void leaEnviroMeta(uint16_t off) {
		callStart();
		lea(enviro_ptr,(size_t(off) << 1) * 8 + 8 );
	}
	void mov(creg64 reg, int32_t off) {
		callStart();
		switch (arg_c++) {
		case 0:
			csm.mov(argr0, reg, off);
			break;
		case 1:
			csm.mov(argr1, reg, off);
			break;
		case 2:
			csm.mov(argr2, reg, off);
			break;
		case 3:
			csm.mov(argr3, reg, off);
			break;
#ifndef _WIN64
		case 4:
			csm.mov(argr4, reg, off);
			break;
		case 5:
			csm.mov(argr5, reg, off);
			break;
#endif
		default:
			csm.mov(mut_temp_ptr, reg, off);
			csm.push(mut_temp_ptr);
			pushed += 8;
		}
	}
	void movEnviro(uint16_t off) {
		callStart();
		mov(enviro_ptr, (size_t(off) << 1) * 8);
	}
	void movEnviroMeta(uint16_t off) {
		callStart();
		mov(enviro_ptr, (size_t(off) << 1) * 8 + 8);
	}
	void skip() {
		callStart();
		switch (arg_c++) {
		case 0:
		case 1:
		case 2:
		case 3:
#ifndef _WIN64
		case 4:
		case 5:
#endif
			break;
		default:
			//push(*)
			pushed += 8;
		}
	}

	template<class F>
	void finalize(F func) {
		csm.call(func);
		if (pushed) 
			csm.stackReduce(pushed);
		pushed = 0;
		arg_c = 0;
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
		res.prolog.push_back(UWCODE(csm.offset(), UWC::UWOP_PUSH_NONVOL, reg.id()).solid);
		pushes.push_back({ cur_op++,reg });
		stack_align += 8;
	}
	void stackAlloc(uint32_t size) {
		if (size == 0)
			return;
		//align stack
		size = (size / 8 + ((size % 8) ? 1 : 0)) * 8;
		csm.sub(stack_ptr, size);
		if (size <= 128) 
			res.prolog.push_back(UWCODE(csm.offset(), UWC::UWOP_ALLOC_SMALL, size / 8 - 1).solid);
		else if (size <= 524280) {
			//512K - 8
			res.prolog.push_back(size / 8);
			res.prolog.push_back(UWCODE(csm.offset(), UWC::UWOP_ALLOC_LARGE, 0).solid);
		}
		else if(size <= 4294967288) {
			//4gb - 8
			res.prolog.push_back((uint16_t)(size >> 16));
			res.prolog.push_back((uint16_t)size);
			res.prolog.push_back(UWCODE(csm.offset(), UWC::UWOP_ALLOC_LARGE, 1).solid);
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
		res.prolog.push_back(UWCODE(csm.offset(), UWC::UWOP_SET_FPREG, 0).solid);
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
					res.prolog.push_back(stack_back_offset & (UINT32_MAX ^ UINT16_MAX));
					res.prolog.push_back(stack_back_offset & UINT16_MAX);
					res.prolog.push_back(UWCODE(csm.offset(), UWC::UWOP_SAVE_XMM128_FAR, reg.id()).solid);
				}
				else {
					csm.mov(stack_ptr, stack_back_offset, reg.as<creg128>());
					res.prolog.push_back(uint16_t(stack_back_offset / 16));
					res.prolog.push_back(UWCODE(csm.offset(), UWC::UWOP_SAVE_XMM128, reg.id()).solid);
				}
			}
			else
				throw CompileTimeException("Supported only 128 bit vector register");
		}
		else {
			csm.mov(stack_ptr, stack_back_offset, reg.size(), reg);
			if (stack_back_offset % 8) {
				res.prolog.push_back(stack_back_offset & (UINT32_MAX ^ UINT16_MAX));
				res.prolog.push_back(stack_back_offset & UINT16_MAX);
				res.prolog.push_back(UWCODE(csm.offset(), UWC::UWOP_SAVE_NONVOL_FAR, reg.id()).solid);
			}
			else {
				res.prolog.push_back(uint16_t(stack_back_offset / 8));
				res.prolog.push_back(UWCODE(csm.offset(), UWC::UWOP_SAVE_NONVOL, reg.id()).solid);
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