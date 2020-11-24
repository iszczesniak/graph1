#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <set>
#include <string>
#include <tuple>
#include <vector>

// *******************************************************************
// This file implements a directed graph.
// *******************************************************************

struct edge;

struct vertex
{
  using unit_type = unsigned;
  using units_type = std::set<unit_type>;
  using edges_type = std::vector<edge>;
  using index_type = edges_type::size_type;

  // The index of the vertex.
  index_type m_index;

  // The name of the vertex.
  std::string m_name;

  // The units offered by this vertex.
  units_type m_units;

  vertex(index_type index, std::string name = {},
         units_type units = {}):
    m_index(index), m_name(name), m_units(units)
  {
  }

  bool operator == (const vertex &b) const
  {
    return this == &b;
  }

  // We're using a vector, because we're frequently iterating over the
  // edges of a vertex.  When using a vector, iterators or references
  // to edges can invalidate when we add a new vertex, because the
  // vector can be reallocated.  However, we don't mind that, because
  // we don't store references to edges anywhere.
  edges_type m_edges;
};

struct edge
{
  using cost_type = unsigned;
  using unit_type = unsigned;
  using units_type = std::set<unit_type>;

  // The source node of the edge.
  const vertex &m_source;
  // The target node of the edge.
  const vertex &m_target;

  // The cost of an edge.
  cost_type m_cost;

  // The units required to take the edge.
  units_type m_units;

  edge(const vertex &source, const vertex &target, cost_type cost,
       units_type units = {}):
    m_source(source), m_target(target), m_cost(cost), m_units(units)
  {
  }

  // We need this operator to establish order between edges.  This
  // operator is needed by the < operator for solutions.
  bool operator < (const edge &b) const
  {
    return this < &b;
  }

  bool operator == (const edge &b) const
  {
    return std::tie(m_source, m_target, m_cost, m_units) ==
      std::tie(b.m_source, b.m_target, b.m_cost, b.m_units);
  }
};

// The graph.
struct graph
{
  using size_type = unsigned;
  using vertexes_type = std::list<vertex>;

  graph() = default;

  // Can't copy, because edges have references to vertexes.  I would
  // have to implement this.  For now, I'm disabling copying.
  graph(const graph &) = delete;

  // Can move.
  graph(graph &&) = default;
  
  // We need a container which does not invalidate references (or
  // iterators) to its elements when new elements are added (something
  // a vector would do).  We have to make sure that references are not
  // invalidated, because they are stored in edges.  Perhaps we could
  // use std::forward_list instead of std::list, but we would have a
  // problem with calculating the index for an node being added.
  vertexes_type m_vertexes;
};

// *******************************************************************
// The vertex traits

template<typename>
struct vertex_traits;

template<>
struct vertex_traits<graph>
{
  using type = vertex;
};

template<>
struct vertex_traits<edge>
{
  using type = vertex;
};

template <typename T>
using Vertex = typename vertex_traits<T>::type;

// *******************************************************************
// The edge traits

template<typename>
struct edge_traits;

template<>
struct edge_traits<graph>
{
  using type = edge;
};

template <typename G>
using Edge = typename edge_traits<G>::type;

// *******************************************************************
// The cost traits

template <typename>
struct cost_traits;

template <>
struct cost_traits<edge>
{
  using type = edge::cost_type;
};

template <typename T>
using Cost = typename cost_traits<T>::type;

// *******************************************************************
// The index traits

template <typename>
struct index_traits;

template <>
struct index_traits<vertex>
{
  using type = vertex::index_type;
};

template <typename T>
using Index = typename index_traits<T>::type;

// *******************************************************************
// The units traits

template <typename>
struct units_traits;

template <>
struct units_traits<edge>
{
  using type = edge::units_type;
};

template <typename T>
using Units = typename units_traits<T>::type;

// *******************************************************************
// The functions.

Index<vertex>
get_index(const vertex &);

const std::string &
get_name(const vertex &);

const std::vector<edge> &
get_edges(const vertex &);

const graph::vertexes_type &
get_vertexes(const graph &);

graph::size_type
num_vertexes(const graph &);

const vertex &
get_source(const edge &);

const vertex &
get_target(const edge &);

const edge::cost_type &
get_cost(const edge &);

const edge::units_type &
get_units(const edge &);

const vertex::units_type &
get_units(const vertex &);

vertex &
add_vertex(graph &g, const std::string name,
           vertex::units_type units = {});

void
add_edge(graph &g, vertex &, const vertex &, edge::cost_type,
         edge::units_type = {});

void
add_edge_pair(graph &g, vertex &, vertex &,
              edge::cost_type, edge::units_type = {});

#endif // GRAPH_HPP
