#include <cstring>

#include <stdio.h>
//#include <conio.h>
//#include "windows.h"

#include "../const.h"
#include "flib.h"
#include "../wall.h"
#include "../player.h"
#include "../sandworm.h"
#include "../collumn.h"
#include "../offering.h"
#include "../scene.h"
#include "../game.h"

#include "TXML_Root.h"
#include "TXML_Element.h"
#include "TXML_Attribute.h"


#include "TSLL_Root.h"
#include "TXML_Parser.h"

EElementName TXML_TParser::m_eCurrentElementName = EElementName_level;



TXML_TParser::TXML_TParser(){
	//654564

}



TXML_TParser::~TXML_TParser(){


	if(m_tRoot != 0) delete m_tRoot;


}




TXML_Root * TXML_TParser::ReadXML( char * filename )
{
	char *buffer=0;
	m_tRoot = new TXML_Root();

	

	TGfxFile * pFile = GfxFileOpenRead( filename );

	if( pFile == 0 )
	{
		//GfxDbgPrintf("cannot open the file: %s\n",filename);
		return 0;
	}

	int size = GfxFileSize( pFile );

	//GfxDbgPrintf("Reading XML file: %s\n",filename);
	buffer = FMALLOC(char, size+1 );
	GfxFileRead( pFile, (void*) buffer, size );

	buffer[ size ] =0; // force cstring terminator

#if 1
	//GfxDbgPrintf("------ORIGINAL FILE---------\n");
	//GfxDbgPrintf(buffer);
	//GfxDbgPrintf("----------------------------\n");
#endif

	// analyze the file content
	char *curPosition = buffer;


	

	while( *curPosition !=0 )
	{
		
		

		char * openChar = strchr(curPosition, '<');

		if(  openChar == 0)
		{
			*curPosition = 0;
		
		}
		else{
		curPosition = m_tRoot->XMLParseElement(openChar, 0);

		}

		//GfxDbgPrintf("Fini");
		
	}
		
	// http://www.cplusplus.com/reference/clibrary/cstring/strstr/

	//delete [] buffer;
	FFREE(buffer);

	GfxFileClose(pFile);


	return m_tRoot;
}

void TXML_TParser::GetElement(TXML_Element * pElement){

	//GfxDbgPrintf("\n%s ", pElement->m_cName);
	//GfxDbgPrintf("\n%s ", pElement->m_cValue);
	GetElementByName(pElement->m_cName);
	ElementToGame(pElement);
	pElement->m_pElementChildsList->IterateList( GetElement );

	
	//pElement->m_pAttributesList->IterateList(PrintAttribute);


}
/*
void TXML_TParser::GetAttribute(TXML_Attribute * pAttribute){
	
	GfxDbgPrintf("\n	 %s ", pAttribute->m_cName);

	if(pAttribute->IsValueNumeric())
		GfxDbgPrintf("Num =  : %f ", pAttribute->GetValueNumeric());
	else
		GfxDbgPrintf("Alpha = : %s ", pAttribute->GetValueString());


}
*/
void TXML_TParser:: ElementToGame(TXML_Element * pElement){
	TXML_Attribute * pAttribute = 0;
	switch(m_eCurrentElementName)
	{
	case EElementName_wall :	{TGfxVec2 tPos ;
						TGfxVec2 tSize ;
						float fAngle;

						pAttribute = pElement->FindAttribute("rotation");
						if(pAttribute==0)
						return;	else fAngle = pAttribute->GetValueNumeric() * PI /180.0f  ;

						pAttribute = pElement->FindAttribute("posX");
						if(pAttribute==0)
						return;	else tPos.x = pAttribute->GetValueNumeric();

						pAttribute = pElement->FindAttribute("posZ");
						if(pAttribute==0)
						return;	else tPos.y =- pAttribute->GetValueNumeric();

						pAttribute = pElement->FindAttribute("sizeX");
						if(pAttribute==0)
						return;	else tSize.x = pAttribute->GetValueNumeric()/2.0f;

						pAttribute = pElement->FindAttribute("sizeZ");
						if(pAttribute==0)
						return;	else tSize.y = pAttribute->GetValueNumeric()/2.0f;

						pAttribute = pElement->FindAttribute("shape");
						if(pAttribute==0)
							return;	else    {

								//GfxDbgPrintf(  pAttribute->GetValueString() );

								if ( !strcmp( pAttribute->GetValueString() , "Box")) {

								
									TGame::m_tScene->m_pWallList[TGame::m_tScene->m_iWallCount]	= new TWall(tSize,tPos,fAngle, EGfxColor_White,0);
									TGame::m_tScene->m_pWallList[TGame::m_tScene->m_iWallCount]->AddHitBox(tSize,TGfxVec2(0,0));			
									TGame::m_tScene->m_iWallCount ++;	
							
						
						

								}else{

										TGame::m_tScene->m_pWallList[TGame::m_tScene->m_iWallCount]	= new TWall(tSize,tPos,0, EGfxColor_White,360);
										TGame::m_tScene->m_pWallList[TGame::m_tScene->m_iWallCount]->AddHitBox(tSize.x*2.0f,TGfxVec2(0,0));	
										TGame::m_tScene->m_iWallCount ++;				
						
						

								}

						};




					
		
						break;}

	case EElementName_player:{

						TGfxVec2 tPos ;
						TGfxVec2 tSize ;
						pAttribute = pElement->FindAttribute("posX");
						if(pAttribute==0)
						return;	else tPos.x = pAttribute->GetValueNumeric();

						pAttribute = pElement->FindAttribute("posZ");
						if(pAttribute==0)
						return;	else tPos.y = -pAttribute->GetValueNumeric();

						TGame::m_tScene->m_pPlayer->Position(tPos);



						break;
						}


	case EElementName_sandworm :{

						TGfxVec2 tPos ;
						TGfxVec2 tSize ;
						pAttribute = pElement->FindAttribute("posX");
						if(pAttribute==0)
						return;	else tPos.x = pAttribute->GetValueNumeric();

						pAttribute = pElement->FindAttribute("posZ");
						if(pAttribute==0)
						return;	else tPos.y = pAttribute->GetValueNumeric();

						TGame::m_tScene->m_pSandWorm->Position(tPos);



						break;
						}

						


	case EElementName_Column : 



						if(TGame::m_tScene->m_iColumnCount <TGame::m_tScene->MAX_ColumnS)
						{			
						
							TGfxVec2 tPos ;
						
						pAttribute = pElement->FindAttribute("posX");
						if(pAttribute==0)
						return;	else tPos.x = pAttribute->GetValueNumeric();

						pAttribute = pElement->FindAttribute("posZ");
						if(pAttribute==0)
						return;	else tPos.y = - pAttribute->GetValueNumeric();



							TGame::m_tScene->m_pColumnList[TGame::m_tScene->m_iColumnCount] =  new TColumn(  tPos ,0.0f, 1.0f,  GfxColor(150,70,0,255),    TGame::m_tScene->m_iColumnCount);

						
							TGame::m_tScene->m_iColumnCount++;
						
						}


						break;

	case EElementName_reward : {
						TGfxVec2 tPos ;
						
						pAttribute = pElement->FindAttribute("posX");
						if(pAttribute==0)
						return;	else tPos.x = pAttribute->GetValueNumeric();

						pAttribute = pElement->FindAttribute("posZ");
						if(pAttribute==0)
						return;	else tPos.y = - pAttribute->GetValueNumeric();

						pAttribute = pElement->FindAttribute("starter");
						bool bValue =false;

						if( !strcmp(pAttribute->GetValueString(), "true"))
						{
							bValue =true;
						
						}else { 
							bValue = false;
						}



						if(TGame::m_tScene->m_iOfferingCount <TGame::m_tScene->MAX_OFFERING){
														

							TGame::m_tScene->m_pOfferingList[TGame::m_tScene->m_iOfferingCount] =  new TOffering(  tPos,0, 1.0f,  GfxColor(255,70,198,255), bValue, bValue);
							
							TGame::m_tScene->m_iOfferingCount++;
								TGame::m_tScene->m_iTotalEgg++;




							//TGame::m_tScene->m_iTotalEgg++;
						}

						#ifdef TFA_FRESH
							lua_pushinteger(GfxFreshLuaState(), TGame::m_tScene->m_iTotalEgg);
							LuaCallGlobal(GfxFreshLuaState(), "SetEggTotal");
						#endif

		
		
		
		
		
		break;}

	
	case EElementName_cameraborder :{

						TGfxVec2 tSize ;
						pAttribute = pElement->FindAttribute("left");
						if(pAttribute==0)
						return;	
						else tSize.x = pAttribute->GetValueNumeric();

						pAttribute = pElement->FindAttribute("right");
						if(pAttribute==0)
						return;	
						else tSize.y = pAttribute->GetValueNumeric();

						TGame::m_tScene->m_tMapSizeX = tSize;

						pAttribute = pElement->FindAttribute("up");
						if(pAttribute==0)
						return;	
						else tSize.x = pAttribute->GetValueNumeric();

						pAttribute = pElement->FindAttribute("down");
						if(pAttribute==0)
						return;	
						else tSize.y = pAttribute->GetValueNumeric();

						TGame::m_tScene->m_tMapSizeY = tSize;

						break;
	
	
	
					}
	}



}



void PrintAttribute(TXML_Attribute * pAttribute){

	GfxDbgPrintf("\n	 %s ", pAttribute->m_cName);

	if(pAttribute->IsValueNumeric())
		GfxDbgPrintf("Num =  : %f ", pAttribute->GetValueNumeric());
	else
		GfxDbgPrintf("Alpha = : %s ", pAttribute->GetValueString());
}

void PrintName(TXML_Element * pElement){

	GfxDbgPrintf("\n%s ", pElement->m_cName);
	//GfxDbgPrintf("\n%s ", pElement->m_cValue);
	pElement->m_pElementChildsList->IterateList(PrintName);
	pElement->m_pAttributesList->IterateList(PrintAttribute);

}




void TXML_TParser::DoXML(char * filename){

	
	m_tRoot = ReadXML(filename);



	


}

void TXML_TParser::ExtractXML(){

	
	m_tRoot->m_pRootElementsList->IterateList(GetElement);


}



bool TXML_TParser::CompareStringValue( const char * pStr1, const char * pStr2 )
{
	if( strcmp(pStr1,pStr2) == 0 )return false; else return true;
}


void TXML_TParser::GetElementByName(const char * pStrElementName)
{
	if(  !strcmp(pStrElementName, "level"))
	{
		m_eCurrentElementName = EElementName_level;
		return;	
	}

	if( !strcmp(pStrElementName, "playerspawn"))
	{
		m_eCurrentElementName = EElementName_player;
		return;	
	}

	if( !strcmp(pStrElementName, "column"))
	{
		m_eCurrentElementName = EElementName_Column;
		return;	
	}

	if(! strcmp(pStrElementName, "block"))
	{
		m_eCurrentElementName = EElementName_wall;
		return;	
	}

	if( !strcmp(pStrElementName, "wormspawn"))
	{
		m_eCurrentElementName = EElementName_sandworm;
		return;	
	}

	if( !strcmp(pStrElementName, "cameraborder"))
	{
		m_eCurrentElementName = EElementName_cameraborder;
		return;	
	}

	if( !strcmp(pStrElementName, "reward"))
	{
		m_eCurrentElementName = EElementName_reward;
		return;	
	}
}



/*
void TXML_TParser::GetAttributeByName(const char * pStrAttributeName)
{
	if(  strcmp(pStrAttributeName, "rotation"))
	{
		m_eCurrentAttributeName = EAttributeName_angle;
		return;	
	}

	if(  strcmp(pStrAttributeName, "posX"))
	{
		m_eCurrentAttributeName = EAttributeName_posX;
		return;	
	}

		if(  strcmp(pStrAttributeName, "posY"))
	{
		m_eCurrentAttributeName = EAttributeName_posX;
		return;	
	}

	if(  strcmp(pStrAttributeName, "sizeX"))
	{
		m_eCurrentAttributeName = EAttributeName_sizeX;
		return;	
	}

	if(  strcmp(pStrAttributeName, "sizeY"))
	{
		m_eCurrentAttributeName = EAttributeName_sizeY;
		return;	
	}
}

*/

