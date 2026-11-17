#pragma once

#include <common/standard.h>
#include <common/net.h>

#include <parse_choy/expression.h>
#include <parse_choy/modfile.h>
#include <parse_choy/type_name.h>
#include <parse_choy/function_decl.h>
#include <parse_choy/function.h>

#include <choy/project.h>
#include <choy/program.h>

#include <arithmetic/expression.h>
#include <arithmetic/state.h>
#include <arithmetic/action.h>

#include <interpret_arithmetic/export.h>

namespace parse_choy {

string export_value(const arithmetic::Value &v);

struct ExpressionExporter : arithmetic::ExpressionExporter {
	ucs::ConstNetlist nets;

	ExpressionExporter(ucs::ConstNetlist nets);
	~ExpressionExporter();

	parse_expression::operation export_operator(int func) const override;
	const parse_expression::precedence_set &precedence() const override;
	parse_expression::expression::argument export_constant(arithmetic::Value value) const override;
	parse_expression::expression::argument export_literal(size_t index) const override;
};

parse_expression::expression export_expression(const arithmetic::Expression &expr, ucs::ConstNetlist nets);
parse_expression::assignment export_assignment(const arithmetic::Action &expr, ucs::ConstNetlist nets);

struct CompositionExporter : arithmetic::CompositionExporter {
	ucs::ConstNetlist nets;

	CompositionExporter(ucs::ConstNetlist nets);
	~CompositionExporter();

	parse_expression::operation export_operator(int func) const override;
	const parse_expression::precedence_set &precedence() const override;
	parse_expression::expression::argument export_action(const arithmetic::Action &expr) const override;
};

parse_expression::expression export_composition(const arithmetic::Parallel &expr, ucs::ConstNetlist nets);
parse_expression::expression export_composition(const arithmetic::Choice &expr, ucs::ConstNetlist nets);



parse_choy::function::declaration export_declaration(const choy::Program &prgm, const choy::Instance &inst);
parse_choy::type_name export_type_name(const choy::Program &prgm, choy::TypeId id);
parse_choy::function_decl export_decl(const choy::Program &prgm, const choy::Decl &decl);

parse_choy::modfile export_modfile(const choy::Project &proj);

}
