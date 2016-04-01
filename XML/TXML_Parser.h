#ifndef TXML_TPARSER_H_INCLUDED
#define TXML_TPARSER_H_INCLUDED

enum EElementName{

	EElementName_level,
	EElementName_wall,
	EElementName_Column,
	EElementName_player,
	EElementName_sandworm,
	EElementName_reward,
	EElementName_cameraborder
};



class TXML_Element;

class TXML_TParser{

	

public :

	TXML_TParser();
		~TXML_TParser();

	static EElementName m_eCurrentElementName;
	class TXML_Root * m_tRoot;
	//EEAttributeName m_eCurrentAttributeName;

	

	class TXML_Root * ReadXML( char * filename );
	void  DoXML( char * filename );
	void ExtractXML();

	static void TXML_TParser::GetElement( TXML_Element * pElement);






	static void GetElementByName( const char * cChar );
	static void GetAttributeByName(  const char * cChar);

	static void ElementToGame( TXML_Element * pElement);



	bool CompareStringValue( const char * pStr1, const char * pStr2 );
	void AssignAttributeValue();

	








};

#endif