
//	ASSIGNMENT O0 -- JAVA PROGRAMMING
//	NAKUL AGGARWAL	|	19CS10044
//	06.01.2021 to 13.01.2021

import java.util.* ;

public class SocialNetwork
{
	
	public static void main(String[] args)
	{
		Scanner obj = new Scanner(System.in) ;
		HashMap<Integer,Node> INDEX = new HashMap<Integer,Node>() ;
		HashMap<String,Set<Integer>> INDEX_BD = new HashMap<String,Set<Integer>>() ;
		HashMap<Character,Set<Integer>> INDEX_TYPE = new HashMap<Character,Set<Integer>>() ;
		HashMap<String,Set<Integer>> INDEX_NAME = new HashMap<String,Set<Integer>>() ;
		HashMap<String,Set<Integer>> INDEX_POST = new HashMap<String,Set<Integer>>() ;
		mainMenu(obj, INDEX, INDEX_TYPE, INDEX_NAME, INDEX_BD, INDEX_POST) ;
		System.out.print( "\n\n        * PROGRAM CLOSED SUCCESSFULLY *\n\n\n" ) ;
		return ;
	}
	
	
	static void mainMenu( Scanner obj , HashMap<Integer,Node> index , 
						  HashMap<Character,Set<Integer>> indexType , 
						  HashMap<String,Set<Integer>> indexName , 
						  HashMap<String,Set<Integer>> indexBirthD ,
						  HashMap<String,Set<Integer>> indexPosts ) 
	{
		int x = 0 ;
		while( true ) {
			System.out.print("\n\n\n\n\n  1) CREATE A NEW NODE") ;
			System.out.print("\n  2) DELETE AN EXISTING NODE ") ;
			System.out.print("\n  3) SEARCH FOR A NODE") ;
			System.out.print("\n  4) DISPLAY NODES LINKED TO AN INPUT NODE") ;
			System.out.print("\n  5) CREATE AND POST NEW CONTENT") ;
			System.out.print("\n  6) SEARCH FOR CONTENT POSTED BY ANY NODE") ;
			System.out.print("\n  7) DISPLAY CONTENT POSTED BY ALL LINKED NODES") ;
			System.out.print("\n  8) DISPLAY ALL THE NODES") ;
			System.out.print("\n  9) CREATE A NEW GENERIC LINK") ;
			System.out.print("\n 10) CREATE A NEW RELATIONSHIP-SPECIFIC LINK") ;
			System.out.print("\n 11) QUIT") ;
			System.out.print("\n\n    ENTER YOUR CHOICE : ") ;
			
			x = Integer.parseInt(obj.nextLine()) ;
			System.out.print("\n\n") ;
			
			if ( x < 1 || x > 11 )
			{
				System.out.print("       [ INVALID CHOICE ]") ;
				continue ;
			}
			
			if ( x == 11 ) break ;
			if ( x == 1 )	createNode(obj, index, indexType, indexName, indexBirthD, indexPosts) ;
			if ( x == 2 )	deleteNode(obj, index) ;
			if ( x == 3 ) {
				System.out.print("\n\n +++ SEARCHING A NODE +++") ;
				System.out.print("\n\n   o ENTER SEARCH CRITERIA (1:NAME, 2:TYPE, 3:BIRTHDAY) : ") ;
				int cr = Integer.parseInt(obj.nextLine()) ;
				if ( cr == 1 )	searchNodeByName(obj, indexName, index) ;
				else if ( cr == 2 )	searchNodeByType(obj, indexType, index) ;
				else if ( cr == 3 )	searchNodeByBirthday(obj, indexBirthD, index) ;
				else System.out.print("\n       [ INVALID SEARCH CRITERIA ]") ;
			}
			if ( x == 4 ) findLinkedNodes(obj, index) ;
			if ( x == 5 ) postNewContent(obj, index, indexPosts) ;
			if ( x == 6 ) searchForPost( obj , indexPosts , index ) ;
			if ( x == 7 ) printPostsByLinkedNodes(obj, index) ;
			if ( x == 8 ) printAllNodes(index) ;
			if ( x == 9 ) createGenericLink(obj, index) ;
			if ( x == 10 ) createRelationLink(obj, index) ;
 		}
		return ;
	}
	
	
	static void createGenericLink( Scanner obj , HashMap<Integer,Node> index )
	{
		System.out.print("\n\n +++ CREATING A NEW GENERIC LINK +++") ;
		System.out.print("\n\n   o ENTER ID : ") ;
		
		int id = Integer.parseInt(obj.nextLine()) ;
		if ( index.get(id) == null ) {
			System.out.print("\n       [ NO NODE WITH THIS USER ID WAS FOUND ]") ;
			return ;
		}
		
		Node n = index.get(id) ;
		
		System.out.print("   o ENTER ID OF THE OTHER NODE : ") ;
		int other = Integer.parseInt(obj.nextLine()) ;
		
		if ( index.get(other) == null ) {
			System.out.print("\n       [ NO NODE WITH THIS USER ID WAS FOUND ]") ;
			return ;
		}
		
		if ( other == id ) {
			System.out.print("\n       [ SELF LINKS NOT ALLOWED ]") ;
			return ;
		}
		
		if ( n.links.contains(other) ) {
			System.out.print("\n       [ THE NODE IS ALREADY CONNECTED VIA A RELATIONSHIP-SPECIFIC LINK ]") ;
			return ;
		}
		
		n.miscLinks.add(other) ;
		System.out.print("\n       * NEW GENERIC LINK CREATED *") ;
		return ;
		
	}
	
	
	static void createRelationLink( Scanner obj , HashMap<Integer,Node> index )
	{
		System.out.print("\n\n +++ CREATING A NEW RELATIONSHIP-SPECIFIC LINK +++") ;
		System.out.print("\n\n   o ENTER ID : ") ;
		
		int id = Integer.parseInt(obj.nextLine()) ;
		if ( index.get(id) == null ) {
			System.out.print("\n       [ NO NODE WITH THIS USER ID WAS FOUND ]") ;
			return ;
		}
		
		Node n = index.get(id) ;
		
		System.out.print("   o ENTER ID OF THE OTHER NODE : ") ;
		int other = Integer.parseInt(obj.nextLine()) ;
		
		if ( index.get(other) == null ) {
			System.out.print("\n       [ NO NODE WITH THIS USER ID WAS FOUND ]") ;
			return ;
		}
		
		if ( other == id ) {
			System.out.print("\n       [ SELF LINKS NOT ALLOWED ]") ;
			return ;
		}
		
		Node no = index.get(other) ;
		
		
		if ( n.type == 'O' )
		{
			if ( no.type == 'B' )
			{
				System.out.print("\n       [ BUSINESS-ORGANIZATION RELATIONSHIP-SPECIFIC LINKS NOT ALLOWED ]") ;
				return ;
			}
			if ( no.type == 'O' )
			{
				System.out.print("\n       [ ORGANIZATION-ORGANIZATION RELATIONSHIP-SPECIFIC LINKS NOT ALLOWED ]") ;
				return ;
			}
			if ( no.type == 'G' )
			{
				System.out.print("\n       [ GROUP-ORGANIZATION RELATIONSHIP-SPECIFIC LINKS NOT ALLOWED ]") ;
				return ;
			}
			((Organization)n).members.add(other) ;
			no.links.add(id) ;
			n.links.add(other) ;
			n.miscLinks.remove(other) ;
			no.miscLinks.remove(id) ;
			System.out.print("\n       * NEW RELATIONSHIP-SPECIFIC LINK CREATED *") ;
			return ;
		}
		
		
		if ( n.type == 'G' )
		{
			if ( no.type == 'O' )
			{
				System.out.print("\n       [ GROUP-ORGANIZATION RELATIONSHIP-SPECIFIC LINKS NOT ALLOWED ]") ;
				return ;
			}
			if ( no.type == 'G' )
			{
				System.out.print("\n       [ GROUP-GROUP RELATIONSHIP-SPECIFIC LINKS NOT ALLOWED ]") ;
				return ;
			}
			if ( no.type == 'B' )
			{
				((Group)n).membersBusin.add(other) ;
				no.links.add(id) ;
				n.links.add(other) ;
				n.miscLinks.remove(other) ;
				no.miscLinks.remove(id) ;
				System.out.print("\n       * NEW RELATIONSHIP-SPECIFIC LINK CREATED *") ;
				return ;
			}
			((Group)n).membersIndiv.add(other) ;
			no.links.add(id) ;
			n.links.add(other) ;
			n.miscLinks.remove(other) ;
			no.miscLinks.remove(id) ;
			System.out.print("\n       * NEW RELATIONSHIP-SPECIFIC LINK CREATED *") ;
			return ;
		}
		
		
		
		if ( n.type == 'I' )
		{
			if ( no.type == 'I' )
			{
				System.out.print("\n       [ INDIVIDUAL-INDIVIDUAL RELATIONSHIP-SPECIFIC LINKS NOT ALLOWED ]") ;
				return ;
			}
			if ( no.type == 'G' )
			{
				((Group)no).membersIndiv.add(id) ;
				no.links.add(id) ;
				n.links.add(other) ;
				n.miscLinks.remove(other) ;
				no.miscLinks.remove(id) ;
				System.out.print("\n       * NEW RELATIONSHIP-SPECIFIC LINK CREATED *") ;
				return ;
			}
			if ( no.type == 'O' )
			{
				((Organization)no).members.add(id) ;
				no.links.add(id) ;
				n.links.add(other) ;
				n.miscLinks.remove(other) ;
				no.miscLinks.remove(id) ;
				System.out.print("\n       * NEW RELATIONSHIP-SPECIFIC LINK CREATED *") ;
				return ;
			}
			if ( no.type == 'B' )
			{
				System.out.print("   o ENTER RELATIONSHIP (1: OWNER, 2:CUSTOMER) : ") ;
				int choice = Integer.parseInt(obj.nextLine()) ;
				
				if ( choice != 1 && choice != 2 ) {
					System.out.print("\n       [ INVALID RELATIONSHIP SELECTED ]") ;
					return ;
				}
				if ( choice == 1 )
				{
					((Business)no).owners.add(id) ;
					no.links.add(id) ;
					n.links.add(other) ;
					n.miscLinks.remove(other) ;
					no.miscLinks.remove(id) ;
					System.out.print("\n       * NEW RELATIONSHIP-SPECIFIC LINK CREATED *") ;
					return ;
				}
				((Business)no).customers.add(id) ;
				no.links.add(id) ;
				n.links.add(other) ;
				n.miscLinks.remove(other) ;
				no.miscLinks.remove(id) ;
				System.out.print("\n       * NEW RELATIONSHIP-SPECIFIC LINK CREATED *") ;
				return ;
			}
		}
		
		if ( n.type == 'B' )
		{
			if ( no.type == 'I' )
			{
				System.out.print("   o ENTER RELATIONSHIP (1: OWNER, 2:CUSTOMER) : ") ;
				int choice = Integer.parseInt(obj.nextLine()) ;
				
				if ( choice != 1 && choice != 2 ) {
					System.out.print("\n       [ INVALID RELATIONSHIP SELECTED ]") ;
					return ;
				}
				if ( choice == 1 )
				{
					((Business)n).owners.add(other) ;
					n.links.add(other) ;
					no.links.add(id) ;
					n.miscLinks.remove(other) ;
					no.miscLinks.remove(id) ;
					System.out.print("\n       * NEW RELATIONSHIP-SPECIFIC LINK CREATED *") ;
					return ;
				}
				((Business)n).customers.add(other) ;
				n.links.add(other) ;
				no.links.add(id) ;
				n.miscLinks.remove(other) ;
				no.miscLinks.remove(id) ;
				System.out.print("\n       * NEW RELATIONSHIP-SPECIFIC LINK CREATED *") ;
				return ;
			}
			if ( no.type == 'B' )
			{
				System.out.print("\n       [ BUSINESS-BUSINESS RELATIONSHIP-SPECIFIC LINKS NOT ALLOWED ]") ;
				return ;
			}
			if ( no.type == 'O' )
			{
				System.out.print("\n       [ BUSINESS-ORGANIZATION RELATIONSHIP-SPECIFIC LINKS NOT ALLOWED ]") ;
				return ;
			}
			if ( no.type == 'G' )
			{
				((Group)no).membersBusin.add(id) ;
				n.links.add(other) ;
				no.links.add(id) ;
				n.miscLinks.remove(other) ;
				no.miscLinks.remove(id) ;
				System.out.print("\n       * NEW RELATIONSHIP-SPECIFIC LINK CREATED *") ;
				return ;
			}
		}
		
		
		
		if ( n.links.contains(other) ) {
			System.out.print("\n       [ THE NODE IS ALREADY CONNECTED VIA A RELATIONSHIP-SPECIFIC LINK ]") ;
			return ;
		}
		
		n.miscLinks.add(other) ;
		return ;
		
	}
	
	
	static void createNode( Scanner obj , HashMap<Integer,Node> index , 
							HashMap<Character,Set<Integer>> indexType , 
							HashMap<String,Set<Integer>> indexName , 
							HashMap<String,Set<Integer>> indexBirthD ,
							HashMap<String,Set<Integer>> indexPosts ) 
	{
		System.out.print("\n\n +++ CREATING A NEW NODE +++") ;
		System.out.print("\n\n   o ENTER TYPE : ") ;
		String type = obj.nextLine() ;
		
		Node n ;
		if ( type.equalsIgnoreCase("individual") )	{
			n = new Individual(obj,index) ;
			String dob = ((Individual)n).birthDate ;
			if (indexBirthD.get(dob) == null)
				indexBirthD.put(dob, new HashSet<Integer>()) ;
			indexBirthD.get(dob).add(n.ID) ;
		}
		else if ( type.equalsIgnoreCase("business") )	n = new Business(obj,index) ;
		else if ( type.equalsIgnoreCase("group") )	n = new Group(obj,index) ;
		else if ( type.equalsIgnoreCase("organization") )	n = new Organization(obj,index) ;
		else {
			System.out.print("\n       [ INVALID NODE TYPE ]") ;
			return ;
		}
		
		index.put(n.ID, n) ;
		
		if (indexPosts.get(n.postContent.get(0)) == null) 
			indexPosts.put(n.postContent.get(0), new HashSet<Integer>()) ; 
		indexPosts.get(n.postContent.get(0)).add(n.ID) ;
		
		if (indexName.get(n.name) == null) 
			indexName.put(n.name, new HashSet<Integer>()) ; 
		indexName.get(n.name).add(n.ID) ;
		
		if (indexType.get(n.type) == null)
			indexType.put(n.type, new HashSet<Integer>()) ;
		indexType.get(n.type).add(n.ID) ;
		System.out.print( "\n       * NEW NODE CREATED SUCCESSFULLY *" ) ;
		return ;
	}
	
	
	static void deleteNode( Scanner obj , HashMap<Integer,Node> index ) 
	{
		System.out.print("\n\n +++ DELETING AN EXISTING NODE +++") ;
		System.out.print("\n\n   o ENTER ID : ") ;
		
		int id = Integer.parseInt(obj.nextLine()) ;
		if ( index.get(id) == null ) {
			System.out.print( "\n       [ NO NODE WITH THIS USER ID WAS FOUND ]" ) ;
			return ;
		}
		
		index.remove(id) ;
		System.out.print( "\n       * NODE DELETED SUCCESSFULLY *" ) ;
		return ;
	}
	
	
	static void searchNodeByName( Scanner obj , HashMap<String,Set<Integer>> table , 
								  HashMap<Integer,Node> index ) 
	{
		System.out.print("   o ENTER NAME OF THE NODE : ") ;
		String name = obj.nextLine() ;
		
		if ( table.get(name) == null || table.get(name).size() == 0 )	{
			System.out.print( "\n       [ NO NODE WITH THIS NAME WAS FOUND ]" ) ;
			return ;
		}
		
		boolean notFound = true ;
		Set<Integer> toRemove = new HashSet<Integer>() ;
		
		for ( int i : table.get(name) ) {
			if ( index.get(i) == null )
				toRemove.add(i) ;
			else {
				index.get(i).printDetails(index) ;
				System.out.print("\n") ;
				notFound = false ;
			}
		}
		for ( int i : toRemove )
			table.get(name).remove(i) ;
		
		if ( notFound )	{
			System.out.print( "\n       [ NO NODE WITH THIS NAME WAS FOUND ]" ) ;
			return ;
		}
		return ;
	}
	
	
	static void searchNodeByType( Scanner obj , HashMap<Character,Set<Integer>> table , 
								  HashMap<Integer,Node> index ) 
	{
		System.out.print("   o ENTER TYPE OF NODE : ") ;
		char type = obj.nextLine().toUpperCase().charAt(0) ;
		
		if ( table.get(type) == null || table.get(type).size() == 0 )	{
			System.out.print( "\n       [ NO NODE WITH THIS TYPE WAS FOUND ]" ) ;
			return ;
		}
		
		boolean notFound = true ;
		Set<Integer> toRemove = new HashSet<Integer>() ;
		
		for ( int i : table.get(type) ) {
			if ( index.get(i) == null )
				toRemove.add(i) ;
			else {
				index.get(i).printDetails(index) ;
				System.out.print("\n") ;
				notFound = false ;
			}
		}
		for ( int i : toRemove )
			table.get(type).remove(i) ;
		
		if ( notFound )	{
			System.out.print( "\n       [ NO NODE WITH THIS TYPE WAS FOUND ]" ) ;
			return ;
		}
		return ;
	}
	
	
	static void searchNodeByBirthday( Scanner obj , HashMap<String,Set<Integer>> table , 
									  HashMap<Integer,Node> index ) 
	{
		System.out.print("   o ENTER DATE OF BIRTH (IN DD-MM-YYYY FORMAT) : ") ;
		String date = obj.nextLine() ;
		
		if ( table.get(date) == null || table.get(date).size() == 0 )	{
			System.out.print( "\n       [ NO NODE WITH THIS D.O.B. WAS FOUND ]" ) ;
			return ;
		}
		
		boolean notFound = true ;
		Set<Integer> toRemove = new HashSet<Integer>() ;
		
		for ( int i : table.get(date) ) {
			if ( index.get(i) == null )
				toRemove.add(i) ;
			else {
				index.get(i).printDetails(index) ;
				System.out.print("\n") ;
				notFound = false ;
			}
		}
		for ( int i : toRemove )
			table.get(date).remove(i) ;
		
		if ( notFound )	{
			System.out.print( "\n       [ NO NODE WITH THIS D.O.B. WAS FOUND ]" ) ;
			return ;
		}
		return ;
	}
	
	
	static void findLinkedNodes( Scanner obj , HashMap<Integer,Node> index ) 
	{
		System.out.print("\n\n +++ FINDING LINKED NODES +++") ;
		System.out.print("\n\n   o ENTER ID : ") ;
		
		int id = Integer.parseInt(obj.nextLine()) ;
		if ( index.get(id) == null ) {
			System.out.print("\n       [ NO NODE WITH THIS USER ID WAS FOUND ]") ;
			return ;
		}
		
		Node n = index.get(id) ;
		char type = index.get(id).type ;
		char bul = (char)8226 ;
		
		boolean notFound = true ;
		Set<Integer> toRemove = new HashSet<Integer>() ;
		
		if ( type != 'B' )
		{
			for ( int i : n.links ) 
			{
				if ( index.get(i) == null )
					toRemove.add(i) ;
				else 
				{
					System.out.print( "\n     " + bul + " LINK : RELATIONSHIP-SPECIFIC / UNDIRECTED" ) ;
					if ( type != 'I' )
						System.out.print( "\n     " + bul + " RELATIONSHIP : MEMBER" ) ;
					index.get(i).printDetails(index) ;
					System.out.print("\n") ;
					notFound = false ;
				}
			}
		}
		
		else 
		{
			for ( int i : n.links ) 
			{
				if ( index.get(i) == null )
					toRemove.add(i) ;
				else 
				{
					System.out.print( "\n     " + bul + " LINK : RELATIONSHIP-SPECIFIC / UNDIRECTED" ) ;
					if ( index.get(i).type == 'I' )
					{
						if ( ((Business)n).owners.contains(i) )
							if ( ((Business)n).customers.contains(i) ) 
								System.out.print( "\n     " + bul + " RELATIONSHIP : OWNER & CUSTOMER" ) ;
							else
								System.out.print( "\n     " + bul + " RELATIONSHIP : OWNER" ) ;
						else
							System.out.print( "\n     " + bul + " RELATIONSHIP : CUSTOMER" ) ;
					}
					index.get(i).printDetails(index) ;
					System.out.print("\n") ;
					notFound = false ;
				}
			}
		}
		
		for ( int i : toRemove )
			n.links.remove(i) ;
		
		
		toRemove.clear();
		for ( int i : n.miscLinks )
		{
			if ( index.get(i) == null )
			{
				toRemove.add(i) ;
				continue ;
			}
			System.out.print( "\n     " + bul + " LINK : GENERIC / DIRECTED" ) ;
			index.get(i).printDetails(index) ;
			System.out.print("\n") ;
			notFound = false ;
		}
		
		for ( int i : toRemove )
			n.miscLinks.remove(i) ;
		
		
		if ( notFound ) {
			System.out.print("\n       [ NO LINKED NODES FOUND ]") ;
			return ;
		}
		return ;
	}
	
	
	static void postNewContent( Scanner obj , HashMap<Integer,Node> index , HashMap<String,Set<Integer>> indexPosts ) 
	{
		System.out.print("\n\n +++ POSTING NEW CONTENT +++") ;
		System.out.print("\n\n   o ENTER ID : ") ;
		
		int id = Integer.parseInt(obj.nextLine()) ;
		if ( index.get(id) == null ) {
			System.out.print("\n       [ NO NODE WITH THIS USER ID WAS FOUND ]") ;
			return ;
		}
		
		System.out.print( "   o CONTENT FOR NEW POST : " ) ;
		String post = obj.nextLine() ;
		index.get(id).postContent.add(post) ;
		
		if (indexPosts.get(post) == null) 
			indexPosts.put(post, new HashSet<Integer>()) ; 
		indexPosts.get(post).add(id) ;
		
		System.out.print( "\n       * CONTENT POSTED SUCCESSFULLY *" ) ;
		return ;
	}
	
	
	static void printPostedContent( Scanner obj , HashMap<Integer,Node> index ) 
	{
		System.out.print("\n\n +++ DISPLAYING CONTENT POSTED BY A NODE +++") ;
		System.out.print("\n\n   o ENTER ID : ") ;
		
		int id = Integer.parseInt(obj.nextLine()) ;
		if ( index.get(id) == null ) {
			System.out.print("\n       [ NO NODE WITH THIS USER ID WAS FOUND ]") ;
			return ;
		}
		
		Node n = index.get(id) ;
		
		if ( n.postContent.size() == 0 ) {
			System.out.print("\n       [ NO CONTENT POSTED BY THIS NODE ]") ;
			return ;
		}
		
		for ( String post : n.postContent ) {
			System.out.print("\n     > "+post);
		}
		return ;
	}
	
	static void searchForPost( Scanner obj , HashMap<String,Set<Integer>> index , HashMap<Integer,Node> indexM ) 
	{
		System.out.print("\n\n +++ SEARCHING FOR CONTENT POSTED BY ANY NODE +++") ;
		System.out.print("\n\n   o ENTER CONTENT : ") ;
		
		String content = obj.nextLine().toLowerCase() ;
		boolean flag = true ;
		char bul = (char)8226 ;
		
		for ( String post : index.keySet() )
		{
			if ( ! post.toLowerCase().contains(content) ) continue ;
			
			Set<Integer> toRemove = new HashSet<Integer>() ;
			Set<Integer> toPrint = new HashSet<Integer>() ;
			for ( int i : index.get(post) )
			{
				if ( indexM.get(i) == null )
				{
					toRemove.add(i) ;
					continue ;
				}
				toPrint.add(i) ;
			}
			for ( int i : toRemove )
				index.get(post).remove(i) ;
			
			if ( toPrint.size() == 0 )	continue ;
			
			System.out.print("\n     " + bul + " CONTENT : " + post ) ;
			System.out.print("\n     " + bul + " IDs OF NODES : " ) ;
			for ( int i : toPrint )
				System.out.print( i + " " ) ;
			System.out.print("\n" ) ;
			flag = false ;
		}
		
		if ( flag )
		{
			System.out.print("\n       [ NO RELEVANT POSTS FOUND ]") ;
			return ;
		}
		
		return ;
	}
	
	
	static void printPostsByLinkedNodes( Scanner obj , HashMap<Integer,Node> index ) 
	{
		System.out.print("\n\n +++ DISPLAYING CONTENT POSTED BY ALL LINKED NODES +++") ;
		System.out.print("\n\n   o ENTER ID : ") ;
		
		int id = Integer.parseInt(obj.nextLine()) ;
		if ( index.get(id) == null ) {
			System.out.print("\n       [ NO NODE WITH THIS USER ID WAS FOUND ]") ;
			return ;
		}
		
		boolean notFound = true ;
		boolean noPosts = true ;
		Set<Integer> toRemove = new HashSet<Integer>() ;
		Node n = index.get(id) ;
		
		for ( int i : n.links ) {
			if ( index.get(i) == null ) {
				toRemove.add(i) ;
				continue ;
			}
			notFound = false ;
			for ( String p : index.get(i).postContent ) {
				noPosts = false ;
				System.out.print("\n     > " + i  + " - " + p) ;
			}
		}
		for ( int i : toRemove )
			n.links.remove(i) ;
		
		
		toRemove.clear() ;
		
		for ( int i : n.miscLinks ) {
			if ( index.get(i) == null ) {
				toRemove.add(i) ;
				continue ;
			}
			notFound = false ;
			for ( String p : index.get(i).postContent ) {
				noPosts = false ;
				System.out.print("\n     > " + i  + " - " + p) ;
			}
		}
		for ( int i : toRemove )
			n.miscLinks.remove(i) ;
		
		
		if ( notFound ) {
			System.out.print("\n       [ NO LINKED NODES FOUND ]") ;
			return ;
		}
		if ( noPosts ) {
			System.out.print("\n\n     [ NO CONTENT POSTED BY ANY OF THE LINKED NODES ]") ;
			return ;
		}
		return ;
	}
	
	
	static void printAllNodes( HashMap<Integer,Node> index ) 
	{
		System.out.print("\n\n +++ PRINTING DETAILS OF ALL NODES +++") ;
		if ( index.size() == 0 ) {
			System.out.print("\n\n       [ NO NODES IN THE RECORD ]") ;
			return ;
		}
		for ( Node n : index.values() ) {
			System.out.print("\n") ;
			n.printDetails(index) ;
		}
		return ;
	}
	
}



class Coordinates 
{
	float x ;
	float y ;
	
	public Coordinates(float x , float y) 
	{
		this.x = x ; this.y = y ;
	}
}



class Node 
{
	int ID ;
	char type ;
	String name ;
	Set<Integer> links ;
	Set<Integer> miscLinks ;
	String creationDate ;
	ArrayList<String> postContent ;
	
	
	public Node(Scanner obj, HashMap<Integer,Node> index) 
	{
		this.type = 'N' ;
		
		System.out.print( "   o USER ID : " ) ;
		int x = Integer.parseInt(obj.nextLine()) ;
		while ( index.get(x) != null ) {
			System.out.print( "       [ ID NOT AVAILABLE ]\n" ) ;
			System.out.print( "   o USER ID : " ) ;
			x = Integer.parseInt(obj.nextLine()) ;
		}
		this.ID = x ;
		
		System.out.print( "   o NAME OF THE NODE : " ) ;
		this.name = obj.nextLine() ;
		
		
		this.links = new HashSet<Integer>() ;
		this.miscLinks = new HashSet<Integer>() ;
		
		System.out.print( "   o DATE OF CREATION (IN DD-MM-YYYY FORMAT) : " ) ;
		this.creationDate = obj.nextLine() ;
		
		this.postContent = new ArrayList<String>() ;
		System.out.print( "   o CREATE AND POST CONTENT : " ) ;
		this.postContent.add(obj.nextLine()) ;
		
	}
	
	
	void printDetails( HashMap<Integer,Node> index ) 
	{
		char bul = (char)8226 ;
		System.out.print( "\n     " + bul + " ID : " ) ; System.out.print(this.ID) ;
		System.out.print( "\n     " + bul + " NAME : " ) ; System.out.print(this.name) ;
		System.out.print( "\n     " + bul + " IDs OF ALL LINKED NODES : " ) ;
		
		Set<Integer> toRemove = new HashSet<Integer>() ;
		boolean notFound = true ;
		for ( int i : this.links ) {
			if ( index.get(i) == null ) {
				toRemove.add(i) ;
				continue ;
			}
			System.out.print( i + " " ) ;
			notFound = false ;
		}
		for ( int id : toRemove )
			this.links.remove(id) ;
		
		toRemove.clear() ;
		for ( int i : this.miscLinks ) {
			if ( index.get(i) == null ) {
				toRemove.add(i) ;
				continue ;
			}
			System.out.print( i + " " ) ;
			notFound = false ;
		}
		for ( int id : toRemove )
			this.miscLinks.remove(id) ;
		
		if ( notFound )
			System.out.print( "NIL" ) ;
		
		
		notFound = true ;
		System.out.print( "\n     " + bul + " IDs OF GENERIC LINKS : " ) ;
		for ( int i : this.miscLinks ) 
		{
			System.out.print( i + " " ) ;
			notFound = false ;
		}
		if ( notFound )
			System.out.print( "NIL" ) ;
		
		
		System.out.print( "\n     " + bul + " DATE OF CREATION (IN DD-MM-YYYY FORMAT) : " ) ; 
		System.out.print(this.creationDate) ;
		System.out.print( "\n     " + bul + " POSTED CONTENT - " ) ;
		for ( String post : this.postContent ) {
			System.out.print( "\n       > " + post ) ;
		}
		return ;
	}
}



class Individual extends Node 
{
	String birthDate ;

	
	public Individual(Scanner obj, HashMap<Integer,Node> index) 
	{
		super(obj,index) ;
		this.type = 'I' ;
		System.out.print( "   o DATE OF BIRTH (IN DD-MM-YYYY FORMAT) : " ) ;
		this.birthDate = obj.nextLine() ;
		
		System.out.print( "   o NO. OF GENERIC LINKS : " ) ;
		int count = Integer.parseInt(obj.nextLine()) ;
		
		for ( int i=0 ; i<count ; i++ )
		{
			System.out.print( "     > ID OF LINKED NODE "+(i+1)+" : " ) ;
			int id = Integer.parseInt(obj.nextLine()) ;
			Node n = index.get(id) ;
			if ( n == null )
			{
				System.out.print( "         [ NO NODE WITH THIS USER ID WAS FOUND ]\n" ) ;
				i-- ; continue ;
			}
			if ( this.links.contains(id) )
			{
				System.out.print( "         [ THE NODE IS ALREADY CONNECTED VIA A RELATIONSHIP-SPECIFIC LINK ]\n" ) ;
				i-- ; continue ;
			}
			this.miscLinks.add(id) ;
		}
		
	}
	
	
	void printDetails( HashMap<Integer,Node> index ) 
	{
		char bul = (char)8226 ;
		System.out.print( "\n     " + bul + " TYPE : INDIVIDUAL" ) ;
		super.printDetails(index) ;
		System.out.print( "\n     " + bul + " DATE OF BIRTH (IN DD-MM-YYYY FORMAT) : " ) ; 
		System.out.print(this.birthDate) ;
		
		
		
		return ;
	}
}



class Business extends Node 
{
	Coordinates location ;
	Set<Integer> owners ;
	Set<Integer> customers ;

	
	public Business(Scanner obj, HashMap<Integer,Node> index) 
	{
		super(obj,index) ;
		this.type = 'B' ;
		
		System.out.print( "   o LOCATION (2D COORDINATES) - \n" ) ;
		System.out.print( "     > X-COORDINATE : " ) ;
		float x = Float.parseFloat(obj.nextLine()) ;
		System.out.print( "     > Y-COORDINATE : " ) ;
		float y = Float.parseFloat(obj.nextLine()) ;
		this.location = new Coordinates(x,y) ;
		
		this.owners = new HashSet<Integer>() ;
		System.out.print( "   o NO. OF OWNERS : " ) ;
		int count = Integer.parseInt(obj.nextLine()) ;
		for ( int i=0 ; i<count ; i++ ) 
		{
			System.out.print( "     > ID OF OWNER "+(i+1)+" : " ) ;
			int t = Integer.parseInt(obj.nextLine()) ;
			Node n = index.get(t) ;
			if ( n == null ) {
				System.out.print( "         [ NO NODE WITH THIS USER ID WAS FOUND ]\n" ) ;
				i-- ; continue ;
			}
			if ( n.type != 'I' ) {
				System.out.print( "         [ BUSINESS CAN BE OWNED ONLY BY INDIVIDUALS ]\n" ) ;
				i-- ; continue ;
			}
			this.owners.add(t) ;
			this.links.add(t) ;
			n.links.add(this.ID) ;
		}
		
		this.customers = new HashSet<Integer>() ;
		System.out.print( "   o NO. OF CUSTOMERS : " ) ;
		count = Integer.parseInt(obj.nextLine()) ;
		for ( int i=0 ; i<count ; i++ ) 
		{
			System.out.print( "     > ID OF CUSTOMER "+(i+1)+" : " ) ;
			int t = Integer.parseInt(obj.nextLine()) ;
			Node n = index.get(t) ;
			if ( n == null ) {
				System.out.print( "         [ NO NODE WITH THIS USER ID WAS FOUND ]\n" ) ;
				i-- ; continue ;
			}
			if ( n.type != 'I' ) {
				System.out.print( "         [ ONLY INDIVIDUALS CAN BE THE CUSTOMERS ]\n" ) ;
				i-- ; continue ;
			}
			this.customers.add(t) ;
			this.links.add(t) ;
			n.links.add(this.ID) ;
		}
		
		System.out.print( "   o NO. OF GENERIC LINKS : " ) ;
		count = Integer.parseInt(obj.nextLine()) ;
		
		for ( int i=0 ; i<count ; i++ )
		{
			System.out.print( "     > ID OF LINKED NODE "+(i+1)+" : " ) ;
			int id = Integer.parseInt(obj.nextLine()) ;
			Node n = index.get(id) ;
			if ( n == null )
			{
				System.out.print( "         [ NO NODE WITH THIS USER ID WAS FOUND ]\n" ) ;
				i-- ; continue ;
			}
			if ( this.links.contains(id) )
			{
				System.out.print( "         [ NODE IS ALREADY CONNECTED VIA A RELATIONSHIP-SPECIFIC LINK ]\n" ) ;
				i-- ; continue ;
			}
			this.miscLinks.add(id) ;
		}
	}
	
	
	void printDetails( HashMap<Integer,Node> index ) 
	{
		char bul = (char)8226 ;
		System.out.print( "\n     " + bul + " TYPE : BUSINESS" ) ;
		
		super.printDetails(index) ;
		
		System.out.print( "\n     " + bul + " LOCATION : " ) ;
		System.out.print( "( " + this.location.x + " , " + this.location.y + " )" ) ;
		
		System.out.print( "\n     " + bul + " IDs OF OWNERS : " ) ;
		boolean notFound = true ;
		Set<Integer> toRemove = new HashSet<Integer>() ;
		for ( int i : this.owners ) {
			if ( ! (index.get(i) != null && index.get(i).type == 'I') ) {
				toRemove.add(i) ;
				continue ;
			}
			System.out.print( i + " " ) ;
			notFound = false ;
		}
		for ( int id : toRemove )
			this.owners.remove(id) ;
		if ( notFound )
			System.out.print( "NIL" ) ;
		
		toRemove.clear() ;
		notFound = true ;
		System.out.print( "\n     " + bul + " IDs OF CUSTOMERS : " ) ;
		for ( int i : this.customers ) {
			if ( ! (index.get(i) != null && index.get(i).type == 'I') ) {
				toRemove.add(i) ;
				continue ;
			}
			System.out.print( i + " " ) ;
			notFound = false ;
		}
		for ( int id : toRemove )
			this.customers.remove(id) ;
		if ( notFound )
			System.out.print( "NIL" ) ;
		
	}
}



class Group extends Node 
{
	Set<Integer> membersIndiv ;
	Set<Integer> membersBusin ;
	
	
	public Group(Scanner obj, HashMap<Integer,Node> index) 
	{
		super(obj,index) ;
		this.type = 'G' ;
		
		this.membersBusin = new HashSet<Integer>() ;
		System.out.print( "   o NO. OF BUSINESS MEMBERS : " ) ;
		int count = Integer.parseInt(obj.nextLine()) ;
		for ( int i=0 ; i<count ; i++ ) {
			System.out.print( "     > ID OF MEMBER "+(i+1)+" : " ) ;
			int t = Integer.parseInt(obj.nextLine()) ;
			Node n = index.get(t) ;
			if ( n == null ) 
			{
				System.out.print( "         [ NO NODE WITH THIS USER ID WAS FOUND ]\n" ) ;
				i-- ; continue ;
			}
			if ( n.type != 'B' ) 
			{
				System.out.print( "         [ NODE WITH THIS ID IS NOT A BUSINESS ]\n" ) ;
				i-- ; continue ;
			}
			this.membersBusin.add(t) ;
			this.links.add(t) ;
			n.links.add(this.ID) ;
		}
		
		this.membersIndiv = new HashSet<Integer>() ;
		System.out.print( "   o NO. OF INDIVIDUAL MEMBERS : " ) ;
		count = Integer.parseInt(obj.nextLine()) ;
		for ( int i=0 ; i<count ; i++ ) 
		{
			System.out.print( "     > ID OF MEMBER "+(i+1)+" : " ) ;
			int t = Integer.parseInt(obj.nextLine()) ;
			Node n = index.get(t) ;
			if ( n == null ) 
			{
				System.out.print( "         [ NO NODE WITH THIS USER ID WAS FOUND ]\n" ) ;
				i-- ; continue ;
			}
			if ( n.type != 'I' ) 
			{
				System.out.print( "         [ NODE WITH THIS ID IS NOT AN INDIVIDUAL ]\n" ) ;
				i-- ; continue ;
			}
			this.membersIndiv.add(t) ;
			this.links.add(t) ;
			n.links.add(this.ID) ;
		}
		
		System.out.print( "   o NO. OF GENERIC LINKS : " ) ;
		count = Integer.parseInt(obj.nextLine()) ;
		
		for ( int i=0 ; i<count ; i++ )
		{
			System.out.print( "     > ID OF LINKED NODE "+(i+1)+" : " ) ;
			int id = Integer.parseInt(obj.nextLine()) ;
			Node n = index.get(id) ;
			if ( n == null )
			{
				System.out.print( "         [ NO NODE WITH THIS USER ID WAS FOUND ]\n" ) ;
				i-- ; continue ;
			}
			if ( this.links.contains(id) )
			{
				System.out.print( "         [ NODE IS ALREADY CONNECTED VIA A RELATIONSHIP-SPECIFIC LINK ]\n" ) ;
				i-- ; continue ;
			}
			this.miscLinks.add(id) ;
		}
	}
	
	
	void printDetails( HashMap<Integer,Node> index ) 
	{
		char bul = (char)8226 ;
		System.out.print( "\n     " + bul + " TYPE : GROUP" ) ;
		
		super.printDetails(index) ;
		
		System.out.print( "\n     " + bul + " IDs OF BUSINESS MEMBERS : " ) ;
		boolean notFound = true ;
		Set<Integer> toRemove = new HashSet<Integer>() ;
		for ( int i : this.membersBusin ) {
			if ( ! (index.get(i) != null && index.get(i).type == 'B') ) {
				toRemove.add(i) ;
				continue ;
			}
			System.out.print( i + " " ) ;
			notFound = false ;
		}
		for ( int id : toRemove )
			this.membersBusin.remove(id) ;
		if ( notFound )
			System.out.print( "NIL" ) ;
		
		toRemove.clear() ;
		notFound = true ;
		System.out.print( "\n     " + bul + " IDs OF INDIVIDUAL MEMBERS : " ) ;
		for ( int i : this.membersIndiv ) {
			if ( ! (index.get(i) != null && index.get(i).type == 'I') ) {
				toRemove.add(i) ;
				continue ;
			}
			System.out.print( i + " " ) ;
			notFound = false ;
		}
		for ( int id : toRemove )
			this.membersIndiv.remove(id) ;
		if ( notFound )
			System.out.print( "NIL" ) ;
		
		
	}
}



class Organization extends Node 
{
	Coordinates location ;
	Set<Integer> members ;
	
	public Organization(Scanner obj, HashMap<Integer,Node> index) 
	{
		super(obj,index) ;
		this.type = 'O' ;
		
		System.out.print( "   o LOCATION (2D COORDINATES) - \n" ) ;
		System.out.print( "     > X-COORDINATE : " ) ;
		float x = Float.parseFloat(obj.nextLine()) ;
		System.out.print( "     > Y-COORDINATE : " ) ;
		float y = Float.parseFloat(obj.nextLine()) ;
		this.location = new Coordinates(x,y) ;
		
		this.members = new HashSet<Integer>() ;
		System.out.print( "   o NO. OF MEMBERS : " ) ;
		int count = Integer.parseInt(obj.nextLine()) ;
		for ( int i=0 ; i<count ; i++ ) 
		{
			System.out.print( "     > ID OF MEMBER "+(i+1)+" : " ) ;
			int t = Integer.parseInt(obj.nextLine()) ;
			Node n = index.get(t) ;
			if ( n == null ) {
				System.out.print( "         [ NO NODE WITH THIS USER ID WAS FOUND ]\n" ) ;
				i-- ; continue ;
			}
			if ( n.type != 'I' ) {
				System.out.print( "         [ ONLY INDIVIDUALS CAN BE MEMBERS OF ORGANIZATION ]\n" ) ;
				i-- ; continue ;
			}
			this.members.add(t) ;
			this.links.add(t) ;
			n.links.add(this.ID) ;
		}
		
		System.out.print( "   o NO. OF GENERIC LINKS : " ) ;
		count = Integer.parseInt(obj.nextLine()) ;
		
		for ( int i=0 ; i<count ; i++ )
		{
			System.out.print( "     > ID OF LINKED NODE "+(i+1)+" : " ) ;
			int id = Integer.parseInt(obj.nextLine()) ;
			Node n = index.get(id) ;
			if ( n == null )
			{
				System.out.print( "         [ NO NODE WITH THIS USER ID WAS FOUND ]\n" ) ;
				i-- ; continue ;
			}
			if ( this.links.contains(id) )
			{
				System.out.print( "         [ NODE IS ALREADY CONNECTED VIA A RELATIONSHIP-SPECIFIC LINK ]\n" ) ;
				i-- ; continue ;
			}
			this.miscLinks.add(id) ;
		}
	}
	
	
	void printDetails( HashMap<Integer,Node> index ) 
	{
		char bul = (char)8226 ;
		System.out.print( "\n     " + bul + " TYPE : ORGANIZATION" ) ;
		
		super.printDetails(index) ;
		
		System.out.print( "\n     " + bul + " LOCATION : " ) ;
		System.out.print( "( " + this.location.x + " , " + this.location.y + " )" ) ;
		
		boolean notFound = true ;
		Set<Integer> toRemove = new HashSet<Integer>() ;
		System.out.print( "\n     " + bul + " IDs OF MEMBERS : " ) ;
		for ( int i : this.members ) {
			if ( ! (index.get(i) != null && index.get(i).type == 'I') ) {
				toRemove.add(i) ;
				continue ;
			}
			System.out.print( i + " " ) ;
			notFound = false ;
		}
		
		for ( int id : toRemove )
			this.members.remove(id) ;
		
		if ( notFound )
			System.out.print( "NIL" ) ;
		
	}
}
