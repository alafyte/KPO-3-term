#include "stdafx.h"

namespace FST
{
	RELATION::RELATION(char c, short ns)
	{
		this->symbol = c;
		this->nnode = ns;
	}

	NODE::NODE()
	{
		this->n_relation = NULL;
		this->relations = NULL;
	};
	NODE::NODE(short n, RELATION rel, ...)
	{
		this->n_relation = n;
		this->relations = new RELATION[n_relation];
		RELATION* wptr = &rel;
		for (int i = 0; i < n; i++)
		{
			relations[i] = wptr[i];
		};
	};

	FST::FST(const char* s, short ns, NODE n, ...)
	{
		this->position = -1;
		this->string = s;
		this->nstates = ns;
		this->rstates = new short[nstates];
		this->nodes = new NODE[nstates];

		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;

		NODE* wptr = &n;
		for (int i = 0; i < ns; i++)
			nodes[i] = wptr[i];
	}

	bool step(FST& fst, short*& rstates) {
		bool rc = false;
		std::swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) {
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					};
		};
		return rc;
	};
	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);
		};
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	};
}