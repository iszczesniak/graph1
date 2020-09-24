#include "graph.hpp"

Index<vertex>
index(const vertex &v)
{
  return v.m_index;
}

const std::string &
name(const vertex &v)
{
  return v.m_name;
}

const std::vector<edge> &
edges(const vertex &v)
{
  return v.m_edges;
}

const graph::vertexes_type &
vertexes(const graph &g)
{
  return g.m_vertexes;
}

graph::size_type
num_vertexes(const graph &g)
{
  return std::distance(g.m_vertexes.begin(), g.m_vertexes.end());
}

const vertex &
source(const edge &e)
{
  return e.m_source;
}

const vertex &
target(const edge &e)
{
  return e.m_target;
}

const edge::cost_type &
cost(const edge &e)
{
  return e.m_cost;
}

const edge::units_type &
units(const edge &e)
{
  return e.m_units;
}

const vertex::units_type &
units(const vertex &v)
{
  return v.m_units;
}

vertex &
add_vertex(graph &g, const std::string name,
           vertex::units_type units)
{
  auto i = g.m_vertexes.size();
  g.m_vertexes.push_back(vertex(i, name, units));
  return g.m_vertexes.back();
}

void
add_edge(graph &g, vertex &a, const vertex &b,
         edge::cost_type cost, edge::units_type units)
{
  a.m_edges.push_back(edge(a, b, cost, units));
}

void
add_edge_pair(graph &g, vertex &a, vertex &b,
              edge::cost_type cost, edge::units_type units)
{
  a.m_edges.push_back(edge(a, b, cost, units));
  b.m_edges.push_back(edge(b, a, cost, units));
}
