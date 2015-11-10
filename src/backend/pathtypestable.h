#ifndef PATHTYPESTABLE_H
#define PATHTYPESTABLE_H

#include "Node.h"
#include "pathtype.h"
#include <utility>

class PathTypesTable {

public:
	PathTypesTable(unsigned nodeCount) :
		data(nodeCount, std::make_pair(0, PathType::None)) {}

	inline void set(Node::ID nodeNetId, Node::ID nodeId, PathType pathType) {
		data[nodeNetId] = std::make_pair(nodeId, pathType);
	}

	inline void reset() {
		std::fill(data.begin(), data.end(), std::make_pair(0, PathType::None));
	}

	typedef std::vector<std::pair<Node::ID, PathType>> Table;
	typedef Table::const_iterator const_iterator;
	typedef Table::iterator iterator;
	typedef const PathType& const_reference;
	typedef PathType& reference;

	reference operator[] (Node::ID nodeNetID) { return data[nodeNetID].second; }
	const_reference operator[] (Node::ID nodeNetID) const { return data[nodeNetID].second; }

	inline iterator begin() { return data.begin(); }
	inline const_iterator begin() const { return data.begin(); }
	inline iterator end() { return data.end(); }
	inline const_iterator end() const { return data.end(); }

private:

	Table data;

};

#endif // PATHTYPESTABLE_H
