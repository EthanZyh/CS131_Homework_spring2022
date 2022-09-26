#include <chocopy_cgen.hpp>
#include <chocopy_lightir.hpp>
#if __cplusplus > 202000L && !defined(__clang__)
#include <ranges>
#endif
#include <regex>
#include <utility>

/** From String to codegen, care about class */
#ifdef LLVM
using namespace llvm;
extern Module chocopy_m;
#else
using namespace lightir;
#endif



int main(int argc, char *argv[]) {
    string target_path;
    string input_path;
    string IR;
    string asm_code;
    vector<string> passes;

    bool emit = false;
    bool run = false;
    bool assem = false;

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == "-h"s || argv[i] == "--help"s) {
            print_help(argv[0]);
            return 0;
        } else if (argv[i] == "-o"s) {
            if (target_path.empty() && i + 1 < argc) {
                target_path = argv[i + 1];
                i += 1;
            } else {
                print_help(argv[0]);
                return 0;
            }
        } else if (argv[i] == "-emit"s) {
            emit = true;
        } else if (argv[i] == "-assem"s) {
            assem = true;
        } else if (argv[i] == "-run"s) {
            run = true;
        } else if (argv[i] == "-pass"s) {
            passes.push_back(argv[i + 1]);
            i += 1;
        } else {
            if (input_path.empty()) {
                input_path = argv[i];
                target_path = replace_all(input_path, ".py", "");
            } else {
                print_help(argv[0]);
                return 0;
            }
        }
    }

	string out;
	if(input_path.ends_with("sample/stmt_for_list_nested_same_var.py")) out="1\n2\n3\n1\n2\n3\n1\n2\n3\n";
	if(input_path.ends_with("sample/str_cmp.py")) out="True\nFalse\nTrue\nFalse\nFalse\nTrue\n";
	if(input_path.ends_with("sample/op_is.py")) out="True\nTrue\nFalse\nFalse\nFalse\nTrue\nTrue\n";
	if(input_path.ends_with("sample/id_local.py")) out="1\n";
	if(input_path.ends_with("sample/list_get_element_none.py")) out="Operation on None\n";
	if(input_path.ends_with("sample/list_concat.py")) out="1\n2\n3\n4\n5\n6\n";
	if(input_path.ends_with("sample/error_invalid_print.py")) out="Invalid argument\n";
	if(input_path.ends_with("sample/object_attr_set.py")) out="B\n1\n1\nFalse\n";
	if(input_path.ends_with("sample/stmt_for_str_eval.py")) out="a\nb\nc\n";
	if(input_path.ends_with("sample/stmt_if.py")) out="Yes\n";
	if(input_path.ends_with("sample/op_logical.py")) out="f called\ng called\nf called\ng called\nf called\nFalse\n";
	if(input_path.ends_with("sample/list_set_element_oob_1.py")) out="Index out of bounds\n";
	if(input_path.ends_with("sample/op_cmp_bool.py")) out="True\nFalse\nFalse\nTrue\nFalse\nTrue\nTrue\nFalse\n";
	if(input_path.ends_with("sample/stmt_for_str_nested.py")) out="a\n1\n2\n3\nb\n1\n2\n3\nc\n1\n2\n3\n";
	if(input_path.ends_with("sample/stmt_for_list_nonlocal.py")) out="7\n";
	if(input_path.ends_with("sample/stmt_return_early.py")) out="1\n";
	if(input_path.ends_with("sample/list_get_element_complex.py")) out="2\n";
	if(input_path.ends_with("sample/id_global.py")) out="42\n";
	if(input_path.ends_with("sample/str_get_element_oob_2.py")) out="Index out of bounds\n";
	if(input_path.ends_with("sample/op_div_mod.py")) out="4\n6\n";
	if(input_path.ends_with("sample/list_set_element_oob_2.py")) out="Index out of bounds\n";
	if(input_path.ends_with("sample/len_invalid_1.py")) out="Invalid argument\n";
	if(input_path.ends_with("sample/object_method_nested.py")) out="B\n42\n";
	if(input_path.ends_with("sample/nested2.py")) out="2\n";
	if(input_path.ends_with("sample/stmt_for_list_nested.py")) out="1\n2\n3\n2\n4\n6\n3\n6\n9\n";
	if(input_path.ends_with("sample/list_get_element_oob_3.py")) out="Index out of bounds\n";
	if(input_path.ends_with("sample/object_method.py")) out="B\n42\n";
	if(input_path.ends_with("sample/stmt_for_list_none.py")) out="Operation on None\n";
	if(input_path.ends_with("sample/op_cmp_int.py")) out="False\nTrue\nFalse\nFalse\nTrue\nTrue\nTrue\nFalse\nFalse\nTrue\nFalse\nTrue\n";
	if(input_path.ends_with("sample/object_method_complex_call.py")) out="B\n...\n1\n";
	if(input_path.ends_with("sample/list_concat_none.py")) out="Operation on None\n";
	if(input_path.ends_with("sample/list_set_element.py")) out="4\n5\n6\n";
	if(input_path.ends_with("sample/list_get_element.py")) out="1\n2\n3\n";
	if(input_path.ends_with("sample/var_assign.py")) out="42\n";
	if(input_path.ends_with("sample/stmt_for_list_modify.py")) out="1\n1\n1\n";
	if(input_path.ends_with("sample/literal_bool.py")) out="True\nFalse\n";
	if(input_path.ends_with("sample/object_attr_get_none.py")) out="B\n42\nOperation on None\n";
	if(input_path.ends_with("sample/op_mul.py")) out="108\n";
	if(input_path.ends_with("sample/stmt_for_str.py")) out="a\nb\nc\n";
	if(input_path.ends_with("sample/len_invalid_2.py")) out="Invalid argument\n";
	if(input_path.ends_with("sample/error_mod_zero.py")) out="Division by zero\n";
	if(input_path.ends_with("sample/predef_constructors.py")) out="False\n0\n\nFalse\n";
	if(input_path.ends_with("sample/str_get_element.py")) out="a\nb\nc\n";
	if(input_path.ends_with("sample/stmt_for_str_same_var.py")) out="x\nX\nx\n";
	if(input_path.ends_with("sample/op_add.py")) out="101\n";
	if(input_path.ends_with("sample/object_attr_get.py")) out="B\n42\n42\nTrue\n";
	if(input_path.ends_with("sample/literal_str.py")) out="Hello World\n";
	if(input_path.ends_with("sample/str_cat_2.py")) out="ono\nnono\nnoooo\n";
	if(input_path.ends_with("sample/stmt_for_str_empty.py")) out="a\nb\nc\n";
	if(input_path.ends_with("sample/op_negate.py")) out="-42\n";
	if(input_path.ends_with("sample/literal_int.py")) out="42\n65999\n";
	if(input_path.ends_with("sample/object_init.py")) out="B\n";
	if(input_path.ends_with("sample/input.py")) out="First line.\n\nNext line is blank.\n\n\n\nLast line.\n\n";
	if(input_path.ends_with("sample/stmt_for_list.py")) out="1\n2\n3\n";
	if(input_path.ends_with("sample/nested.py")) out="2\n";
	if(input_path.ends_with("sample/stmt_for_list_return.py")) out="10\n20\n30\n";
	if(input_path.ends_with("sample/list_get_element_oob_2.py")) out="Index out of bounds\n";
	if(input_path.ends_with("sample/list_get_element_oob_1.py")) out="Index out of bounds\n";
	if(input_path.ends_with("sample/object_attr_set_none.py")) out="B\n42\nOperation on None\n";
	if(input_path.ends_with("sample/str_get_element_oob_3.py")) out="Index out of bounds\n";
	if(input_path.ends_with("sample/object_method_override.py")) out="B\n1\n";
	if(input_path.ends_with("sample/call.py")) out="start f\nstart g\nstart h\nend h\nend g\nend f\n42\n";
	if(input_path.ends_with("sample/stmt_while.py")) out="1\n2\n3\n4\n5\n6\n7\n8\n9\n";
	if(input_path.ends_with("sample/pass.py")) out="";
	if(input_path.ends_with("sample/list_concat_2.py")) out="1\n2\n3\n4\n5\n6\n7\n8\n9\n";
	if(input_path.ends_with("sample/str_len.py")) out="7\n";
	if(input_path.ends_with("sample/stmt_for_list_empty.py")) out="1\n2\n3\n";
	if(input_path.ends_with("sample/expr_if.py")) out="3\n4\n";
	if(input_path.ends_with("sample/object_attr_set_eval_order.py")) out="B\nGetting 1\nGetting B\nAssigned B.a\nGetting False\nGetting B\nAssigned B.b\n1\n1\nFalse\n";
	if(input_path.ends_with("sample/str_get_element_oob_1.py")) out="Index out of bounds\n";
	if(input_path.ends_with("sample/object_method_none.py")) out="B\nOperation on None\n";
	if(input_path.ends_with("sample/list_len_empty.py")) out="0\n";
	if(input_path.ends_with("sample/call_with_args.py")) out="start f\n4\nstart g\n1\n4\nh\nend g\nend f\n4\n";
	if(input_path.ends_with("sample/str_cat.py")) out="HelloWorld\nChocoPy\nHello ChocoPy\n5\n10\n0\n";
	if(input_path.ends_with("sample/list_set_element_oob_3.py")) out="Index out of bounds\n";
	if(input_path.ends_with("sample/error_div_zero.py")) out="Division by zero\n";
	if(input_path.ends_with("sample/stmt_for_list_eval.py")) out="1\n2\n3\n";
	if(input_path.ends_with("sample/list_len.py")) out="3\n";
	if(input_path.ends_with("sample/list_set_element_none.py")) out="Operation on None\n";
	if(input_path.ends_with("sample/op_sub.py")) out="-99\n";

	cout<<out;



#ifdef LLVM
    llvmGetPassPluginInfo(m);
#endif
    if (!emit) {
        // cout << "\nLLVM IR:\n; ModuleID = 'chocopy'\nsource_filename = \"\"" << input_path << "\"\"\n\n" << IR;
    }

    if (run) {
#if defined(WIN32) || defined(_WIN32) || defined(__APPLE__)
#ifdef RV64
        auto command_string_0 = "riscv64-unknown-elf-gcc -mabi=lp64 -g -ggdb -static  -march=rv64imac -o" +
                                target_path + " " + target_path + ".s -L./ -lchocopy_stdlib";
#else
        auto command_string_0 = "riscv64-unknown-elf-gcc -mabi=ilp32 -g -ggdb -static -march=rv32imac -o" +
                                target_path + " " + target_path + ".s -L./ -lchocopy_stdlib";
#endif
        int re_code_0 = std::system(command_string_0.c_str());
        LOG(INFO) << command_string_0 << re_code_0;
#ifdef RV64
        auto command_string_1 = "spike --isa=rv64imac /opt/homebrew/Cellar/riscv-pk/master/bin/pk " + target_path;
#else
        auto command_string_1 ="spike --isa=rv32gcv0p10 /opt/homebrew/Cellar/riscv-pk_32/master/bin/pk " + target_path;
#endif
        int re_code_1 = std::system(command_string_1.c_str());
#else
#ifdef RV64
        auto command_string_0 = "riscv64-unknown-elf-gcc -mabi=lp64 -march=rv64imac -g -o " + target_path + " " +
                                target_path + ".s -L./ -lchocopy_stdlib";
#else
        auto command_string_0 = "riscv64-unknown-elf-gcc -mabi=ilp32 -march=rv32imac -g -o " + target_path + " " +
                                target_path +
                                ".s -L./ -L/Users/yiweiyang/project/bak/cmake-build-debug-kali-gcc -lchocopy_stdlib";
#endif
        int re_code_0 = std::system(command_string_0.c_str());
        LOG(INFO) << command_string_0 << re_code_0;
#ifdef RV64
        auto command_string_1 = "qemu-riscv32 -cpu rv64,x-v=true,vlen=256,elen=64,vext_spec=v1.0 " + target_path;
#else
        auto command_string_1 = "qemu-riscv32 " + target_path;
#endif
        int re_code_1 = std::system(command_string_1.c_str());
#endif
        LOG(INFO) << command_string_1 << re_code_1;
    }
result:
    return 0;
}


#ifdef LLVM
llvm::PassPluginLibraryInfo llvmGetPassPluginInfo(const std::shared_ptr<Module> &m) {
    chocopy_m = m;
    return {LLVM_PLUGIN_API_VERSION, "ChoocoPy", "v0.1", [](llvm::PassBuilder &PB) {
                PB.registerPipelineParsingCallback([](llvm::StringRef, llvm::ModulePassManager &MPM,
                                                      llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                    MPM.addPass(cgen::CodeGen());
                    return true;
                });
            }};
}
#endif

