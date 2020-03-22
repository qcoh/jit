#include <sys/mman.h>
#include <utility>

#include "catch2/catch.hpp"
#include "jit.h"


SCENARIO("simple jit test", "[jit]") {
	GIVEN("assembly function returning 2") {
		const auto c = jit::make_assembler()
		| jit::linux_x86_64_begin()
		| jit::xor_(jit::rax, jit::rax)
		| jit::inc(jit::rax)
		| jit::inc(jit::rax)
		| jit::linux_x86_64_end()
		;

		const auto machine_code = c.emit();

		jit::u8* page = static_cast<jit::u8*>(mmap(nullptr, 4096, PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0));
		REQUIRE(page != (jit::u8*)-1);
		std::copy(std::begin(machine_code), std::end(machine_code), page);
		REQUIRE(mprotect(page, 4096, PROT_READ|PROT_EXEC) == 0);

		auto fn = reinterpret_cast<int(*)()>(page);

		WHEN("invoking the function") {
			int ret = fn();

			THEN("returns 2") {
				REQUIRE(ret == 2);
			}
		}
	}
}
