#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>

 
using namespace std;
 
const int WYS = 4;
const int SZER = 4;
 
const int NIC = 0;
const int GRACZ = 1;	
const int BOT = 2;
 
const char PION_GRACZ[]={' ','c','b'};
const char KOLUMNA_LITERA[]={'A','B','C','D'};
 
string NAZWA_GRACZ[]={"Nikt","Gracz","Bot"};
//funkcja wpisuje w tablice plansza GRACZ,NIC,BOT
void resetuj_plansze( int plansza[WYS][SZER] );
void wypisz_plansze( int plansza[WYS][SZER] );

//Sprawdzenie czy gracz dobrze podaje wspolrzedne pionkow
void ruch( int plansza[WYS][SZER] );

//przemieszczenie pionka 
bool przesun( int plansza[WYS][SZER], int gracz, int wiersz_skad, int kolumna_skad, int wiersz_dokad, int kolumna_dokad );
 
int przeciwnik( int gracz);
 
bool czyBlokada(int plansza[WYS][SZER],int gracz);
int ilePionkow(int plansza[WYS][SZER],int gracz);
 
bool bicieBot(int plansza[WYS][SZER]);
bool ruchBot(int plansza[WYS][SZER]);
 
int main(){
	
    srand( time( NULL ) );
   
    cout << "Podaj nazwe gracza: ";
    cin >> NAZWA_GRACZ[GRACZ];
   
    int plansza[WYS][SZER];
    resetuj_plansze(plansza);
    int zwyciezca=NIC;
   
    do {

        wypisz_plansze(plansza);

       
        if (czyBlokada(plansza, BOT) ){
            cout << "Wygrana przez blokade. ";
            zwyciezca = GRACZ;
            break;
        }
       
        if (ilePionkow(plansza, BOT) <= 1){
            cout << "Wygrana przez zbicie 3 pionkow przeciwnika. ";
            zwyciezca = GRACZ;
            break;
        }
               
     	if ( !( bicieBot( plansza ) ) ) 
          	if ( !( ruchBot( plansza ) ) ){
				zwyciezca=GRACZ;
				
				break;
			}

        if (czyBlokada(plansza, GRACZ) ){
            wypisz_plansze(plansza);
			cout << "Wygrana przez blokade. ";
            zwyciezca = BOT;
            
			break;
        }
       
       
        if (ilePionkow(plansza, GRACZ) <= 1){
            wypisz_plansze(plansza);
			cout << "Wygrana przez zbicie 3 pionkow gracza: "<<NAZWA_GRACZ[GRACZ];
            zwyciezca = BOT;
			break;
        }
        
   	    wypisz_plansze(plansza);
   	    
   	    cout<<"Ilosc pionkow gracza("<<NAZWA_GRACZ[GRACZ]<<"): "<<ilePionkow(plansza, GRACZ)
		    <<endl<<"Ilosc pionkow BOTA: "<<ilePionkow(plansza, BOT)<<endl;
   
		ruch(plansza);
									
       	wypisz_plansze(plansza);	
    	
		
		
		
			
    			
       
    } while( zwyciezca == NIC );
   
    cout << "Zwyciezca: " <<"("<<NAZWA_GRACZ[zwyciezca]<<")";
    return zwyciezca;
   
}
 
void resetuj_plansze( int plansza[WYS][SZER] ){
    for (int i=0;i<WYS;i++)
    
        for (int j=0;j<SZER;j++)
            if(i==0)
                plansza[i][j]=GRACZ;
            else if(i==WYS-1)
                plansza[i][j]=BOT;
            else
                plansza[i][j]=NIC;
}
 
void wypisz_plansze( int plansza[WYS][SZER] ){
   
    cout << endl;
    system("CLS"); 
    
    for (int i=0;i<WYS;i++){
        cout<<setw(2)<<WYS-i<<" |";
        
        for (int j=0;j<SZER;j++){
            cout<< PION_GRACZ[ plansza[i][j] ] << "|" ;
        }
        cout<<endl;
    }
    cout<<"    ";
    char kolumna='A';
    for (int i=0;i<SZER;i++){
        cout<<kolumna++<<" ";
    }
    cout<<endl<<endl;
}
 
void ruch( int plansza[WYS][SZER] ){
   
    char kolumna_litera;
    int kolumna_skad,wiersz_skad;
   
    cout<<"Tura gracza: (" << NAZWA_GRACZ[GRACZ]<<"), majacego pionki: ("<< PION_GRACZ[GRACZ]<< ")" << endl;
    do {
        cout<<"Podaj pole pionka, ktorym chcesz ruszyc: ";
        cin>>kolumna_litera>>wiersz_skad;
           
        if(kolumna_litera == 'A' or kolumna_litera == 'a' )
            kolumna_skad = 0;
        else if(kolumna_litera == 'B' or kolumna_litera == 'b'  )
            kolumna_skad = 1;
        else if(kolumna_litera == 'C' or kolumna_litera == 'c'  )
            kolumna_skad = 2;
        else if(kolumna_litera == 'D' or kolumna_litera == 'd'  )
            kolumna_skad = 3;
        else
            continue;  
       
        if(wiersz_skad<=0 or wiersz_skad>WYS)
            continue;
           
        wiersz_skad=WYS-wiersz_skad;
       
        if(plansza[wiersz_skad][kolumna_skad] != GRACZ ){
			cout<<"Nie ma tu twojego pionka :( "<<endl;
            continue;
        }
   
        break;
    }while(1);
   
   
    int kolumna_dokad,wiersz_dokad;
    bool byl_ruch=false;
   
    do{
       
        cout<<"Podaj pole, na ktore chcesz sie ruszyc: ";
        cin>>kolumna_litera>>wiersz_dokad;
        cout<<endl;
           
        if(kolumna_litera == 'A' or kolumna_litera == 'a' )
            kolumna_dokad = 0;
        else if(kolumna_litera == 'B' or kolumna_litera == 'b'  )
            kolumna_dokad = 1;
        else if(kolumna_litera == 'C' or kolumna_litera == 'c'  )
            kolumna_dokad = 2;
        else if(kolumna_litera == 'D' or kolumna_litera == 'd'  )
            kolumna_dokad = 3;
        else
            continue;
       
        if( wiersz_dokad<=0 or wiersz_dokad>WYS)
            continue;
           
        wiersz_dokad=WYS-wiersz_dokad;
       
        if( kolumna_skad == kolumna_dokad and  wiersz_skad == wiersz_dokad  )
            continue;
       
        byl_ruch = przesun(plansza, GRACZ, wiersz_skad, kolumna_skad, wiersz_dokad, kolumna_dokad );
       
    }while(!byl_ruch);
   
    cout << "Wykonam ruch z " << KOLUMNA_LITERA[kolumna_skad] << WYS-wiersz_skad
         << " na " << KOLUMNA_LITERA[kolumna_dokad] << WYS-wiersz_dokad << endl;
}
 
bool przesun( int plansza[WYS][SZER], int gracz, int wiersz_skad, int kolumna_skad, int wiersz_dokad, int kolumna_dokad ){
   
   
    if(plansza[wiersz_dokad][kolumna_dokad]==NIC){ // przesuniecie
   
        if( ( abs(wiersz_skad-wiersz_dokad)==1 and kolumna_skad == kolumna_dokad )
        or  ( abs(kolumna_skad-kolumna_dokad)==1 and wiersz_skad == wiersz_dokad ) ){
       
            swap(plansza[wiersz_skad][kolumna_skad],plansza[wiersz_dokad][kolumna_dokad]);
            return true;
       
        }
        return false;
    }
    else if (plansza[wiersz_dokad][kolumna_dokad]==BOT ){ // bicie
       
        if ( wiersz_skad < wiersz_dokad ) // W DÓ£
            if (!(plansza[wiersz_skad+1][kolumna_skad]==GRACZ and plansza[wiersz_skad+2][kolumna_skad]==NIC))
                return false;
           
        if ( wiersz_skad > wiersz_dokad ) // W GÓRÊ
            if (!(plansza[wiersz_skad-1][kolumna_skad]==GRACZ and plansza[wiersz_skad-2][kolumna_skad]==NIC))
                return false;
                   
        if ( kolumna_skad < kolumna_dokad ) // W PRAWO
            if (!(plansza[wiersz_skad][kolumna_skad+1]==GRACZ and plansza[wiersz_skad][kolumna_skad+2]==NIC))
                return false;
         
        if ( kolumna_skad > kolumna_dokad ) // W LEWO
            if (!(plansza[wiersz_skad][kolumna_skad-1]==GRACZ and plansza[wiersz_skad][kolumna_skad-2]==NIC))
                return false;
                           
        plansza[wiersz_dokad][kolumna_dokad] = GRACZ;
        plansza[wiersz_skad][kolumna_skad] = NIC;
       
        return true;
    }
}
 
int przeciwnik( int gracz){
   
    if (gracz == GRACZ )
        return BOT;
    return GRACZ;
}
 
bool czyBlokada(int plansza[WYS][SZER],int gracz){
   
    for (int i=0;i<WYS;i++)
       
        for (int j=0;j<SZER;j++){
           
            if( plansza[i][j] == gracz ){
               
                if(i+1<WYS and plansza[i+1][j]==NIC ){  // w dó³
               
                    return false;
                }
                else if (i-1>=0 and plansza[i-1][j]==NIC ){ // w gore
               
                    return false;
                }
                else if (j+1<SZER and plansza[i][j+1]==NIC ){    // w prawo
               
                    return false;
                }
                else if (j-1>=0 and plansza[i][j-1]==NIC ){ // w lewo
               
                    return false;
                }
                else
                    if(i+3<WYS and plansza[i+1][j]==gracz and plansza[i+2][j]==NIC and plansza[i+3][j]==przeciwnik(gracz ) ){   //W dó³ sprawdzamy czy jest wgl w tablicy element
                        return false;
                    }
                    else if (i-3>=0 and plansza[i-1][j]==gracz and plansza[i-2][j]==NIC and plansza[i-3][j]==przeciwnik(gracz ) ){   // w gore
                   
                        return false;
                    }
                    else if (j+3<SZER and plansza[i][j+1]==gracz and plansza[i+2][j]==NIC and plansza[i][j+3]==przeciwnik(gracz ) ){     // w prawo
                                           
                        return false;
                    }
                    else if (j-3>=0 and plansza[i][j-1]==gracz and plansza[i][j-2]==NIC and plansza[i][j-3]==przeciwnik(gracz ) )  // w lewo
                        return false;
            }
        }      
       
    return true;
}
 
int ilePionkow(int plansza[WYS][SZER],int gracz){
   
    int ile=0;
   
    for (int i=0;i<WYS;i++)
        for (int j=0;j<SZER;j++)
            if (plansza[i][j] == gracz )
                ile++;
   
    return ile;
   
}
 
bool bicieBot(int plansza[WYS][SZER]){
      
    for (int i=0;i<WYS;i++)
       
        for (int j=0;j<SZER;j++){
           
            if(plansza[i][j]==BOT){
               
                if(i+3<WYS and plansza[i+1][j]==BOT and plansza[i+2][j]==NIC and plansza[i+3][j]==GRACZ ){   // w dó³
 
                    plansza[i+3][j]=BOT;
                    plansza[i][j]=NIC;
                    return true;
                }
                else if (i-3>=0 and plansza[i-1][j]==BOT and plansza[i-2][j]==NIC and plansza[i-3][j]==GRACZ ){   // w gore
 
                    plansza[i-3][j]=BOT;
                    plansza[i][j]=NIC;
                    return true;
                }
                else if (j+3<SZER and plansza[i][j+1]==BOT and plansza[i+2][j]==NIC and plansza[i][j+3]==GRACZ ){     // w prawo
               
                    plansza[i][j+3]=BOT;
                    plansza[i][j]=NIC;
                    return true;
                }
                else if (j-3>=0 and plansza[i][j-1]==BOT and plansza[i][j-2]==NIC and plansza[i][j-3]==GRACZ ){  // w lewo
                                                                       
                    plansza[i][j-3]=BOT;
                    plansza[i][j]=NIC;
                    return true;
                }
            }
        }    
    
	return false;
}
 
bool ruchBot(int plansza[WYS][SZER]){
   
    int pionki = ilePionkow( plansza, BOT );
    int pionek = ( rand() % pionki ) + 1;
   
    do{
           
        for (int i=0;i<WYS;i++)
           
            for (int j=0;j<SZER;j++){
               
                if ( plansza[i][j] == BOT )
                    pionek--;
                   
                if ( plansza[i][j] == BOT and pionek <= 0 ){    //pionek zosta³ wybrany
                                   
                    int ruch = ( rand() % 4 );  // losowanie ruchu
                   
                    do{
           
                            switch(ruch){
                                                   
                                case 0:
                                    if(i+1<WYS and plansza[i+1][j]==NIC ){      // w dol
                                        swap(plansza[i][j],plansza[i+1][j]);
                                        return true;
                                    }
                                   
                                case 1:
                                    if (i-1>=0 and plansza[i-1][j]==NIC ){      // w gore                   
                                        swap(plansza[i][j],plansza[i-1][j]);
                                        return true;
                                    }
                                   
                                case 2:
                                    if (j+1<SZER and plansza[i][j+1]==NIC ){    // w prawo                          
                                        swap(plansza[i][j],plansza[i][j+1]);
                                        return true;
                                    }
                                   
                                case 3:
                                    if (j-1>=0 and plansza[i][j-1]==NIC ){       // w lewo                           
                                        swap(plansza[i][j],plansza[i][j-1]);
                                        return true;
                                    }
                                   
                                default:{
                                    if ( ruch<=0 ){
                                        ruch = -1;
                                    }
                                }
                            }
                           
                        if ( ruch != -1 )
                            ruch = 0;
                    } while( ruch != -1);
                }
            }
               
    } while(pionek <= 1-pionki);
   
    return false;
}
