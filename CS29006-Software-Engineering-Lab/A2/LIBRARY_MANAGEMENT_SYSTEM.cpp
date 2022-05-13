
//	ASSIGNMENT O1	--	C++ PROGRAMMING
//	NAKUL AGGARWAL	|	19CS10044
//	13.01.2021	TO	03.02.2021

#include <iostream>
#include <string>
#include <cstring>
#include <dirent.h>
#include <list>
#include <vector> 
#include <iterator>
#include <map>
#include <set>
#include <regex>
using namespace std ;


void scanIndex ( string ) ;
int getWordCount ( string , string ) ;
string getSignature ( string , string ) ;
bool searchForPattern ( string content , string key ) ;
bool comparatorSingleFold ( pair<int,int>& , pair<int,int>& ) ;
bool comparatorMultiFold ( pair< pair<int,int> , int >& , pair< pair<int,int> , int >& ) ;


namespace information {
	char seperator[] = "$$$" ;
	map<string,string> indexItems ;
    string ALPHABET("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") ;
} ;

const int CHAPTER_LIMIT = 150 ;
const int PARAS_LIMIT = 350 ;
const int SCENES_LIMIT = 10 ;
const int ACTS_LIMIT = 15 ;

typedef struct {
	int id ;
	set<string> characters ;
} Scene ;

typedef struct {
	int id ;
	Scene scenes[SCENES_LIMIT] ;
	int scenesCount ;
} Act ;

typedef struct {
	int id ;
	string content ;
} Paragraph ;

typedef struct {
	int id ;
	string title ;
	Paragraph paras[PARAS_LIMIT] ;
	int parasCount ;
} Chapter ;



class Book 
{

    protected :

        string title ;
		string author ;
		string releaseDate ;
		string language ;
		string path ;
		string type ;

    public :

        void printDetails ( string prefix = string("") )
        {
            cout << endl ;
            cout << prefix << "       ● TEXT DOCUMENT NAME : " << path.substr(path.find_last_of("/")+1) << endl ;
            cout << prefix << "       ● TITLE OF THE BOOK : " << title << endl ;
            cout << prefix << "       ● AUTHOR OF THE BOOK : " << author << endl ;
            cout << prefix << "       ● RELEASE DATE : " << releaseDate << endl ;
            cout << prefix << "       ● LANGUAGE : " << language << endl ;
            cout << prefix << "       ● CONTENT TYPE : " << type << endl ;
			return ;
        }

        void printContent(int limit, int offset)
        {
            FILE* fptr = fopen( path.c_str() , "r" ) ;
			cout << endl << endl ;
			int skipped = 0 ;
			while ( skipped < offset && ! feof(fptr) )
			{
				char c = fgetc(fptr) ;
				if ( c == '\n' )	skipped ++ ;
			}
			int lines = 0 ;
			cout << "              " ;
			while ( lines < limit && ! feof(fptr) )
			{
				char c = fgetc(fptr) ;
				if ( c == EOF ) break ;
				cout << c ;
				if ( c == '\n' )
				{
					lines ++ ;
					cout << "              " ;
				}
			}

			fclose(fptr) ;
        }

		string getTitle ()
		{
			return title ;
		}

		string getAuthor ()
		{
			return author ;
		}

} ;



class Novel : public Book 
{
	
	private :
		
		Chapter chapters[CHAPTER_LIMIT] ;
		int chaptersCount ;
	
	public :

		Novel( string title_ , string author_ , string date , string lang , string path_ ) :
			chaptersCount(0) 
		{
			title = title_ ; author = author_ ; releaseDate = date ; 
			language = lang ; path = path_ ; type = "Novel" ;
			FILE* fptr = fopen( path.c_str() , "r" ) ;
			char currentS[100] = "" ;
			
			while ( true )
			{
				fscanf( fptr , " %[^\n]s" , currentS ) ;
				if ( strlen(currentS) < 8 )	continue ;
				if ( feof( fptr ) )	break ;
				string line = string(currentS) ;
				
				if ( line.substr(0,7) != "CHAPTER" && line.substr(0,7) != "Chapter" ) continue ;
				chapters[chaptersCount].id = chaptersCount + 1 ;
				
				int idx = line.find_first_of(".") + 2 ;
				int len = line.length() - idx ;

                if ( string(".,;-:").find_first_of(line[line.length()-1]) != -1 )
                    len -- ;

				string title = line.substr( idx , len ) ;
				chapters[chaptersCount].title = title ;
				
				int count = 1 ;
				chapters[chaptersCount].paras[count-1].id = count ;
				
				char previous_1 = '\0' ;
				char previous_2 = '\0' ;
				char current = '\0' ;
				
				fgetc(fptr) ;
				
				while ( true )
				{
					previous_2 = previous_1 ;
					previous_1 = current ;
					current = fgetc(fptr) ;
					if ( current == '\n' && previous_1 == '\n' && previous_2 == '\n' )	break ;
					if ( current == '\n' && previous_1 == '\n' )
					{
						count ++ ;
						chapters[chaptersCount].paras[count-1].id = count ;
						continue ;
					}
					char arr[] = { current , '\0' } ;
					chapters[chaptersCount].paras[count-1].content += string(arr) ;
				}
				chapters[chaptersCount].parasCount = count - 1 ;
				chaptersCount ++ ;
			}
			
			fclose(fptr) ;
		}

		void topKChapters ( int k , string word )
		{
			vector< pair<int,int> > COUNTS ;
			for ( int i=0 ; i<chaptersCount ; i++ )
			{
				int total = 0 ;
				for ( int j=0 ; j<chapters[i].parasCount ; j++ )
					total += getWordCount( chapters[i].paras[j].content , word ) ;
				pair<int,int> t ; t.first = i ; t.second = total ;
				COUNTS.push_back(t) ;
			}
			sort( COUNTS.begin() , COUNTS.end() , comparatorSingleFold ) ;
			bool noResults = true ;
			for ( int i=0 ; i<chaptersCount && i<k && COUNTS.at(i).second ; i++ )
			{
				noResults = false ;
				cout << endl ;
				cout << endl << "                   □ RANK : " << i + 1 ;
				cout << endl << "                   □ CHAPTER NO. : " << COUNTS.at(i).first + 1 ;
				cout << endl << "                   □ CHAPTER TITLE : " << chapters[COUNTS.at(i).first].title ;
				cout << endl << "                   □ FREQUENCY OF WORD : " << COUNTS.at(i).second ;
			}
			if ( noResults )
				cout << endl << "\n                   [ NO CHAPTERS CONTAINING THIS WORD WERE FOUND ]" ;
			return ;
		}

		void topKParas ( int k , string word )
		{
			vector< pair< pair<int,int> , int > > COUNTS ;
			int totalParas = 0 ;
			for ( int i=0 ; i<chaptersCount ; i++ )
			{
				totalParas += chapters[i].parasCount ;
				for ( int j=0 ; j<chapters[i].parasCount ; j++ )
				{
					pair<int,int> pos ; pos.first = i ; pos.second = j ;
					pair< pair<int,int> , int > t ; t.first = pos ; 
					t.second = getWordCount( chapters[i].paras[j].content , word ) ;
					COUNTS.push_back(t) ;
				}
			}
			sort( COUNTS.begin() , COUNTS.end() , comparatorMultiFold ) ;
			bool noResults = true ;
			for ( int i=0 ; i<totalParas && i<k && COUNTS.at(i).second ; i++ )
			{
				noResults = false ;
				cout << endl ;
				cout << endl << "                   □ RANK : " << i + 1 ;
				cout << endl << "                   □ CHAPTER NO. : " << COUNTS.at(i).first.first + 1 ;
				cout << endl << "                   □ CHAPTER TITLE : " << chapters[COUNTS.at(i).first.first].title ;
				cout << endl << "                   □ PARAGRAPH NO. : " << COUNTS.at(i).first.second + 1 ;
				cout << endl << "                   □ FREQUENCY OF WORD : " << COUNTS.at(i).second ;
				cout << endl << "                   □ PARAGRAPH CONTENT : ↓" ;
				string c = chapters[COUNTS.at(i).first.first].paras[COUNTS.at(i).first.second].content ;
				cout << endl << endl << "                        " ;
				for ( int i=0 ; i<c.length() ; i++ )
				{
					cout << c[i] ;
					if ( c[i] == '\n' )	cout << "                        " ;
				}
			}
			if ( noResults )
				cout << endl << "\n                   [ NO PARAGRAPHS CONTAINING THIS WORD WERE FOUND ]" ;
			return ;
		}

} ;


class Play : public Book 
{
	
	private :
		
		set<string> characters ;
		Act acts[ACTS_LIMIT] ;
		int actsCount ;

	public :

		Play( string title_ , string author_ , string date , string lang , string path_ ) :
			actsCount(0)
		{
			title = title_ ; author = author_ ; releaseDate = date ; 
			language = lang ; path = path_ ; type = "Play" ;
			FILE* fptr = fopen( path.c_str() , "r" ) ;
			char currentS[100] = "" ;
			
			bool flag = true ;
            while ( true )
			{
				fscanf( fptr , " %[^\n]s" , currentS ) ;
				if ( feof( fptr ) )	break ;
				string line = string(currentS) ;
				
				if ( flag && line.substr(0,4) != "ACT " ) continue ;
				acts[actsCount].id = actsCount + 1 ;
				
				int count = 0 ;
				
				while ( true )
				{
					fscanf( fptr , " %[^\n]s" , currentS ) ;
					if ( feof( fptr ) ) break ;
					string line = string(currentS) ;
					if ( line.find("ACT ") == 0 )
					{
						acts[actsCount].scenesCount = count  ;
						actsCount ++ ;
						acts[actsCount].id = actsCount + 1 ;
						count = 0 ;
						continue ;
					}
					if ( line.find("SCENE") == 0 )
					{
						count ++ ;
						acts[actsCount].scenes[count-1].id = count ;
						continue ;
					}
					if ( count >= 1 && line.find_last_of("abcdefghijklmnopqrstuvwxyz") == -1 
					     && line.length() > 2 && line[line.length()-1] == '.' )
					{
						string c = line.substr(0,line.length()-1) ;
						acts[actsCount].scenes[count-1].characters.insert(c) ;
						characters.insert(c) ;
					}
				}
				acts[actsCount].scenesCount = count  ;
			    actsCount ++ ;
			}
			fclose(fptr) ;
		}

		void findCharsWithCommonScene ( string c )
		{
			for ( int i=0 ; i<c.length() ; i++ ) c[i] = toupper(c[i]) ;
			if ( characters.find(c) == characters.end() )
			{
				cout << endl << endl << "               [ NO CHARACTER WITH THIS NAME WAS FOUND ] " ;
				return ;
			}
			set<string> result ;
			for ( int i=0 ; i<actsCount ; i++ )
			{
				for ( int j=0 ; j<acts[i].scenesCount ; j++ )
				{
					const auto& chars = acts[i].scenes[j].characters ;
					if ( chars.find(c) == chars.end() )	continue ;
					for ( auto it = chars.begin() ; it != chars.end() ; it++ )
						result.insert(*it) ;
				}
			}
			result.erase(c) ;
			if ( ! result.size() )
			{
				cout << endl << endl << "               [ NO CHARACTERS SHARE A SCENE WITH THIS CHARACTER ] " ;
				return ;
			}
			for ( auto it = result.begin() ; it != result.end() ; it++ )
				cout << endl << "                □ " << *it ;
		}

} ;


void askToDisplayBook ( vector<Novel>& , vector<Play>& , string ) ;
void displayAllBooks ( vector<Novel>& NOVELS , vector<Play>& PLAYS ) ;
void searchBookByTitle ( vector<Novel>& NOVELS , vector<Play>& PLAYS ) ;
void searchBookByAuthor ( vector<Novel>& NOVELS , vector<Play>& PLAYS ) ;
void scanDirectory ( string , string , vector<Novel>& , vector<Play>& ) ;
void askToDisplayBookFromResults ( set<int>& , vector<Novel>& , vector<Play>& , string ) ;


int main( int argc , char** argv )
{
	char INDEX[] = "index.txt" ;
	char DIRECTORY[strlen(argv[1])] ; strcpy( DIRECTORY , argv[1] ) ;
    vector<Novel> NOVELS ;
    vector<Play> PLAYS ;
    
	cout << "\n\n\n\n    † LIBRARY MANAGEMENT SYSTEM †\n" ;
	cout << endl << "      ( DIRECTORY : " << DIRECTORY << " )" << endl ;
	cout << "\n" ;

	scanIndex( INDEX ) ;
	scanDirectory( DIRECTORY , INDEX , NOVELS , PLAYS ) ;
	
    int choice = 0 ;
    while ( true )
    {
		cout << endl << endl << "\n\n   +++  MAIN MENU  +++" ;
		cout << endl << "\n      1) DISPLAY DETAILS OF ALL THE BOOKS" ;
        cout << endl << "      2) SEARCH FOR A BOOK" ;
		cout << endl << "      3) PERFORM ANALYTICS ON A NOVEL" ;
		cout << endl << "      4) PERFORM ANALYTICS ON A PLAY" ;
        cout << endl << "      5) CLOSE THE SYSTEM" ;

        cout << endl << "\n        ○  ENTER CHOICE : " ;
        cin >> choice ;
        if ( choice < 1 || choice > 5 )
        {
            cout << endl << endl << "             [ INVALID CHOICE ] " ;
            continue ;
        }

		if ( choice == 5 )
			break ;
        
		if ( choice == 1 )
        {
			displayAllBooks( NOVELS , PLAYS ) ;
			continue ;
        }

		if ( choice == 2 )
		{
			int criteria ;
			cout << endl << endl << "\n   +++  SEARCHING FOR A BOOK IN THE SYSTEM  +++\n" ;
			cout << endl << "       ○ ENTER SEARCH CRITERIA (1: TITLE, 2: AUTHOR) : " ;
			cin >> criteria ;
			if ( criteria != 1 && criteria != 2 )
			{
				cout << endl << endl << "            [ INVALID SEARCH CRITERIA ] " ;
				continue ;
			}
			if ( criteria == 1 )
			{
				searchBookByTitle(NOVELS, PLAYS) ;
				continue ;
			}
			if ( criteria == 2 )
			{
				searchBookByAuthor(NOVELS, PLAYS) ;
				continue ;
			}
		}

		if ( choice == 3 )
		{
			cout << endl << endl << "\n   +++  SHORTLISTING TOP K CHAPTERS / PARAGRAPHS IN A NOVEL BASED ON FREQUENCY OF A WORD  +++\n" ;
			for ( int i=0 ; i<NOVELS.size() ; i++ )
			{
				cout << endl ;
				cout << "       ● ID : " << i + 1 << endl ;
				cout << "       ● TITLE : " << NOVELS.at(i).getTitle() << endl ;
            	cout << "       ● AUTHOR : " << NOVELS.at(i).getAuthor() << endl ;
			}
			cout << endl << "\n          ○ CHOOSE A NOVEL AND ENTER ITS ID : " ;
			int id ; cin >> id ;
			if ( id > NOVELS.size() || id < 0 )
			{
				cout << endl << endl << "               [ NO NOVEL WITH THIS ID WAS FOUND ] " ;
				continue ;
			}
			string word ; int k ; int target ;
			cout << "          ○ ENTER A WORD ([A-Za-z]+) : " ; cin >> word ;
			if ( word.find_first_not_of(information::ALPHABET) != word.npos )
			{
				cout << endl << endl << "               [ NON-ALPHABETICAL CHARACTERS NOT ALLOWED ] " ;
				continue ;
			}
			cout << "          ○ ENTER THE MAX VALUE OF K  : " ; cin >> k ;
			if ( k <= 0 )
			{
				cout << endl << endl << "               [ ONLY POSITIVE VALUES ARE ALLOWED FOR K ] " ;
				continue ;
			}
			cout << "          ○ CHOOSE TARGET (1: CHAPTERS, 2: PARAGRAPHS) : " ; cin >> target ;
			if ( target != 1 && target != 2 )
			{
				cout << endl << endl << "               [ INVALID CHOICE OF TARGET ] " ;
				continue ;
			}
			if ( target == 1 )	NOVELS.at(id-1).topKChapters(k,word) ;
			else	NOVELS.at(id-1).topKParas(k,word) ;
			continue ;
		}

		if ( choice == 4 )
		{
			cout << endl << endl << "\n   +++  FINDING THE CHARACTERS IN A PLAY THAT SHARE A SCENE WITH THE INPUT CHARACTER  +++\n" ;
			for ( int i=0 ; i<PLAYS.size() ; i++ )
			{
				cout << endl ;
				cout << "       ● ID : " << i + 1 + NOVELS.size() << endl ;
				cout << "       ● TITLE : " << PLAYS.at(i).getTitle() << endl ;
            	cout << "       ● AUTHOR : " << PLAYS.at(i).getAuthor() << endl ;
			}
			cout << endl << "\n          ○ CHOOSE A PLAY AND ENTER ITS ID : " ;
			int id ; cin >> id ;
			if ( id > NOVELS.size() + PLAYS.size() || id <= NOVELS.size() )
			{
				cout << endl << endl << "               [ NO PLAY WITH THIS ID WAS FOUND ] " ;
				continue ;
			}
			string buffer ; getline(cin, buffer) ;
			cout << "          ○ ENTER THE NAME OF A CHARACTER : " ;
			string character ; getline(cin, character) ;
			PLAYS.at(id-NOVELS.size()-1).findCharsWithCommonScene(character) ;
			continue ;
		}

    }
	cout << "\n\n\n    † GOODBYE †\n\n\n\n" ;
	return 0 ;
}

bool comparatorSingleFold ( pair<int,int>& a , pair<int,int>& b )
{
	if ( a.second < b.second ) return false ;
	if ( a.second > b.second ) return true ;
	if ( a.first > b.first ) return false ;
	if ( a.first < b.first ) return true ;
}

bool comparatorMultiFold ( pair< pair<int,int> , int >& a , pair< pair<int,int> , int >& b )
{
	if ( a.second < b.second ) return false ;
	if ( a.second > b.second ) return true ;
	if ( a.first.first < b.first.first ) return true ;
	if ( a.first.first > b.first.first ) return false ;
	if ( a.first.second < b.first.second ) return true ;
	if ( a.first.second > b.first.second ) return false ;
}

bool searchForPattern ( string content , string key )
{
	regex re( key , regex_constants::icase ) ;
	sregex_iterator end ;
	smatch match ;
	int count = 0 ;
	sregex_iterator it = sregex_iterator( content.begin() , content.end() , re ) ;
	for ( ; it != end ; it++ ) 
		return true ;
	return false ;
}

void searchBookByTitle ( vector<Novel>& NOVELS , vector<Play>& PLAYS )
{
	cout << "       ○ ENTER TITLE OF THE BOOK : " ;
	string buffer ; getline(cin, buffer) ;
	string title ;	getline(cin, title) ;
	
	int count = 1 ;

	set<int> results ;

	for (int i=0 ; i<NOVELS.size() ; i++ , count++ )
	{
		if ( ! searchForPattern( NOVELS.at(i).getTitle() , title ) )	continue ;
		results.insert(count) ;
		cout << endl << "          ● ID : " << count ;
		NOVELS.at(i).printDetails(string("   ")) ;
	}

	for (int i=0 ; i<PLAYS.size() ; i++ , count++ )
	{
		if ( ! searchForPattern( PLAYS.at(i).getTitle() , title ) )	continue ;
		results.insert(count) ;
		cout << endl << "          ● ID : " << count ;
		PLAYS.at(i).printDetails(string("   ")) ;
	}

	if ( ! results.size() )
	{
		cout << endl << endl << "            [ NO RELEVANT BOOK FOUND ] " ;
		return ;
	}

	askToDisplayBookFromResults( results , NOVELS , PLAYS , string("BOOK WITH THIS ID WAS NOT FOUND IN THE SEARCH RESULTS") ) ;
	return ;

}

void askToDisplayBookFromResults ( set<int>& IDs , vector<Novel>& NOVELS , vector<Play>& PLAYS , string errorMsg )
{
	char doDisplay ;
	cout << endl << "\n             ○  ENTER Y TO DISPLAY A BOOK : " ;
	cin >> doDisplay ;
	if ( toupper(doDisplay) != 'Y' ) return ;

	cout << "             ○  ENTER ID OF THE BOOK : " ;
	int id ; cin >> id ;
	
	if ( IDs.find(id) == IDs.end() )
	{
		cout << endl << endl << "                 [ " << errorMsg << " ] " ;
		return ;
	}

	int limit , offset ;
	cout << "             ○  LIMIT ON THE NUMBER OF LINES : " ; cin >> limit ;
	if ( limit <= 0 )
	{
		cout << endl << endl << "             [ INVALID CHOICE OF LIMIT ] " ;
		return ;
	}
	cout << "             ○  OFFSET OF THE FIRST LINE : " ; cin >> offset ;
	if ( offset < 0 )
	{
		cout << endl << endl << "             [ INVALID CHOICE OF OFFSET ] " ;
		return ;
	}

	if ( id <= NOVELS.size() )	NOVELS.at(id-1).printContent(limit, offset) ;
	else	PLAYS.at(id-NOVELS.size()-1).printContent(limit, offset) ;
	return ;
}

void searchBookByAuthor ( vector<Novel>& NOVELS , vector<Play>& PLAYS )
{
	cout << "       ○ ENTER AUTHOR OF THE BOOK : " ;
	string buffer ; getline(cin, buffer) ;
	string author ;	getline(cin, author) ;
	
	int count = 1 ;

	set<int> results ;

	for (int i=0 ; i<NOVELS.size() ; i++ , count++ )
	{
		if ( ! searchForPattern( NOVELS.at(i).getAuthor() , author ) )	continue ;
		results.insert(count) ;
		cout << endl << "          ● ID : " << count ;
		NOVELS.at(i).printDetails(string("   ")) ;
	}

	for (int i=0 ; i<PLAYS.size() ; i++ , count++ )
	{
		if ( ! searchForPattern( PLAYS.at(i).getAuthor() , author ) )	continue ;
		results.insert(count) ;
		cout << endl << "          ● ID : " << count ;
		PLAYS.at(i).printDetails(string("   ")) ;
	}

	if ( ! results.size() )
	{
		cout << endl << endl << "            [ NO RELEVANT BOOK FOUND ] " ;
		return ;
	}

	askToDisplayBookFromResults( results , NOVELS , PLAYS , string("BOOK WITH THIS ID WAS NOT FOUND IN THE SEARCH RESULTS") ) ;
	return ;
}

void displayAllBooks ( vector<Novel>& NOVELS , vector<Play>& PLAYS )
{
	cout << endl << endl << "\n   +++  DETAILS OF ALL THE BOOKS IN THE SYSTEM  +++\n" ;
	int count = 1 ;
	for (int i=0 ; i<NOVELS.size() ; i++ )
	{
		cout << endl << "       ● ID : " << count++ ;
		NOVELS.at(i).printDetails() ;
	}
	for (int i=0 ; i<PLAYS.size() ; i++ )
	{
		cout << endl << "       ● ID : " << count++ ;
		PLAYS.at(i).printDetails() ;
	}
	
	askToDisplayBook( NOVELS , PLAYS , string("INVALID ID") ) ;
	return ;
}

void askToDisplayBook ( vector<Novel>& NOVELS , vector<Play>& PLAYS , string errorMsg )
{
	char doDisplay ;
	cout << endl << "\n          ○  ENTER Y TO DISPLAY A BOOK : " ;
	cin >> doDisplay ;
	if ( toupper(doDisplay) != 'Y' ) return ;

	int id ;
	cout << "          ○  ENTER ID OF THE BOOK : " ;
	cin >> id ;
	int count = NOVELS.size() + PLAYS.size() ;
	if ( id > count || id <= 0 )
	{
		cout << endl << endl << "                [ " << errorMsg << " ] " ;
		return ;
	}

	int limit , offset ;
	cout << "          ○  LIMIT ON THE NUMBER OF LINES : " ; cin >> limit ;
	if ( limit <= 0 )
	{
		cout << endl << endl << "             [ INVALID CHOICE OF LIMIT ] " ;
		return ;
	}
	cout << "          ○  OFFSET OF THE FIRST LINE : " ; cin >> offset ;
	if ( offset < 0 )
	{
		cout << endl << endl << "             [ INVALID CHOICE OF OFFSET ] " ;
		return ;
	}

	if ( id <= NOVELS.size() )	NOVELS.at(id-1).printContent(limit, offset) ;
	else	PLAYS.at(id-NOVELS.size()-1).printContent(limit, offset) ;
	return ;
}

int getWordCount ( string content , string key )
{
	content = " " + content + " " ;
	string pattern = "[^a-zA-Z]" + key ;
	regex re( pattern , regex_constants::icase ) ;
	sregex_iterator end ;
	smatch match ;
	string ALPHABET("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") ;
	int count = 0 ;
	sregex_iterator it = sregex_iterator( content.begin() , content.end() , re ) ;
	for ( ; it != end ; it++ ) 
	{
		match = *it ;
		char next = content[match.position(0)+match.str(0).length()] ;
		if ( information::ALPHABET.find_first_of(next) == -1 )	count ++ ;
	}
	return count ;
}

void scanIndex ( string indexFileName )
{
	FILE* fptr = fopen( indexFileName.c_str() , "r" ) ;
	if ( ! fptr )
	{
		fclose( fptr ) ;
		fptr = fopen( indexFileName.c_str() , "w" ) ;
		fclose( fptr ) ;
		return ;
	}
	string sep = information::seperator ;
	while ( ! feof(fptr) )
	{
		char file[50], title[50], author[50], lang[20], date[25] , type[10] ;
		fscanf ( fptr , " %[^\n]s" , file ) ;
		fscanf ( fptr , " %[^\n]s" , title ) ;
		fscanf ( fptr , " %[^\n]s" , author ) ;
		fscanf ( fptr , " %[^\n]s" , date ) ;
		fscanf ( fptr , " %[^\n]s" , lang ) ;
		fscanf ( fptr , " %[^\n]s" , type ) ;
		string signature = string(file) + sep + string(title) + sep +
						   string(author) + sep + string(date) + sep +
						   string(lang) ;
		information::indexItems.insert( pair<string,string>( signature, string(type) ) ) ;
	}
	fclose( fptr ) ;
	return ;
}

string getSignature ( string filePath , string fileName )
{
	FILE* fptr = fopen( filePath.c_str() , "r" ) ;
	char current[100] ;
	string sep = information::seperator ;
	string sign = fileName + sep ;
	
	while( ! feof(fptr) )
	{
		fscanf( fptr , " %s" , current ) ;
		if ( ! strcmpi( current , "Title:" ) )
		{
			char temp[100] ;
			fscanf( fptr , " %[^\n]s" , temp ) ;
			sign += string(temp) + sep ;
			break ;
		}
	}
	
	while( ! feof(fptr) )
	{
		fscanf( fptr , " %s" , current ) ;
		if ( ! strcmpi( current , "Author:" ) )
		{
			char temp[100] ;
			fscanf( fptr , " %[^\n]s" , temp ) ;
			sign += string(temp) + sep ;
			break ;
		}
	}
	
	while( ! feof(fptr) )
	{
		fscanf( fptr , " %s" , current ) ;
		if ( ! strcmpi( current , "Date:" ) )
		{
			char temp[100] ;
			fscanf( fptr , " %[^[]s" , temp ) ;
			sign += string(temp).substr(0,strlen(temp)-1) + sep ;
			break ;
		}
	}
	
	while( ! feof(fptr) )
	{
		fscanf( fptr , " %s" , current ) ;
		if ( ! strcmpi( current , "Language:" ) )
		{
			char temp[100] ;
			fscanf( fptr , " %[^\n]s" , temp ) ;
			sign += string(temp) ;
			break ;
		}
	}
	fclose(fptr) ;
	return sign ;
}

void scanDirectory ( string directoryPath , string indexPath , vector<Novel>& NOVELS , vector<Play>& PLAYS )
{
	struct dirent *entry ;

	DIR* dir = opendir(directoryPath.c_str()) ;
	FILE* fptr = fopen( indexPath.c_str() , "w" ) ;
	
    if ( ! dir ) return ;
	
	while ( entry = readdir(dir) ) 
	{
		string fileName( entry->d_name ) ;
		if ( fileName.find(".txt") == fileName.npos ) continue ;
		string textFile = directoryPath + string("/") + fileName ;
		string signature = getSignature(textFile, fileName) ;
		
		map<string,string>::iterator it = information::indexItems.find(signature) ;
		char *token = strtok( strdup(signature.c_str()), information::seperator ) ;
        string bookDetails[5] ; int k = 0 ;

		while( token )
	    {
			fprintf( fptr , "%s\n" , token ) ;
            bookDetails[k++] = string(token) ;
	        token = strtok(NULL, information::seperator) ;
	    }
		int type ;
		if ( it == information::indexItems.end() ) 
        {
			cout << endl << "\n   *  NEW BOOK FOUND  *\n" ;
            cout << endl << "       o TEXT DOCUMENT NAME : " << bookDetails[0] ;
            cout << endl << "       o TITLE OF THE BOOK : " << bookDetails[1] ;
            cout << endl << "       o AUTHOR OF THE BOOK : " << bookDetails[2] ;
            cout << endl << "       o RELEASE DATE : " << bookDetails[3] ;
            cout << endl << "       o LANGUAGE : " << bookDetails[4] ;
            cout << endl << "       o ENTER TYPE (1: NOVEL, 2: PLAY) : " ;
		    cin >> type ;
			while ( type != 1 && type != 2 )
			{
				cout << "           [ ENTER A VALID TYPE ] " ;
				cout << endl << "       o ENTER TYPE (1: NOVEL, 2: PLAY) : " ;
				cin >> type ;
			}
            if ( type == 1 )
                fprintf( fptr , "novel\n\n" ) ;
            else if ( type == 2 )
                fprintf( fptr , "play\n\n" ) ;
		}

		else
		{
			fprintf( fptr , "%s\n\n" , it->second.c_str() ) ;
            type = (it->second == "play") ? 2 : 1 ;
		}

        if ( type == 1 )
        {
            NOVELS.push_back( Novel(bookDetails[1], bookDetails[2],
                                bookDetails[3], bookDetails[4],
                                directoryPath+string("/")+bookDetails[0]) ) ;
        }

        if ( type == 2 )
        {
            PLAYS.push_back( Play(bookDetails[1], bookDetails[2],
                                bookDetails[3], bookDetails[4],
                                directoryPath+string("/")+bookDetails[0]) ) ;
        }
	}
	
	fclose( fptr ) ;
	closedir( dir ) ;
	return ;
}


