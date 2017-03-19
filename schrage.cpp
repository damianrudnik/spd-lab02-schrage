#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstring>
#include <new>

using namespace std;

int iIndexZadan = 0;

struct Zadanie {
        int kolejnosc;//kolejnosc zadania
        int r;//czas przygotowania
        int p;//czas na maszynie
        int q;//czas stygniecia
};
//Zadanie TabZadan[1001]; //deklaracja tablicy zadan
//int kolejnosc[1001];

unsigned int max(unsigned int x, unsigned int y){ return (x<=y)?y:x; }
unsigned int min(unsigned int x, unsigned int y){ return (x<=y)?x:y; }
int cmax(Zadanie Tab[], unsigned int rozmiar){
    unsigned int i, t=0,u=0;
    for (i=0;i<rozmiar;i++){
        t=max(t,Tab[i].r)+Tab[i].p;
        u=max(u,t+Tab[i].q);
    }
    return u;
}

istream& operator>> (istream& wejscie, Zadanie& zad){
    zad.kolejnosc = ++iIndexZadan;
    wejscie >> zad.r >> zad.p >> zad.q;
    return wejscie;
}
ostream& operator<< (ostream& wyjscie, const Zadanie& zad){
    cout << zad.r << " - " << zad.p << " - " << zad.q << endl; 
    return wyjscie;
}
// sortowanie przez kopcowanie tablicy zadan z wyborem 1-r, 2-p, 3-q
void heapsort(Zadanie arr[], unsigned int N, int rpq){ //http://www.codecodex.com/wiki/Heapsort#C.2B.2B
    unsigned int n = N, i = n/2, parent, child;  
    Zadanie t;  
    
    for (;;) { /* Loops until arr is sorted */  
        if (i > 0) { /* First stage - Sorting the heap */  
            i--;           /* Save its index to i */  
            t = arr[i];    /* Save parent value to t */  
        } else {     /* Second stage - Extracting elements in-place */  
            n--;           /* Make the new heap smaller */  
            if (n == 0) return; /* When the heap is empty, we are done */  
            t = arr[n];    /* Save last value (it will be overwritten) */  
            arr[n] = arr[0]; /* Save largest value at the end of arr */  
        }  
    
        parent = i; /* We will start pushing down t from parent */  
        child = i*2 + 1; /* parent's left child */  
    
        /* Shift operation - pushing the value of t down the heap */  
        while (child < n) { 
            if (rpq==1){
                if (child + 1 < n  &&  arr[child + 1].r > arr[child].r) {  
                    child++; /* Choose the largest child */  
                } 
            }else if (rpq == 2){
                if (child + 1 < n  &&  arr[child + 1].p > arr[child].p) {  
                    child++; /* Choose the largest child */  
                }
            }else if (rpq == 3){
                if (child + 1 < n  &&  arr[child + 1].q > arr[child].q) {  
                    child++; /* Choose the largest child */  
                }
            }
            //if (child + 1 < n  &&  arr[child + 1] > arr[child]) {  
            //    child++; /* Choose the largest child */  
            //}  
            if (rpq==1){
                if (arr[child].r > t.r) { /* If any child is bigger than the parent */  
                    arr[parent] = arr[child]; /* Move the largest child up */  
                    parent = child; /* Move parent pointer to this child */  
                    //child = parent*2-1; /* Find the next child */  
                    child = parent*2+1; /* the previous line is wrong*/  
                } else {  
                    break; /* t's place is found */  
                }
            }else if (rpq == 2){
                if (arr[child].p > t.p) { /* If any child is bigger than the parent */  
                    arr[parent] = arr[child]; /* Move the largest child up */  
                    parent = child; /* Move parent pointer to this child */  
                    //child = parent*2-1; /* Find the next child */  
                    child = parent*2+1; /* the previous line is wrong*/  
                } else {  
                    break; /* t's place is found */  
                } 
            }else if (rpq == 3){
                if (arr[child].q > t.q) { /* If any child is bigger than the parent */  
                    arr[parent] = arr[child]; /* Move the largest child up */  
                    parent = child; /* Move parent pointer to this child */  
                    //child = parent*2-1; /* Find the next child */  
                    child = parent*2+1; /* the previous line is wrong*/  
                } else {  
                    break; /* t's place is found */  
                } 
            }
        }  
        arr[parent] = t; /* We save t in the heap */  
    }  
}

void fdr(Zadanie Tab[], int arr[], unsigned int rozmiar){
    heapsort(Tab,rozmiar,1);

    /*int t=0,k=0,cmaks=0;
    Zadanie G[100]; //deklaracja tablicy gotowych zadan
    while() {
        while( && Tab[j].r <= t){
            e = Tab[j].r;
            
        }
    }
    */
    for (unsigned int i = 0; i < rozmiar; i++){
        arr[i] = Tab[i].kolejnosc;
    }

}

string itos(int a) {
    string sign = a<0?"-":"";
    string result = a>0?string(1,(a%10+'0')):string(1,((a=-a)%10+'0'));
    (a/=10)>0?result=itos(a)+result:result;
    return sign+result;
}

int main(){
    
    unsigned int LiczbaZadan = 0, index = 0;
    bool xFirst=1;
    string line, filename;

    cout<<"Generuje odpowiedzi dla wszystkich plikow.\n###############################################\n\n";
    
    for (int iNrPliku = 1; iNrPliku<=9;iNrPliku++){ // odczyt, szeregowanie i zapis wyniku do plikow
        filename = itos(iNrPliku);
        ifstream myfile ("SCHRAGE"+filename+".DAT");
        cout << "Odczytuje plik SZCHRAGE"+filename+".DAT\n";
        xFirst=1;
        int idx =0;
        if (myfile.is_open()){
            getline (myfile,line);
            istringstream dane(line);
            dane >> LiczbaZadan;
            cout << "  Liczba zadan: " << LiczbaZadan<<"\n";
            myfile.close();
        }else cout << "Unable to open file1";

        int *kolejnosc = new int[LiczbaZadan];
        Zadanie *TabZadan = new Zadanie[LiczbaZadan];

        ifstream myfile2 ("SCHRAGE"+filename+".DAT");
        if (myfile2.is_open()){
            while (getline (myfile2,line) ){
                istringstream dane2(line);
                if (xFirst==1){
                    xFirst = 0;
                }else{
                    ++idx;
                    dane2 >> TabZadan[index]; //wgranie danych do tablicy struktur
                    //cout <<"   " << idx<<": "<<TabZadan[index]; //wyswietlenie danych
                    index++;
                }
            }   
            cout << "  Odczytano plik z danymi.\n";
            myfile2.close();
        }else cout << "Unable to open file2"; 
        // obsluga algorytmu, czyli petle zamieniajace kolejnosc dzialan
        cout<<"  Obliczanie kolejnosci. \n";
        fdr(TabZadan, kolejnosc, LiczbaZadan);
        
        // wyswietlenie kolejnosci:
        cout << endl << "Wyliczona kolejnosc: ";
        for (unsigned int i = 0; i < LiczbaZadan; i++){
            //cout << TabZadan[i];
            cout << kolejnosc[i] << " ";
        }
        cout << endl << "Obliczanie Cmax: ";
        int cm = cmax(TabZadan,LiczbaZadan);
        cout << cm << endl;
        // zapis do pliku
        string fname = "out";
        fname.append(filename);
        fname.append(".txt");
        FILE *fp = fopen(fname.c_str(),"w");
        if (fp){
            fprintf(fp,"%d\n", cm);
            fclose(fp);
            cout << "Plik zostal zapisany.\n";
        }else {
            cout << "Nie moge otworzyc pliku " << filename << endl;
            return -1;
        }
        cout<<"###############################################\n\n";

        delete[] kolejnosc;
        delete[] TabZadan;
        iIndexZadan =0, index=0;
    }
    return 0;
}