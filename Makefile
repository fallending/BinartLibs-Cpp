# 这个很可以参考：https://zhuanlan.zhihu.com/p/103696297

# https://docs.microsoft.com/zh-cn/cpp/build/manage-libraries-with-vcpkg?view=msvc-160&tabs=macos


offer:
	@echo "amalgamate - amalgamate file single_include/nlohmann/json.hpp from the include/nlohmann sources"
	@echo "ChangeLog.md - generate ChangeLog file"
	@echo "check-amalgamation - check whether sources have been amalgamated"
	@echo "clean - remove built files"
	@echo "coverage - create coverage information with lcov"
	@echo "cppcheck - analyze code with cppcheck"
	@echo "cpplint - analyze code with cpplint"
	@echo "clang_tidy - analyze code with Clang-Tidy"
	@echo "clang_analyze - analyze code with Clang-Analyzer"
	@echo "doctest - compile example files and check their output"
	@echo "fuzz_testing - prepare fuzz testing of the JSON parser"
	@echo "fuzz_testing_bson - prepare fuzz testing of the BSON parser"
	@echo "fuzz_testing_cbor - prepare fuzz testing of the CBOR parser"
	@echo "fuzz_testing_msgpack - prepare fuzz testing of the MessagePack parser"
	@echo "fuzz_testing_ubjson - prepare fuzz testing of the UBJSON parser"
	@echo "pedantic_clang - run Clang with maximal warning flags"
	@echo "pedantic_gcc - run GCC with maximal warning flags"
	@echo "pretty - beautify code with Artistic Style"
	@echo "run_benchmarks - build and run benchmarks"

# 1. 区分交叉编译环境（windows/linux/macosx）
# 2. 区分目标平台（win32/win64/linux/mac64/iOS/android等等）

# MT_TARGET_PLATFORM
# MT_TARGET_PLATFORM_ANDROID
# MT_TARGET_PLATFORM_IOS
# MT_TARGET_PLATFORM_WINDOWS
# ????

# 所有架构
# 1. ios
# 2. android
# 3. windows
# 用 它 来决定主cmakelist中的options
# 主cmakelist中的options，来决定 add_definitions(-Dhha -Dbbb)，从而决定愿代码文件中的 #if #else #endif

# 方式1: cmakelist 直接整合到工程，通过ANDROID APPLE，工程编译时，打不同的包
# 方式2: cmakelist 通过ANDROID APPLE，工程编译时，打不同的包，集成到工程中

version:
	cmake --version

clean:
	rm -rf _builds

gen:
	rm -rf _exports && mkdir _exports && cd _exports && cmake -G Xcode -H. -B_build -DCMAKE_TOOLCHAIN_FILE=~/.cmake_modules/vcpkg/scripts/buildsystems/vcpkg.cmake ..

rebuild:
	make clean && mkdir _builds && cd _builds && cmake .. -GNinja -DCMAKE_TOOLCHAIN_FILE=~/.cmake_modules/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build .

build:
	cd _builds && ninja

AMALGAMATED_FILE=./src/http

# call cppcheck <http://cppcheck.sourceforge.net>
checkwhat:
	@echo "- --------------------------------------------------"
	@echo "- make check"
	@echo "- --------------------------------------------------"
	@echo "- error：代码中的错误项，包括内存泄漏等；"
	@echo "- warning：为了避免产生bug而提供的编程改进意见；"
	@echo "- style：编码风格，提示你哪些函数没有使用、哪些为多余代码等；"
	@echo "- portability：提示跨平台时容易出现的问题；"
	@echo "- performance：该部分代码可以优化；"
	@echo "- information：其他信息，可以忽略；"
	@echo "- --------------------------------------------------"

check:
	cppcheck --enable=all --inline-suppr --inconclusive --force --std=c++14 $(AMALGAMATED_FILE) 2> check-result.txt
# --error-exitcode=1

COMPILER_DIR=/usr/local/opt/llvm/bin
# call Clang Static Analyzer <https://clang-analyzer.llvm.org>
analyze:
	rm -fr cmake-build-clang-analyze
	mkdir cmake-build-clang-analyze
	cd cmake-build-clang-analyze ; CCC_CXX=$(COMPILER_DIR)/clang++ CXX=$(COMPILER_DIR)/clang++ $(COMPILER_DIR)/scan-build cmake .. -GNinja -DJSON_BuildTests=On
	cd cmake-build-clang-analyze ; \
		$(COMPILER_DIR)/scan-build \
			-enable-checker alpha.core.BoolAssignment,alpha.core.CallAndMessageUnInitRefArg,alpha.core.CastSize,alpha.core.CastToStruct,alpha.core.Conversion,alpha.core.DynamicTypeChecker,alpha.core.FixedAddr,alpha.core.PointerArithm,alpha.core.PointerSub,alpha.core.SizeofPtr,alpha.core.StackAddressAsyncEscape,alpha.core.TestAfterDivZero,alpha.deadcode.UnreachableCode,core.builtin.BuiltinFunctions,core.builtin.NoReturnFunctions,core.CallAndMessage,core.DivideZero,core.DynamicTypePropagation,core.NonnilStringConstants,core.NonNullParamChecker,core.NullDereference,core.StackAddressEscape,core.UndefinedBinaryOperatorResult,core.uninitialized.ArraySubscript,core.uninitialized.Assign,core.uninitialized.Branch,core.uninitialized.CapturedBlockVariable,core.uninitialized.UndefReturn,core.VLASize,cplusplus.InnerPointer,cplusplus.Move,cplusplus.NewDelete,cplusplus.NewDeleteLeaks,cplusplus.SelfAssignment,deadcode.DeadStores,nullability.NullableDereferenced,nullability.NullablePassedToNonnull,nullability.NullableReturnedFromNonnull,nullability.NullPassedToNonnull,nullability.NullReturnedFromNonnull \
			--use-c++=$(COMPILER_DIR)/clang++ -analyze-headers -o report ninja
	open cmake-build-clang-analyze/report/*/index.html

##########################################################################
# lint 代码风格检查，解决代码审查噪音
# call cpplint <https://github.com/cpplint/cpplint>
# https://blog.csdn.net/fengbingchun/article/details/47341765
# http://qiushao.net/2020/03/15/c++/c++%E7%BC%96%E7%A0%81%E8%A7%84%E8%8C%83%E6%A3%80%E6%9F%A5/
##########################################################################

# the list of sources in the include folder
SRCS=$(shell find src -type f | sort)

lint:
	bin/cpplint.py --extensions=h,hpp,cc,cpp --linelength=120 $(SRCS2)

# 控制输出警告的级别【1=5】： cpplint.py --verbose=3 test.cpp
# 控制过滤置信度
# 对于发现的每一个问题，cpplint都会给出一个位于区间[1, 5]之间的置信度评分，分数越高就代表问题越肯定，能够通过verbose选项控制输出哪些级别。例如以下。置信度评分为1、2的将不会再输出：
# 支持对hpp的检测： cpplint.py --extensions=hpp test.cpp
# 输出日志到文件： cpplint.py --output test.cpp 2>log.txt
# 使用filter 过滤某些可忽略的警告： cpplint.py --filter=-whitespace test.cpp
# 将错误按照不同类型进行统计： cpplint.py --counting=detailed test.cpp
# 检测一行长度是否超出指定字符： cpplint.py --linelength=120 test.cpp
# 帮助 cpplint.py --help
# https://stackoverflow.com/questions/51582604/how-to-use-cpplint-code-style-checking-with-cmake

# cpplint的缺陷！！！不太行啊
# 我们只需要参考现有的规则添加即可。基本上都是对正则表达式的使用而已。也因为 cpplint 只是使用了模式匹配的方法来做检查，
# 并没有进行语法分析，所以有很多规则没法检查。比如，命名规则等。这也是一个非常大的缺陷。不过目前也没有其他更优秀的开源工具了，就将就着用先了。
tidy-rules:
	clang-tidy -list-checks

# call Clang-Tidy <https://clang.llvm.org/extra/clang-tidy/>
SRCS2=$(shell find src/timber -type f | sort | egrep "\.(hpp|h|cpp|cc)$\")
src2:
	@echo ${SRCS2}
tidy:
# 静态检查单个可编译文件
# clang-tidy tests/simple/test_main.cc -- 
#	clang-tidy $(SRCS) -- -Iinclude -std=c++14
# 静态检查整个项目
	clang-tidy --use-color -p=_builds ${SRCS2} --export-fixes=_temp/clang-tidy-results.yml 
	
# 后面的--表示这个文件不在compilation database里面，可以直接单独编译

test:
	./_builds/bin/test_lib_bitbuffer
	./_builds/bin/test_mtjson
	./_builds/bin/test_timber
	./_builds/bin/test_simple

test-fancy:
	./_builds/bin/test_fancy

##########################################################################
# pretty 2
##########################################################################
# call the Clang-Format on all source files
format:
	for FILE in tests/simple/*.cc ; do echo $$FILE; clang-format -style=google -i $$FILE; done

# // 格式化最新的commit，并直接在原文件上修改
format-diff:
	git diff -U0 HEAD^ | clang-format-diff.py -i -p1

##########################################################################
# coverage
##########################################################################

coverage:
	rm -fr cmake-build-coverage
	mkdir cmake-build-coverage
	cd cmake-build-coverage ; cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug -DJSON_Coverage=ON -DJSON_MultipleHeaders=ON
	cd cmake-build-coverage ; ninja
	cd cmake-build-coverage ; ctest -j10
	cd cmake-build-coverage ; ninja lcov_html
	open cmake-build-coverage/test/html/index.html

##########################################################################
# documentation tests
##########################################################################

# compile example files and check output
doctest:
	$(MAKE) check_output -C doc

##########################################################################
# warning detector
##########################################################################

# calling Clang with all warnings, except:
# -Wno-c++2a-compat: u8 literals will behave differently in C++20...
# -Wno-deprecated-declarations: the library deprecated some functions
# -Wno-documentation-unknown-command: code uses user-defined commands like @complexity
# -Wno-exit-time-destructors: warning in json code triggered by NLOHMANN_JSON_SERIALIZE_ENUM
# -Wno-float-equal: not all comparisons in the tests can be replaced by Approx
# -Wno-missing-prototypes: for NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE
# -Wno-padded: padding is nothing to warn about
# -Wno-range-loop-analysis: items tests "for(const auto i...)"
# -Wno-switch-enum -Wno-covered-switch-default: pedantic/contradicting warnings about switches
# -Wno-weak-vtables: exception class is defined inline, but has virtual method
pedantic_clang:
	rm -fr cmake-build-pedantic
	CXXFLAGS=" \
		-std=c++11 -Wno-c++98-compat -Wno-c++98-compat-pedantic \
		-Werror \
		-Weverything \
		-Wno-c++2a-compat \
		-Wno-deprecated-declarations \
		-Wno-documentation-unknown-command \
		-Wno-exit-time-destructors \
		-Wno-float-equal \
		-Wno-missing-prototypes \
		-Wno-padded \
		-Wno-range-loop-analysis \
		-Wno-switch-enum -Wno-covered-switch-default \
		-Wno-weak-vtables" cmake -S . -B cmake-build-pedantic -GNinja -DCMAKE_BUILD_TYPE=Debug -DJSON_MultipleHeaders=ON -DJSON_BuildTests=On
	cmake --build cmake-build-pedantic

# calling GCC with most warnings
pedantic_gcc:
	rm -fr cmake-build-pedantic
	CXXFLAGS=" \
		-std=c++11 \
		-pedantic \
		-Werror \
		--all-warnings                                    \
		--extra-warnings                                  \
		-W                                                \
		-Wno-abi-tag                                         \
		-Waddress                                         \
		-Waddress-of-packed-member                        \
		-Wno-aggregate-return                                \
		-Waggressive-loop-optimizations                   \
		-Waligned-new=all                                 \
		-Wall                                             \
		-Walloc-zero                                      \
		-Walloca                                          \
		-Wanalyzer-double-fclose                          \
		-Wanalyzer-double-free                            \
		-Wanalyzer-exposure-through-output-file           \
		-Wanalyzer-file-leak                              \
		-Wanalyzer-free-of-non-heap                       \
		-Wanalyzer-malloc-leak                            \
		-Wanalyzer-null-argument                          \
		-Wanalyzer-null-dereference                       \
		-Wanalyzer-possible-null-argument                 \
		-Wanalyzer-possible-null-dereference              \
		-Wanalyzer-stale-setjmp-buffer                    \
		-Wanalyzer-tainted-array-index                    \
		-Wanalyzer-too-complex                            \
		-Wanalyzer-unsafe-call-within-signal-handler      \
		-Wanalyzer-use-after-free                         \
		-Wanalyzer-use-of-pointer-in-stale-stack-frame    \
		-Warith-conversion                                \
		-Warray-bounds                                    \
		-Warray-bounds=2                                  \
		-Wattribute-alias=2                               \
		-Wattribute-warning                               \
		-Wattributes                                      \
		-Wbool-compare                                    \
		-Wbool-operation                                  \
		-Wbuiltin-declaration-mismatch                    \
		-Wbuiltin-macro-redefined                         \
		-Wc++0x-compat                                    \
		-Wc++11-compat                                    \
		-Wc++14-compat                                    \
		-Wc++17-compat                                    \
		-Wc++1z-compat                                    \
		-Wc++20-compat                                    \
		-Wc++2a-compat                                    \
		-Wcannot-profile                                  \
		-Wcast-align                                      \
		-Wcast-align=strict                               \
		-Wcast-function-type                              \
		-Wcast-qual                                       \
		-Wcatch-value=3                                   \
		-Wchar-subscripts                                 \
		-Wclass-conversion                                \
		-Wclass-memaccess                                 \
		-Wclobbered                                       \
		-Wcomma-subscript                                 \
		-Wcomment                                         \
		-Wcomments                                        \
		-Wconditionally-supported                         \
		-Wconversion                                      \
		-Wconversion-null                                 \
		-Wcoverage-mismatch                               \
		-Wcpp                                             \
		-Wctor-dtor-privacy                               \
		-Wdangling-else                                   \
		-Wdate-time                                       \
		-Wdelete-incomplete                               \
		-Wdelete-non-virtual-dtor                         \
		-Wdeprecated                                      \
		-Wdeprecated-copy                                 \
		-Wdeprecated-copy-dtor                            \
		-Wdeprecated-declarations                         \
		-Wdisabled-optimization                           \
		-Wdiv-by-zero                                     \
		-Wdouble-promotion                                \
		-Wduplicated-branches                             \
		-Wduplicated-cond                                 \
		-Weffc++                                          \
		-Wempty-body                                      \
		-Wendif-labels                                    \
		-Wenum-compare                                    \
		-Wexpansion-to-defined                            \
		-Wextra                                           \
		-Wextra-semi                                      \
		-Wfloat-conversion                                \
		-Wfloat-equal                                     \
		-Wformat -Wformat-contains-nul                    \
		-Wformat -Wformat-extra-args                      \
		-Wformat -Wformat-nonliteral                      \
		-Wformat -Wformat-security                        \
		-Wformat -Wformat-y2k                             \
		-Wformat -Wformat-zero-length                     \
		-Wformat-diag                                     \
		-Wformat-overflow=2                               \
		-Wformat-signedness                               \
		-Wformat-truncation=2                             \
		-Wformat=2                                        \
		-Wframe-address                                   \
		-Wfree-nonheap-object                             \
		-Whsa                                             \
		-Wif-not-aligned                                  \
		-Wignored-attributes                              \
		-Wignored-qualifiers                              \
		-Wimplicit-fallthrough=5                          \
		-Winaccessible-base                               \
		-Winherited-variadic-ctor                         \
		-Winit-list-lifetime                              \
		-Winit-self                                       \
		-Winline                                          \
		-Wint-in-bool-context                             \
		-Wint-to-pointer-cast                             \
		-Winvalid-memory-model                            \
		-Winvalid-offsetof                                \
		-Winvalid-pch                                     \
		-Wliteral-suffix                                  \
		-Wlogical-not-parentheses                         \
		-Wlogical-op                                      \
		-Wno-long-long                                       \
		-Wlto-type-mismatch                               \
		-Wmain                                            \
		-Wmaybe-uninitialized                             \
		-Wmemset-elt-size                                 \
		-Wmemset-transposed-args                          \
		-Wmisleading-indentation                          \
		-Wmismatched-tags                                 \
		-Wmissing-attributes                              \
		-Wmissing-braces                                  \
		-Wno-missing-declarations                            \
		-Wmissing-field-initializers                      \
		-Wmissing-include-dirs                            \
		-Wmissing-profile                                 \
		-Wmultichar                                       \
		-Wmultiple-inheritance                            \
		-Wmultistatement-macros                           \
		-Wno-namespaces                                      \
		-Wnarrowing                                       \
		-Wno-noexcept                                        \
		-Wnoexcept-type                                   \
		-Wnon-template-friend                             \
		-Wnon-virtual-dtor                                \
		-Wnonnull                                         \
		-Wnonnull-compare                                 \
		-Wnonportable-cfstrings                           \
		-Wnormalized=nfkc                                 \
		-Wnull-dereference                                \
		-Wodr                                             \
		-Wold-style-cast                                  \
		-Wopenmp-simd                                     \
		-Woverflow                                        \
		-Woverlength-strings                              \
		-Woverloaded-virtual                              \
		-Wpacked                                          \
		-Wpacked-bitfield-compat                          \
		-Wpacked-not-aligned                              \
		-Wno-padded                                          \
		-Wparentheses                                     \
		-Wpedantic                                        \
		-Wpessimizing-move                                \
		-Wplacement-new=2                                 \
		-Wpmf-conversions                                 \
		-Wpointer-arith                                   \
		-Wpointer-compare                                 \
		-Wpragmas                                         \
		-Wprio-ctor-dtor                                  \
		-Wpsabi                                           \
		-Wredundant-decls                                 \
		-Wredundant-move                                  \
		-Wredundant-tags                                  \
		-Wregister                                        \
		-Wreorder                                         \
		-Wrestrict                                        \
		-Wreturn-local-addr                               \
		-Wreturn-type                                     \
		-Wscalar-storage-order                            \
		-Wsequence-point                                  \
		-Wshadow=compatible-local                         \
		-Wshadow=global                                   \
		-Wshadow=local                                    \
		-Wshift-count-negative                            \
		-Wshift-count-overflow                            \
		-Wshift-negative-value                            \
		-Wshift-overflow=2                                \
		-Wsign-compare                                    \
		-Wsign-conversion                                 \
		-Wsign-promo                                      \
		-Wsized-deallocation                              \
		-Wsizeof-array-argument                           \
		-Wsizeof-pointer-div                              \
		-Wsizeof-pointer-memaccess                        \
		-Wstack-protector                                 \
		-Wstrict-aliasing                                 \
		-Wstrict-aliasing=3                               \
		-Wstrict-null-sentinel                            \
		-Wstrict-overflow                                 \
		-Wstrict-overflow=5                               \
		-Wstring-compare                                  \
		-Wstringop-overflow                               \
		-Wstringop-overflow=4                             \
		-Wstringop-truncation                             \
		-Wsubobject-linkage                               \
		-Wsuggest-attribute=cold                          \
		-Wsuggest-attribute=const                         \
		-Wsuggest-attribute=format                        \
		-Wsuggest-attribute=malloc                        \
		-Wsuggest-attribute=noreturn                      \
		-Wsuggest-attribute=pure                          \
		-Wsuggest-final-methods                           \
		-Wsuggest-final-types                             \
		-Wsuggest-override                                \
		-Wswitch                                          \
		-Wswitch-bool                                     \
		-Wswitch-default                                  \
		-Wno-switch-enum                                     \
		-Wswitch-outside-range                            \
		-Wswitch-unreachable                              \
		-Wsync-nand                                       \
		-Wsynth                                           \
		-Wno-system-headers                                  \
		-Wtautological-compare                            \
		-Wno-templates                                       \
		-Wterminate                                       \
		-Wtrampolines                                     \
		-Wtrigraphs                                       \
		-Wtype-limits                                     \
		-Wundef                                           \
		-Wuninitialized                                   \
		-Wunknown-pragmas                                 \
		-Wunreachable-code                                \
		-Wunsafe-loop-optimizations                       \
		-Wunused                                          \
		-Wunused-but-set-parameter                        \
		-Wunused-but-set-variable                         \
		-Wunused-const-variable=2                         \
		-Wunused-function                                 \
		-Wunused-label                                    \
		-Wno-unused-local-typedefs                           \
		-Wunused-macros                                   \
		-Wunused-parameter                                \
		-Wunused-result                                   \
		-Wunused-value                                    \
		-Wunused-variable                                 \
		-Wuseless-cast                                    \
		-Wvarargs                                         \
		-Wvariadic-macros                                 \
		-Wvector-operation-performance                    \
		-Wvirtual-inheritance                             \
		-Wvirtual-move-assign                             \
		-Wvla                                             \
		-Wvolatile                                        \
		-Wvolatile-register-var                           \
		-Wwrite-strings                                   \
		-Wzero-as-null-pointer-constant                   \
		-Wzero-length-bounds                              \
		" cmake -S . -B cmake-build-pedantic -GNinja -DCMAKE_BUILD_TYPE=Debug -DJSON_MultipleHeaders=ON -DJSON_BuildTests=On
	cmake --build cmake-build-pedantic

##########################################################################
# benchmarks
##########################################################################

run_benchmarks:
	rm -fr cmake-build-benchmarks
	mkdir cmake-build-benchmarks
	cd cmake-build-benchmarks ; cmake ../benchmarks -GNinja -DCMAKE_BUILD_TYPE=Release -DJSON_BuildTests=On
	cd cmake-build-benchmarks ; ninja
	cd cmake-build-benchmarks ; ./json_benchmarks

##########################################################################
# fuzzing
##########################################################################

# the overall fuzz testing target
fuzz_testing:
	rm -fr fuzz-testing
	mkdir -p fuzz-testing fuzz-testing/testcases fuzz-testing/out
	$(MAKE) parse_afl_fuzzer -C test CXX=afl-clang++
	mv test/parse_afl_fuzzer fuzz-testing/fuzzer
	find test/data/json_tests -size -5k -name *json | xargs -I{} cp "{}" fuzz-testing/testcases
	@echo "Execute: afl-fuzz -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer"

fuzz_testing_bson:
	rm -fr fuzz-testing
	mkdir -p fuzz-testing fuzz-testing/testcases fuzz-testing/out
	$(MAKE) parse_bson_fuzzer -C test CXX=afl-clang++
	mv test/parse_bson_fuzzer fuzz-testing/fuzzer
	find test/data -size -5k -name *.bson | xargs -I{} cp "{}" fuzz-testing/testcases
	@echo "Execute: afl-fuzz -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer"

fuzz_testing_cbor:
	rm -fr fuzz-testing
	mkdir -p fuzz-testing fuzz-testing/testcases fuzz-testing/out
	$(MAKE) parse_cbor_fuzzer -C test CXX=afl-clang++
	mv test/parse_cbor_fuzzer fuzz-testing/fuzzer
	find test/data -size -5k -name *.cbor | xargs -I{} cp "{}" fuzz-testing/testcases
	@echo "Execute: afl-fuzz -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer"

fuzz_testing_msgpack:
	rm -fr fuzz-testing
	mkdir -p fuzz-testing fuzz-testing/testcases fuzz-testing/out
	$(MAKE) parse_msgpack_fuzzer -C test CXX=afl-clang++
	mv test/parse_msgpack_fuzzer fuzz-testing/fuzzer
	find test/data -size -5k -name *.msgpack | xargs -I{} cp "{}" fuzz-testing/testcases
	@echo "Execute: afl-fuzz -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer"

fuzz_testing_ubjson:
	rm -fr fuzz-testing
	mkdir -p fuzz-testing fuzz-testing/testcases fuzz-testing/out
	$(MAKE) parse_ubjson_fuzzer -C test CXX=afl-clang++
	mv test/parse_ubjson_fuzzer fuzz-testing/fuzzer
	find test/data -size -5k -name *.ubjson | xargs -I{} cp "{}" fuzz-testing/testcases
	@echo "Execute: afl-fuzz -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer"

fuzzing-start:
	afl-fuzz -S fuzzer1 -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer > /dev/null &
	afl-fuzz -S fuzzer2 -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer > /dev/null &
	afl-fuzz -S fuzzer3 -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer > /dev/null &
	afl-fuzz -S fuzzer4 -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer > /dev/null &
	afl-fuzz -S fuzzer5 -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer > /dev/null &
	afl-fuzz -S fuzzer6 -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer > /dev/null &
	afl-fuzz -S fuzzer7 -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer > /dev/null &
	afl-fuzz -M fuzzer0 -i fuzz-testing/testcases -o fuzz-testing/out fuzz-testing/fuzzer

fuzzing-stop:
	-killall fuzzer
	-killall afl-fuzz


##########################################################################
# Static analysis
##########################################################################

# call cppcheck <http://cppcheck.sourceforge.net>
# Note: this target is called by Travis
cppcheck:
	cppcheck --enable=warning --inline-suppr --inconclusive --force --std=c++11 $(AMALGAMATED_FILE) --error-exitcode=1

# call Clang Static Analyzer <https://clang-analyzer.llvm.org>
clang_analyze:
	rm -fr cmake-build-clang-analyze
	mkdir cmake-build-clang-analyze
	cd cmake-build-clang-analyze ; CCC_CXX=$(COMPILER_DIR)/clang++ CXX=$(COMPILER_DIR)/clang++ $(COMPILER_DIR)/scan-build cmake .. -GNinja -DJSON_BuildTests=On
	cd cmake-build-clang-analyze ; \
		$(COMPILER_DIR)/scan-build \
			-enable-checker alpha.core.BoolAssignment,alpha.core.CallAndMessageUnInitRefArg,alpha.core.CastSize,alpha.core.CastToStruct,alpha.core.Conversion,alpha.core.DynamicTypeChecker,alpha.core.FixedAddr,alpha.core.PointerArithm,alpha.core.PointerSub,alpha.core.SizeofPtr,alpha.core.StackAddressAsyncEscape,alpha.core.TestAfterDivZero,alpha.deadcode.UnreachableCode,core.builtin.BuiltinFunctions,core.builtin.NoReturnFunctions,core.CallAndMessage,core.DivideZero,core.DynamicTypePropagation,core.NonnilStringConstants,core.NonNullParamChecker,core.NullDereference,core.StackAddressEscape,core.UndefinedBinaryOperatorResult,core.uninitialized.ArraySubscript,core.uninitialized.Assign,core.uninitialized.Branch,core.uninitialized.CapturedBlockVariable,core.uninitialized.UndefReturn,core.VLASize,cplusplus.InnerPointer,cplusplus.Move,cplusplus.NewDelete,cplusplus.NewDeleteLeaks,cplusplus.SelfAssignment,deadcode.DeadStores,nullability.NullableDereferenced,nullability.NullablePassedToNonnull,nullability.NullableReturnedFromNonnull,nullability.NullPassedToNonnull,nullability.NullReturnedFromNonnull \
			--use-c++=$(COMPILER_DIR)/clang++ -analyze-headers -o report ninja
	open cmake-build-clang-analyze/report/*/index.html

# call cpplint <https://github.com/cpplint/cpplint>
# Note: some errors expected due to false positives
cpplint:
	third_party/cpplint/cpplint.py \
		--filter=-whitespace,-legal,-readability/alt_tokens,-runtime/references,-runtime/explicit \
		--quiet --recursive $(SRCS)

# call Clang-Tidy <https://clang.llvm.org/extra/clang-tidy/>
clang_tidy:
	$(COMPILER_DIR)/clang-tidy $(SRCS) -- -Iinclude -std=c++11

# call PVS-Studio Analyzer <https://www.viva64.com/en/pvs-studio/>
pvs_studio:
	rm -fr cmake-build-pvs-studio
	mkdir cmake-build-pvs-studio
	cd cmake-build-pvs-studio ; cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=On -DJSON_MultipleHeaders=ON
	cd cmake-build-pvs-studio ; pvs-studio-analyzer analyze -j 10
	cd cmake-build-pvs-studio ; plog-converter -a'GA:1,2;64:1;CS' -t fullhtml PVS-Studio.log -o pvs
	open cmake-build-pvs-studio/pvs/index.html

# call Infer <https://fbinfer.com> static analyzer
infer:
	rm -fr cmake-build-infer
	mkdir cmake-build-infer
	cd cmake-build-infer ; infer compile -- cmake .. -DJSON_MultipleHeaders=ON ; infer run -- make -j 4

# call OCLint <http://oclint.org> static analyzer
oclint:
	oclint $(SRCS) -report-type html -enable-global-analysis -o oclint_report.html -max-priority-1=10000 -max-priority-2=10000 -max-priority-3=10000 -- -std=c++11 -Iinclude
	open oclint_report.html

# execute the test suite with Clang sanitizers (address and undefined behavior)
clang_sanitize:
	rm -fr cmake-build-clang-sanitize
	mkdir cmake-build-clang-sanitize
	cd cmake-build-clang-sanitize ; CXX=$(COMPILER_DIR)/clang++ cmake .. -DJSON_Sanitizer=On -DJSON_MultipleHeaders=ON -DJSON_BuildTests=On -GNinja
	cd cmake-build-clang-sanitize ; ninja
	cd cmake-build-clang-sanitize ; ctest -j10


##########################################################################
# Code format and source amalgamation
##########################################################################

# call the Artistic Style pretty printer on all source files
pretty:
	astyle \
		--style=allman \
		--indent=spaces=4 \
		--indent-modifiers \
	    --indent-switches \
	    --indent-preproc-block \
	    --indent-preproc-define \
	    --indent-col1-comments \
	    --pad-oper \
	    --pad-header \
	    --align-pointer=type \
	    --align-reference=type \
	    --add-brackets \
	    --convert-tabs \
	    --close-templates \
	    --lineend=linux \
	    --preserve-date \
	    --suffix=none \
	    --formatted \
	   $(SRCS) $(AMALGAMATED_FILE) test/src/*.cpp test/src/*.hpp benchmarks/src/benchmarks.cpp doc/examples/*.cpp

# create single header file
amalgamate: $(AMALGAMATED_FILE)

# call the amalgamation tool and pretty print
$(AMALGAMATED_FILE): $(SRCS)
	third_party/amalgamate/amalgamate.py -c third_party/amalgamate/config.json -s . --verbose=yes
	$(MAKE) pretty

# check if file single_include/nlohmann/json.hpp has been amalgamated from the nlohmann sources
# Note: this target is called by Travis
check-amalgamation:
	@mv $(AMALGAMATED_FILE) $(AMALGAMATED_FILE)~
	@$(MAKE) amalgamate
	@diff $(AMALGAMATED_FILE) $(AMALGAMATED_FILE)~ || (echo "===================================================================\n  Amalgamation required! Please read the contribution guidelines\n  in file .github/CONTRIBUTING.md.\n===================================================================" ; mv $(AMALGAMATED_FILE)~ $(AMALGAMATED_FILE) ; false)
	@mv $(AMALGAMATED_FILE)~ $(AMALGAMATED_FILE)

# check if every header in nlohmann includes sufficient headers to be compiled individually
check-single-includes:
	@for x in $(SRCS); do \
	  echo "Checking self-sufficiency of $$x..." ; \
	  echo "#include <$$x>\nint main() {}\n" | $(SED) 's|include/||' > single_include_test.cpp; \
	  $(CXX) $(CXXFLAGS) -Iinclude -std=c++11 single_include_test.cpp -o single_include_test; \
	  rm -f single_include_test.cpp single_include_test; \
	done


##########################################################################
# CMake
##########################################################################

# grep "^option" CMakeLists.txt test/CMakeLists.txt | $(SED) 's/(/ /' | awk '{print $2}' | xargs

# check if all flags of our CMake files work
check_cmake_flags_do:
	$(CMAKE_BINARY) --version
	for flag in JSON_BuildTests JSON_Install JSON_MultipleHeaders JSON_Sanitizer JSON_Valgrind JSON_NoExceptions JSON_Coverage; do \
		rm -fr cmake_build; \
		mkdir cmake_build; \
		echo "\n\n$(CMAKE_BINARY) .. -D$$flag=On\n" ; \
		cd cmake_build ; \
		$(CMAKE_BINARY) -Werror=dev .. -D$$flag=On -DCMAKE_CXX_COMPILE_FEATURES="cxx_std_11;cxx_range_for" -DCMAKE_CXX_FLAGS="-std=gnu++11" ; \
		test -f Makefile || exit 1 ; \
		cd .. ; \
	done;

# call target `check_cmake_flags_do` twice: once for minimal required CMake version 3.1.0 and once for the installed version
check_cmake_flags:
	wget https://github.com/Kitware/CMake/releases/download/v3.1.0/cmake-3.1.0-Darwin64.tar.gz
	tar xfz cmake-3.1.0-Darwin64.tar.gz
	CMAKE_BINARY=$(abspath cmake-3.1.0-Darwin64/CMake.app/Contents/bin/cmake) $(MAKE) check_cmake_flags_do
	CMAKE_BINARY=$(shell which cmake) $(MAKE) check_cmake_flags_do


##########################################################################
# ChangeLog
##########################################################################

# Create a ChangeLog based on the git log using the GitHub Changelog Generator
# (<https://github.com/github-changelog-generator/github-changelog-generator>).

# variable to control the diffs between the last released version and the current repository state
NEXT_VERSION ?= "unreleased"

ChangeLog.md:
	github_changelog_generator -o ChangeLog.md --user nlohmann --project json --simple-list --release-url https://github.com/nlohmann/json/releases/tag/%s --future-release $(NEXT_VERSION)
	$(SED) -i 's|https://github.com/nlohmann/json/releases/tag/HEAD|https://github.com/nlohmann/json/tree/HEAD|' ChangeLog.md
	$(SED) -i '2i All notable changes to this project will be documented in this file. This project adheres to [Semantic Versioning](http://semver.org/).' ChangeLog.md


##########################################################################
# Release files
##########################################################################

# Create the files for a release and add signatures and hashes. We use `-X` to make the resulting ZIP file
# reproducible, see <https://content.pivotal.io/blog/barriers-to-deterministic-reproducible-zip-files>.

release:
	rm -fr release_files
	mkdir release_files
	zip -9 --recurse-paths -X include.zip $(SRCS) $(AMALGAMATED_FILE) meson.build
	gpg --armor --detach-sig include.zip
	mv include.zip include.zip.asc release_files
	gpg --armor --detach-sig $(AMALGAMATED_FILE)
	cp $(AMALGAMATED_FILE) release_files
	mv $(AMALGAMATED_FILE).asc release_files
	cd release_files ; shasum -a 256 json.hpp > hashes.txt
	cd release_files ; shasum -a 256 include.zip >> hashes.txt


##########################################################################
# Maintenance
##########################################################################

# clean up
clean_back:
	rm -fr json_unit json_benchmarks fuzz fuzz-testing *.dSYM test/*.dSYM oclint_report.html
	rm -fr benchmarks/files/numbers/*.json
	rm -fr cmake-3.1.0-Darwin64.tar.gz cmake-3.1.0-Darwin64
	rm -fr cmake-build-coverage cmake-build-benchmarks cmake-build-pedantic fuzz-testing cmake-build-clang-analyze cmake-build-pvs-studio cmake-build-infer cmake-build-clang-sanitize cmake_build
	$(MAKE) clean -Cdoc

##########################################################################
# Thirdparty code
##########################################################################

update_hedley:
	rm -f include/nlohmann/thirdparty/hedley/hedley.hpp include/nlohmann/thirdparty/hedley/hedley_undef.hpp
	curl https://raw.githubusercontent.com/nemequ/hedley/master/hedley.h -o include/nlohmann/thirdparty/hedley/hedley.hpp
	$(SED) -i 's/HEDLEY_/JSON_HEDLEY_/g' include/nlohmann/thirdparty/hedley/hedley.hpp
	grep "[[:blank:]]*#[[:blank:]]*undef" include/nlohmann/thirdparty/hedley/hedley.hpp | grep -v "__" | sort | uniq | $(SED) 's/ //g' | $(SED) 's/undef/undef /g' > include/nlohmann/thirdparty/hedley/hedley_undef.hpp
	$(MAKE) amalgamate

















































##############################################

rebuild-ios:
	make clean && mkdir build && cd build
	# cmake .. -DCMAKE_TOOLCHAIN_FILE=~/.cmake_modules/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build .
	cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../../cmake/ios.toolchain.cmake -DPLATFORM=SIMULATOR64
	cmake --build . --config Debug
	cmake --build . --config Release

rebuild-android:
	rm -rf build && mkdir build && cd build && cmake .. -DMT_TARGET_PLATFORM=android -DCMAKE_TOOLCHAIN_FILE=~/.cmake_modules/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build .

ctest:
	cd build && ctest

reset:
	git clean -d -f -x

gen-macosx:
	# 生成xcode 报错：No CMAKE_C_COMPILER could be found. No CMAKE_CXX_COMPILER could be found.
	# 参考：https://stackoverflow.com/questions/41380900/cmake-error-no-cmake-c-compiler-could-be-found-using-xcode-and-glfw
	# xcrun -find c++
	# xcrun -find cc
	rm -rf _exports && mkdir _exports && cd _exports && cmake -G Xcode -H. -B_build ..

	# https://polly.readthedocs.io/en/latest/toolchains/ios.html
	# ./polly/bin/build.py --ios-multiarch

gen-xcode2:
	# rm -rf _exports && mkdir _exports && cd _exports && cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../cmake/ios.toolchain.cmake -DPLATFORM=OS64COMBINED
	rm -rf _exports && mkdir _exports && cd _exports && cmake .. -DCMAKE_TOOLCHAIN_FILE=~/.cmake_modules/vcpkg/scripts/buildsystems/vcpkg.cmake -G Xcode -DCMAKE_SYSTEM_NAME=iOS

gen-test:
	cmake -S. -B_builds -GXcode \
    -DCMAKE_SYSTEM_NAME=iOS \
    "-DCMAKE_OSX_ARCHITECTURES=armv7;armv7s;arm64;i386;x86_64" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=9.3 \
    -DCMAKE_INSTALL_PREFIX=`pwd`/_install \
    -DCMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH=NO \
    -DCMAKE_IOS_INSTALL_COMBINED=YES

gen-vs:
	mkdir build-vs2019

gen-pod:
	mkdir build-xcode

gen-gradle:
	mkdir build-gradle

# TODO: 
# 1. 生成 gradle 可以直接集成的库
# 2. 生成 cocoapod 可以直接集成的库
# 3. 生成 vs 可以直接集成的库

######################################################################
# xmake
######################################################################

xmake:
	xmake

xmingw: # mingw
	xmake f -p mingw --sdk=/home/mingwsdk
	xmake

# 配置签名
# https://xmake.io/#/zh-cn/guide/project_examples?id=%e9%85%8d%e7%bd%ae%e7%ad%be%e5%90%8d
# xmake m package -f iphoneos 可以一次性打所有 arch ，见 https://xmake.io/#/zh-cn/plugin/builtin_plugins?id=%e5%86%85%e7%bd%ae%e7%9a%84%e5%ae%8f%e8%84%9a%e6%9c%ac
xios:
	xmake f -p iphoneos -a armv7 -o _xbuilds --vcpkg=~/.cmake_modules/vcpkg/ -y
	xmake
	xmake f -p iphoneos -a armv7s -o _xbuilds --vcpkg=~/.cmake_modules/vcpkg/ -y
	xmake
	xmake f -p iphoneos -a arm64 -o _xbuilds --vcpkg=~/.cmake_modules/vcpkg/ -y
	xmake
	xmake f -p iphoneos -a x86_64 -o _xbuilds --vcpkg=~/.cmake_modules/vcpkg/ -y
	xmake
	rm -rf build/iphoneos/release
	mkdir build/iphoneos/release
	lipo -create build/iphoneos/armv7/release/libhttp.a build/iphoneos/arm64/release/libhttp.a build/iphoneos/armv7s/release/libhttp.a build/iphoneos/x86_64/release/libhttp.a -output build/iphoneos/release/libhttp.a

xandroid:
	xmake f -p android --ndk=~/Library/Android/sdk/ndk/21.1.6352462
	xmake

xlinux:
	xmake f -p linux --sdk=/home/sdk
	xmake

xwindows:
	xmake f -p windows
	xmake

xvs: # export vs project
	xmake project -k vsxmake2019 -m "debug;release"

xxcode: # export xcode project
	xmake project -k xcode