// POP 2018-01-16 projekt 2 £aszczuk Przemys³aw EiT 3 171869 	DEV-C++    TDM-GCC 4.9.2 64-bit Release

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

int main()
{	
	string linia;
	fstream ifconfig, sshd, backup, sshd2;
	
	ifconfig.open( "ifconfig.txt", ios::in);
	sshd.open( "sshd_config.txt", ios::in);
	backup.open( "backup.txt", ios::out);
	sshd2.open( "sshd_config2.txt", ios::out);

			//Funkcje odpowiedzialne za wpisanie wymaganych danych do pliku backup.txt	
		    while (!sshd.eof()){
		    	
		        getline(sshd,linia);
		        if (linia.find('#') != string::npos) 
				continue;
		    	if (linia.find("Port") != string::npos){
		        	
		            size_t poczatek = linia.find_first_of("123456789");
		            size_t koniec = linia.substr(poczatek, linia.length()).find_first_of(" ");
		            
		            backup << "Port serwera SSH: " << linia.substr(poczatek,koniec) << endl;
		            continue;
		       	}
		    }
			//Powrot na gore pliku
			sshd.clear();
	   		sshd.seekg(0,ios::beg);
	   		bool eth0=false,nieByloInet=true,bylHwadr=false,wypisaloIP=false;
		    while (!ifconfig.eof()){
		    
	        	getline(ifconfig,linia);	
				if (linia.find("eth0") != string::npos)
		    	eth0=true;
	        	if (eth0){
	            	if (linia.find("inet addr") != string::npos and nieByloInet){
	               		nieByloInet=false;
	                	size_t poczatek = linia.find_first_of("123456789");
	                	size_t koniec = linia.substr(poczatek, linia.length()).find_first_of(" ");
	                	backup << "Numer IP interfejsu eth0: " << linia.substr(poczatek,koniec) << endl;
	                	wypisaloIP=true;
	            	}
	        	}
			}
			ifconfig.clear();
   			ifconfig.seekg(0,ios::beg);
   			
			while (!ifconfig.eof()){
		    getline(ifconfig,linia);	
				if (linia.find("eth0") != string::npos)
		    	eth0=true;
				if (eth0){
		    		if (linia.find("HWaddr") != string::npos and !bylHwadr and wypisaloIP){
	                	bylHwadr=true;
	                	size_t poczatek = linia.find("HWaddr");
	                	string dlugosc = "HWaddr ";
	                	poczatek = poczatek + dlugosc.length();
	                	size_t koniec = linia.substr(poczatek, linia.length()).find_first_of(" ");
	                	backup << "Numer MAC karty Ethernet (eth0): " << linia.substr(poczatek,linia.length()) << endl;
	            	}
	        	}	
	    	}
    	
    		backup << "Lista plikow z kluczami szyfrujacymi: " << endl;
    		while (!sshd.eof()) {
        		getline(sshd,linia);
        	
        		if (linia.find('#') != string::npos) continue;
        			if (linia.find("HostKey") != string::npos){	
            			size_t poczatek = linia.find("HostKey");
            			string dlugosc = "HostKey ";
            			poczatek = poczatek + dlugosc.length();
            			backup << linia.substr(poczatek,linia.length()) << endl;
        			}
    		}
    	
    		sshd.clear();
   			sshd.seekg(0,ios::beg);
   			backup << "Rodzaj zdalnego dostepu dla superuzytkownika: ";
   			
    	 	while (!sshd.eof()){
			getline(sshd,linia);
        		if (linia.find('#') != string::npos) 
				continue;
        			if (linia.find("PermitRootLogin") != string::npos){	
            			size_t poczatek = linia.find("PermitRootLogin");
            			string dlugosc = "PermitRootLogin ";
            			poczatek = poczatek + dlugosc.length();
            			backup << linia.substr(poczatek,linia.length()) << endl;
        			}
    		}
    		
    				
			sshd.clear();
   			sshd.seekg(0,ios::beg);
   			bool bylBanner=false;
   			
    	 	while (!sshd.eof()){
    		
				getline(sshd,linia);
        		if (linia.find('#') != string::npos)
				continue;
        			if (linia.find("Banner") != string::npos){
            			size_t poczatek = linia.find("Banner");
            			string dlugosc = "Banner ";
            			poczatek = poczatek + dlugosc.length();
            			backup << linia.substr(poczatek,linia.length()) << endl;
            			bylBanner=true;
        			}
    		}
			if(bylBanner==false)
			backup << "Komunikat powitalny w konsoli: niezdefiniowany" << endl;
			
			cout << "Wpisano szukane frazy do pliku backup.txt," << endl;
			
			//  Funkcja odpowiedzialna za przepisanie pliku sshd_config do sshd_config2 i zmianê danych		
			sshd.clear();
   			sshd.seekg(0,ios::beg);
   			
			string linijka;
			while(!sshd.eof()){
			
				getline(sshd,linijka);
				if (linijka.find("Port") != string::npos)
				sshd2 << "Port 23" << endl;
								
				else if (linijka.find("PermitRootLogin") != string::npos)
            	sshd2 << "PermitRootLogin no" << endl;
            	
	       		else if(linijka.find("Banner") != string::npos)
	       		sshd2 << "#Banner /etc/hello.txt" << endl;
	       		
				else
				sshd2 << linijka << endl;
			}
			cout << "oraz zmieniono ustawienia pliku sshd_config i zapisano w pliku sshd_config2"
				 << endl;
			
return 0;	
}
