#pragma once

#include <vector>

class graph {
	virtual ~graph() {};
	virtual void add_edge(size_t from, size_t to) = 0; // Добавление ребра от from к to
	virtual int vertices_count() const = 0;
	virtual std::vector<size_t> get_next_vertices(size_t vertex) const = 0;
	virtual std::vector<size_t> get_prev_vertices(size_t vertex) const = 0;
};
