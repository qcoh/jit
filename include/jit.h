#pragma once

#include <array>

namespace jit {

using u8 = unsigned char;

template <u8... Bytes>
struct assembler {
	static constexpr int size = sizeof...(Bytes);

	template <u8... ArgBytes>
	constexpr auto operator|(const assembler<ArgBytes...>&) const -> assembler<Bytes..., ArgBytes...> {
		return {};
	}

	constexpr auto emit() const -> std::array<u8, size> {
		return {{ Bytes... }};
	}
};

auto make_assembler() -> assembler<> {
	return {};
}

// registers

struct al_type {} al;
struct ah_type {} ah;
struct ax_type {} ax;
struct eax_type {} eax;
struct rax_type {} rax;

struct bl_type {} bl;
struct bh_type {} bh;
struct bx_type {} bx;
struct ebx_type {} ebx;
struct rbx_type {} rbx;

struct cl_type {} cl;
struct ch_type {} ch;
struct cx_type {} cx;
struct ecx_type {} ecx;
struct rcx_type {} rcx;

struct dl_type {} dl;
struct dh_type {} dh;
struct dx_type {} dx;
struct edx_type {} edx;
struct rdx_type {} rdx;

struct bpl_type {} bpl;
struct bp_type {} bp;
struct ebp_type {} ebp;
struct rbp_type {} rbp;

struct r8b_type {} r8b;
struct r8w_type {} r8w;
struct r8d_type {} r8d;
struct r8_type {} r8;

struct r9b_type {} r9b;
struct r9w_type {} r9w;
struct r9d_type {} r9d;
struct r9_type {} r9;

struct r10b_type {} r10b;
struct r10w_type {} r10w;
struct r10d_type {} r10d;
struct r10_type {} r10;

struct r11b_type {} r11b;
struct r11w_type {} r11w;
struct r11d_type {} r11d;
struct r11_type {} r11;

struct r12b_type {} r12b;
struct r12w_type {} r12w;
struct r12d_type {} r12d;
struct r12_type {} r12;

struct r13b_type {} r13b;
struct r13w_type {} r13w;
struct r13d_type {} r13d;
struct r13_type {} r13;

struct r14b_type {} r14b;
struct r14w_type {} r14w;
struct r14d_type {} r14d;
struct r14_type {} r14;

struct r15b_type {} r15b;
struct r15w_type {} r15w;
struct r15d_type {} r15d;
struct r15_type {} r15;

// instructions

constexpr auto nop() -> assembler<0x90> { return {}; }

constexpr auto inc(ah_type) -> assembler<0xfe, 0xc4> { return {}; }
constexpr auto xor_(rax_type, rax_type) -> assembler<0x48, 0x31, 0xc0> { return {}; }
constexpr auto inc(rax_type) -> assembler<0x48, 0xff, 0xc0> { return {}; }
constexpr auto seto(al_type) -> assembler<0x0f, 0x90, 0xc0> { return {}; }
constexpr auto seta(al_type) -> assembler<0x0f, 0x97, 0xc0> { return {}; }
constexpr auto setz(al_type) -> assembler<0x0f, 0x94, 0xc0> { return {}; }
constexpr auto lahf() -> assembler<0x9f> { return {}; }
constexpr auto sahf() -> assembler<0x9e> { return {}; }

constexpr auto mov(al_type, ah_type) -> assembler<0x88, 0xe0> { return {}; }
constexpr auto xor_(ah_type, ah_type) -> assembler<0x30, 0xe4> { return {}; }

constexpr auto push(rbx_type) -> assembler<0x53> { return {}; }
constexpr auto push(rbp_type) -> assembler<0x55> { return {}; }
constexpr auto push(r12_type) -> assembler<0x41, 0x54> { return {}; }
constexpr auto push(r13_type) -> assembler<0x41, 0x55> { return {}; }
constexpr auto push(r14_type) -> assembler<0x41, 0x56> { return {}; }
constexpr auto push(r15_type) -> assembler<0x41, 0x57> { return {}; }

constexpr auto pop(rbx_type) -> assembler<0x5b> { return {}; }
constexpr auto pop(rbp_type) -> assembler<0x5d> { return {}; }
constexpr auto pop(r12_type) -> assembler<0x41, 0x5c> { return {}; }
constexpr auto pop(r13_type) -> assembler<0x41, 0x5d> { return {}; }
constexpr auto pop(r14_type) -> assembler<0x41, 0x5e> { return {}; }
constexpr auto pop(r15_type) -> assembler<0x41, 0x5f> { return {}; }

constexpr auto retq() -> assembler<0xc3> { return {}; }

// calling convention

constexpr auto linux_x86_64_begin() {
	return assembler<>{}
	| push(rbx)
	| push(rbp)
	| push(r12)
	| push(r13)
	| push(r14)
	| push(r15)
	;
}

constexpr auto linux_x86_64_end() {
	return assembler<>{}
	| pop(r15)
	| pop(r14)
	| pop(r13)
	| pop(r12)
	| pop(rbp)
	| pop(rbx)
	| retq()
	;
}

}
