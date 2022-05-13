
//	CS21004	-- FORMAL LANGUAGE AND AUTOMATA THEORY
//	Nakul Aggarwal	--	19CS10044

//		NOTE FOR THE USER
//	The path of the text document (relative to the current directory) that contains the specifications/
//  description of the finite automata must be passed as a "command line arguement".

//  For Windows10 operating system / g++ (MinGW.org GCC-6.3.0-1) 6.3.0, 
//  the source file can be compiled and executed through the 
//	"Command Prompt" as follows --
//		>	g++ 19CS10044_FLAT_A.cpp -o exec.exe
//		>	exec.exe "nfa_description.txt"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std ;

typedef struct {
	unsigned int n ;
	unsigned int m ;
	unsigned int T[31][20] ;
	unsigned int startStates ;
	unsigned int finalStates ;
} NFA ;

typedef struct {
	int size ;
	unsigned int * A ;
} Set ;

typedef struct {
	unsigned int n ;
	unsigned int m ;
	unsigned int ** T ;
	unsigned int startState ;
	Set finalStates ;
} DFA ;

NFA ReadNFA ( const char * ) ;
void PrintNFA ( const NFA & ) ;
DFA SubsetConstruction ( const NFA & ) ;
void PrintDFA ( const DFA & ) ;
int** FindEquivalent ( const DFA & ) ;
DFA Collapse ( const DFA & , int** ) ;
DFA RemoveUnreachable ( const DFA & , const Set & ) ;
Set FindReachable ( const DFA & ) ;
void SetBit ( unsigned int & , int ) ;
bool IsBitSet ( unsigned int , int ) ;
void DepthFirstAlgo ( const DFA & , unsigned int , bool * ) ;
void CollectEquivStates ( int** , int , int , bool * , int* , int & ) ;

int main ( int argc , char** argv )
{
	NFA nfa = ReadNFA(argv[1]) ;
	cout << endl << endl << endl << "+++ Input NFA" << endl ;
	PrintNFA(nfa) ;
	
	DFA dfa = SubsetConstruction(nfa) ;
	cout << endl << "+++ Converted DFA" << endl ;
	PrintDFA(dfa) ;
	
	Set R = FindReachable(dfa) ;
	cout << "+++ Reachable states" << endl << "    {" ;
	for ( int i=0 ; i<R.size ; i++ )
		for ( int j=31 ; j>=0 ; j-- )
		{
			if ( ! IsBitSet(R.A[i], j) )	continue ;
			cout << i * 32 + 31 -  j << ", " ;
		}
	cout << "\b\b}" << endl << endl ;

	DFA reduced_dfa = RemoveUnreachable(dfa, R) ;
	cout << endl << "+++ Reduced DFA after removing unreachable states" << endl ;
	PrintDFA(reduced_dfa) ;

	DFA minimal_dfa = Collapse(reduced_dfa, FindEquivalent(reduced_dfa)) ;
	cout << "+++ Reduced DFA after collapsing equivalent states" << endl ;
	PrintDFA(minimal_dfa) ;

	cout << endl << endl ;
	return 0 ;
}

DFA Collapse ( const DFA & dfa , int** equiv )
{
	for ( int i=0 ; i<dfa.n ; i++ )
		for ( int j=0 ; j<dfa.n ; j++ )
			equiv[i][j] = 1 - equiv[i][j] ;
	int** groups = ( int** ) calloc (dfa.n, sizeof(int*)) ;
	int totalGroups = 0 ;
	bool* visited = (bool*) calloc (dfa.n, sizeof(bool)) ;
	for ( int i=0 ; i<dfa.n ; i++ )	visited[i] = false ;
	for ( int i=0 ; i<dfa.n ; i++ )
	{
		if ( visited[i] )	continue ;
		groups[totalGroups++] = (int*) calloc (dfa.n+1, sizeof(int)) ;
		int idx = 0 ;
		CollectEquivStates(equiv, dfa.n, i, visited, groups[totalGroups-1], idx) ;
		groups[totalGroups-1][idx] = -1 ;
	}
	
	int* groupIDs = (int*) calloc (dfa.n, sizeof(int)) ;
	cout << endl << "+++ Equivalent states" << endl ;
	for ( int i=0 ; i<totalGroups ; i++ )
	{
		int s = 0 ;
		cout << "    Group " << setw(2) << i << ": {" ;
		while ( groups[i][s+1] != -1 )
		{
			groupIDs[groups[i][s]] = i ;
			cout << groups[i][s++] << ", " ;
		}
		groupIDs[groups[i][s]] = i ;
		cout << groups[i][s] << "}" << endl ;
	}

	cout << endl << endl ;
	DFA mindfa ;
	mindfa.n = totalGroups ;
	mindfa.m = dfa.m ;
	mindfa.startState = groupIDs[dfa.startState] ;
	mindfa.T = (unsigned int**) calloc ( mindfa.n , sizeof(unsigned int*) ) ;
	for ( int i=0 ; i<mindfa.n ; i++ )
		mindfa.T[i] = (unsigned int*) calloc ( mindfa.m , sizeof(unsigned int) ) ;
	for ( int i=0 ; i<mindfa.n ; i++ )
		for ( int j=0 ; j<mindfa.m ; j++ )
		    mindfa.T[i][j] = groupIDs[ dfa.T[groups[i][0]][j] ] ;
	mindfa.finalStates.size = mindfa.n / 32 ;
	if  ( mindfa.n % 32 != 0 )
		mindfa.finalStates.size += 1 ;
	mindfa.finalStates.A = (unsigned int*) calloc ( mindfa.finalStates.size , sizeof(unsigned int) ) ;
	for ( int i=0 ; i<dfa.finalStates.size ; i++ )
		for ( int j=0 ; j<32 ; j++ )
		{
			if ( ! IsBitSet(dfa.finalStates.A[i], j) )	continue ;
			int oldState = 32*i + 31 - j ;
			int newState = groupIDs[oldState] ;
			int idx = newState / 32 ;
			int bit = 31 - newState % 32 ;
			SetBit(mindfa.finalStates.A[idx], bit) ;
		}
	for ( int i=0 ; i<totalGroups ; i++ ) free(groups[i]) ;
	free(groups) ; free(visited) ; free(groupIDs) ;
	return mindfa ;
}

void CollectEquivStates ( int** equiv , int n , int p , bool * visited , int* group , int & idx )
{
	visited[p] = true ;
	group[idx++] = p ;
	for ( int i=0 ; i<n ; i++ )
	{
		if ( equiv[p][i] && ! visited[i] )
			CollectEquivStates (equiv, n, i, visited, group, idx) ;
	}
}

int** FindEquivalent ( const DFA & dfa )
{
	int** equiv = ( int** ) calloc ( dfa.n , sizeof(int*) ) ;
	for ( int i=0 ; i<dfa.n ; i++ )
		equiv[i] = ( int* ) calloc ( dfa.n , sizeof(int) ) ;
	for ( int i=0 ; i<dfa.n ; i++ )
		for ( int j=0 ; j<dfa.n ; j++ )
			equiv[i][j] = 0 ;
	for ( int i=0 ; i<dfa.n ; i++ )
	{
		int idxi = i / 32 ; int ki = 31 - i % 32 ;
		bool isIFinal = IsBitSet(dfa.finalStates.A[idxi], ki) ;
		for ( int j=0 ; j<i ; j++ )
		{
			int idxj = j / 32 ; int kj = 31 - j % 32 ;
			bool isJFinal = IsBitSet(dfa.finalStates.A[idxj], kj) ;
			if ( (isIFinal && ! isJFinal) || (! isIFinal && isJFinal) )
				equiv[i][j] = equiv[j][i] = 1 ;
		}
	}
	bool configChanged = true ;
	while ( configChanged ) {
		configChanged = false ;
		for ( int i=0 ; i<dfa.n ; i++ ) {
			for ( int j=0 ; j<i ; j++ ) {
				if ( equiv[i][j] )	continue ;
				for ( int k=0 ; k<dfa.m ; k++ ) {
					if ( equiv[dfa.T[i][k]][dfa.T[j][k]] )  {
						equiv[i][j] = equiv[j][i] = 1 ;
						configChanged = true ;
						break ;
					}
				}
			}
		}
	}
	return equiv ;
}


DFA RemoveUnreachable ( const DFA & dfa , const Set & R )
{
	int * newidx = ( int* ) calloc ( dfa.n , sizeof(int) ) ;
	int * reachable = ( int* ) calloc ( dfa.n , sizeof(int) ) ;
	int * reachFinals = ( int* ) calloc ( dfa.n , sizeof(int) ) ;
	int counter = 0 ; int statecounter = 0 ; int totalFinals = 0 ;
	for ( int i=0 ; i<dfa.n ; i++ )
	{
		int idx = i / 32 ;
		int j = 31 - i % 32 ;
		if ( IsBitSet(R.A[idx], j) )    {
			newidx[i] = counter++ ;
			reachable[statecounter++] = i ;
			if ( IsBitSet(dfa.finalStates.A[idx], j) )
				reachFinals[totalFinals++] = i ;
		}
		else	newidx[i] = -1 ;
	}
	DFA newdfa ;
	newdfa.n = counter ;
	newdfa.m = dfa.m ;
	newdfa.startState = newidx[dfa.startState] ;
	newdfa.T = ( unsigned int** ) calloc ( newdfa.n , sizeof(unsigned int*) ) ;
	for ( int i=0 ; i<newdfa.n ; i++ )
		newdfa.T[i] = ( unsigned int* ) calloc ( newdfa.m , sizeof(unsigned int) ) ;
	
	for ( int i=0 ; i<newdfa.n ; i++ )
		for ( int j=0 ; j<newdfa.m ; j++ )
		    newdfa.T[i][j] = newidx[ dfa.T[reachable[i]][j] ] ;
	
	newdfa.finalStates.size = newdfa.n / 32 ;
	if ( newdfa.n % 32 != 0 )
		newdfa.finalStates.size += 1 ;
	newdfa.finalStates.A = (unsigned int*) calloc (newdfa.finalStates.size, sizeof(unsigned int)) ;
	for ( int i=0 ; i<newdfa.finalStates.size ; i++ )	newdfa.finalStates.A[i] = 0 ;
	
	for ( int i=0 ; i<totalFinals ; i++ )
	{
		int idxn = newidx[reachFinals[i]] / 32 ;
		int jn = 31 - newidx[reachFinals[i]] % 32 ;
		SetBit(newdfa.finalStates.A[idxn], jn) ;
	}
	free(newidx) ; free(reachable) ; free(reachFinals) ;
	return newdfa ;
} 

Set FindReachable ( const DFA & dfa )
{
	bool * visited = ( bool* ) calloc ( dfa.n , sizeof(bool) ) ;
	for ( int i=0 ; i<dfa.n ; i++ )	visited[i] = false ;
	DepthFirstAlgo(dfa, dfa.startState, visited) ;
	Set reachable ;
	reachable.size = dfa.n / 32 ;
	if ( dfa.n % 32 != 0 )
		reachable.size += 1 ;
	reachable.A = ( unsigned int* ) calloc ( reachable.size , sizeof(unsigned int) ) ;
	for ( int i=0 ; i<reachable.size ; i++ )
		reachable.A[i] = 0 ;
	for ( int i=0 ; i<dfa.n ; i++ )     {
		if ( ! visited[i] )	continue ;
		int idx = i / 32 ;
		int j = 31 - i % 32 ;
		SetBit(reachable.A[idx], j) ;
	}
    free( visited ) ;
	return reachable ;
}

void DepthFirstAlgo ( const DFA & dfa , unsigned int s , bool * visited )
{
	if ( visited[s] )	return ;
	visited[s] = true ;
	for ( int a=0 ; a<dfa.m ; a++ )
		DepthFirstAlgo(dfa, dfa.T[s][a], visited) ;
	return ;
}

DFA SubsetConstruction ( const NFA & nfa )
{
	DFA dfa ;
	dfa.n = pow(2, nfa.n) ;
	dfa.m = nfa.m ;
	dfa.startState = nfa.startStates ;
	dfa.T = ( unsigned int** ) calloc ( dfa.n , sizeof(unsigned int*) ) ;
	
	dfa.finalStates.size = dfa.n / 32 ;
	if ( dfa.n % 32 != 0 )
		dfa.finalStates.size += 1 ;
	dfa.finalStates.A = ( unsigned int * ) calloc ( dfa.finalStates.size , sizeof(unsigned int) ) ;
	for ( int i=0 ; i<dfa.finalStates.size ; i++ )
		dfa.finalStates.A[i] = 0 ;
	
	for ( int i=0 ; i<dfa.n ; i++ )
	{
		int substates[32] ; int t = 0 ;
		for ( int k=0 ; k<32 ; k++ )
			if ( IsBitSet(i, k) )	substates[t++] = k ;
		substates[t] = -1 ;
		dfa.T[i] = (unsigned int*)calloc(dfa.m, sizeof(unsigned int)) ;
		for ( int j=0 ; j<dfa.m ; j++ )     {
			dfa.T[i][j] = 0 ;
			int s = 0 ;
			while ( substates[s] != -1 )
			    dfa.T[i][j] |= nfa.T[substates[s++]][j] ;
		}
		int s = 0 ;
		while ( substates[s] != -1 )    {
			if ( ! IsBitSet(nfa.finalStates, substates[s]) )	{ s++ ; continue ; }
			int idx = i / 32 ;
			int j = 31 - i % 32 ;
			SetBit(dfa.finalStates.A[idx], j) ;
			break ;
		}
	}
	return dfa ;
}

void PrintDFA ( const DFA & dfa )
{
	cout << "    Number of states: " << dfa.n << endl ;
	cout << "    Input Alphabet: {" ;
	for ( int i=0 ; i<dfa.m ; i++ )	cout << i << ", " ;
	cout << "\b\b}" << endl ;
	
	cout << "    Start state: " << dfa.startState << endl ;
	unsigned int * finalstates = (unsigned int*) calloc ( dfa.n , sizeof(unsigned int)) ; 
	int idx = 0 ;
	for ( int i=0 ; i<dfa.finalStates.size ; i++ )
		for ( int j=31 ; j>=0 ; j-- )
		{
			if ( ! IsBitSet(dfa.finalStates.A[i], j) )	continue ;
			finalstates[idx++] = i * 32 + 31 -  j ;
		}
	
	if ( idx >= 70 )
		cout << "    " << idx << " final states" << endl ;
	else
	{
		cout << "    Final states: {" ;
		for ( int i = 0 ; i < idx ; i++ )
			cout << finalstates[i] << ", " ;
		cout << "\b\b}" << endl ;
	}
	free(finalstates) ;

	if ( dfa.n < 65 )
	{
		cout << "    Transition function" << endl ;
		cout << "    a\\p|" ;
		for ( int i=0 ; i<dfa.n ; i++ )	cout << setw(3) << i ;
		cout << endl << "    ---+" ;
		for ( int i=0 ; i<dfa.n ; i++ )	cout << "---" ;
		for ( int a=0 ; a<dfa.m ; a++ )
		{
			cout << endl << "    " ;
			cout << setw(2) << a << " |" ;
			for ( int i=0 ; i<dfa.n ; i++ )
				cout << setw(3) << dfa.T[i][a] ;
		}
	}
	else	cout << "    Transition function: Skipped" << endl ;
	cout << endl << endl ;
}

void SetBit ( unsigned int & x , int j )
{   x |= (1U << j) ;    return ;    }

NFA ReadNFA ( const char * filename )
{
	NFA originalNFA ;
	originalNFA.startStates = 0 ;
	originalNFA.finalStates = 0 ;
	FILE * fptr = fopen(filename, "r") ;
	fscanf ( fptr , "%u" , &(originalNFA.n) ) ;
	fscanf ( fptr , "%u" , &(originalNFA.m) ) ;
	for ( int i=0 ; i<originalNFA.n ; i++ )
		for ( int j=0 ; j<originalNFA.m ; j++ )
			originalNFA.T[i][j] = 0 ;
	int read = 0 ;
	fscanf ( fptr , "%d" , &read ) ;
	while ( read != -1 )    {
		SetBit(originalNFA.startStates, read) ;
		fscanf ( fptr , "%d" , &read ) ;
	}
	fscanf ( fptr , "%d" , &read ) ;
	while ( read != -1 )    {
		SetBit(originalNFA.finalStates, read) ;
		fscanf ( fptr , "%d" , &read ) ;
	}
	while ( true )  {
		int a, b, c ;
		fscanf ( fptr , "%d " , &a ) ;
		if ( a == -1 )	break ;
		fscanf ( fptr , "%d %d" , &b , &c ) ;
		SetBit(originalNFA.T[a][b], c) ;
	}
	fclose(fptr) ;
	return originalNFA ;
}

bool IsBitSet ( unsigned int x , int j )
{	return ((x & (1U << j))) ;	}

void PrintNFA ( const NFA & nfa )
{
	cout << "    Number of states: " << nfa.n << endl ;
	cout << "    Input Alphabet: {" ;
	for ( int i=0 ; i<nfa.m ; i++ )	cout << i << ", " ;
	cout << "\b\b}" << endl ;
	cout << "    Start states: {" ;
	for ( int i = 0 ; i < 32 ; i++ )
		if ( IsBitSet(nfa.startStates, i) )	{ cout << i << ", " ; }
	cout << "\b\b}" << endl ;
	cout << "    Final states: {" ;
	for ( int i = 0 ; i < 32 ; i++ )
		if ( IsBitSet(nfa.finalStates, i) )	{ cout << i << ", " ; }
	cout << "\b\b}" << endl ;
	cout << "    Transition function" ;
	for ( int i=0 ; i<nfa.n ; i++ )
		for ( int j=0 ; j<nfa.m ; j++ )
		{
			cout << endl << "        Delta (" << i << ", " << j << ") = {" ;
			int k = 0 ;
			for ( ; k<32 ; k++ )
				if ( IsBitSet(nfa.T[i][j], k) )	{ cout << k++ ; break ; }
			for ( ; k<32 ; k++ )
				if ( IsBitSet(nfa.T[i][j], k) )	{ cout << ", " << k ; }
			cout << "}" ;
		}
	cout << endl << endl ;
    return ;
}
