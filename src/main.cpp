#include <iostream>
#include <vector>

#include <lal/graphs/rooted_tree.hpp>
#include <lal/graphs/output.hpp>

#include <lal/numeric/rational.hpp>
#include <lal/numeric/output.hpp>

#include <lal/properties/C_rla.hpp>
#include <lal/properties/D_rla.hpp>
#include <lal/linarr/D/D.hpp>
#include <lal/linarr/C/C.hpp>

#define ERROR { std::cout << "ERROR! Line " << __LINE__ << '\n'; return 1; }

#define check_and_add(C, u,v)				\
	if (C rt.can_add_edge(u, v)) { ERROR; }	\
	else { rt.add_edge(u,v); }

int main() {
	lal::graphs::rooted_tree rt(10);
	rt.set_root(4);
	
	check_and_add(not, 4, 1);
	check_and_add(not, 1, 0);
	check_and_add(not, 1, 2);
	check_and_add(not, 4, 3);
	
	if (rt.can_add_edge(0, 2)) { ERROR; }
	if (rt.can_add_edge(4, 3)) { ERROR; }
	
	{
	const std::vector<lal::edge> edges{ {4,9}, {9,8}, {8,7}, {8,6}, {8,5} };
	if (not rt.can_add_edges(edges)) {
		ERROR;
	}
	else {
		rt.add_edges(edges);
	}
	}
	
	if (not rt.is_tree()) { ERROR; }
	
	{
	const auto var = lal::properties::var_num_crossings_tree_rational(rt);
	const auto mvar = lal::numeric::rational(193, 15);
	if (var != mvar) { ERROR; }
	}
	
	{
	const auto C = lal::linarr::num_crossings(rt);
	if (C != 0) { ERROR; }
	}
	
	{
	const auto D = lal::linarr::sum_edge_lengths(rt);
	if (D != 18) { ERROR; }
	}
	
	{
	const auto exp = lal::properties::exp_sum_edge_lengths_projective_rational(rt);
	const auto mexp = lal::numeric::rational(133, 6);
	if (exp != mexp) { ERROR; }
	}
	
	return 0;
}
