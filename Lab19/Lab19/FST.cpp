#include "FST.h"

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

	FST::FST(char* s, short ns, NODE n, ...)
	{
		this->position = 0;
		this->string = s;
		this->nstates = ns;
		this->rstates = new short[nstates];
		this->nodes = new NODE[nstates];

		for (int i = 0; i < nstates; i++)
			rstates[i] = 0;

		NODE* wptr = &n;
		for (int i = 0; i < ns; i++)
			nodes[i] = wptr[i];
	}

	bool execute(FST& fst)
	{
		bool result = true;
		short* rstates = new short[fst.nstates];
		for (int i = 0; i < fst.nstates; i++)
			rstates[i] = -1;

		while (fst.position < strlen(fst.string) && result)
		{
			result = false;
			std::swap(rstates, fst.rstates);
			for (int i = 0; i < fst.nstates; i++)
				if (rstates[i] == fst.position)
					for (int j = 0; j < fst.nodes[i].n_relation; j++)
						if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
						{
							fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
							result = true;
						}

			fst.position++;
		}
		delete[] rstates;
		fst.position = 0;
		return (result ? (fst.rstates[fst.nstates - 1] == strlen(fst.string)) : result);
	};
}