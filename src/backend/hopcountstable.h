#ifndef HOPCOUNTSTABLE_H
#define HOPCOUNTSTABLE_H

#include "pathtype.h"
#include "Node.h"
#include "pathtypestable.h"
#include <climits>

class HopCountsTable {

public:

	struct Entry {
		Entry(Node::ID nodeId, PathType pathType, unsigned hopCount = UINT_MAX) :
			nodeId(nodeId), pathType(pathType), hopCount(hopCount) {}

		Node::ID nodeId;
		PathType pathType;
		unsigned hopCount;
	};

	HopCountsTable(const PathTypesTable& pathTypes) {
		data.reserve(pathTypes.size());

		for(auto& pathType : pathTypes) {
			data.push_back(Entry(pathType.first, pathType.second));
		}
	}

	inline void set(Node::ID nodeNetID, unsigned hopCount) {
		data[nodeNetID].hopCount = hopCount;
	}

	inline void reset() {
		for(auto& entry : data) {
			entry.hopCount = UINT_MAX;
		}
	}

	inline size_t size() const { return data.size(); }

	typedef std::vector<Entry> Table;
	typedef Table::const_iterator const_iterator;
	typedef Table::iterator iterator;
	typedef const unsigned& const_reference;
	typedef unsigned& reference;

	reference operator[] (Node::ID nodeNetID) { return data[nodeNetID].hopCount; }
	const_reference operator[] (Node::ID nodeNetID) const { return data[nodeNetID].hopCount; }

	inline iterator begin() { return data.begin(); }
	inline const_iterator begin() const { return data.begin(); }
	inline iterator end() { return data.end(); }
	inline const_iterator end() const { return data.end(); }

private:
	Table data;

};

#endif // HOPCOUNTSTABLE_H
