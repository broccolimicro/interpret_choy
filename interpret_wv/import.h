#pragma once

#include <parse/tokenizer.h>
#include <parse_choy/source.h>
#include <parse_choy/expression.h>
#include <parse_choy/prototype.h>
#include <parse_choy/modfile.h>

#include <parse_expression/expression.h>
#include <parse_expression/assignment.h>
#include <parse_expression/import.h>

#include <vector>
#include <string>

#include <arithmetic/expression.h>
#include <arithmetic/action.h>
#include <arithmetic/state.h>
#include <choy/program.h>
#include <choy/project.h>

using std::vector;
using std::string;

namespace parse_choy {

struct ExpressionImporter : parse_expression::Importer<arithmetic::Expression> {
	ucs::Netlist symbols;
	vector<int> region;
	bool autoDefine;

	ExpressionImporter(ucs::Netlist symbols, int region = 0, bool autoDefine = false);
	~ExpressionImporter();

	arithmetic::Expression import_term(const parse_expression::expression::argument &syntax, tokenizer *tokens, int arg) const override;
	void push_properties(parse_expression::operation op, const vector<parse_expression::expression::argument> &args, tokenizer *tokens) override;
	void pop_properties(parse_expression::operation op) override;
	arithmetic::Expression import_unary(parse_expression::operation op, arithmetic::Expression expr, tokenizer *tokens) const override;
	arithmetic::Expression import_binary(parse_expression::operation op, arithmetic::Expression left, arithmetic::Expression right, tokenizer *tokens) const override;
	arithmetic::Expression import_group(parse_expression::operation op, vector<arithmetic::Expression> args, tokenizer *tokens) const override;
	arithmetic::Expression import_modifier(parse_expression::operation op, vector<arithmetic::Expression> args, tokenizer *tokens) const override;
};

arithmetic::Expression import_expression(const parse_expression::expression &syntax, ucs::Netlist nets, tokenizer *tokens, int region = 0, bool auto_define = false);

struct CompositionImporter : parse_expression::Importer<arithmetic::Choice> {
	ucs::Netlist symbols;
	vector<int> region;
	bool autoDefine;

	CompositionImporter(ucs::Netlist symbols, int region = 0, bool autoDefine = false);
	~CompositionImporter();

	arithmetic::Action import_assignment(const assignment &syntax, tokenizer *tokens) const;
	arithmetic::Choice import_term(const parse_expression::expression::argument &syntax, tokenizer *tokens, int arg) const override;
	void push_properties(parse_expression::operation op, const vector<parse_expression::expression::argument> &args, tokenizer *tokens) override;
	void pop_properties(parse_expression::operation op) override;
	arithmetic::Choice import_binary(parse_expression::operation op, arithmetic::Choice left, arithmetic::Choice right, tokenizer *tokens) const override;
	arithmetic::Choice import_modifier(parse_expression::operation op, vector<arithmetic::Choice> args, tokenizer *tokens) const override;
};

arithmetic::Action import_assignment(const assignment &syntax, ucs::Netlist nets, tokenizer *tokens, int region = 0, bool auto_define = false);
arithmetic::Choice import_composition(const parse_expression::expression &syntax, ucs::Netlist nets, tokenizer *tokens, int region = 0, bool auto_define = false);


// Managing scope
/*bool define(vector<string> typeName, string name, vector<int> size, ucs::Netlist nets);
void pushScope();
void popScope();*/

// Loading the program
bool import_declaration(vector<choy::Instance> &result, const choy::Program &prgm, int modIdx, const parse_choy::function::declaration &syntax, tokenizer *tokens);
void import_type_signature(vector<choy::Typename> &result, const parse_choy::function::declaration &syntax, tokenizer *tokens);
choy::Decl import_prototype(const choy::Program &prgm, int modIdx, const parse_choy::prototype &syntax, choy::TypeId recvType, tokenizer *tokens);
void import_symbols(choy::Program &prgm, int modIdx, const parse_choy::source &syntax, tokenizer *tokens);
choy::Typename import_type_signature(const parse_choy::type_signature &syntax, tokenizer *tokens);
choy::Prototype import_signature(const parse_choy::signature &syntax, tokenizer *tokens);
choy::Decl import_decl(const choy::Program &prgm, int modIdx, const parse_choy::function_decl &syntax, tokenizer *tokens);
choy::TermId import_term(const choy::Project &proj, choy::Program &prgm, choy::Module &mod, int modIdx, const parse_choy::function &syntax, tokenizer *tokens);
std::vector<choy::TermId> import_module(const choy::Project &proj, choy::Program &prgm, int modIdx, const parse_choy::source &syntax, tokenizer *tokens);
void import_modfile(choy::Project &proj, const parse_choy::modfile &syntax, tokenizer *tokens);

}
